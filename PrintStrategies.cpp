#include "PrintStrategies.h"

void PrintStation::print( PublicTransport* public_transport, int code_station, const string& code_line) const {
	/// <summary>
	/// Prints basic information about station.
	/// </summary>

	try {
		// setting current station to one which we want to print
		public_transport->setCurrentStation(code_station);
		// opening file stajaliste_code_station.txt
		ofstream output_file;
		output_file.open("stajaliste_" + to_string(code_station) + ".txt");
		output_file << public_transport->getCurrentStation()->printCodeAndName() << " ["
			<< public_transport->getCurrentStation()->printLinesStoppingOnThisStation() << ']';
		// closing file and reseting current station
		output_file.close();
		public_transport->resetCurrentStation();
	}
	catch (NoStationWithThatCode* e) {
		cout << e->what() << " (sifra: " << code_station << ") Molimo Vas, ponovo izaberite opciju 1." << endl << endl;
		throw e;
	}
}

void PrintLine::print( PublicTransport* public_transport, int code_station, const string& code_line) const {
	/// <summary>
	/// Prints basic information about line.
	/// </summary>
	
	try {
		// setting current line to one which we want to print
		public_transport->setCurrentBusLine(code_line);
		// opening file linija_code_line.txt
		ofstream output_file;
		output_file.open("linija_" + code_line + ".txt");
		output_file << public_transport->getCurrentLine()->print();
		// closing file and reseting current station
		output_file.close();
		public_transport->resetCurrentBusLine();
	}
	catch (NoLineWithThatCode* e) {
		cout << e->what() << " (sifra: " << code_line << ") Molimo Vas, ponovo izaberite opciju 2." << endl << endl;
		throw e;
	}
}

void PrintLineStatistics::print(PublicTransport* public_transport, int code_station, const string& code_line) const {
	/// <summary>
	/// Prints statistics of a line.
	/// </summary>

	try {
		// setting current line to one which we want to print
		public_transport->setCurrentBusLine(code_line);
		// opening file linija_code_line.txt
		ofstream output_file;
		output_file.open("statistika_" + code_line + ".txt");
		
		output_file << code_line << endl;
		public_transport->findLinesWithCommonStations(code_line);
		bool first = true;
		for (auto curr : public_transport->getBusLines()) {
			if (curr->getCounter() > 0) {
				if (first) {
					output_file  << curr->getCode();
					first = false;
				}
				else output_file << ' ' << curr->getCode();
			}
		}
		if (first) output_file <<"Nijedna linija ne staje na istim stajalistima kao trazena." <<endl<<endl;
		else {
			output_file << endl;
			// finding one with biggest number of common stations
			first = true;
			vector<BusLine*> max = public_transport->findLineWithMostSameStations();
			for (auto curr : max) {
				if (first) { output_file << curr->getCode(); first = false; }
				else output_file << ", " << curr->getCode();
			}
		}
		// closing file and reseting current station
		output_file.close();
		public_transport->resetCurrentBusLine();
		for (auto curr : public_transport->getBusLines()) curr->resetCounter();
	}
	catch (NoLineWithThatCode* e) {
		cout << e->what() << " (sifra: " << code_line << ") Molimo Vas, ponovo izaberite opciju 3." << endl << endl;
		throw e;
	}
}
