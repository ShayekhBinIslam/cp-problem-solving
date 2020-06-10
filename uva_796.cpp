#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
#include <limits>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>
#include <sstream>
#include <numeric>

namespace cp {
    int n = 0;
    std::vector<std::vector<int> > g;
    std::vector<int> dfs_low, dfs_num, dfs_parent;
    std::vector<std::pair<int, int>> articulation_bridge;
    int dfs_number_counter, root_children, dfs_root;
    const int NIL = -1;
    const int UNIVISITED = -1;
    int answer = 0;


    void init() {
        g.assign(n, std::vector<int>());
        dfs_low.assign(n, 0);
        articulation_bridge = std::vector<std::pair<int, int>>();
        dfs_num.assign(n, UNIVISITED);
        dfs_parent.assign(n, NIL);
        dfs_number_counter = 0;

    }

    void add_edge(int u, int v, bool directed=false) {
        // std::cout << "add edge: " << u << "->" << v << '\n';
        g[u].emplace_back(v);
        if (!directed) {
            g[v].emplace_back(u);
        }
    }

    void print_graph(int offset=0) {
        std::cout << "Nodes: " << n << '\n';
        int i = 0;
        for (std::vector<int> u: g) {
            std::cout << (i++ + offset) ;
            for (int v: u) {
                std::cout << " " << (v+offset);
            }
            std::cout << '\n';
        }
    }
    
    void take_input() {
        int u = -1, v, m = -1;
        // std::cout << "N: " << n << '\n';
        char c;
        std::string line;
        getline(std::cin, line);
        if (n == 0) {
            return;
        }
        while (getline(std::cin, line)) {
            if (line[0] == '\0') {
                break;
            }
            // std::cout << "line: " << line << '\n';
            std::stringstream iss(line);
            iss >> u >> c >> m >> c;
            while (iss >> v) {
                // std::cout << " " << v;
                add_edge(u, v, true);
            }
            // std::cout << "\n";
        }
        // print_graph();
    }

    void articulation(int u) {
        dfs_low[u] = dfs_num[u] = dfs_number_counter++;
        for (int v: g[u]) {
            if (dfs_num[v] == UNIVISITED) {
                dfs_parent[v] = u;
                articulation(v);
                if (dfs_low[v] > dfs_num[u]) {
                    articulation_bridge.push_back(
                        {std::min(u, v), std::max(u,v)});
                }
                dfs_low[u] = std::min(dfs_low[u], dfs_low[v]);
            }
            else if (v != dfs_parent[u]) {
                dfs_low[u] = std::min(dfs_low[u], dfs_num[v]);
            }
        }
    }

    void solve() {
        for (int i = 0; i < n; ++i) {
            if (dfs_num[i] == UNIVISITED) {
                articulation(i);
            }
        }
        std::sort(
            articulation_bridge.begin(),
            articulation_bridge.end());
    }
    
    void print_output() {
        std::cout << articulation_bridge.size() << " critical links\n";
        for (auto& e: articulation_bridge) {
            std::cout << e.first;
            std::cout << " - ";
            std::cout << e.second << '\n';
        }
        std::cout << '\n';
    }


    void one_loop() {
        init();
        take_input();
        solve();
        print_output();
    }
    
    void run() {
        // int T = 1; 
        // std::cin >> T;
        while ( std::cin >> n ) {
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
g++ uva_796.cpp && ./a < test_cases/uva_796_1_in.txt

Test Case: 1
Input:


Output:


*/