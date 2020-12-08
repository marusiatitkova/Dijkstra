#include <iostream>
#include <vector>
#include <ctime>

const int INF = INT_MAX;
int n, m;
std::vector< std::vector< std::pair<int, int> > > graph; // graph --- pair (toVertex, weight)
std::vector<int> distance; // vector of path lengths
std::vector<bool> used; // visited and unvisited nodes
time_t start, finish;
double duration;

void processInitializationGraph(int start) {
    freopen("out100000.txt", "r", stdin);
    std::cin >> n; // nodes count
    std::cin >> m; // edges count

    graph.resize(n);
    distance.resize(n, INF);
    used.resize(n, false);

    for (int i = 0; i < m; i++) {
        int from, to, w;
        std::cin >> from >> to >> w;
        graph[from].push_back(std::make_pair(to, w));
        graph[to].push_back(std::make_pair(from, w));
    }

    distance[start] = 0;
}

int minDistance(std::vector<int> dist, std::vector<bool> used)
{
    // Initialize min value
    int min = INF, min_index;

    for (int v = 0; v < dist.size(); v++)
        if (!used[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

int main()
{
    int s = 0; //start vertex
    start = clock();
    processInitializationGraph(s);

    for (int i = 0; i < n; i++) {
        int c = minDistance(distance, used);
        used[c] = true;
        if (distance[c] == INF)
            break;

        for (int j = 0; j < graph[c].size(); j++){
            int to = graph[c][j].first;
            int len = graph[c][j].second;
            if (!used[to] && distance[c] + len < distance[to] ) {
                distance[to] = distance[c] + len;
            }
        }
    }
    finish = clock();
    duration = (finish-start)/double(CLOCKS_PER_SEC);
    // print shortest distances
//    for (int l = 0; l < n; l++) {
//        std::cout << "To vertex " << l << " shortest distance is " << distance[l] << "\n";
//    }
    std::cout << "duration = " << duration;

    return 0;
}
