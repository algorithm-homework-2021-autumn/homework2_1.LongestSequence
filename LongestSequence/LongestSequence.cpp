// LongestSequence.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const int LCS_maxn = 4;
const int string_maxn = 100010;
const int LIS_maxn = 2;
inline int mymax(int x, int y) { return x > y ? x : y; }
void get_LCS_data(char **a) {
    std::ifstream LCSData;
    LCSData.open("LCS_Data.txt");
    std::string b;
    for (int i = 0; i < LCS_maxn; ++i) {
        LCSData >> b;
        int siz = b.length();
        for (int j = 0; j < siz; ++j) {
            a[i][j] = b[j];
        }a[i][siz] = '\0';
    }
    LCSData.close();
}
int LCSdfs(char* a, char* b, int i, int j, int** f) {
    if (i == 0 || j == 0)return 0;
    if (f[i][j] != -1)return f[i][j];
    if (a[i - 1] == b[j - 1])f[i][j] = 1 + LCSdfs(a, b, i - 1, j - 1, f);
    else {
        f[i][j] = 0;
        f[i][j] = mymax(f[i][j], LCSdfs(a, b, i, j - 1, f));
        f[i][j] = mymax(f[i][j], LCSdfs(a, b, i - 1, j, f));
    }
    return f[i][j];
}
void LCS(char *a, char *b, int** f) {
    int asiz = strlen(a);
    int bsiz = strlen(b);
    for (int i = 0; i <= asiz; ++i) {
        for (int j = 0; j <= bsiz; ++j) {
            f[i][j] = -1;
        }
    }
    LCSdfs(a, b, asiz, bsiz, f);
    std::cout << "LCS长度为：" << f[asiz][bsiz] << std::endl;
    char* ans = new char[f[asiz][bsiz] + 10];
    int tot = 0;
    for (int i = asiz, j = bsiz;;) {
        if (i == 0 || j == 0 || tot == f[asiz][bsiz])break;
        if (a[i-1] == b[j-1]) {
            ans[tot++] = a[i-1];
            --i; --j;
        }
        else if(f[i][j]==f[i-1][j]){
            --i;
        }
        else {
            --j;
        }
    }ans[tot] = '\0';
    for (int i = tot - 1, j = 0; j < i; --i, ++j) {
        char z = ans[i];
        ans[i] = ans[j];
        ans[j] = z;
    }
    std::cout << "LCS为：" << ans << std::endl;
    delete [] ans;
}
void do_LCS() {
    //new储存字符串的char数组
    char** a = new char* [LCS_maxn];
    for (int i = 0; i < LCS_maxn; ++i)a[i] = new char[string_maxn];

    //输入各字符串序列
    get_LCS_data(a);
    
    //new动态规划需要的f数组,mx为四字符串中最大的长度
    int mx = 0;
    for (int i = 0; i < LCS_maxn; ++i)mx = mymax(mx, strlen(a[i]));
    mx += 10;
    int** f = new int* [mx];
    for (int i = 0; i < mx; ++i)f[i] = new int [mx];
    
    //找各字符串间的LCS
    // A - B, 
    std::cout << "计算A和B的最长公共子序列：" << std::endl;
    LCS(a[0], a[1], f);
    std::cout << std::endl;
    // C - D,
    std::cout << "计算C和D的最长公共子序列：" << std::endl;
    LCS(a[2], a[3], f);
    std::cout << std::endl;
    // A - D,
    std::cout << "计算A和D的最长公共子序列：" << std::endl;
    LCS(a[0], a[3], f);
    std::cout << std::endl;
    // C - B
    std::cout << "计算C和B的最长公共子序列：" << std::endl;
    LCS(a[2], a[1], f);
    std::cout << std::endl;
    
    //delete分配的空间
    for (int i = 0; i < mx; ++i)delete [] f[i];
    delete [] f;
    for (int i = 0; i < LCS_maxn; ++i)delete[] a[i];
    delete[] a;
}
bool LIScmp(int x,int y) {
    return x > y;
}
int LISdfs(int* a, int* b, int i, int j, int** f) {
    if (i == 0 || j == 0)return 0;
    if (f[i][j] != -1)return f[i][j];
    if (a[i - 1] == b[j - 1])f[i][j] = 1 + LISdfs(a, b, i - 1, j - 1, f);
    else {
        f[i][j] = 0;
        f[i][j] = mymax(f[i][j], LISdfs(a, b, i, j - 1, f));
        f[i][j] = mymax(f[i][j], LISdfs(a, b, i - 1, j, f));
    }
    return f[i][j];
}
void get_LIS_data(int** a,int *siz) {
    std::ifstream LISData;
    int num; 
    for (int i = 0; i < LIS_maxn; ++i) {
        std::string b = "LIS_DATA";
        b = b + char('1' + i);
        b = b + ".txt";
        LISData.open(b);
        siz[i] = 0;
        while (LISData >> num) {
            a[i][siz[i]++] = num;
        }
        LISData.close();
    }
}
void LIS(int* a, int siz, int** f) {
    int* b = new int[siz + 10];
    int sizb = 0;
    for (int i = 0; i < siz; ++i){
        b[i] = a[i];
    }
    std::sort(b, b + siz, LIScmp);
    for (int i = 0; i < siz; ++i) {
        if (i == 0 || b[i] != b[i - 1]) b[sizb++] = b[i];
    }

    for (int i = 0; i <= siz; ++i) {
        for (int j = 0; j <= sizb; ++j) {
            if(i==0||j==0)f[i][j] = 0;
            f[i][j] = -1;
        }
    }
    LISdfs(a, b, siz, sizb, f);
    std::cout << "LIS长度为：" << f[siz][sizb] << std::endl;
    int* ans = new int[f[siz][sizb] + 10];
    int tot = 0;
    for (int i = siz, j = sizb;;) {
        if (i == 0 || j == 0 || tot == f[siz][sizb])break;
        if (a[i - 1] == b[j - 1]) {
            ans[tot++] = a[i - 1];
            --i; --j;
        }
        else if (f[i][j] == f[i - 1][j]) {
            --i;
        }
        else {
            --j;
        }
    }
    std::cout << "LIS为：";
    for (int i = tot - 1; i >= 0; --i) {
        std::cout << ans[i] << ' ';
    }
    std::cout << std::endl;
    delete[] ans;
    delete[] b;
}
void do_LIS() {
    //new储存字符串的char数组
    int* siz = new int [LIS_maxn];
    int** a = new int* [LIS_maxn];
    for (int i = 0; i < LIS_maxn; ++i)a[i] = new int[string_maxn];

    //输入各序列
    get_LIS_data(a, siz); 

    //new动态规划需要的f数组,mx取最大的序列长度
    int mx = 0;
    for (int i = 0; i < LIS_maxn; ++i)mx = mymax(mx, siz[i]);
    mx += 10;
    int** f = new int* [mx];
    for (int i = 0; i < mx; ++i)f[i] = new int[mx];

    //找各序列的最长递减子序列
    std::cout << "计算序列1最长递减子序列：" << std::endl;
    LIS(a[0], siz[0], f); 
    std::cout << std::endl;
    std::cout << "计算序列2最长递减子序列：" << std::endl;
    LIS(a[1], siz[1], f);
    std::cout << std::endl;

    //delete分配的空间
    for (int i = 0; i < mx; ++i)delete[] f[i];
    delete[] f;
    for (int i = 0; i < mx; ++i)delete[] a[i];
    delete[] a;
    delete[] siz;
}
int main()
{
    do_LCS();
    
    do_LIS();
    return 0;
}