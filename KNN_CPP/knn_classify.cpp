// INFORMATION--------------------------------------------------------------------------
// DEVELOPER:        Anthony Harris
// GITHUB:           Anthony999
// DATE:             21 January 2019
// PURPOSE:          KNN algorithm implementation in C++ for CSC736: Machine Learning.
//--------------------------------------------------------------------------------------

// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

#include <iostream>
#include <vector>
using std::vector;

int main(int argc, char* argv[])
{
    const int classIndex = 16;
    vector<vector<int>> trainingData;
    vector<vector<int>> testData;
    std::cout << argv[1] << std::endl;
}


// FUNCTION DESCRIPTION-----------------------------------------------------------------
        // Function Name:    distanceMeasure
        // Parameters:  entry1
        //                  Use:    Represents an entry in the trainingDataSet for use in
        //                          calculating the distance between it and entry2
        //              entry2
        //                  Use:    Represents the current entry of the testDataSet for use
        //                          in calculating the distance between it and entry1
        // Returns:          A floating point representation of the 'distance measure' of the
        //                   2 entries.
        // Description:      For each element e of the entries, find the summation of the 
        //                   absolute value of the difference bewteen e1 and e2 and then take
        //                   the Nth root of that sum
        //--------------------------------------------------------------------------------------