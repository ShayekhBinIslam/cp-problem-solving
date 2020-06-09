#include <iostream>
#include <sstream>
#include <utility>
#include <functional>
#include <algorithm>
#include <limits>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>

namespace cp {
    int n = 0;
    bool end_of_input = false;
    std::vector<std::vector<int> > g;
    std::vector<int> dfs_low, dfs_num, dfs_parent;
    std::vector<bool> articulation_vertex;
    int dfs_number_counter, root_children, dfs_root;
    const int NIL = -1;
    const int UNIVISITED = -1;
    int answer = 0;


    void init() {
        g.assign(n, std::vector<int>());
        dfs_low.assign(n, 0);
        articulation_vertex.assign(n, false);
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
        int u, v;
        std::string line;
        while (getline(std::cin, line)) {
            // std::cout << "line: " << line << '\n';
            if (line[0] == '0') {
                break;
            }
            std::istringstream iss(line);
            iss >> u;
            // std::cout << u << " ";
            --u;
            while (iss >> v) {
                // std::cout << " " << v;
                add_edge(u, --v);
            }
            // std::cout << "\n";
        }
        // print_graph(1);
    }

    void articulation(int u) {
        dfs_low[u] = dfs_num[u] = dfs_number_counter++;
        for (int v: g[u]) {
            if (dfs_num[v] == UNIVISITED) {
                dfs_parent[v] = u;
                if (u == dfs_root) {
                    ++root_children;
                }
                articulation(v);

                if (dfs_low[v] >= dfs_num[u]) {
                    articulation_vertex[u] = true;
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
                dfs_root = i;
                root_children = 0;
                articulation(i);
                articulation_vertex[dfs_root] = (root_children > 1);
            }
        }
        answer = std::accumulate(
            articulation_vertex.begin(),
            articulation_vertex.end(), 0);
    }
    
    void print_output() {
        std::cout << answer << '\n';

    }


    void one_loop() {
        init();
        take_input();
        solve();
        print_output();
    }
    
    void run() {
        for ( ; ; ) {
            // std::cout << "Case " << (i+1) << ":\n";
            std::cin >> n;
            if (!n) break;
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
g++ uva_315.cpp && a < test_cases/uva_315_1_in.txt

Test Case: 1
Input:


Output:


*/