//het_gokcandemiralp 22-07-21
#ifndef __FITTING_H__
#define __FITTING_H__

#include <iostream>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;


/**
 * partition function takes a vector<int> reference and 2 integer variables
 * The helper funtion for quicksort algorithm
 * It divides the vector with respect to pivot point
 * and returns the next partition point as an integer 
 */
int partition(vector<int>& v, int start, int end);

/**
 * logn avarage quicksort algorithm
 * takes in the vector to be sorted and the boundries of the vector
 * uses partition function as a helper
 * sorting is executed over the original vector
 */
void quickSort(vector<int>& vec, int start, int end);

/**
 * binarySearch function takes in the reference of the vector that the search will be conducted, 
 * It takes in the boundaries and the element to be searched
 * It is a modified binarySearch algorithm
 * it searches for the element x if found returns the index
 * if it cannot find the exact integer it returns the next smallest integers index
 * if there is no element smaller than searched element it returns -1
 */
int binarySearch(vector<int> &vec, int l, int r, int x);

/**
 * Tail function for the recursive binarySearch algorithm
 * It doesnt take in the boundries, instead calculates them and
 * passes them to binarySearch function
 */
int nextSmallest(vector<int>& vec, int x);


/**
 * fit() function is the actual fitting function
 * it takes in the pieces to be fitted as vector<int>
 * it takes an integer as the limit of stacking
 * the last integer variable is for determining the distance between each pieces
 * 
 * 1- fit() function first sorts the vector input using quickSort()
 * 2- it stacks the integers until it doesnt fit anymore starting from the greatest 
 * 3- then it searches for a possible fit for the leftover distance using nextSmallest()
 * 4- It tries to find an exact fit, if it cannot find an exact fit
 * 5- It finds the biggest fit for the leftover area 
 * 6- If there is still leftover place it repeats the step 5
 */
vector<vector<int>> fit(vector<int> vec, int chunk, int gap);

/**
 * picasso() function is the function that visualizes the fitting algorihms result
 * it takes in a gap parameter to leave some space between elements
 * it takes in a scale parameter, it scales the elements and gaps down according to that
 * printed size is (actual size)/scale
 * integer thicc is for determining the thickness of the items
 * thicc is also for determining the distance between each line
 * it uses opencv to visulize items
 */
void picasso(Mat drawing, vector<vector<int>> vec, int gap, int scale,  int thicc);


#endif
