//het_gokcandemiralp 28-07-21
#ifndef __SLOPEFITTING_H__
#define __SLOPEFITTING_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;


/**
 * quad struct is used to represent trapezoids
 * int X is the x coordinate of the right bottom point
 * y coordinate and the thickness is undetermined
 * L1 is the upper edge lenght, L2 is the lower edge lenght
 */
struct quad{
    int X;
    int L1;
    int L2; 
};

/**
 * flips quad's horizontally.
 * it modifies the 3 representation integers of quad.
 */
void flip_horizontal(quad& q);

/**
 * flips quad's vertically.
 * it modifies the 3 representation integers of quad.
 */
void flip_vertical(quad& q);


/**
 * rotates the secont piece so that it can
 * occupy as little space as possible.
 */
void rotate(quad a, quad& b);

/**
 * calculates how much a piece should be moved
 * for that piece to not overlap with others.
 */
int offset(quad a, quad b, int gap);

/**
 * calculates how much a piece moves the rightmost point to right.
 * Later functions use this function to 
 * check the rightmost point to be within that boundaries.
 */
int rightMost(quad a, quad b, int gap);

/**
 * partition function takes a vector<quad> reference and 2 integer variables
 * The helper funtion for quicksort algorithm
 * It divides the vector with respect to pivot point
 * and returns the next partition point as an integer
 */
int partition(vector<quad>& vec, int start, int end);

/**
 * logn avarage quicksort algorithm
 * takes in the vector to be sorted and the boundries of the vector
 * uses partition function as a helper
 * sorting is executed over the original vector
 * the magnitude is calculated by L1+L2
 * sorting is conducted from smallest to largest
 */
void quickSort(vector<quad>& vec, int start, int end);

/**
 * binarySearch function takes in the reference of the vector that the search will be conducted,
 * It takes in the boundaries and the element to be searched
 * It is a modified binarySearch algorithm
 * it searches for the element x if found returns the index
 * the magnitude is calculated by L1+L2
 * if it cannot find the exact magnitude it returns the next smallest magnitude's index
 * if there is no element smaller than searched element it returns -1
 */
int binarySearch(vector<quad>& vec, int l, int r, int x);

/**
 * Tail function for the recursive binarySearch algorithm
 * It doesnt take in the boundries, instead calculates them and
 * passes them to binarySearch function
 */
int nextSmallest(vector<quad>& vec, quad a , int total, int gap);

/**
 * closestSlope() function finds the quad with the closest slope 
 * of the right side of the quad a by looking inside the vector
 */
vector<quad>::iterator closestSlope(vector<quad>& vec, quad a);

/**
 * fit() function is the actual fitting function
 */
vector<vector<quad>> fit(vector<quad> vec, int chunk, int gap);

/**
 * donatello() function is the function that visualizes the fitting algorihms result
 * it takes in a gap parameter to leave some space between elements
 * integer thickness is for determining the thickness of the items
 * thickness is also for determining the distance between each line
 * it uses opencv to visulize items
 */
void donatello(Mat drawing, vector<vector<quad>> vec, int gap, int thickness);

#endif
