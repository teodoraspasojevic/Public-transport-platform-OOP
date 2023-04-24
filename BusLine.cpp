#include "BusLine.h"


BusLine::BusLine(const BusLine& line) {
	this->code_ = line.code_;
	for (auto curr : line.direction_A_) {
		this->direction_A_.push_back(new BusStation(*curr));
	}
	for (auto curr : line.direction_B_) {
		this->direction_B_.push_back(new BusStation(*curr));
	}
}

BusLine::~BusLine() {
	for (auto curr : direction_A_) delete curr;
	direction_A_.clear();
	for (auto curr : direction_B_) delete curr;
	direction_B_.clear();
	code_ = "";
	count_of_a_station_ = 0;
}

string BusLine::getCode() const {
	return code_;
}

BusStation* BusLine::getFirstStation() const {
	return direction_A_.front();
}

BusStation* BusLine::getLastStation() const {
	return direction_A_.back();
}

BusStation* BusLine::findStationOnDirection(int code, char direction) {
	/// <summary>
	/// Looks if there is already a bus station with asked code in asked direction.
	/// </summary>
	/// <returns> returns found station, otherwise nullptr </returns>
	
	if (direction == 'A') {
		for (auto curr : direction_A_) {
			if (curr->getCode() == code)
				return new BusStation(*curr);
		}
	}
	else {
		for (auto curr : direction_B_) {
			if (curr->getCode() == code)
				return new BusStation(*curr);
		}
	}
	return nullptr;
}

bool BusLine::areStationsNextToEachOther(BusStation* b1, BusStation* b2) {

	for (auto curr = direction_A_.begin(); curr != direction_A_.end() - 1; curr++) {
		if (**curr == *b1 && **(curr + 1) == *b2) return true;
	}
	for (auto curr = direction_B_.begin(); curr != direction_B_.end() - 1; curr++) {
		if (**curr == *b1 && **(curr + 1) == *b2) return true;
	}
	return false;
}

vector<BusStation*> BusLine::getDirectionA() const {
	return direction_A_;
}

vector<BusStation*> BusLine::getDirectionB() const {
	return direction_B_;
}

int BusLine::getCounter() const {
	return count_of_a_station_;
}

void BusLine::addStationA(BusStation* station) {
	BusStation* found_station = findStationOnDirection(station->getCode(), 'A');
	if (found_station) {
		delete found_station;
		throw new StationAlreadyExists();
	}
	else {
		delete found_station;
		direction_A_.push_back(station);
	}
}

void BusLine::addStationB(BusStation* station) {
	BusStation* found_station = findStationOnDirection(station->getCode(), 'B');
	if (found_station) {
		delete found_station;
		throw new StationAlreadyExists();
	}
	else {
		delete found_station;
		direction_B_.push_back(station);
	}
}

void BusLine::addBusLineCode(const string& code_line, int code) {
	/// <summary>
	/// Adds code of the line "code_line" to all stations on this line
	/// </summary>

	for (auto curr : direction_A_) {
		if (curr->getCode() == code) {
			curr->addBusLineCode(code_line);
			break;
		}
	}
	for (auto curr : direction_B_) {
		if (curr->getCode() == code) {
			curr->addBusLineCode(code_line);
			break;
		}
	}
}

string BusLine::print() const {
	/// <summary>
	/// Returns string to be printed in print strategies.
	/// Format: code first_station->last_station'\n'station1_code station1_name'\n'...
	/// </summary>

	// first we add line code, first and last bus station
	string output = "";
	output += this->code_;
	output += ' ';
	output += this->getFirstStation()->getName();
	output += "->";
	output += this->getLastStation()->getName();
	output += '\n';

	// then we add all stations in both directions
	output += this->printAllStationsOnThisLine(direction_A_);
	output += '\n';
	output += this->printAllStationsOnThisLine(direction_B_);
	return output;
}

string BusLine::printAllStationsOnThisLine(vector<BusStation*> direction) const {
	/// <summary>
	/// Returns string with all stations on this line in one directions.
	/// Format: station1_code station1_name'\n'...
	/// </summary>
	string str ="";

	for (BusStation* station : direction) {
		str += station->printCodeAndName();
		if (station!=direction.back()) str += '\n';
	}

	return str;
}

void BusLine::countStation() {
	count_of_a_station_++;
}

void BusLine::resetCounter() {
	count_of_a_station_ = 0;
}
