#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
#include <limits>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>


namespace cp_utils {
    template<class T>
    int argmax(const std::vector<T>& v) {
        return std::distance(v.begin(), 
            std::max_element(v.begin(), v.end()));
    }
}

namespace cp {
    using cp_utils::argmax;
    const int INF_INT = std::numeric_limits<int>::max() / 4;
    const int MAX_NODES = 10'000 + 100; // C++14: 10'000
    typedef int VERTEX_T;
    int n;
    std::vector<std::vector<VERTEX_T> > g; // std::vector<bool> visited;
    std::bitset<MAX_NODES> visited;
    std::vector<int> dist;
    std::queue<VERTEX_T> q;
    
    void add_edge(VERTEX_T u, VERTEX_T v, bool directed=false) {
        g[u].emplace_back(v);
        if (!directed) {
            g[v].emplace_back(u);
        }
    }
    
    void mark_n_push(const VERTEX_T vertex) {
        visited.set(vertex); // visited[vertex] = true;
        q.emplace(vertex);
    }
    
    void bfs_ds_init() {
        visited.reset(); // visited.assign(n, false);
        dist.assign(n, INF_INT);
        q = std::queue<VERTEX_T>();
    }

    void bfs(const VERTEX_T src) {
        bfs_ds_init();
        dist[src] = 0;
        mark_n_push(src);
        
        while (!q.empty()) {
            VERTEX_T u = q.front();
            q.pop();

            for (const VERTEX_T& v: g[u]) {
                // if (!visited[v]) {
                if (!visited.test(v)) { 
                    dist[v] = dist[u] + 1;
                    mark_n_push(v);
                }
            }
        }
    }

    void take_input() {
        std::cin >> n;
        g.assign(n, std::vector<VERTEX_T>());
        for (int i = 0; i < n-1; ++i) {
            VERTEX_T u, v;
            std::cin >> u >> v;
            add_edge(--u, --v);
        }
    }
    
    void print_output() {
        std::cout << *std::max_element(dist.begin(), dist.end());
        std::cout << '\n'; // Standard pratice, ending with a blank line.
    }
    
    void run() {
        take_input();
        bfs(0);
        bfs(argmax(dist));
        print_output();
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
