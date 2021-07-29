//het_gokcandemiralp 28-07-21
#ifndef __SLOPEACCESSORIES_H__
#define __SLOPEACCESSORIES_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include "slopeFitting.h"

using namespace std;

/**
 * randomQuad function takes in 4 integer variables
 * The 1st integer variable is to determine the size of the vector
 * 2nd and the 3rd variable determines the boundaries
 * 4th integer is used to create acceptable slopes
 * it randomly creates quad's between upper and lower limits
 * it pushes quad's into the vector n many times
 * one can generate random quad's to test the sloped fit function
 */
vector<quad> randomQuad(int n, int low, int up, int thickness);

/**
 * kpi - key performance indicator
 * indicates mean optimization
 */
void kpi(vector<vector<quad>> vec, int chunk, int gap);


/**
 * not a fitting function but places pieces in a given order
 * without surpassing the chunk limit. It places quad's by leaving gaps
 */
vector<vector<quad>> badFit(vector<quad> vec, int chunk, int gap);

#endif
