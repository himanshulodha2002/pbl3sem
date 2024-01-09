// Simple w/o priority queues

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>   // for sort
#include "main_data.h" //has vars mydata and mylabels.

using namespace std;
int most_found(const vector<int> &array)
{
    map<int, int> count;
    int max_count = 0;
    int most_counted = array[0];

    for (const auto &item : array)
    {
        count[item]++;
        if (count[item] > max_count)
        {
            max_count = count[item];
            most_counted = item;
        }
    }

    return most_counted;
}
int k_nearest_neighbors(const vector<float> &point, const vector<vector<float>> &data, const vector<int> &labels, int k = 3)
{
    vector<pair<float, int>> distances;

    for (int i = 0; i < data.size(); ++i)
    {
        float euclidean_dist = 0;
        for (int d = 0; d < point.size(); ++d)
        {
            float dist = point[d] - data[i][d];
            euclidean_dist += dist * dist;
        }
        distances.push_back({sqrt(euclidean_dist), i});
    }
    ////////////////////////////////////////////////////////////////////////////////////////////
    sort(distances.begin(), distances.end());
    ////////////////////////////////////////////////////////////////////////////////////////////
    vector<int> neighbor_labels;
    for (int i = 0; i < k; ++i)
    {
        neighbor_labels.push_back(labels[distances[i].second]);
    }

    return most_found(neighbor_labels);
}

int main()
{
    vector<float> point = {0, 137, 40, 35, 168, 43.1, 2.288, 33};
    int label = k_nearest_neighbors(point, mydata, mylabels);
    cout << "The predicted label for the point is: " << label << endl;
    return 0;
}