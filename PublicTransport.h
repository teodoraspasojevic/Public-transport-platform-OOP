#ifndef PUBLIC_TRANSPORT_H
#define PUBLIC_TRANSPORT_H

#include "BusLine.h"
#include "BusStation.h"
#include "Exception.h"
#include "Graph.h"
#include "LoadStrategies.h"
#include "PathStrategies.h"
#include "PrintStrategies.h"

#include <iostream>
#include <list>
#include <set>
using namespace std;

class LoadStrategies;
class PathStrategies;
class PrintStrategies;

class PublicTransport : public Graph {
/// <summary>
/// Implementation of the public transport. It is class derived from class Graph in which we will store bus stations. 
/// It extends class graph with list in which we will store bus lines.
/// </summary>
public:
	PublicTransport(const PublicTransport&) = delete;
	PublicTransport& operator=(const PublicTransport&) = delete;
	~PublicTransport();

	static PublicTransport& getInstance();

	list<BusLine*> getBusLines() const;
	BusLine* getCurrentLine() const;

	void addBusLine(BusLine* bus_line);
	void addLineCodeToAllStations(const string& code_line, int code_station);
	void newStationOnALine(BusLine* line, char direction_char, int code);
	bool chechIfThereIsLine(const string& code);
	void sortLines();

	BusLine* findLineByCode(const string& code);
	void findLinesWithCommonStations(const string& code_line);
	vector<BusLine*> findLineWithMostSameStations();
	set<string> findCommonLinesForStations(BusStation* b1, BusStation* b2);

	void setCurrentBusLine(const string& line_code);
	void resetCurrentBusLine();
	void resetNewStationFunctionCall();

	// strategies
	void setPrintStrategy(PrintStrategies* strategy);
	void printStrategy(int code_station = 0, const string& code_line = "") const;

	void setLoadStrategy(LoadStrategies* strategy);
	void loadStrategy(const string& file_path);

	void setPathStrategy(PathStrategies* strategy);
	void findPath(int start, int end);

private:
	PublicTransport() : Graph(), current_bus_line_(nullptr), print_strategy_(nullptr), load_strategy_(nullptr), path_strategy_(nullptr) {};

	list<BusLine*> bus_lines_;                 // list of all bus lines 
	BusLine* current_bus_line_;                // pointer to a current bus line
	PrintStrategies* print_strategy_;          // pointer to a print strategy
	PathStrategies* path_strategy_;            // pointer to a path strategy
	LoadStrategies* load_strategy_;            // pointer to a load strategy

	static int function_new_station_on_line_calls_;

};

#endif