#include <iostream>
#include <cstring>
#include <queue>
#include <limits.h>

using namespace std;

const int MAXN = 1e3;

class GraphFloydWarshall {
public:
    int distances[MAXN][MAXN]{};
    int numberOfVertex{};
    int numberOfEdges{};

    GraphFloydWarshall() {
        cin >> numberOfVertex >> numberOfEdges;
        for (int i = 0; i < numberOfVertex; i++) {
            for (int j = 0; j < numberOfVertex; j++) {
                distances[i][j] = 1e8;
            }
            distances[i][i] = 0;
        }
        for (int i = 0; i < numberOfEdges; i++) {
            int v1, v2, w;
            cin >> v1 >> v2 >> w;
            distances[v1][v2] = w;
        }
    }

    void floydWarshall() {
        for (int x = 0; x < numberOfVertex; x++) {
            for (int i = 0; i < numberOfVertex; i++) {
                for (int j = 0; j < numberOfVertex; j++ ){
                    distances[i][j] = min(distances[i][j], distances[i][x] + distances[x][j]);
                }
            }
        }
        for (int i = 0; i < numberOfVertex; ++i) {
            cout << "Vertice " << i << ": ";
            for (int j = 0; j < numberOfVertex; ++j) {
                cout << distances[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    GraphFloydWarshall graphFloydWarshall;
    graphFloydWarshall.floydWarshall();
    return 0;
}