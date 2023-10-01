#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include <time.h>
#include <vector>


class Timber
{
private:
    double x1;
    double y1;
    double x2;
    double y2;
    double r;
public:
    Timber(double size_x, double size_y);
    Timber(double x01, double y01,
        double x02, double y02,
        double r0) : x1(x01), y1(y01),
        x2(x02), y2(y02), r(r0) {}

    double get_x1() const { return x1; }
    double get_y1() const { return y1; }
    double get_x2() const { return x2; }
    double get_y2() const { return y2; }
    double get_r() const { return r; }
    double dist(double x0, double y0) const;
};

class Hill
{
private:
    double x; // координаты
    double y; // неровности
    double sigma; // средне квадратичное отклонение
    double hight; // "высота" холма
public:
    Hill(double size_x, double size_y);
    Hill(double x0, double y0,
        double sigma0, double hight0) :
        x(x0), y(y0), hight(hight0)
    {
        sigma = abs(sigma0);
    }

    // Нормальное распределение в точке относительно холма
    double Gauss(double x0, double y0) const;
};

class Stone
{
private:
    double x;
    double y;
    double r;
public:
    Stone(double size_x, double size_y);
    Stone(double x0, double y0,
        double r0) : x(x0), y(y0), r(r0) {}

    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_r() const { return r; }
    double dist(double x0, double y0) const;
};

// Бездорожье
class Offroad
{
private:
    double size_x; // размеры 
    double size_y; // поверхности
    std::vector<Hill> hills; // вектор холмов
    std::vector<Stone> Stones;
    std::vector<Timber> Timbers;
    int count_hills; // количество холмов
    int count_Stones;
    int count_Timbers;
public:
    Offroad() = default;
    Offroad(double x, double y, int count_hills = 0,
        int count_Stones = 0, int count_Timbers = 0);

    // Вывод поверхности в файл для GNUplot
    void print(std::ofstream& file, std::ofstream& File,
        std::ofstream& FILE) const;
};

// Двумерная функция Гаусса о нормальном распределении
double f(double x, double y, Hill H);

// Задача про бездорожье
// Nazarov Zahar - 212 group
int main()
{
    srand(time(NULL));
    Offroad Swamp(25, 25, 25, 10, 5);
    std::ofstream file("hills.txt");
    std::ofstream File("Stones.txt");
    std::ofstream FILE("Timbers.txt");
    Swamp.print(file, File, FILE);
    file.close();
    File.close();
    FILE.close();
    return 0;
}

Hill::Hill(double size_x, double size_y)
{
    x = random() / double(RAND_MAX) * size_x - size_x / 2;
    y = random() / double(RAND_MAX) * size_y - size_y / 2;
    sigma = random() / double(RAND_MAX) * 1.9 + 0.1;
    hight = random() / double(RAND_MAX) * 10 - 5;
}

Stone::Stone(double size_x, double size_y)
{
    x = random() / double(RAND_MAX) * size_x - size_x / 2;
    y = random() / double(RAND_MAX) * size_y - size_y / 2;
    r = random() / double(RAND_MAX) * 1 + 0.5;
}

Timber::Timber(double size_x, double size_y)
{
    x1 = random() / double(RAND_MAX) * size_x - size_x / 2;
    y1 = random() / double(RAND_MAX) * size_y - size_y / 2;
    r = random() / double(RAND_MAX) * 1 + 0.5;
    double lenght = (random() / double(RAND_MAX) * 3 + 1) * r;
    double direction = random() / double(RAND_MAX) * 2;
    x2 = x1 + lenght * cos(direction * M_PI);
    y2 = y1 + lenght * sin(direction * M_PI);
}

Offroad::Offroad(double x, double y, int count_hills,
    int count_Stones, int count_Timbers) :
    size_x(x), size_y(y), count_hills(count_hills),
    count_Stones(count_Stones), count_Timbers(count_Timbers)
{
    for (int i = 0; i < count_hills; i++)
    {
        hills.push_back(Hill(x, y));
    }
    for (int i = 0; i < count_Stones; i++)
    {
        Stones.push_back(Stone(x, y));
    }
    for (int i = 0; i < count_Timbers; i++)
    {
        Timbers.push_back(Timber(x, y));
    }
}


double Hill::Gauss(double x0, double y0) const
{
    double e = exp(-((x - x0) * (x - x0) + (y - y0) * (y - y0)) / 2 * sigma * sigma);
    return (hight * e) / (sigma * sqrt(2 * M_PI));
}

void Offroad::print(std::ofstream& file, std::ofstream& File,
    std::ofstream& FILE) const
{
    double z;
    for (double i = -size_x / 2; i <= size_x / 2; i += size_x / 40)
    {
        for (double j = -size_y / 2; j <= size_y / 2; j += size_y / 40)
        {
            z = 0;
            for (int k = 0; k < count_hills; k++)
            {
                z += hills[k].Gauss(i, j);
            }
            file << i << " " << j << " " << z << "\n";
        }
        file << "\n";
    }


    for (int k = 0; k < count_Stones; k++)
    {
        z = 0;
        for (int m = 0; m < count_hills; m++)
        {
            z += hills[m].Gauss(Stones[k].get_x(), Stones[k].get_y());
        }
        for (double i = Stones[k].get_r(); i > 0; i -= Stones[k].get_r() / 5)
        {
            for (double j = 0; j <= 2.1; j += 0.1)
            {
                File << Stones[k].get_x() + i * cos(j * M_PI) <<
                    " " << Stones[k].get_y() + i * sin(j * M_PI) <<
                    " " << sqrt(Stones[k].get_r() * Stones[k].get_r() - i * i) + z << "\n";
            }
            File << "\n";
        }
        File << "\n";
    }
    double z1, z2, a, b, l;
    for (int k = 0; k < count_Timbers; k++)
    {
        z1 = 0;
        z2 = 0;
        for (int m = 0; m < count_hills; m++)
        {
            z1 += hills[m].Gauss(Timbers[k].get_x1(), Timbers[k].get_y1());
            z2 += hills[m].Gauss(Timbers[k].get_x2(), Timbers[k].get_y2());
        }
        a = Timbers[k].get_y1() - Timbers[k].get_y2();
        b = Timbers[k].get_x2() - Timbers[k].get_x1();
        l = sqrt(a * a + b * b);
        for (double i = -Timbers[k].get_r(); i <= Timbers[k].get_r(); i += Timbers[k].get_r() / 10)
        {
            for (double d = 0; d <= 1; d += 0.25) {
                FILE << Timbers[k].get_x1() + a * i / l <<
                    " " << Timbers[k].get_y1() + b * i / l <<
                    " " << (sqrt(Timbers[k].get_r() * Timbers[k].get_r() - i * i) + z1) * d << "\n";
            }
            for (double j = 0; j <= 1; j += 0.05)
            {
                FILE << Timbers[k].get_x1() + a * i / l + b * j <<
                    " " << Timbers[k].get_y1() + b * i / l - a * j <<
                    " " << sqrt(Timbers[k].get_r() * Timbers[k].get_r() - i * i) + (z2 - z1) * j << "\n";
            }
            for (double d = 1; d >= 0; d -= 0.25) {
                FILE << Timbers[k].get_x2() + a * i / l <<
                    " " << Timbers[k].get_y2() + b * i / l <<
                    " " << (sqrt(Timbers[k].get_r() * Timbers[k].get_r() - i * i) + z2) * d << "\n";
            }
            FILE << "\n";
        }
        FILE << "\n";
    }
}
