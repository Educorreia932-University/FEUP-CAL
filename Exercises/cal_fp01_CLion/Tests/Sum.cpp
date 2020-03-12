/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <fstream>
#include <iostream>

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
void generate_graph() {
    for (int i = 10; i <= 500; i += 10) {
        double total_time = 0;

        for (int j = 0; j < 1000; j++) {
            int *sequence = new int[i];

            srand(time(nullptr));

            for (int k = 0; k < i; k++)
                sequence[i] = rand()%(10 * i - 1) + 1;

            auto start = chrono::high_resolution_clock::now();

            calcSum(sequence, i);

            auto finish = chrono::high_resolution_clock::now();
            auto mili = chrono::duration_cast<chrono::milliseconds>(finish - start).count();

            total_time += mili;
        }

        double time = total_time / 1000;

        cout << time << "\n";
    }
}
