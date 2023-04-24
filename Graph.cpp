#include "Graph.h"

Graph::~Graph() {
	for (auto curr : main_stations_) {
		delete curr.first;
		for (auto curr2 : curr.second) delete curr2;
	}
	main_stations_.clear();
}

BusStation* Graph::getCurrentStation() const {
	return current_station_->first;
}

BusStation* Graph::findStationByCode(int code) const {
	/// <summary>
	/// Finds station by code and returns it if it is found, otherwise returns nullptr.
	/// </summary>

	for (auto curr : main_stations_) {
		if (curr.first->getCode() == code)
			return curr.first;
	}
	return nullptr;
}

void Graph::setCurrentStation(int code) {
	/// <summary>
	/// Sets current on station by code in parameter.
	/// </summary>
	/// <param name="code">we are looking for station among nodes of the graph with this code</param>
	
	auto it = main_stations_.begin();
	for (; it != main_stations_.end(); it++) {
		if (it->first->getCode() == code) {
			current_station_ = it;
			break;
		}
	}
	if (it==main_stations_.end()) throw new NoStationWithThatCode();
}

void Graph::resetCurrentStation() {
	current_station_ = main_stations_.begin();
}

void Graph::addMainStation(BusStation* bus_station) {
	/// <summary>
	/// Adds Station (node) to the graph.
	/// </summary>
	/// <param name="bus_station"> station that we are adding </param>
	
	BusStation* station = findStationByCode(bus_station->getCode());
	if (station) {
		delete station;
		throw new StationAlreadyExists();
	}
	else {
		delete station;
		list<BusStation*> l;
		main_stations_.insert(pair<BusStation*, list<BusStation*>>(bus_station, l));
	}
}

void Graph::addNextStation(BusStation* bus_station) {
	/// <summary>
	/// Adds station next to station stored in current head.
	/// </summary>
	
	BusStation* station = nullptr;
	for (auto curr : current_station_->second) {
		if (*curr == *bus_station) {
			station = curr;
			break;
		}
	}
	if (!station) current_station_->second.push_back(bus_station);
	else delete bus_station;
	station = nullptr;
	delete station;
}
