#include <algorithm>
#include <fstream>
#include <iostream>
#pragma GCC optimize("Ofast")
int         tot = 0;
bool        htp[9][9], stp[9][9], ftp[3][3][9];
char        p[9][9];
struct pl {
    int  x, y;
    void init(int xx, int yy) { x = xx, y = yy; }
    int  count() {
         int res = 0;
         for (int i = 0; i < 9; i++) {
             if ('0' <= p[x][i] && p[x][i] <= '9') res++;
            if ('0' <= p[i][y] && p[i][y] <= '9') res++;
            if ('0' <= p[x / 3 * 3 + i % 3][y / 3 * 3 + i / 3] &&
                p[x / 3 * 3 + i % 3][y / 3 * 3 + i / 3] <= '9')
                res++;
        }
         return res;
    }
};
pl   q[81];
int  cnt = 0;
void q_sort() {
    for (int i = 0; i < cnt; i++) {
        for (int j = cnt - 1; j > i; j--) {
            if (q[j - 1].count() < q[j].count()) std::swap(q[j], q[j - 1]);
        }
        p[q[i].x][q[i].y] = '0';
    }
}
std::ifstream input("puz");
std::ofstream out("output2");
void          print() {
             printf("#Case %d\n", ++tot);
             for (int i = 0; i < 9; i++) {
                 if (i == 3 || i == 6)
            std::cout << "-------+-------+------" << std::endl;
        std::cout << ' ';
                 for (int j = 0; j < 9; j++) {
                     std::cout << p[i][j] << ' ';
                     out << p[i][j];
                     if (j == 2 || j == 5) std::cout << "| ";
        }
                 std::cout << std::endl;
                 out << std::endl;
    }
             std::cout << std::endl;
}
bool ok(int x, int y, int num) {
    if (htp[x][num]) return 0;
    if (stp[y][num]) return 0;
    int u = x / 3, v = y / 3;
    if (ftp[u][v][num]) return 0;
    htp[x][num] = stp[y][num] = ftp[u][v][num] = 1;
    return 1;
}
void hs(int x, int y, int num) {
    htp[x][num] = stp[y][num] = ftp[x / 3][y / 3][num] = 0;
}
void dfs(int st) {
    //	std::cout<<x<<"&"<<y<<std::endl;print();
    if (st == cnt) {
        print();
        return;
    }
    int x = q[st].x, y = q[st].y;
    for (int i = '1'; i <= '9'; i++) {
        p[x][y] = i;
        if (ok(x, y, i - '0')) {
            dfs(st + 1);
            hs(x, y, i - '0');
        }
    }
}
int main() {

    for (int i = 0; i < 9; i++)
        input >> p[i];
    int t1 = clock();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (p[i][j] >= '1' && p[i][j] <= '9')
                htp[i][p[i][j] - '0']                = stp[j][p[i][j] - '0'] =
                    ftp[i / 3][j / 3][p[i][j] - '0'] = 1;
            else {
                q[cnt++].init(i, j);
            }
        }
    }
    q_sort();

    std::cout << "--- START PROSESSING ---" << std::endl;
    dfs(0);

    if (tot)
        printf("Only %d cases in total.\n", tot);
    else
        std::cout << "No solution." << std::endl;
    out.close();
    input.close();
    printf("\nAnd it took %.2fs only.\n",
           (clock() - t1) * 1.0 / CLOCKS_PER_SEC);
}
/*
*1*******
**3******
6**9*8251
**7*4***9
*5*****3*
4***2*6**
8295*1**4
******8**
*******7*
*/
