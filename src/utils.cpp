#include "utils.h"


double safeDivision(double numerator, double denominator, double subst){
    denominator = denominator == 0 ? subst: denominator;
    return numerator/denominator;
}
