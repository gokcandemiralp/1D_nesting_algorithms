// het_gokcandemiralp 23-07-21
#include "slopeAccessories.h"

vector<quad> randomQuad(int n, int low, int up) {
    vector<quad> ans;
    for (int i = 0; i < n; ++i) {
        ans.push_back(quad{ (rand() % (up - low)), (rand() % (up - low) + low), (rand() % (up - low) + low) });
    }
    return ans;
}

void kpi(vector<vector<quad>> vec, int chunk) {

}
