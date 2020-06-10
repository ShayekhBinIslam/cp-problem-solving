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
    std::vector<std::vector<int> > SCCs;

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
        SCCs = std::vector<std::vector<int> >();
    }

    void add_edge(int u, int v, bool directed=false) {
        // std::cout << "add edge: " << u << "->" << v << '\n';
        g[u].emplace_back(v);
        if (!directed) {
            g[v].emplace_back(u);
        }
    }

    void take_input() {
        int u, v;
        for (int i = 0; i < m; ++i) {
            std::cin >> u >> v;
            // std::cout << u << " " << v << '\n';
            add_edge(--u, --v, true);
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
            std::vector<int> current_ssc;
            while (true) {
                v = s.top();
                s.pop();
                visited[v] = false;
                current_ssc.push_back(v);
                if (u == v) break;
            }
            ++scc_counter;
            SCCs.push_back(current_ssc);
        }
    }

    void vanilla_dfs(int src) {
        visited[src] = true;
        for (auto& v: g[src]) {
            if (!visited[v])
                vanilla_dfs(v);
        }
    }

    void solve() {
        for (int i = 0; i < n; ++i) {
            if (dfs_num[i] == UNVISITED)
                scc_tarjan(i);
        }
        answer = 0;

        for (auto it = SCCs.rbegin(); it != SCCs.rend(); ++it) {
            auto& v = *it;
            for (auto& k: v) {
                // std::cout << k+1 << " ";
                if (!visited[k]) {
                    vanilla_dfs(k);
                    ++answer;
                }   
            }
            // std::cout << '\n';
        }
    }

    void print_output() {
        std::cout << answer << "\n";
    }

    void one_loop() {
        std::cin >> n >> m;
        init();
        take_input();
        solve();
        print_output();
    }
    
    void run() {
        int T = 1; 
        std::cin >> T;
        for (int i = 0; i < T; ++i) {
            // std::cout << "Case " << (i+1) << ":\n";
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
g++ uva_11504.cpp && ./a < test_cases/uva_11504_1_in.txt

Test Case: 1
Input:


Output:


*/