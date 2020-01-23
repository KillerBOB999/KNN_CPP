#include "DataEntry.h"

DataEntry::DataEntry()
{
}

DataEntry::DataEntry(const vector<double> entryData, const int entryClassification)
{
	data = entryData;
	classification = entryClassification;
}

void DataEntry::setAttribute(const int& index, const double& value)
{
	data[index] = value;
}

const vector<double>& DataEntry::getData()
{
	return data;
}

const int& DataEntry::getClassification()
{
	return classification;
}
