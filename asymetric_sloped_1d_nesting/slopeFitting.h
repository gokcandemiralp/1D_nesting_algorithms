//het_gokcandemiralp 26-07-21
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

struct quad{
    int X;
    int L1;
    int L2; 
};


void flip_horizontal(quad& q);

void flip_vertical(quad& q);

int offset(quad a, quad b, int gap);

int rightMost(quad a, quad b, int gap);

int partition(vector<quad>& vec, int start, int end);

void quickSort(vector<quad>& vec, int start, int end);

int binarySearch(vector<quad>& vec, int l, int r, int x);

int nextSmallest(vector<quad>& vec, quad a , int total);

vector<quad>::iterator closestSlope(vector<quad>& vec, quad a);

vector<vector<quad>> fit(vector<quad> vec, int chunk, int gap);

void donatello(Mat drawing, vector<vector<quad>> vec, int gap, int thickness);

#endif
