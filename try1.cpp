#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "main_data.h"
using namespace std;

void priorityQ(vector<pair<float, int>> &v, pair<float, int> p, int k)
{
  auto it = v.begin();
  for (; it != v.end() && p.first > it->first; ++it)
    ;
  if (it != v.end() || v.size() < k)
    v.insert(it, p);
  if (v.size() > k)
    v.erase(v.end() - 1);
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
    priorityQ(pq, make_pair(e_dist, i), k);
  }

  vector<int> neighbor_labels;
  for (int i = 0; i < k; ++i)
    neighbor_labels.push_back(labels[pq[i].second]);
  return most_found(neighbor_labels);
}
void zscore2D(vector<vector<float>> &v, vector<float> &point)
{
  int rows = v.size();
  int cols = v[0].size();

  for (int j = 0; j < cols; ++j)
  {
    // Calculate mean and standard deviation for each column
    float sum = 0.0;
    for (int i = 0; i < rows; ++i)
    {
      sum += v[i][j];
    }
    float mean = sum / rows;

    float sq_sum = 0.0;
    for (int i = 0; i < rows; ++i)
    {
      sq_sum += (v[i][j] - mean) * (v[i][j] - mean);
    }
    float std_dev = sqrt(sq_sum / rows);

    // Apply z-score normalization
    for (int i = 0; i < rows; ++i)
    {
      v[i][j] = (v[i][j] - mean) / std_dev;
    }

    // Scale the point
    point[j] = (point[j] - mean) / std_dev;
  }
}
void accuracy(vector<vector<float>> &data, vector<int> &labels, float testRatio = 0.2)
{
  // srand(unsigned(time(0)));
  auto seed = unsigned(time(0));
  srand(seed);
  random_shuffle(data.begin(), data.end());
  srand(seed);
  random_shuffle(labels.begin(), labels.end());

  int testSize = (int)(data.size() * testRatio);
  vector<vector<float>> testData(data.begin(), data.begin() + testSize);
  vector<vector<float>> trainData(data.begin() + testSize, data.end());
  vector<int> testLabels(labels.begin(), labels.begin() + testSize);
  vector<int> trainLabels(labels.begin() + testSize, labels.end());

  int count = 0;
  for (int i = 0; i < testData.size(); i++)
  {
    if (k_nearest_neighbors(testData[i], trainData, trainLabels) == testLabels[i])
      count++;
  }
  double acc = count * 100 / testData.size();
  cout << "Accuracy is:" << acc << endl;
}
vector<float> interface(){
  // add interface and take in point values.
  ;

  return {5, 121, 72, 23, 112, 26.2, 0.245, 30};
}
int main()
{
  vector<float> point = interface();
  cout << "Before noralization, ";
  accuracy(mydata, mylabels);
  zscore2D(mydata, point);
  int label = k_nearest_neighbors(point, mydata, mylabels);
  cout << endl << "The predicted label for the point is: " << label << endl << endl;
  cout << "After noralization, ";
  accuracy(mydata, mylabels);
  return 0;
}