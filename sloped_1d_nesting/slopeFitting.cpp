//het_gokcandemiralp 01-08-21
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
    int RightMost = 0;
    int D1 = a.L1 - (a.L2 + a.X);
    int D2 = -b.X;
    (D1 - D2 > 0) ? Offset = a.L1 + gap : Offset = a.X + a.L2 - b.X + gap;
    (b.L1 > b.X + b.L2) ? RightMost = Offset + b.L1 : RightMost = Offset + b.X + b.L2;
    (a.L1 > a.X + a.L2) ? RightMost -= a.L1 : RightMost -= (a.X + a.L2);

    return RightMost;
}

int partition(vector<quad>& vec, int start, int pivot) { //pivot is the upper boundary
    int j = start;
    for (int i = start; i < pivot; ++i) {
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

int binarySearch(vector<quad>& vec, int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (2*x == vec[mid].L1 + vec[mid].L2)
            return mid;
        else if (mid == 0)
            return -1;
        else if (2 * x < vec[mid].L1 + vec[mid].L2)
            return binarySearch(vec, l, mid - 1, x);
        else
            return binarySearch(vec, mid + 1, r, x);
    }
    return r;
}

int nextSmallest(vector<quad>& vec, quad a , int total, int gap) {
    int ans;
    quad b;
    ans = binarySearch(vec, 0, vec.size() - 1, total);

    while (ans >= 0) {
        b = vec[ans];
        rotate(a, b);
        if ((total - rightMost(a, vec[ans], gap)) > 0) { break; }
        --ans;
    }
    return ans;
}

vector<quad>::iterator closestSlope(vector<quad>& vec, quad a) {
    int D1 = a.L1 - (a.L2 + a.X);
    int D2 , D3, temp;
    int lowest = INT_MAX;
    vector<quad>::iterator ans;
    quad b;

    for (vector<quad>::iterator e = (vec.end() - 1); vec.size()>0 ;--e) {
        quad b = (*e);
        D2 = -b.X;
        D3 = b.L1 - b.X - b.L2;
        (abs(abs(D1) - abs(D2)) < abs(abs(D1) - abs(D3))) ? temp = abs(abs(D1) - abs(D2)) : temp = abs(abs(D1) - abs(D3));
        if (temp == 0) { lowest = temp; return e; }
        if (temp < lowest) { lowest = temp; ans = e; }
        if (e == vec.begin()) { break; }
    }
    return ans;
}

vector<vector<quad>> fit(vector<quad> vec, int chunk, int gap) {
    quickSort(vec, 0, vec.size() - 1);
    
    vector<vector<quad>> ans;
    int total = 0;
    bool signal = true;
    quad a = {0,0,0};
    quad b;
    vector<quad>::iterator e;

    for (int size = vec.size(); size > 0; size = vec.size()) {
        vector<quad> temp;
        total = -gap;  // this line prevents unnecessary gap in the begining
        a = { 0,0,0 };
        e = closestSlope(vec, a); // find a piece with a fitting slope 
        b = (*e);
        rotate(a, b); //create a quad piece with 0 lenght and with no slope as the first piece

        for (; size > 0 && (total + rightMost(a, b, gap)) <= chunk; size = vec.size()) {
            total += rightMost(a, b, gap);
            temp.push_back(b);
            vec.erase(e);
            if (vec.end() == vec.begin()) { break; }
            a = b;
            e = closestSlope(vec, a); // find a piece with a fitting slope 
            b = (*e);
            rotate(a, b); // flip that piece so that it fits as perfect as possible
        }

        for (int index = nextSmallest(vec, a, (chunk - total), gap); size > 0 && index != -1; size = vec.size(), index = nextSmallest(vec, a, (chunk - total), gap)) {
            b = vec[index]; //finds an index with the biggest piece that can fit the remaining space ( until it doesnt fit anymore )
            rotate(a, b);
            total += rightMost(a, b, gap); //checks how much space have left
            temp.push_back(vec[index]);
            vec.erase(vec.begin() + index);
            a = b;
        }
        ans.push_back(temp);
    }
    return ans;
}

void donatello(Mat drawing, vector<vector<quad>> vec, int gap, int thickness) {
    int Offset = 5;
    vector<vector<quad>>::iterator i = vec.begin();
    int Y = 5;
    quad A = {0,0,0};
    
    for (; i != vec.end(); ++i) {
        vector<quad>::iterator j = (*i).begin();
        if (j != (*i).end() && (*j).X < 0) { Offset -= (*j).X;}
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
        Offset = 5;
    }
}
