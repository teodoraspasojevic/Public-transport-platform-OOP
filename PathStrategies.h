#ifndef PATH_STRATEGIES_H
#define PATH_STRATEGIES_H

#include "PublicTransport.h"

#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <queue>
using namespace std;

class PublicTransport;

class PathStrategies {
/// <summary>
/// Abstract class that abstracts all strategies for finding path between two stations needed in class PublicTransport.
/// </summary>
public:
	virtual void findPath(PublicTransport* public_transport, int start, int end) = 0;
	vector<vector<BusStation*>> findAllPaths(PublicTransport* public_transport, int start, int end);
	bool isVisited(BusStation* station, vector<BusStation*> path);
	void printPath(PublicTransport* public_transport, vector<BusStation*> path, const string& file_path);
	void printOneLine(vector<BusStation*>::iterator& it_start, vector<BusStation*>::iterator it_end ,const string& line, const string& file_path);
};

class PathWithMinStations : public PathStrategies {
	/// <summary>
	/// Strategy used for finding any path between two stations, if there is one.
	/// </summary>
public:
	void findPath(PublicTransport* public_transport, int start, int end) override;
	vector<BusStation*> findPathWithMinStations(vector<vector<BusStation*>> paths);
};

class PathWithMinLines : public PathStrategies {
	/// <summary>
	/// Strategy used for finding any path between two stations, if there is one.
	/// </summary>
public:
	void findPath(PublicTransport* public_transport, int start, int end) override;
	vector<BusStation*> findPathWithMinTransfers(PublicTransport* public_transport, vector<vector<BusStation*>> paths);
	int countTransfers(PublicTransport* public_transport, vector<BusStation*> path);
};

#endif