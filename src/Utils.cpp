#include "Utils.h"


double safeDivision(double numerator, double denominator, double subst){
    denominator = denominator == 0 ? subst: denominator;
    return numerator/denominator;
}

template <class T>
int binarySearch (ulli target, vector<T> v){

    int end = v.size() ;
    int begin = 0 ;
    while (end >= begin) {
        int mid = begin + (end- begin) / 2;
        cout << "mid : " <<  mid << endl;
        if (target > v[mid]  ) begin = mid +1 ;
        else if (target < v[mid] ) end = mid - 1;
        else return mid;
    }

    return -1;

}