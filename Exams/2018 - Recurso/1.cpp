#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n = 7;
    int m = 5;

    vector<int> d = {3, 5, 7, 8, 13, 14, 15}; // Distâncias das estações de carregamento ao ponto de partida (d0, d1, d2, d3..)
    int lastCharge = 0; // Número da estação de carregamento em que o carro abasteceu mais recentemente

    for (int i = 0; i < n - 1; i++) {
        if (lastCharge + m < d[i + 1]) {
            lastCharge = d[i];

            cout << i << " - d: " << d[i]<< endl; 
        }
    }

    return 0;
}