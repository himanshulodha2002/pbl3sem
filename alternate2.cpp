// using self made priority queue

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include "main_data.h" //has vars mydata and mylabels.
using namespace std;

void priorityQ(vector<pair<float, int>> &v, pair<float, int> p)
{
  auto it = v.begin();
  for (; it != v.end() && p.first > it->first; ++it)
    ;
  v.insert(it, p);
}

int most_found(vector<int> &array)
{
  map<int, int> count;
  int max_count = 0;
  int most_counted = array[0];

  for (auto &item : array)
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
int k_nearest_neighbors(vector<float> point, vector<vector<float>> data, vector<int> labels, int k = 3)
{
  vector<pair<float, int>> pq;
  for (int i = 0; i < data.size(); ++i)
  {
    float e_dist = 0;
    for (int d = 0; d < point.size(); ++d)
    {
      float dist = point[d] - data[i][d];
      e_dist += dist * dist;
    }
    e_dist = sqrt(e_dist);
    priorityQ(pq, make_pair(e_dist, i));
  }

  vector<int> neighbor_labels;
  for (int i = 0; i < k; ++i)
  {
    neighbor_labels.push_back(labels[pq[i].second]);
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