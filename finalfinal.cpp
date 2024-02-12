#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "main_data.h"
#include <unistd.h>
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
    float sum = 0.0;
    for (int i = 0; i < rows; ++i)
      sum += v[i][j];
    float mean = sum / rows;
    float sq_sum = 0.0;
    for (int i = 0; i < rows; ++i)
      sq_sum += (v[i][j] - mean) * (v[i][j] - mean);
    float std_dev = sqrt(sq_sum / rows);

    for (int i = 0; i < rows; ++i)
      v[i][j] = (v[i][j] - mean) / std_dev;
    point[j] = (point[j] - mean) / std_dev;
  }
}
void accuracy(vector<vector<float>> &data, vector<int> &labels, float testRatio = 0.2)
{
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
    if (k_nearest_neighbors(testData[i], trainData, trainLabels) == testLabels[i])
      count++;
  double acc = count * 100 / testData.size();
  cout << "Accuracy is:" << acc << endl;
}
vector<float> interface(int d)
{
  // add interface and take in point values & return it.
  int choice;
  float pregnancies, glucose, bp, skin_thickness, insulin, bmi, age, pedigree;
  cout << "\t\t\t\t\tD4: Data Driven Diabetes Decipher:\n\n";
  //sleep(1);
  cout<<"DESCRIPTION: In the context of diabetes prediction, this model likely analyzes features such as blood sugar levels, BMI, and other relevant health indicators to make predictions if you are diabetic or not .";
  cout<<"\n Press Enter to continue :";
  getchar();
  cout << "Do you want to enter your values or test the application for predined inputs?(choose 1 or 0 respectively):   ";
  cin >> choice;
  //choice =0;
  //sleep(0.5);
  if (choice)
  {
    vector<float> input_point(d);
    cout << "\n1.Enter the number of Pregnancies: ";
    cin >> pregnancies;
    input_point.push_back(pregnancies);
    cout << "\n2.Enter glucose level: ";
    cin >> glucose;
    input_point.push_back(glucose);
    cout << "\n3.Enter the Blood Pressure: ";
    cin >> bp;
    input_point.push_back(bp);
    cout << "\n4.Enter the skin thickness: ";
    cin >> skin_thickness;
    input_point.push_back(skin_thickness);
    cout << "\n5.Enter the Insulin level: ";
    cin >> insulin;
    input_point.push_back(insulin);
    cout << "\n6.Enter BMI (Body Mass Index): ";
    cin >> bmi;
    input_point.push_back(bmi);
    cout << "\n7.Enter Diabetes Pedigree Function(Genetic likelihood of diabetes ): ";
    cin >> pedigree;
    input_point.push_back(pedigree);
    cout << "\n8.Enter the age: ";
    cin >> age;
    input_point.push_back(age);
    return input_point;
  }
  return {0, 137, 40, 35, 168, 43.1, 2.288, 33};
}
int main()
{
  vector<float> point = interface(sizeof(mydata[0]));
  cout << "\nBefore noralization, ";
  accuracy(mydata, mylabels);
  zscore2D(mydata, point);
  //sleep(1);
  int label = k_nearest_neighbors(point, mydata, mylabels);
  cout << endl
       << "The predicted label for the point is: " << label << endl
       << endl;
  //sleep(1);
  cout << "After noralization, ";
  //sleep(1);
  accuracy(mydata, mylabels);
  //sleep(1);
  cout<<"\n\nInterpretation of data:";
  if(label){
    cout<<" There are high possibilities that you have diabetes.";
  }
  else{
      cout<<" Given data shows no risk of diabetes. But it's advisable to take precautions.\n\n";
  }
  return 0;
}