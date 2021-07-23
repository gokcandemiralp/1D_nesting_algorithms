//het_gokcandemiralp 23-07-21
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

void rotate(quad a, quad& b);

int offset(quad a, quad b, int gap);

int rightMost(quad a, quad b, int gap);

int partition(vector<quad>& vec, int start, int end);

void quickSort(vector<quad>& vec, int start, int end);

vector<vector<quad>> fit(vector<quad> vec, int chunk, int gap);

void donatello(Mat drawing, vector<vector<quad>> vec, int gap, int thickness);

#endif
