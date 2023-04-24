#ifndef BUS_LINE_H
#define BUS_LINE_H

#include "BusStation.h"
#include "Exception.h"

#include <string>
#include <vector>
using namespace std;

class BusLine {
/// <summary>
/// Implementation of a bus line, read from text file.
/// </summary>
public:
	BusLine(const string& code) : code_(code), count_of_a_station_(0) {};
	BusLine(const BusLine& line);
	~BusLine();

	// we need this so we can enable using sort function on list<BusLine*> in PublicTransport.h
	struct Comparator {
		bool operator()(const BusLine* b1, const BusLine* b2) const {
			if (b1->getCode().compare(b2->getCode()) < 0) {
				return true;
			}
			else return false;
		}
	};

	string getCode() const;
	BusStation* getFirstStation() const;
	BusStation* getLastStation() const;
	vector<BusStation*> getDirectionA() const;
	vector<BusStation*> getDirectionB() const;
	int getCounter() const;

	BusStation* findStationOnDirection(int code, char direction);
	bool areStationsNextToEachOther(BusStation* b1, BusStation* b2);

	void addStationA(BusStation* station);
	void addStationB(BusStation* station);
	void addBusLineCode(const string& code_line, int code);

	string print() const;
	string printAllStationsOnThisLine(vector<BusStation*> direction) const;

	void countStation();
	void resetCounter();

private:
	string code_;                       // code of the bus line
	vector<BusStation*> direction_A_;   // pointers to the bus stations through which line passes in direction A
	vector<BusStation*> direction_B_;   // pointers to the bus stations through which line passes in direction B
	int count_of_a_station_;            // for last stategy of printing
};

#endif

