//het_gokcandemiralp 21-07-21
#include "fitting.h"
#include "accessories.h"

using namespace std;
using namespace cv;

int main() {

    Mat drawing;
    vector<int> vec;

    int piece_gap = 10;
    int thickness = 2;
    int scale = 3;

    std::ifstream infile("1DpartList.csv");     //reading the csv file where lenght of the pieces are stored
    int temp;                                   //every integer is stored in a seperate line
    while (infile >> temp) {
        vec.push_back(temp);
    }

    //creating a window for the result to be displayed at
    drawing = Mat::zeros(Size(1440, 810), CV_8UC3);

    //actually creating the visual on the window (using the integer figures from before )
    picasso(drawing, fit(vec, 4000, piece_gap), piece_gap, scale, thickness); 

    //opening the window
    imshow("image", drawing);

    //file close trigger ( file closes when a button is pressed )
    waitKey(0);

}
