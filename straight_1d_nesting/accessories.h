//het_gokcandemiralp 20-07-21
#ifndef __ACCESSORIES_H__
#define __ACCESSORIES_H__

#include <iostream>
#include <vector>
#include <fstream>

/**
 * randomVector function takes in 3 integer variables
 * The 1st integer variable is to determine the size of the vector
 * 2nd and the 3rd variable determines the boundaries
 * it randomly assigns integers between upper and lower limits
 * it pushes integers into the vector n many times
 * one can generate random vectors to test the fit function
 */
std::vector<int> randomVector(int n, int low, int up); 

/**
 * printVector2D funtion takes in a vector cantaining another vector that contains integers
 * it prints integers contained in each vector<int> in a seperate line using std::cout
 * it seperates each element with "," and each line with "\n"
 */
void printVector2D(std::vector<std::vector<int>> vec);

/**
 * printVector1D funtion takes in a vector that contains integers
 * it prints integers in a single line using std::cout
 * it seperates each element with ","
 */
void printVector1D(std::vector<int> vec); 


/**
 * kpi - key performance indicator
 * indicates mean optimization
 */
void kpi(std::vector<std::vector<int>> vec, int chunk);

#endif
