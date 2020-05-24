#ifndef TOURMATEAPP_UTILS_H
#define TOURMATEAPP_UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include "Errors.h"

using namespace std;


/**
 * @file Utils.h
 */
#define INF std::numeric_limits<double>::max()
#define ERRORS(message)      Error(__FUNCTION__, __FILE__, __LINE__,message)

/**
 *
 * @return Returns true if the program is running on a unix environment
 */
bool isUnix();

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
typedef long long int lli;

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

#endif //TOURMATEAPP_UTILS_H
