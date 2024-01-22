#include <chrono>
#include <fstream>
#include <iostream>
#pragma GCC optimize("Ofast")

int s[500000] = {1};

int main() {
    auto          start_time = std::chrono::high_resolution_clock::now();
    std::ofstream outfile("out.txt");
    int           l = 1;
    for (int i = 2; i <= 50000; i++) {
        for (int j = 0; j < l; j++) {
            s[j] *= i;
        }
        for (int j = 0; j < l; j++) {
            if (s[j] >= 10) {
                s[j + 1] += s[j] / 10;
                s[j] %= 10;
                if (j == l - 1) l++;
            }
        }
    }
    for (int j = l - 1; j >= 0; j--) {
        outfile << s[j];
    }
    outfile.close();
    std::cout
        << (std::chrono::high_resolution_clock::now() - start_time).count() /
               1e9
        << std::endl;
    system("diff -q out.txt ans.txt");
}