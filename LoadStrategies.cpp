#include "LoadStrategies.h"

void LoadStations::load(PublicTransport* public_transport, const string& file_path) {
	///<summary>
	/// Loading information about stations from file.
	///</summary>

	// opening file 
	ifstream input_file;
	input_file.open(file_path);

	try {
		// if file is not opened correctly
		if (!input_file.is_open()) throw new FileNotOpenedCorrectly();

		int code;
		string code_str;
		string name;

		// we read every line of the file and add station to the graph
		while (input_file) {
			try {
				getline(input_file, code_str, ' ');   // read code as a string
				code = stoi(code_str);                // converting string to int, throw exception if it cannot get int out of string
				input_file >> ws;                     // reading white spaces
				getline(input_file, name);            // reading name
				input_file >> ws;                     // reading white spaces

				public_transport->addMainStation(new BusStation(code, name));
			}
			catch (const std::invalid_argument& e) {
				cout << "Error: " << code_str << " nije validna sifra stanice. Nastavlja se sa daljim ucitavanjem stajalista.\n\n";
				string extra;
				getline(input_file, extra);
			}
			catch (StationAlreadyExists* e) {
				cout<<e->what()<< " Nastavlja se sa daljim ucitavanjem stajalista.\n\n";
				delete e;
			}
		}
	}
	catch (FileNotOpenedCorrectly* e) {
		input_file.close();
		cout << e->what() << " Molimo Vas da ponovo izaberete opciju 1." << endl << endl;
		throw e;
	}

	input_file.close();
}

void LoadLines::load(PublicTransport* public_transport, const string& file_path) {
	///<summary>
	/// Loading information about lines from file.
	///</summary>

	// opening file 
	ifstream input_file;
	input_file.open(file_path);

	try {
		// if file is not opened correctly
		if (!input_file.is_open()) throw new FileNotOpenedCorrectly();

		string code;
		string direction_A;
		string direction_B;

		// we read every line of the file, add line to the list and see which stations are next to eachother
		while (input_file) {

			getline(input_file, code, ' ');
			input_file >> ws; // reading white spaces
			getline(input_file, direction_A, '#');
			getline(input_file, direction_B);
			input_file >> ws; // reading white spaces

			try { if (public_transport->chechIfThereIsLine(code)) throw new LineAlreadyExists(); }
			catch (LineAlreadyExists* e) {
				cout << e->what() << " (sifra ponovljene linije: " << code << ") Nastavlja se sa daljim ucitavanjem linija.\n\n";
				delete e;
				continue;
			}
			BusLine* line = new BusLine(code);
			parsDirections(public_transport, direction_A, line, 'A');
			public_transport->resetNewStationFunctionCall();
			parsDirections(public_transport, direction_B, line, 'B');
			public_transport->resetNewStationFunctionCall();
			public_transport->resetCurrentStation();
			public_transport->resetCurrentBusLine();
			public_transport->addBusLine(line);
			public_transport->sortLines();
		}
	}
	catch (FileNotOpenedCorrectly* e) {
		input_file.close();
		cout << e->what() << " Molimo Vas da ponovo izaberete opciju 1." << endl << endl;
		throw e;
	}

	input_file.close();
}

void LoadStrategies::parsDirections(PublicTransport* public_transport, const string& direction, BusLine* line, char direction_char) {
	///<summary>
	/// Parses the whole direction of a line.
	///</summary>
	
	string station_code = "";
	int i = 0;

	for (; i<= direction.length(); i++) {
		try {
			switch (direction[i]) {
				// case when we read one station code
			case ' ': case '#': case '\0': {
				// makes int out of string
				int code = stoi(station_code);
				station_code = "";
				public_transport->newStationOnALine(line, direction_char, code);
				break;
			}
			default: {
				station_code += direction[i];
				break;
			}
			}
		}
		catch (const std::invalid_argument& e) {
			cout << "Error: " << station_code << " nije validna sifra stanice. Nastavlja se sa daljim ucitavanjem stajalista na liniji.\n\n";
			moveToNextStation(direction, i);
			station_code = "";
		}
	}
}

void LoadStrategies::moveToNextStation(const string& str, int& i) {
	/// <summary>
	/// Moves string iterator to the position of code of the next line in direction.
	/// </summary>

	while ((str[i]) != ' ' && (str[i]) != '#' && i != str.length()) i++;
}
