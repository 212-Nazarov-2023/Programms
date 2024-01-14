#include "Processor.h"
//212 - Nazarov - Zakhar

My_processor::My_processor(int A1, int A2, int B1, int B2, Rover& Tracker)
    : A1{ A1 }, A2{ A2 }, B1{ B1 }, B2{ B2 }, Tracker{ Tracker } {
}

My_processor::My_processor() : A1{ 0 }, A2{ 0 }, B1{ 0 }, B2{ 0 } {
}

void My_processor::route() {
	ofstream stream("route.txt");
    int i; 
    int j; 
    int k; 
    int l; 
    int m;
    int n = 128 * 128;
    int s = A1 * 127 + A2;
    int t = B1 * 127 + B2;
    int size = 128;
    vector<vector<int>> adj(n);
    vector<int> dist(n, n);
    vector<int> p(n, -1);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            for (k = i - 1; k < i + 2; k++) {
                for (l = j - 1; l < j + 2; l++) {
                    if (k > 0 && k < size && l > 0 && l < size && !(k == i && l == j)) {
                        if (Tracker.sensor(i, j, k, l) && Tracker.angles(i, j, k, l)) {
                            m = 127 * i + j;
                            adj[m].push_back(127 * k + l);
                        }
                    }
                }
            }
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (dist[u] > dist[v] + 1) {
                p[u] = v;
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    if (dist[t] == n) {
        cout << " Rover can't get from A to B" << endl;
    }
    vector<int> path;
    while (t != -1) {
        path.push_back(t);
        t = p[t];
    }
    for (i = path.size() - 1; i > -1; i--) {
        k = path[i] / 127;
        l = path[i] % 127;
        stream << double(k * 10) / size << " " << double(l * 10) / size << " " << double(Tracker.Off_road.Pixel[k][l] * 10) / size << endl;
    }
}