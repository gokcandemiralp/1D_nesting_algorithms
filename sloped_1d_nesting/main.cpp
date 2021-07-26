//het_gokcandemiralp 26-07-21
#include "slopeFitting.h"
#include "slopeAccessories.h"

int main() {

    Mat drawing;
    vector<quad> vec;

    vec= randomQuad(180, 30, 90);

    drawing = Mat::zeros(Size(1600, 900), CV_8UC3);

    donatello(drawing, fit(vec,1440,4), 4, 20);
    imshow("image", drawing);
    waitKey(0);

    //kpi(fit(vec, 1440, 2), 1440 , 2);
    //cout << "\n";
    //kpi(badFit(vec, 1440, 2), 1440, 2);

}
