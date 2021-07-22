//het_gokcandemiralp 22-07-21
#include "accessories.h"


vector<int> randomVector(int n, int low, int up){
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        ans.push_back((low + (rand() % (up-low))));
    }
    return ans;
}

void printVector2D(vector<vector<int>> vec) {
    for (vector<vector<int>>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
        for (std::vector<int>::const_iterator j = (*i).begin(); j != (*i).end(); ++j) {
            std::cout << *j << " , ";
        }
        std::cout << "\n";
    }
}

void printVector1D(vector<int> vec) {
    for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
        std::cout << *i << " , ";
    }
}

void kpi(std::vector<std::vector<int>> vec, int chunk) {
    float left = 0; float total = 0; float lines = 0;
    for (vector<vector<int>>::const_iterator i = vec.begin(); (i+1) != vec.end(); ++i) {
        left = 0;
        for (std::vector<int>::const_iterator j = (*i).begin(); j != (*i).end(); ++j) {
            left += (*j);
        }
        ++lines;
        total += chunk - left;
    }
    std::cout << "scrapped percantage is % " << ((total / (lines * chunk)) * 100);
}
