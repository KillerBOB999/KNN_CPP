// INFORMATION--------------------------------------------------------------------------
// DEVELOPER:        Anthony Harris
// GITHUB:           https://github.com/KillerBOB999/KNN_CPP
// DATE:             21 January 2019
// PURPOSE:          KNN algorithm implementation in C++ for CSC736: Machine Learning.
//--------------------------------------------------------------------------------------

// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>
#include "DataEntry.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::vector;
using std::string;
using std::tuple;

double calcDistance(DataEntry entry1, DataEntry entry2)
{
    double sum = 0;
    for (int attributeIndex = 0; attributeIndex < entry1.getData().size(); ++attributeIndex)
    {
        sum += (pow(entry1.getData()[attributeIndex] - entry2.getData()[attributeIndex], 2));
    }
    return sqrt(sum);
}

vector<double> calcSTD(vector<DataEntry>& dataSet, const vector<double>& means)
{
    vector<double> stds;
    for (int attributeIndex = 0; attributeIndex < dataSet[0].getData().size(); ++attributeIndex)
    {
        double sum = 0;
        for (auto& entry : dataSet)
        {
            sum += pow(entry.getData()[attributeIndex] - means[attributeIndex], 2);
        }
        stds.push_back(sqrt(sum / dataSet.size()));
    }

    return stds;
}

vector<double> calcMeans(vector<DataEntry>& dataSet) 
{
    vector<double>means;
    for (int attributeIndex = 0; attributeIndex < dataSet[0].getData().size(); ++attributeIndex)
    {
        double sum = 0;
        for (auto& entry : dataSet)
        {
            sum += entry.getData()[attributeIndex];
        }
        means.push_back(sum / dataSet.size());
    }
    return means;
}

void standardizeData(vector<DataEntry>& dataSet)
{
    vector<double> means = calcMeans(dataSet);
    vector<double> stds = calcSTD(dataSet, means);
    
    for (auto& entry : dataSet)
    {
        for (int attributeIndex = 0; attributeIndex < entry.getData().size(); ++attributeIndex)
        {
            entry.setAttribute(attributeIndex, (entry.getData()[attributeIndex] - means[attributeIndex]) / stds[attributeIndex]);
        }
    }
}

vector<DataEntry> collectData(const string& fileName)
{
    vector<DataEntry> dataSet;
    vector<double> data;
    ifstream inFile = ifstream(fileName + ".txt");
    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            int value;
            inFile >> value;

            if (data.size() < 16) // Number of attributes per entry
            {
                data.push_back(value);
            }
            else
            {
                dataSet.push_back(DataEntry(data, value));
                data.clear();
            }
        }
        inFile.close();
    }

    return dataSet;
}

int main(int argc, char* argv[]) // invoked by: knn_classify pendigits_training pendigits_test <k>
{
    vector<DataEntry> trainingData = collectData(argv[1]);
    vector<DataEntry> testData = collectData(argv[2]);
    const int k = (int)argv[3];

    standardizeData(trainingData);
    standardizeData(testData);
    
    return 0;
}