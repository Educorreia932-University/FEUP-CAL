/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>

// Exercise 3. a)
string calcSum(int* sequence, int size) {
    int sum, min_sum;
    string pair, result;

    // Number of contiguous digits
    for (int i = 0; i < size; i++) {
        min_sum = INT_MAX;

        // Groupings
        for (int j = 0; j < size - i; j++) {
            sum = 0;

            for (int k = j; k < j + i + 1; k++)
                sum += sequence[k];

            if (sum < min_sum) {
                pair = to_string(sum) + "," + to_string(j) + ";";
                min_sum = sum;
            }
        }

        result += pair;
    }

    return result;
}

// Exercise 3. b)
int main() {
    for (int i = 0; i < 500; i++) {
        int* sequence = new int[i];

        srand(time(nullptr));

        for (int j = 0; j < i; j++)
            sequence[i] = rand();

        auto start = chrono::high_resolution_clock::now();

        calcSum(sequence, i);

        auto finish = chrono::high_resolution_clock::now();
        auto mili = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    }
}
