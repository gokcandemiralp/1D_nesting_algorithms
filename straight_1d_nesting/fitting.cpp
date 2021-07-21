//het_gokcandemiralp 21-07-21
#include "fitting.h"

using namespace std;
using namespace cv;

int partition(vector<int>& vec, int start, int end){
	int pivot = end;
	int j = start;
	for (int i = start; i < end; ++i) {
		if (vec[i] < vec[pivot]) {
			swap(vec[i], vec[j]);
			++j;
		}
	}
	swap(vec[j], vec[pivot]);
	return j;
}

void quickSort(vector<int>& vec, int start, int end) {
	if (start < end) {
		int p = partition(vec, start, end);
        quickSort(vec, start, p - 1);
        quickSort(vec, p + 1, end);
	}
}

int binarySearch(vector<int> &vec, int l, int r, int x){
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (vec[mid] == x)
            return mid;
        else if (mid == 0)
            return -1;
        else if (x < vec[mid])
            return binarySearch(vec, l, mid - 1, x);
        else
            return binarySearch(vec, mid + 1, r, x);       
    }
    return r;
}

int nextSmallest(vector<int>& vec, int x) {
    return binarySearch(vec, 0, vec.size()-1, x);
}

vector<vector<int>> fit(vector<int> vec , int chunk , int gap) {
    vector<vector<int>> ans;
    quickSort(vec, 0, vec.size() - 1);
    
    for (int size = vec.size(); size > 0; size = vec.size()) {
        vector<int> temp;
        int total = 0;
        auto e = (vec.end()-1);

        // It stacks the integers until it doesnt fit anymore starting from the greatest
        for (; size > 0 && (total + *e) < chunk; size = vec.size(), e = (vec.end() - 1)) {
            total = total+*e + gap;
            temp.push_back(*e);
            vec.pop_back();
            if (vec.end() == vec.begin()) { break; }
        }

        // It searches for a possible fit for the leftover distance using nextSmallest(), the closest fit possible
        for (int index = nextSmallest(vec, (chunk - total)); size > 0 && index != -1  ; size = vec.size(), index = nextSmallest(vec, (chunk - total))) {
            total = total + vec[index] + gap;
            temp.push_back(vec[index]);
            vec.erase(vec.begin()+index);
        }
        // If there is still leftover place it repeats the step above

        ans.push_back(temp);
    }
    return ans;
}

void picasso(Mat drawing, vector<vector<int>> vec, int gap , int scale, int thicc) {
    int x = 5;
    int y = 5;
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        int x = 5;
        for (auto j = (*i).begin(); j != (*i).end(); ++j) {
            auto p1 = Point(x, y);
            auto p2 = Point(x + (*j / scale), y + thicc);
            rectangle(drawing, p1, p2 , Scalar(155, 155, 155), -1);
           
            x += (*j + gap ) / scale; //since it is not always an integer the gaps could differ
        }
        y += 2 * thicc + 1;
    } 
}


