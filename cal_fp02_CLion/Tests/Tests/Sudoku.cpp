/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku() {
	this->initialize();
}

/**
 * Inicia um Sudoku com um conteúdo inicial.
 * Lança excepção IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9]) {
	this->initialize();

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (nums[i][j] != 0) {
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
}

void Sudoku::initialize() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			for (int n = 0; n < 10; n++) {
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}

	this->countFilled = 0;
}

/**
 * Obtem o conteúdo actual (só para leitura!).
 */
int** Sudoku::getNumbers() {
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++) {
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku já está completamente resolvido
 */
bool Sudoku::isComplete() {
	return countFilled == 9 * 9;
}

/**
 * Resolve o Sudoku.
 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
 */
bool Sudoku::solve() {
    for (int y = 0; y <= 8; y++) {
        for (int x = 0; x <= 8; x++) {
            int number = numbers[y][x];

            // Unassigned cell
            if (!number) {
                for (int i = 1; i < 10; i++) {
                    if (lineHasNumber[y][i] || columnHasNumber[x][i] || block3x3HasNumber[y / 3][x / 3][i])
                        continue;

                    countFilled++;
                    numbers[y][x] = i;
                    lineHasNumber[y][i] = true;
                    columnHasNumber[x][i] = true;
                    block3x3HasNumber[y / 3][x / 3][i] = true;

                    if (solve())
                        break;

                    countFilled--;
                    numbers[y][x] = 0;
                    lineHasNumber[y][i] = false;
                    columnHasNumber[x][i] = false;
                    block3x3HasNumber[y / 3][x / 3][i] = false;
                }

                if (!numbers[y][x])
                    return false;
            }
        }
    }

    return true;
}

/**
 * Imprime o Sudoku.
 */
void Sudoku::print() {
	for (int i = 0; i < 9; i++) {
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
