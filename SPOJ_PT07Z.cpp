#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <functional>
#include <algorithm>
#include <limits>
#include <bitset>


typedef long long int64;

namespace cp_utils {
    template<class T>
    int argmax(const std::vector<T>& vec) {
        return std::distance(vec.begin(), 
            std::max_element(vec.begin(), vec.end()));
    }
}

namespace cp {
    using cp_utitls::argmax;
    const int INF_INT = std::numeric_limits<int>::max()/4; // C++14
    const int MAX_NODES = 10'000 + 100;
    int n;
    std::vector<std::vector<int> > g;
    // std::vector<bool> visited;
    std::bitset<MAX_NODES>visited;
    std::vector<int> dist;
    
    void add_edge(int u, int v, bool directed=false) {
        g[u].emplace_back(v);
        if (!directed) {
            g[v].emplace_back(u);
        }
    }

    void bfs(int src) {
        visited.reset(); // visited.assign(n, false);
        dist.assign(n, INF_INT);
        std::queue<int> q;
        visited.set(src); // visited[src] = true;
        dist[src] = 0;
        q.push(src);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const auto& v: g[u]) {
                // if (visited[v] == false) {
                if (visited.test(v) == false) { 
                    dist[v] = dist[u] + 1;
                    // visited[v] = true;
                    visited.set(v);
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
            add_edge(u, v);
        }
    }
    
    void run() {
        take_input();
        bfs(0);
        bfs(argmax(dist));
        std::cout << dist[argmax(dist)];
    }
}

int main() {
    cp::run();

    return 0;
}


/*
Test Case: 1
Input:
3
1 2
2 3

Output:
2

*/
