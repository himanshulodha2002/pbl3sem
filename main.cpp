#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include "main_data.h"

using namespace std;
int most_found(const vector<int>& array);
int k_nearest_neighbors(const vector<float>& point, const vector<vector<float>>& data, const vector<int>& labels, int k = 3);


int main() {
    vector<float> point = {0, 137, 40, 35, 168, 43.1, 2.288, 33};
    int label = k_nearest_neighbors(point, mydata, mylabels);
    cout << "The predicted label for the point is: " << label << endl;
    return 0;
}