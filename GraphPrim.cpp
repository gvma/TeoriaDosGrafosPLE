#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

class GraphPrim {
public:
    vector<bool> visited;
    vector<vector<pair<int,int>>> adjList;
    vector<vector<pair<int,int>>> mst;

    GraphPrim() {
        long long int numberOfVertexes, numberOfEdges;
        cin >> numberOfVertexes >> numberOfEdges;
        vector<bool> visited;
        visited.resize(numberOfVertexes + 1);
        vector<vector<pair<int, int>>> adjList;
        adjList.resize(numberOfVertexes + 1);
        vector<vector<pair<int, int>>> mst;
        mst.resize(numberOfVertexes + 1);
        this->adjList = move(adjList);
        this->visited = move(visited);
        this->mst = move(mst);
        for (int j = 1; j <= numberOfEdges; j++)
        {
            long long int v1, v2, w;
            cin >> v1 >> v2 >> w;
            this->adjList[v1].push_back(make_pair(v2,w));
            this->adjList[v2].push_back(make_pair(v1,w));
        }
    }

    long long int prim(int source, bool minimumSpanningTree) {
        this->visited[source] = true;
        priority_queue<pair<int,pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int,int>>>> priorityQueue;
        pair<int, pair<int, int>> front;
        pair<int, int> v;
        long long int cost = 0;
        for (int j = 0; j < (int)this->adjList[source].size(); ++j) {
            v = this->adjList[source][j];
            pair<int, pair<int, int>> p = minimumSpanningTree ? make_pair(v.second, make_pair(v.first, source)) : make_pair(-v.second, make_pair(-v.first, source));
            priorityQueue.push(p);
        }
        while (!priorityQueue.empty()) {
            front = priorityQueue.top();
            int u = minimumSpanningTree ? front.second.first : -front.second.first;
            int w = minimumSpanningTree ? front.first : -front.first;
            int previous = priorityQueue.top().second.second;
            priorityQueue.pop();
            if (!this->visited[u]) {
                cost += (long long int)w;
                visited[u] = true;
                mst[u].push_back(make_pair(previous, w));
                mst[previous].push_back(make_pair(u, w));
                for (int j = 0; j < (int)this->adjList[u].size(); ++j) {
                    v = adjList[u][j];
                    if (!visited[v.first]) {
                        pair<int, pair<int, int>> p = minimumSpanningTree ? make_pair(v.second, make_pair(v.first, u)) : make_pair(-v.second, make_pair(-v.first, u));
                        priorityQueue.push(p);
                    }
                }
            }
        }
        printMST();
        return cost;
    }

    void printMST() {
        int i = 0;
        for (const auto& x : this->mst) {
            cout << "Lista do " << i++ << endl;
            for (auto y : x) {
                cout << "(" << y.first << ", " << y.second << ") ";
            }
            cout << endl;
        }
    }
};

int main()
{
    GraphPrim prim;
    cout << prim.prim(1, true) << endl;
    return 0;
}
