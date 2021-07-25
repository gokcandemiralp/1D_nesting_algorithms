// het_gokcandemiralp 25-07-21
#include "slopeAccessories.h"

vector<quad> randomQuad(int n, int low, int up) {
    vector<quad> ans;
    for (int i = 0; i < n; ++i) {
        ans.push_back(quad{ (rand() % (up - low)), (rand() % (up - low) + low), (rand() % (up - low) + low) });
    }
    return ans;
}

void kpi(vector<vector<quad>> vec, int chunk, int gap) { 
    float left = 0; float total = 0; float lines = 0;
    vector<vector<quad>>::const_iterator i = vec.begin();
    for (; (i + 1) != vec.end(); ++i) {     //calculates all the lines except the last
        left = 0;
        for (std::vector<quad>::const_iterator j = (*i).begin(); j != (*i).end(); ++j) {
            left += ((*j).L1+ (*j).L2);
        }
        ++lines;
        total += (chunk) - (left/2);
    }

    quad a; quad b; int last_piece = 0; 
    if (i != vec.end()) {   //calculates the last line
        left = 0;
        a = { 0,0,0 };
        for (std::vector<quad>::const_iterator j = (*i).begin(); j != (*i).end(); ++j) {
            b = (*j);
            last_piece += rightMost(a, b, gap);
            left += ((*j).L1 + (*j).L2);
            a = b;
        }
        ++lines;
        total += last_piece - (left / 2);
    }

    std::cout << "scrapped percantage is % " << ((total / (lines * chunk)) * 100);
}

vector<vector<quad>> badFit(vector<quad> vec, int chunk, int gap) {

    vector<vector<quad>> ans;
    int total = 0;
    quad a = { 0,0,0 };
    quad b;
    auto e = (vec.end() - 1);

    for (int size = vec.size(); size > 0; size = vec.size()) {
        vector<quad> temp;
        total = 0;
        b = (*e);

        for (; size > 0 && (total + rightMost(a, b, gap)) < chunk; size = vec.size()) {
            total += rightMost(a, b, gap);
            temp.push_back(b);
            vec.pop_back();
            if (vec.end() == vec.begin()) { break; }
            a = b;
            e = (vec.end() - 1);
            b = (*e);
        }
        ans.push_back(temp);
    }
    return ans;
}
