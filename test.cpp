#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "BusStation.h"
#include "BusLine.h"
#include "Graph.h"
#include "PublicTransport.h"

#include <fstream>
#include <iostream>
using namespace std;

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int switcher=0;
	bool stations_read = false;

	while (true) {
		if (switcher == 0) cout << "Dobro dosli u simulator mreze gradskog prevoza. ";
		cout << "Molimo Vas, odaberite opciju:" << endl
			<< "1. Ucitavanje podataka o mrezi gradskog prevoza\n0. Kraj rada" << endl << endl;
		cin >> switcher;
		cout << endl;
		if (switcher == 0) { cout << "Zavrseno sa radom. Pozdrav." << endl; break; }
		else if (switcher == 1) { 
			// loading stations
			if (!stations_read) {
				cout << "Molimo Vas, unesite putanju do fajla sa stajalistima:" << endl << endl;
				string file_path_stations;
				cin >> file_path_stations;
				cout << endl;
				PublicTransport::getInstance().setLoadStrategy(new LoadStations());
				try { PublicTransport::getInstance().loadStrategy(file_path_stations); }
				catch (FileNotOpenedCorrectly* e) { delete e; continue; }
				stations_read = true;
			}

			// loading lines
			cout << "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza:" <<endl<< endl;
			string file_path_lines;
			cin >> file_path_lines;
			cout << endl;
			PublicTransport::getInstance().setLoadStrategy(new LoadLines());
			try { PublicTransport::getInstance().loadStrategy(file_path_lines); }
			catch (FileNotOpenedCorrectly* e) { delete e; continue; }

			cout << "Mreza gradskog prevoza je uspesno ucitana." << endl<<endl;
			break;
		}
		else { cout << "Nepravilan unos. "; }
	}

	while (switcher != 0) {
		cout << "Molimo Vas, unesite jednu od opcija za dalji rad:" << endl
			<< "1. Prikaz informacija o stajalistu" << endl
			<< "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl
			<< "3. Prikaz statistickih informacija o liniji gradskog prevoza" << endl
			<< "4. Pronalazak putanje izmedju dva stajalista" << endl
			<< "0. Kraj rada" << endl<<endl;
		cin >> switcher;
		cout << endl;
		switch (switcher) {
		case 0: {
			cout << "Zavrseno sa radom. Pozdrav." << endl;
			break;
		}
		case 1: {
			int code;
			PublicTransport::getInstance().setPrintStrategy(new PrintStation());
			cout << "Molimo Vas, unesite oznaku stanice cije informacije zelite da ispisete:" << endl<<endl;
			cin >> code;
			cout << endl;
			try {
				PublicTransport::getInstance().printStrategy(code);
				cout << "Generisan je fajl stajaliste_" << code << ".txt sa informacijama o stajalistu sifre " << code << ".\n\n";
			}
			catch (exception* e) { delete e; }
			break;
		}
		case 2: {
			string code;
			PublicTransport::getInstance().setPrintStrategy(new PrintLine());
			cout << "Molimo Vas, unesite oznaku linije cije informacije zelite da ispisete:" << endl<<endl;
			cin >> code;
			cout << endl;
			try {
				PublicTransport::getInstance().printStrategy(-1, code);
				cout << "Generisan je fajl linija_" << code << ".txt sa osnovnim informacijama o liniji " << code << ".\n\n";
			}
			catch (exception* e) { delete e; }
			break;
		}
		case 3: {
			string code;
			PublicTransport::getInstance().setPrintStrategy(new PrintLineStatistics());
			cout << "Molimo Vas, unesite oznaku linije ciju statistiku zelite da ispisete:" << endl << endl;
			cin >> code;
			cout << endl;
			try {
				PublicTransport::getInstance().printStrategy(-1, code);
				cout << "Generisan je fajl statistika_" << code << ".txt sa statistickim informacijama o liniji " << code << ".\n\n";
			}
			catch (exception* e) { delete e; }
			break;
		}
		case 4: {
			int start, end;
			int path_switcher;
			cout << "Molimo Vas, unesite jednu od opcija za nalazenje putanje izmedju stajalista:" << endl
				<< "1. Pretraga bez filtera" << endl
				<< "2. Pretraga sa najmanjim brojem stajalista" << endl
				<< "3. Pretraga sa najmanjim brojem presedanaja" << endl<<endl;
			cin >> path_switcher;
			cout <<endl<< "Molimo Vas, unesite oznaku pocetnog stajalista: " << endl << endl;
			cin >> start;
			cout << endl;
			cout << "Molimo Vas, unesite oznaku krajnjeg stajalista: " << endl << endl;
			cin >> end;
			cout << endl;
			if (start == end) {
				cout << "Neuspesan unos. Pocetno i krajnje stajaliste su iste sifre. Molimo Vas, ponovo izaberite opciju 4." << endl << endl;
				break;
			}
			switch (path_switcher) {
			case 1: case 2: {
				PublicTransport::getInstance().setPathStrategy(new PathWithMinStations());
				break;
			}
			case 3: {
				PublicTransport::getInstance().setPathStrategy(new PathWithMinLines());
				break;
			}
			default: {
				cout << "Neuspesan unos. Molimo Vas, ponovo izaberite opciju 4." << endl << endl;
				break;
			}
			}
			if (path_switcher==1 || path_switcher == 2 || path_switcher == 3 ) {
				try {
					PublicTransport::getInstance().findPath(start, end);
					cout << "Generisan je fajl putanja_" << start <<'_'<<end<< ".txt sa nadjenom putanjom izmedju stajalista. " <<endl<<endl;
				}
				catch (SameStation* e) { cout << e->what() << endl << endl; delete e; }
				catch (exception* e) { delete e; }
			}
			break;
		}
		default: {
			cout << "Neuspesan unos. ";
			break;
		}
		}
	}
	
	return 0;
}