//het_gokcandemiralp 23-07-21
#ifndef __SLOPEACCESSORIES_H__
#define __SLOPEACCESSORIES_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include "slopeFitting.h"

using namespace std;

vector<quad> randomQuad(int n, int low, int up);

/**
 * kpi - key performance indicator
 * indicates mean optimization
 */
void kpi(vector<vector<quad>> vec, int chunk, int gap);

vector<vector<quad>> badFit(vector<quad> vec, int chunk, int gap);

#endif
