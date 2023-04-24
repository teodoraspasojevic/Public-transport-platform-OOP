#include "PathStrategies.h"

vector<vector<BusStation*>> PathStrategies::findAllPaths(PublicTransport* public_transport, int start, int end) {
	/// <summary>
	/// Finds all paths from one station to the other in graph.
	/// </summary>

	vector<vector<BusStation*>> final_paths; // vector in which we store final paths
	queue<vector<BusStation*>> queue;        // queue in which we store paths we create while finding final paths
	vector<BusStation*> path;                // vector in which we store current paths

	path.push_back(public_transport->findStationByCode(start));
	queue.push(path);

	while (!queue.empty()) {

		path = queue.front();
		queue.pop();
		BusStation* last = path[path.size() - 1];
		public_transport->setCurrentStation(last->getCode());

		// if we found path that ends with asked station, we add it to queue with final paths
		if (last->getCode() == end)
			final_paths.push_back(path);

		// if we still haven't found the path we create new paths, by adding next stations of last in path, and add new paths to queue
		for (auto curr : public_transport->getNextStations()) {
			if (!isVisited(curr, path)) {
				vector<BusStation*> new_path(path);
				new_path.push_back(curr);
				queue.push(new_path);
			}
		}
	}
	return final_paths;
}

bool PathStrategies::isVisited(BusStation* station, vector<BusStation*> path) {

	for (auto curr : path) {
		if (*curr == *station) return true;
	}
	return false;
}

void PathStrategies::printPath(PublicTransport* public_transport, vector<BusStation*> path, const string& file_path) {

	fstream output_file;
	output_file.open(file_path);
	bool first = true;
	string old_line = "";
	vector<BusStation*>::iterator it_start = path.begin();

	set<string> common;
	for (vector<BusStation*>::iterator it = path.begin(); it != path.end(); it++) {
		set<string> old_common = common;
		if (it != path.end()-1) {
			for (set<string>::iterator curr = common.begin(); curr != common.end(); ) {
				set<string> s = (*(it + 1))->getBusLinesCodes();
				public_transport->setCurrentBusLine(*curr);
				if (s.find(*curr) == s.end() || !public_transport->getCurrentLine()->areStationsNextToEachOther(*it, *(it+1))) {
					curr = common.erase(curr);
				}
				else curr++;
				if (common.empty()) break;
			}
		}
		if ((common.empty() && it != path.begin())|| it == path.end()-1) {
			string line ="->" + *old_common.begin();
			if (first) first = false;
			else line = '\n'+old_line + line;
			old_line = *old_common.begin();
			printOneLine(it_start, it, line, file_path);
			if (it != path.end() - 1) common = public_transport->findCommonLinesForStations(*it, *(it + 1));
		}
		if (it == path.begin()) common = public_transport->findCommonLinesForStations(*it, *(it + 1));
	}

	output_file.close();
}

void PathStrategies::printOneLine(vector<BusStation*>::iterator& it_start, vector<BusStation*>::iterator it_end, const string& line, const string& file_path) {

	fstream file(file_path, ios::app);
	file << line << endl;
	while (true) {
		if (it_start == it_end) {
			file << (*it_start)->getCode();
			break;
		}
		else file << (*it_start)->getCode() << " ";
		it_start++;
	}
}

void PathWithMinStations::findPath(PublicTransport* public_transport, int start, int end) {
	/// <summary>
	/// Finds path with minimum number of stations between two stations.
	/// </summary>

	try {
		// setting current stations so we can check if they exist, and leaving it on station form which we start search
		public_transport->setCurrentStation(end);
		string end_name = public_transport->getCurrentStation()->getName();
		public_transport->setCurrentStation(start);
		string start_name = public_transport->getCurrentStation()->getName();

		if (start_name == end_name) {
			throw new SameStation();
		}

		vector<vector<BusStation*>> paths = findAllPaths(public_transport, start, end);

		if (!paths.empty()) {
			stringstream s;
			s << "putanja_" << start << "_" <<end << ".txt";
			
			vector<BusStation*> min = findPathWithMinStations(paths);
			printPath(public_transport, min, s.str());
		}
		else {
			cout << "Ne postoji putanja kojom se moze doci od stanice " << start << " do stanice " << end << '.' << endl << endl;
			throw new NoPath();
		}
	}
	catch (NoStationWithThatCode* e) {
		cout << e->what() << " (sifre: " << start << ", " << end << ") Molimo Vas, ponovo izaberite opciju 4." << endl << endl;
		throw e;
	}
	public_transport->resetCurrentStation();
}

vector<BusStation*> PathWithMinStations::findPathWithMinStations(vector<vector<BusStation*>> paths) {
	/// <summary>
	/// Finds path with the least number of stations, from all paths.
	/// </summary>
	
	vector<BusStation*> min;
	for (auto it = paths.begin(); it != paths.end(); it++) {
		if (min.empty()) min = *it;
		else if ((*it).size() < min.size()) min = *it;
	}
	return min;
}

void PathWithMinLines::findPath(PublicTransport* public_transport, int start, int end) {
	/// <summary>
	/// Finds path with minimum number of changes of line between two stations.
	/// </summary>

	try {
		// setting current stations so we can check if they exist, and leaving it on station form which we start search
		public_transport->setCurrentStation(end);
		string end_name = public_transport->getCurrentStation()->getName();
		public_transport->setCurrentStation(start);
		string start_name = public_transport->getCurrentStation()->getName();

		if (start_name == end_name) {
			throw new SameStation();
		}

		vector<vector<BusStation*>> paths = findAllPaths(public_transport, start, end);

		if (!paths.empty()) {

			stringstream s;
			s << "putanja_" << start << "_" << end << ".txt";

			vector<BusStation*> min = findPathWithMinTransfers(public_transport, paths);
			printPath(public_transport, min, s.str());
		}
		else {
			cout << "Ne postoji putanja kojom se moze doci od stanice " << start << " do stanice " << end << '.' << endl << endl;
			throw new NoPath();
		}
	}
	catch (NoStationWithThatCode* e) {
		cout << e->what() << " (sifre: " << start << ", " << end << ") Molimo Vas, ponovo izaberite opciju 4." << endl << endl;
		throw e;
	}
	public_transport->resetCurrentStation();
}

vector<BusStation*> PathWithMinLines::findPathWithMinTransfers(PublicTransport* public_transport, vector<vector<BusStation*>> paths) {

	vector<BusStation*> min_path = paths.front();
	int min = countTransfers(public_transport, min_path);
	for (auto it = paths.begin() + 1; it != paths.end(); it++) {
		int count = countTransfers(public_transport, *it);
		if (count < min) {
			min = count;
			min_path = *it;
		}
	}
	return min_path;
}

int PathWithMinLines::countTransfers(PublicTransport* public_transport, vector<BusStation*> path) {

	int counter = 0;
	set<string> common;
	for (vector<BusStation*>::iterator it = path.begin(); it != path.end()-1; it++) {
		for (set<string>::iterator curr = common.begin(); curr != common.end(); ) {
			set<string> s = (*(it + 1))->getBusLinesCodes();
			if (s.find(*curr) == s.end()) {
				curr = common.erase(curr);
			}
			else curr++;
			if (common.empty()) break;
		}
		if (common.empty() && it != path.begin()) {
			counter++;
			common = public_transport->findCommonLinesForStations(*it, *(it + 1));
		}
		if (it==path.begin()) common = public_transport->findCommonLinesForStations(*it, *(it + 1));
	}
	return counter;
}
