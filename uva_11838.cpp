#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
#include <limits>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>

namespace cp {
    const int UNVISITED = -1;
    int n, m;

    std::vector<std::vector<int> > g;
    std::vector<int> dfs_low, dfs_num;
    std::vector<bool> visited;
    std::stack<int> s;

    int dfs_number_counter, scc_counter;
    int answer = 0;

    void init() {
        g.assign(n, std::vector<int>());
        dfs_low.assign(n, 0);
        visited.assign(n, false);
        dfs_num.assign(n, UNVISITED);
        dfs_number_counter = 0;
        s = std::stack<int>();
        scc_counter = 0;
    }

    void add_edge(int u, int v, bool directed=false) {
        // std::cout << "add edge: " << u << "->" << v << '\n';
        g[u].emplace_back(v);
        if (!directed) {
            g[v].emplace_back(u);
        }
    }
    
    void take_input() {
        for (int i = 0; i < m; ++i) {
            int u, v, p; 
            std::cin >> u >> v >> p;
            add_edge(--u, --v, p == 1);
        }
    }

    void scc_tarjan(int u) {
        dfs_num[u] = dfs_low[u] = dfs_number_counter++;
        s.emplace(u); 
        visited[u] = true;

        for (int v: g[u]) {
            if (dfs_num[v] == UNVISITED) 
                scc_tarjan(v);
            if (visited[v]) 
                dfs_low[u] = std::min(dfs_low[u], dfs_low[v]);
        }

        if (dfs_num[u] == dfs_low[u]) {
            int v;
            while (true) {
                v = s.top();
                s.pop();
                visited[v] = false;
                if (u == v) break;
            }
            ++scc_counter;
        }
}

    void solve() {
        for (int i = 0; i < n; ++i) {
            if (dfs_num[i] == UNVISITED)
                scc_tarjan(i);
        }
        answer = int(scc_counter == 1);
    }
    
    void print_output() {
        std::cout << answer << "\n";
    }


    void one_loop() {
        init();
        take_input();
        solve();
        print_output();
    }
    
    void run() {
        int T = 1; 
        // std::cin >> T;
        for ( ; ; ) {
            // std::cout << "Case " << (i+1) << ":\n";
            std::cin >> n >> m;
            if (n == 0 && m == 0) break;
            one_loop();
        }
    }
}

int main() {
    cp::run();

    return 0;
}


/*
Run: 
g++ uva_11838.cpp && a < test_cases/uva_11838_1_in.txt

Test Case: 1
Input:


Output:


*/