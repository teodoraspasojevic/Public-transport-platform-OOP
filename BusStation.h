#ifndef BUS_STATION_H
#define BUS_STATION_H

#include <set>
#include <string>
#include <vector>
using namespace std;

class BusStation {
/// <summary>
/// Implementation of a bus station, read from text file.
/// </summary>
public:
	BusStation(unsigned int code, const string& name) : code_(code), name_(name) {};
	BusStation(BusStation& bus);
	~BusStation();

	friend bool operator==(const BusStation& s1, const BusStation& s2);
	friend bool operator!=(const BusStation& s1, const BusStation& s2);

	int getCode() const;
	string getName() const;
	bool isThereThisLine(const string& code_line) const;
	set<string> getBusLinesCodes() const;

	string codeToString() const;
	string printCodeAndName() const;
	string printLinesStoppingOnThisStation() const;

	void addBusLineCode(const string& code);

private:
	unsigned int code_;               // code od the station
	string name_;                     // name of the station
	set<string> bus_lines_codes_;     // codes of the bus line that stop on this station

};

#endif