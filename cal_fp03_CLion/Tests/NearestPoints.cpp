/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right) {
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right) {
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
	Result res;
	double dmin;

	for (int i = 0; i < vp.size() - 1; i++)
	    for (int j = i + 1; j < vp.size(); j++) {
            if ((dmin = vp[i].distSquare(vp[j])) < res.dmin) {
                res.dmin = dmin;
                res.p1 = vp[i];
                res.p2 = vp[j];
            }
        }

	res.dmin = sqrt(res.dmin);

	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);

    double dmin;

    for (int i = 0; i < vp.size() - 1; i++)
        for (int j = i + 1; j < vp.size(); j++) {
            if (vp[j].x - vp[i].x > sqrt(res.dmin))
                break;

            else if ((dmin = vp[i].distSquare(vp[j])) < res.dmin) {
                res.dmin = dmin;
                res.p1 = vp[i];
                res.p2 = vp[j];
            }
        }

    res.dmin = sqrt(res.dmin);

	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res) {
    double dmin;

    for (int i = left; i < right + 1; i++)
        for (int j = i + 1; j < right + 1; j++) {
            if (abs(vp[i].y - vp[j].y) > res.dmin)
                break;

            else if ((dmin = vp[i].distance(vp[j])) < res.dmin) {
                res.dmin = dmin;
                res.p1 = vp[i];
                res.p2 = vp[j];
            }
        }
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
	// Base case of two points
	if (right - left == 1)
        return Result(vp[left].distance(vp[right]), vp[left], vp[right]);

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
    if (right - left == 0)
        return Result(MAX_DOUBLE, vp[left], vp[left]);

	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
    Result left_half, right_half;
    int middle = (left + right) / 2;

    if (numThreads <= 1) {
        left_half = np_DC(vp, left, middle, numThreads);
        right_half = np_DC(vp, middle + 1, right, numThreads);
    }

    // Multi-threaded solution credits to JoaoCostaIFG
    else {
        thread t([&vp, &left_half, left, middle, numThreads] {
            vector<Point> vv(vp); // copy array -> multiple threads might sort part of it at the same time
            left_half = np_DC(vv, left, middle, numThreads / 2);
        });

        right_half = np_DC(vp, middle + 1, right, numThreads / 2);
        t.join(); // Wait for the other thread
    }

	// Select the best solution from left and right
	Result res = left_half.dmin < right_half.dmin ? left_half : right_half;

	// Determine the strip area around middle point
	middle = (vp[right].x + vp[left].x) / 2;
    int strip_left = middle - res.dmin;
    int strip_right = middle + res.dmin;

	// Order points in strip area by Y coordinate
    int strip_left_index = left;
    int strip_right_index = right;

    for (int i = left; i < right; i++) {
        if (vp[i].x < strip_left)
            strip_left_index = i;

        if (vp[i].x > strip_right) {
            strip_right_index = i - 1;
            break;
        }
    }

    sortByY(vp, strip_left_index, strip_right_index);

	// Calculate nearest points in strip area (using npByY function)
	npByY(vp, strip_left_index, strip_right_index, res);

	// Reorder points in strip area back by X coordinate
    sortByX(vp, strip_left_index, strip_right_index);

	return res;
}

/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;

void setNumThreads(int num) {
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}

/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() - 1);

	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
