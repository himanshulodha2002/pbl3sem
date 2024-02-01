
#include <QApplication>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
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
// vector<float> interface(int d)
// {
//   // add interface and take in point values & return it.
//   int choice;
//   float pregnancies, glucose, bp, skin_thickness, insulin, bmi, age, pedigree;
//   cout << "\t\t\t\t\tD4: Data Driven Diabetes Decipher:\n\n";
//   sleep(1);
//   cout << "Do you want to enter your values or test the application for predined inputs?(choose 1 or 0 respectively):   ";
//   cin >> choice;
//   //choice =0;
//   sleep(0.5);
//   if (choice)
//   {
//     vector<float> input_point(d);
//     cout << "\n1.Enter the number of Pregnancies: ";
//     cin >> pregnancies;
//     input_point.push_back(pregnancies);
//     cout << "\n2.Enter glucose level: ";
//     cin >> glucose;
//     input_point.push_back(glucose);
//     cout << "\n3.Enter the Blood Pressure: ";
//     cin >> bp;
//     input_point.push_back(bp);
//     cout << "\n4.Enter the skin thickness: ";
//     cin >> skin_thickness;
//     input_point.push_back(skin_thickness);
//     cout << "5.Enter the Insulin level: ";
//     cin >> insulin;
//     input_point.push_back(insulin);
//     cout << "6.Enter BMI (Body Mass Index): ";
//     cin >> bmi;
//     input_point.push_back(bmi);
//     cout << "7.Enter Diabetes Pedigree Function(Genetic likelihood of diabetes ): ";
//     cin >> pedigree;
//     input_point.push_back(pedigree);
//     cout << "8.Enter the age: ";
//     cin >> age;
//     input_point.push_back(age);
//     return input_point;
//   }
//   return {5, 121, 72, 23, 112, 26.2, 0.245, 30}; // arbitarily chosen value;
// }
int main()
{
    vector<float> point = interface(sizeof(mydata[0]));
    cout << "Before noralization, ";
    accuracy(mydata, mylabels);
    zscore2D(mydata, point);
    sleep(1);
    int label = k_nearest_neighbors(point, mydata, mylabels);
    cout << endl
         << "The predicted label for the point is: " << label << endl
         << endl;
    sleep(1);
    cout << "After noralization, ";
    sleep(1);
    accuracy(mydata, mylabels);
    return 0;
}

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QWidget window;
    QFormLayout layout(&window);

    QLineEdit pregnanciesEdit;
    layout.addRow("Pregnancies:", &pregnanciesEdit);

    QLineEdit glucoseEdit;
    layout.addRow("Glucose:", &glucoseEdit);

    // Add more QLineEdit objects for each input parameter...
    QLineEdit bloodPressureEdit;
    layout.addRow("Blood Pressure:", &bloodPressureEdit);

    QLineEdit skinThicknessEdit;
    layout.addRow("Skin Thickness:", &skinThicknessEdit);

    QLineEdit insulinEdit;
    layout.addRow("Insulin:", &insulinEdit);

    QLineEdit bmiEdit;
    layout.addRow("BMI:", &bmiEdit);

    QLineEdit diabetesPedigreeEdit;
    layout.addRow("Diabetes Pedigree:", &diabetesPedigreeEdit);

    QLineEdit ageEdit;
    layout.addRow("Age:", &ageEdit);
    QPushButton button("Submit");
    layout.addRow(&button);

    QLabel resultLabel;
    layout.addRow("Result:", &resultLabel);

    QObject::connect(&button, &QPushButton::clicked, [&]()
                     {
        float pregnancies = pregnanciesEdit.text().toFloat();
        float glucose = glucoseEdit.text().toFloat();
        float bloodPressure = bloodPressureEdit.text().toFloat();
        float skinThickness = skinThicknessEdit.text().toFloat();
        float insulin = insulinEdit.text().toFloat();
        float bmi = bmiEdit.text().toFloat();
        float diabetesPedigree = diabetesPedigreeEdit.text().toFloat();
        float age = ageEdit.text().toFloat();
        vector<float> point = {pregnancies, glucose, bloodPressure, skinThickness, insulin, bmi, diabetesPedigree, age};
        cout << "Before noralization, ";
        accuracy(mydata, mylabels);
        zscore2D(mydata, point);
        int label = k_nearest_neighbors(point, mydata, mylabels);
        cout << endl
            << "The predicted label for the point is: " << label << endl
            << endl;
        sleep(1);
        cout << "After noralization, ";
        sleep(1);
        accuracy(mydata, mylabels);
        resultLabel.setText(QString::number(result)); });
    window.show();
    return app.exec();
}