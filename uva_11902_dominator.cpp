#include <iostream>
#include <bitset>

namespace cp {
    const int MAX_NODES = 100;
    int AdjMat[MAX_NODES][MAX_NODES];
    int n = 0;
    std::bitset<MAX_NODES> visited_init;
    std::bitset<MAX_NODES> visited_later;
    
    void take_input() {
        std::cin >> n;
        // std::cout << n << '\n';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> AdjMat[i][j];
                // std::cout << AdjMat[i][j] << " ";
            }
            // std::cout << '\n';
        }
    }
    void dfs_ds_init(std::bitset<MAX_NODES>& visited) {
        visited.reset();
    }

    void dfs(int src, std::bitset<MAX_NODES>& visited, int dest=-1) {
        if (src == dest) {
                return;
        }
        visited.set(src);
        
        for (int i = 0; i < n; ++i) {
            if (AdjMat[src][i] && !visited.test(i)) {
                dfs(i, visited, dest);
            }
        }

    }
    
    void print_output() {

    }

    void print_table_line() {
        std::cout << '+';
        for (int i = 0; i < 2*n - 1; ++i)
            std::cout << '-';
        std::cout << "+\n";
    }

    inline bool is_dominating(int i, int j) {
        return visited_init.test(j) && !visited_later.test(j);
    }

    void solve() {
        dfs_ds_init(visited_init);
        dfs(0, visited_init);
        print_table_line();
        
        for (int i = 0; i < n; ++i) {
            dfs_ds_init(visited_later);
            dfs(0, visited_later, i);
            std::cout << '|';
            for (int j = 0; j < n; ++j) {
                std::cout << (is_dominating(i, j) ? 'Y': 'N');
                std::cout << '|';
            }
            std::cout << '\n';
            print_table_line();
        }
    }

    void one_loop() {
        take_input();
        solve();
        print_output();
    }
    
    void run() {
        int T; 
        std::cin >> T;
        for (int i = 0; i < T; ++i) {
            std::cout << "Case " << (i+1) << ":\n";
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
g++ uva_11902_dominator.cpp && a < test_cases/uva_11902_dominator_1.txt

Test Cases:
Input:
2
5
0  1  1  0  0
0  0  0  1  0
0  0  0  1  0
0  0  0  0  1
0  0  0  0  0
1
1

Output:
Case 1:
+---------+
|Y|Y|Y|Y|Y|
+---------+
|N|Y|N|N|N|
+---------+
|N|N|Y|N|N|
+---------+
|N|N|N|Y|Y|
+---------+
|N|N|N|N|Y|
+---------+
Case 2:
+-+
|Y|
+-+

*/
