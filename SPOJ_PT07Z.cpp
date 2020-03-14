#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <functional>
#include <algorithm>

typedef long long int64;

namespace cp {
    int n;
    const int INF_INT = 1'000'000'000;
    std::vector<std::vector<int> > g;
    std::vector<bool> visited;
    std::vector<int> dist;

    void bfs(int src) {
        visited.assign(n, false);
        dist.assign(n, INF_INT);
        std::queue<int> q;
        visited[src] = true;
        dist[src] = 0;
        q.push(src);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto& v: g[u]) {
                if (visited[v] == false) {
                    dist[v] = dist[u] + 1;
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    void take_input() {
        std::cin >> n;
        g.assign(n, std::vector<int>());
        for (int i = 0; i < n-1; ++i) {
            int u, v;
            std::cin >> u >> v;
            --u;
            --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

    }

    int find_max() {
        return std::distance(dist.begin(), 
            std::max_element(dist.begin(), dist.end()));
    }

    void run() {
        take_input();
        bfs(0);
        bfs(find_max());

        std::cout << dist[find_max()];

    }
    
}



int main() {
    cp::run();


    return 0;
}