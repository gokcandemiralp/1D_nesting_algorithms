//het_gokcandemiralp 23-07-21
#include "slopeFitting.h"


void flip_horizontal(quad &q){
    int temp;
    q.X = -q.X;
    temp = q.L1;
    q.L1 = q.L2;
    q.L2 = temp;
}

void flip_vertical(quad& q) {
    q.X = q.L1 - q.L2 - q.X;
}

void rotate(quad a, quad &b) {
    int D1 = a.L1 - (a.L2 + a.X);
    int D2 = -b.X;
    int D3 = b.L1 - b.X - b.L2;
    
    if (abs(abs(D1) - abs(D2)) < abs(abs(D1) - abs(D3))) {
        if (abs(D1) + abs(D2) == abs(D1-D2)) {
            flip_horizontal(b);
        }
    }
    else {
        if (abs(D1) + abs(D3) == abs(D1 + D3)) {
            flip_vertical(b);
            flip_horizontal(b);
        }
        else{
            flip_vertical(b);
        }
    }
}


int offset(quad a, quad b, int gap) {
    int Offset = 0;
    int D1 = a.L1 - (a.L2 + a.X);
    int D2 = -b.X;
    (D1 - D2 > 0) ? Offset = a.L1 + gap : Offset = a.X + a.L2 - b.X + gap;
    return Offset;
}

int rightMost(quad a, quad b, int gap) {
    int Offset = 0;
    int rightMost = 0;
    int D1 = a.L1 - (a.L2 + a.X);
    int D2 = -b.X;
    (D1 - D2 > 0) ? Offset = a.L1 + gap : Offset = a.X + a.L2 - b.X + gap;
    (b.L1 > b.X + b.L2) ? rightMost = Offset + b.L1 : rightMost = Offset + b.X + b.L2;
    (a.L1 > a.X + a.L2) ? rightMost -= a.L1 : rightMost -= (a.X + a.L2);

    return rightMost;
}

int partition(vector<quad>& vec, int start, int end) {
    int pivot = end;
    int j = start;
    for (int i = start; i < end; ++i) {
        if ((vec[i].L1 + vec[i].L2) < (vec[pivot].L1 + vec[pivot].L2)) {
            swap(vec[i], vec[j]);
            ++j;
        }
    }
    swap(vec[j], vec[pivot]);
    return j;
}

void quickSort(vector<quad>& vec, int start, int end) {
    if (start < end) {
        int p = partition(vec, start, end);
        quickSort(vec, start, p - 1);
        quickSort(vec, p + 1, end);
    }
}

vector<quad>::iterator closestSlope(vector<quad>& vec, quad a) {
    int D1 = a.L1 - (a.L2 + a.X);
    int D2 , temp;
    int lowest = INT_MAX;
    vector<quad>::iterator ans;
    quad b;

    for (vector<quad>::iterator e = (vec.end() - 1); vec.size()>0 ;--e) {
        quad b = (*e);
        D2 = -b.X;
        temp = abs(abs(D1) - abs(D2));
        if (temp < lowest) { lowest = temp; ans = e; }
        if (e == vec.begin()) { break; }
    }
    
    return ans;
}

vector<vector<quad>> fit(vector<quad> vec, int chunk, int gap) {
    quickSort(vec, 0, vec.size() - 1);
    
    vector<vector<quad>> ans;
    int total = 0;
    quad a = {0,0,0};
    quad b;
    auto e = closestSlope(vec, a);

    for (int size = vec.size(); size > 0; size = vec.size()) {
        vector<quad> temp;
        total = 0;
        b = (*e);
        rotate(a, b);

        for (; size > 0 && (total + rightMost(a, b, gap)) < chunk; size = vec.size()) {
            total += rightMost(a, b, gap);
            temp.push_back(b);
            vec.pop_back();
            if (vec.end() == vec.begin()) { break; }
            a = b;
            e = closestSlope(vec, a);
            b = (*e);
            rotate(a, b);
        }

        ans.push_back(temp);
    }

    return ans;
}

void donatello(Mat drawing, vector<vector<quad>> vec, int gap, int thickness) {
    int Offset = 0;
    auto i = vec.begin();
    int Y = 5;
    
    for (; i != vec.end(); ++i) {
        auto j = (*i).begin();
        for (; j != (*i).end(); ++j) {
            quad a = (*j);
            vector<Point> poligon = { Point(0 + Offset,Y),Point(a.X + Offset, thickness + Y),Point(a.X + (*j).L2 + Offset,thickness + Y),Point(a.L1 + Offset, Y) };
            fillConvexPoly(drawing, poligon, cv::Scalar(255, 255, 255));

            if ((j + 1) != (*i).end()) {
                quad b = *(j + 1);
                Offset += offset(a, b, gap);
            }
        }
        Y += 2 * thickness;
        Offset = 0;
    }
}
