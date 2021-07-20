//het_gokcandemiralp 20-07-21
#include "fitting.h"
#include "accessories.h"

using namespace std;
using namespace cv;

int main() {

    Mat drawing;
    vector<int> vec;
    int gap = 10;

    std::ifstream infile("1DpartList.csv");
    int temp;
    while (infile >> temp) {
        vec.push_back(temp);
    }

    quickSort(vec, 0, vec.size() - 1);


    drawing = Mat::zeros(Size(1920, 1080), CV_8UC3);
    picasso(drawing, fit(vec, 4000, gap), gap, 3, 3);
    imshow("image", drawing);
    kpi(fit(vec, 4000, gap), 4000);
    waitKey(0);

}