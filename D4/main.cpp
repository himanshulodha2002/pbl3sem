#include <QApplication>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPlainTextEdit>
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
int k_nearest_neighbors(vector<float> point, vector<vector<float>> data, vector<int> labels, int k = 2)
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
double accuracy(vector<vector<float>> &data, vector<int> &labels, float testRatio = 0.2)
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
    return acc;
}
int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QWidget window;
    window.resize(800, 600);
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    app.setPalette(darkPalette);
    app.setStyle("Fusion");
    QFormLayout layout(&window);

    QLabel heading("D4: Data Driven Diabetes Decipher");
    QFont headingFont = heading.font();
    headingFont.setPointSize(24);
    heading.setFont(headingFont);
    heading.setAlignment(Qt::AlignCenter);
    layout.addRow(&heading);

    QLabel description("DESCRIPTION: In the context of diabetes prediction, this model likely analyzes features such as blood sugar levels, BMI, and other relevant health indicators to make predictions if you are diabetic or not .");
    QFont descriptionFont = description.font();
    descriptionFont.setPointSize(9);
    description.setFont(descriptionFont);
    description.setWordWrap(true);
    description.setAlignment(Qt::AlignJustify);

    layout.addRow(&description);

    QLineEdit pregnanciesEdit;
    pregnanciesEdit.setText("1");
    layout.addRow("Pregnancies:", &pregnanciesEdit);

    QLineEdit glucoseEdit;
    glucoseEdit.setText("85");
    layout.addRow("Glucose:", &glucoseEdit);

    QLineEdit bloodPressureEdit;
    bloodPressureEdit.setText("66");
    layout.addRow("Blood Pressure:", &bloodPressureEdit);

    QLineEdit skinThicknessEdit;
    skinThicknessEdit.setText("29");
    layout.addRow("Skin Thickness:", &skinThicknessEdit);

    QLineEdit insulinEdit;
    insulinEdit.setText("0");
    layout.addRow("Insulin:", &insulinEdit);

    QLineEdit bmiEdit;
    bmiEdit.setText("26.6");
    layout.addRow("BMI:", &bmiEdit);

    QLineEdit diabetesPedigreeEdit;
    diabetesPedigreeEdit.setText("0.351");
    layout.addRow("Diabetes Pedigree:", &diabetesPedigreeEdit);

    QLineEdit ageEdit;
    ageEdit.setText("31");
    layout.addRow("Age:", &ageEdit);

    QPushButton button("Submit");
    layout.addRow(&button);

    QLabel resultLabel;
    layout.addRow("Result:", &resultLabel);

    QTextEdit outputTextEdit;

    layout.addRow(&outputTextEdit);
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
        outputTextEdit.append("Before normalization, ");
        outputTextEdit.append("Accuracy is: " + QString::number(accuracy(mydata, mylabels)) + "%");
        zscore2D(mydata, point);
        
        outputTextEdit.append("After normalization, ");
        outputTextEdit.append("Accuracy is: " + QString::number(accuracy(mydata, mylabels)) + "%");
        int label = k_nearest_neighbors(point, mydata, mylabels);
        outputTextEdit.append("The predicted label for the point is: " + QString::number(label));
        if(label)
            outputTextEdit.append("There are high possibilities that you may have diabetes.");
        else
            outputTextEdit.append("Given data shows no risk of diabetes. But it's advisable to take precautions."); });
    window.show();
    return app.exec();
}
