//het_gokcandemiralp 29-07-21
#include "slopeFitting.h"
#include "slopeAccessories.h"

int main() {

    Mat drawing;
    vector<quad> vec;
    int thickness = 20;
    int chunk = 1440;
    int gap = 4;

    vec= randomQuad(291, 30, 90, thickness);

    drawing = Mat::zeros(Size(1600, 900), CV_8UC3);

    donatello(drawing, fit(vec,chunk,gap), gap, thickness);
    imshow("image", drawing);
    waitKey(0);

    //kpi(fit(vec, 1440, 2), 1440 , 2);
    //cout << "\n";
    //kpi(badFit(vec, 1440, 2), 1440, 2);

}