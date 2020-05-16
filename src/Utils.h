#ifndef TOURMATEAPP_UTILS_H
#define TOURMATEAPP_UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include "Errors.h"

using namespace std;

#define INF std::numeric_limits<double>::max()
#define ERROR(message)      Error(__FUNCTION__, __FILE__, __LINE__,message)

/**
 * Message shows where the error happended. Invoked with ERROR
 * @param file Name of the file
 * @param function Name of the function
 * @param line Number of the line where the error happened
 * @param message The message to be transmited
 */
static inline void Error(const string &function, const string &file, const int &line, const string &message) {
    cout << "(" << function << ")[" << file << ":" << line << "]" << "\t" << message << endl;
    exit(1);
}

typedef unsigned long long int ulli;

/**
 * Case the denominator is zero, the denominator swapped
 * @param numerator
 * @param denominator
 * @param subst Value with whom the denominator will have its value swapped
 * @return The value of the division
 */
double safeDivision(double numerator, double denominator, double subst);
/**
 * @brief Checks if the input given is a number, not a string
 * @return return the number case it's a number
 */
double checkNumber();
/**
 * @brief Function makes the user waits until it presses enter
 */
void wait();
#endif //TOURMATEAPP_UTILS_H
