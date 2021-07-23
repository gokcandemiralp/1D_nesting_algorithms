//het_gokcandemiralp 23-07-21
#include "slopeFitting.h"
#include "slopeAccessories.h"

int main() {

    Mat drawing;
    vector<quad> vec;

    vec= randomQuad(60, 30, 60);

    drawing = Mat::zeros(Size(1600, 900), CV_8UC3);

    
    donatello(drawing, fit(vec,1440,2), 2, 20);
    imshow("image", drawing);
    waitKey(0);

}