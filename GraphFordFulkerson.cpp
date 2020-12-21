#include <iostream>
#include <cstring>
#include <queue>
#include <limits.h>

using namespace std;

const int MAXN = 1e3;

class GraphFordFulkerson {
public:
    int residualGraph[MAXN][MAXN]{};
    int numberOfVertexes{};
    int numberOfEdges{};
    int source{}, destination{};

    GraphFordFulkerson() {
        cin >> numberOfVertexes >> numberOfEdges;
        for (auto & i : residualGraph) {
            for (int & j : i) {
                j = 0;
            }
        }
        for (int i = 0; i < numberOfEdges; ++i) {
            int u, v, cost;
            cin >> u >> v >> cost;
            residualGraph[u][v] += cost;
        }
        cin >> source >> destination;
    }

    void printGraph() {
        cout << endl;
        for (int i = 0; i < numberOfVertexes; ++i) {
            for (int j = 0; j < numberOfVertexes; ++j) {
                cout << residualGraph[i][j] << ", ";
            }
            cout << endl;
        }
    }

    bool bfs(int parent[]) {
        bool visited[numberOfVertexes];
        memset(visited, 0, sizeof(visited));

        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < numberOfVertexes; v++) {
                if (!visited[v] && residualGraph[u][v] > 0) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        return visited[destination];
    }

    int fordFulkerson() {
        int u, v;
        int parent[numberOfVertexes];
        int maxFlow = 0;

        while(bfs(parent)) {
            int pathFlow = INT_MAX;
            for (v = destination; v != source; v = parent[v]) {
                u = parent[v];
                pathFlow = min(pathFlow, residualGraph[u][v]);
            }
            for (v = destination; v != source; v = parent[v]) {
                u = parent[v];
                residualGraph[u][v] -= pathFlow;
                residualGraph[v][u] += pathFlow;
            }
            maxFlow += pathFlow;
        }
        return maxFlow;
    }
};

int main() {
    GraphFordFulkerson graphFordFulkerson;
    cout << "Max flow = " << graphFordFulkerson.fordFulkerson() << endl;
}