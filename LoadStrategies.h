#ifndef LOAD_STRATEGIES_H
#define LOAD_STRATEGIES_H

#include "Exception.h"
#include "PublicTransport.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class PublicTransport;

class LoadStrategies {
/// <summary>
/// Abstract class that abstracts all load strategies needed in class PublicTransport
/// </summary>
public:
	virtual void load(PublicTransport* public_transport, const string& file_path) = 0;
protected:
	void parsDirections(PublicTransport* public_transport, const string& direction, BusLine* line, char direction_char);
	void moveToNextStation(const string& str, int& it);
	
};

class LoadStations : public LoadStrategies {
/// <summary>
/// Strategy for loading bus stations.
/// </summary>
public:
	void load(PublicTransport* public_transport, const string& file_path) override;
};

class LoadLines : public LoadStrategies {
/// <summary>
/// Strategy for loading bus lines.
/// </summary>
public:
	void load(PublicTransport* public_transport, const string& file_path) override;
};


#endif