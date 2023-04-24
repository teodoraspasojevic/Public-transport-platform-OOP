#include "BusStation.h"

BusStation::BusStation(BusStation& bus) {
	code_ = bus.code_;
	name_ = bus.name_;
	for (auto curr: bus.bus_lines_codes_) {
		this->bus_lines_codes_.insert(curr);
	}
}

BusStation::~BusStation() {
	bus_lines_codes_.clear();
}

bool operator==(const BusStation& s1, const BusStation& s2) {
	return s1.code_ == s2.code_;
}

bool operator!=(const BusStation& s1, const BusStation& s2) {
	return s1.code_ != s2.code_;
}

int BusStation::getCode() const {
	return code_;
}

string BusStation::getName() const {
	return name_;
}

bool BusStation::isThereThisLine(const string& code_line) const {
	for (auto curr : bus_lines_codes_) {
		if (curr == code_line) return true;
	}
	return false;
}

set<string> BusStation::getBusLinesCodes() const {
	return bus_lines_codes_;
}

string BusStation::codeToString() const {
	return to_string(code_);
}

string BusStation::printCodeAndName() const {
	/// <summary>
	/// Return string with station name and code to be printed.
	/// </summary>
	
	return this->codeToString()+' '+this->name_;
}

string BusStation::printLinesStoppingOnThisStation() const{
	/// <summary>
	/// Returns string with lines stopping on this station.
	/// Format: line1_code' 'line2_code' '...
	/// </summary>
	/// <returns></returns>
	string str = "";

	for (auto curr : bus_lines_codes_) {
		if (!str.empty()) str += ' ';
		str += curr;
	}
	return str;
}

void BusStation::addBusLineCode(const string& code) {
	/// <summary>
	/// Adds code of the line that passes through this station in alphabetical order.
	/// </summary>
	
	bool is_inserted = false;
	bool already_there = false;

	// chech if code is already added
	for (auto curr : bus_lines_codes_) {
		if (curr == code) {
			already_there = true;
			break;
		}
	}
	if (!already_there) {
		for (set<string>::const_iterator curr = bus_lines_codes_.begin(); curr != bus_lines_codes_.end(); curr++) {
			if ((*curr).compare(code) >= 0) {
				is_inserted = true;
				bus_lines_codes_.insert(curr, code); // if string code is alphabetically before string *curr, than we insert it before iterator curr
				break;
			}
		}
		if (!is_inserted) bus_lines_codes_.insert(code); // if code is after all strings in vector
	}
}
