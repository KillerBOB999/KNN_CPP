// INFORMATION--------------------------------------------------------------------------
// DEVELOPER:        Anthony Harris
// GITHUB:           https://github.com/KillerBOB999/KNN_CPP
// DATE:             21 January 2019
// PURPOSE:          KNN algorithm implementation in C++ for CSC736: Machine Learning.
//--------------------------------------------------------------------------------------

// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

#include <iostream>
using std::cin;
using std::cout;

#include <vector>
using std::vector;

using std::tuple;

int main(int argc, char* argv[]) // invoked by: knn_classify pendigits_training pendigits_test <k>
{
    vector<tuple<vector<int>, int>> trainingData;
    vector<tuple<vector<int>, int>> testData;
    const int k = (int)argv[3];
}