/*
 * Partioning.cpp
 */

#include "Partitioning.h"
#include <vector>

using namespace std;

int s_recursive(int n, int k) {
    if (k == 1 || k ==n)
        return 1;

    return s_recursive(n - 1, k - 1) + k * s_recursive(n - 1, k);
}

int s_dynamic(int n, int k) {
    vector<vector<int>> c(n, vector<int>(k));

    for (int i = 0; i < n; i++)
        c[i][0] = 1;

    for (int i = 1; i < n; i++)
        for (int j = 1; j < k; j++)
            c[i][j] = c[i - 1][j - 1] + (j + 1) * c[i - 1][j];

    return c[n - 1][k - 1];
}

int b_recursive(int n) {
    int sum = 0;

    for(int k = 1; k <= n; k++)
        sum += s_recursive(n, k);

    return sum;
}

int b_dynamic(int n) {
    int sum = 0;

    for(int k = 1; k <= n; k++)
        sum += s_dynamic(n, k);

    return sum;
}


