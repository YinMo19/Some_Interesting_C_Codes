#include <bits/types/clock_t.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
// #pragma GCC                optimize("Ofast")
const unsigned int         MXD = 4294967295;
const unsigned long long   MXP = 4294967296;
typedef unsigned long long ull;

// debug the struct blow
struct BN {
    std::vector<unsigned int> c;
    int                       len;
    void                      init(ull x) {
                             c.clear();
                             while (x) {
                                 c.push_back(x & MXD);
                                 x >>= 32;
        }
                             len = c.size();
    }
    bool friend operator<(BN a, BN b) {
        if (a.len != b.len) return a.len > b.len;
        for (int i = a.len - 1; i >= 0; i--) {
            if (a.c[i] != b.c[i]) return a.c[i] > b.c[i];
        }
        return 0;
    }
    void add(int x, ull y) {
        while (y) {
            if (len <= x) {
                for (int i = x - len; i >= 0; i--) {
                    c.push_back(0);
                }
                len = x + 1;
            }
            ull z = y + c[x];
            y     = z >> 32;
            c[x]  = z & MXD;
            x++;
        }
    }
    BN friend operator*(const BN &a, const BN &b) {
        BN res;
        res.init(0);
        for (int i = 0; i < a.len; i++) {
            for (int j = 0; j < b.len; j++) {
                // std::cout << ull(a.c[i]) * b.c[j] << "^^" << i + j <<
                // std::endl;
                res.add(i + j, ull(a.c[i]) * b.c[j]);
            }
        }
        return res;
    }
    void print() {
        ull x = 0;
        for (int i = len - 1; i >= 0; i--) {
            //   std::cout <<c[i]<< "*\n";
            x = (x * MXP) + c[i];
        }
        std::cout << x << std::endl;
    }
};

std::priority_queue<BN> list;

int main() {
    int n = 20000;
    // scanf("%d",&n);
    clock_t       t1 = clock();
    std::ofstream out("out.txt");
    BN            x, y;
    x.init(1);
    for (int i = 2; i <= n; i++) {
        x.init(i);
        list.push(x);
    }
    while (list.size() > 1) {
        x = list.top();
        list.pop();
        y = list.top();
        list.pop();
        list.push(x * y);
    }
    x = list.top();

    //   for (int i = 2; i <= n; i++) {
    //     y.init(i);
    //     x = x * y;
    //   }

    for (int i = x.len - 1; i >= 0; i--) {
        out << '%' << x.c[i];
    }
    out.close();
    std::cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << std::endl;

    // std::string com = "python check.py " + std::to_string(n);
    // system(com.c_str());
 
    return 0;
}