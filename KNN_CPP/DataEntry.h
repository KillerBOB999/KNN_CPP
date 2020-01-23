#pragma once
#include <vector>
using std::vector;

class DataEntry
{
private:
	vector<double> data;
	int classification;

public:
	DataEntry();
	DataEntry(const vector<double> entryData, const int entryClassification);

	void setAttribute(const int& index, const double& value);
	const vector<double>& getData();
	const int& getClassification();
};

