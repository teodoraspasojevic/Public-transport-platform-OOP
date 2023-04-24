#ifndef PRINT_STRATEGIES_H
#define PRINT_STRATEGIES_H

#include "PublicTransport.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class PublicTransport;

class PrintStrategies {
/// <summary>
/// Abstract class that abstracts all print strategies needed in class PublicTransport.
/// </summary>
public:
	virtual void print( PublicTransport* public_transport, int code_station=0, const string& code_line="") const = 0;
};

class PrintStation : public PrintStrategies {
/// <summary>
/// Strategy used for printig information about bus stations.
/// </summary>
public:
	void print( PublicTransport* public_transport, int code_station = 0, const string& code_line = "") const override;
};

class PrintLine : public PrintStrategies {
	/// <summary>
	/// Strategy used for printig information about bus line.
	/// </summary>
public:
	void print( PublicTransport* public_transport, int code_station = 0, const string& code_line = "") const override;
};

class PrintLineStatistics : public PrintStrategies {
	/// <summary>
	/// Strategy used for printig statictis of a bus line.
	/// </summary>
public:
	void print(PublicTransport* public_transport, int code_station = 0, const string& code_line = "") const override;
};

#endif
