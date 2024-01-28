#include <bits/types/clock_t.h>
#include <fstream>
#include <iostream>

int main() {
  clock_t t1 = clock();
  system("./Ke/dfs_byKe > blank --wait");
  clock_t t2 = clock();
  system("./sudoku2 > blank --wait");
  clock_t t3 = clock();
  std::cout << (t3 - t2) * 1.0 / CLOCKS_PER_SEC << 's' << std::endl;
  std::cout << (t2 - t1) * 1.0 / CLOCKS_PER_SEC << 's' << std::endl;
}