#pragma once
#include <vector>
#include <map>

using std::vector;
using std::map;

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

	double calcDistance(DataEntry& other);
};

