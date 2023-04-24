#ifndef GRAPH_H
#define GRAPH_H

#include "BusStation.h"
#include "Exception.h"

#include <list>
#include <map>
using namespace std;

typedef map<BusStation*, list<BusStation*>>::iterator graph_it;

class Graph {
/// <summary>
/// Implementation of structure graph in which we will store loaded bus station.
/// It will be implemented as a map in which key is main station we add, and with it we will save vector of stations next to her.
/// </summary>
public:
	Graph() = default;
	Graph(const Graph&) = delete;
	Graph& operator=(const Graph&) = delete;
	~Graph();

	BusStation* getCurrentStation() const;
	int getCounter() const { return main_stations_.size(); }
	list<BusStation*> getNextStations() const { return current_station_->second; }

	BusStation* findStationByCode(int code) const;

	void setCurrentStation(int code);
	void resetCurrentStation();

	void addMainStation(BusStation* bus_station);
	void addNextStation(BusStation* bus_station);

protected:
	map<BusStation*, list<BusStation*>> main_stations_;   // map with all stations
	graph_it current_station_;                            // iterator to a current station in map
};

#endif 
