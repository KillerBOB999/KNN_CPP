// INFORMATION--------------------------------------------------------------------------
// DEVELOPER:        Anthony Harris
// GITHUB:           https://github.com/KillerBOB999/KNN_CPP
// DATE:             27 January 2019
// PURPOSE:          KNN algorithm implementation in C++ for CSC736: Machine Learning.
//--------------------------------------------------------------------------------------

// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>
#include <thread>
#include "DataEntry.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::vector;
using std::string;
using std::tuple;
using std::make_pair;

int findClassVote(const map<int, double>& neighbors, vector<DataEntry>& trainingDataSet)
{
    map<int, double> classVote =
    {
        { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 }, { 6, 0 }, { 7, 0 }, { 8, 0 }, { 9, 0 }
    };

    for (auto& neighbor : neighbors)
    {
        for (auto& classLabel : classVote)
        {
            if (trainingDataSet[neighbor.first].getClassification() == classLabel.first)
            {
                classLabel.second += 1 / neighbor.second;
            }
        }
    }

    auto finalVote = make_pair(-1, 0.0);
    for (auto& vote : classVote)
    {
        if (vote.second > finalVote.second) finalVote = vote;
    }

    return finalVote.first;
}

map<int, double> findNeighbors(DataEntry& entry, vector<DataEntry>& trainingDataSet, const int& k)
{
    map<int, double> neighbors;

    for (int entryIndex = 0; entryIndex < trainingDataSet.size(); ++entryIndex)
    {
        if (neighbors.size() < k) neighbors.insert(make_pair(entryIndex, entry.calcDistance(trainingDataSet[entryIndex])));
        else
        {
            double currentDistance = entry.calcDistance(trainingDataSet[entryIndex]);
            auto currentFarthestNeighbor = make_pair(-1, 0.0);
            for (auto& neighbor : neighbors)
            {
                if (neighbor.second > currentFarthestNeighbor.second)
                {
                    currentFarthestNeighbor = neighbor;
                }
            }
            if (currentDistance < currentFarthestNeighbor.second)
            {
                neighbors.erase(currentFarthestNeighbor.first);
                neighbors.insert(make_pair(entryIndex, currentDistance));
            }
        }
    }
    return neighbors;
}

void runKNN(vector<DataEntry>& trainingDataSet, vector<DataEntry>& testDataSet, const int& k)
{
    double correct = 0;
    double incorrect = 0;
    int ID = 0;
    for (auto& entry : testDataSet)
    {
        map<int, double> neighbors = findNeighbors(entry, trainingDataSet, k);
        int classPrediction = findClassVote(neighbors, trainingDataSet);
        classPrediction == entry.getClassification() ? ++correct : ++incorrect;
        printf("ID=%5d, predicted=%3d, true=%3d\n", ID, classPrediction, entry.getClassification());
        ++ID;
    }
    printf("classification accuracy=%6.4lf\n", correct / (correct + incorrect));
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
    const int k = atoi(argv[3]);

    standardizeData(trainingData);
    standardizeData(testData);
    
    runKNN(trainingData, testData, k);

    return 0;
}