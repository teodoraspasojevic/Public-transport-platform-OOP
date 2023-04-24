#include "PublicTransport.h"

int PublicTransport::function_new_station_on_line_calls_=0;

PublicTransport::~PublicTransport() {
    delete print_strategy_;
    delete load_strategy_;
    delete path_strategy_;
    current_bus_line_ = nullptr;
    for (auto curr : bus_lines_) {
        delete curr;
    }
    bus_lines_.clear();
}

PublicTransport& PublicTransport::getInstance() {
    
    static PublicTransport instance;
    return instance;
}

list<BusLine*> PublicTransport::getBusLines() const {
    return bus_lines_;
}

BusLine* PublicTransport::getCurrentLine() const {
    return current_bus_line_;
}

void PublicTransport::addBusLine(BusLine* bus_line) {
    if (!chechIfThereIsLine(bus_line->getCode())) 
        bus_lines_.push_back(bus_line);
}

void PublicTransport::addLineCodeToAllStations(const string& code_line, int code_station) {
    /// <summary>
    /// Adds code of a line to every bus station with code "code_station" in graph.
    /// </summary>
    /// <param name="code_line">code of a line to be added</param>
    /// <param name="code_station">code of the stations to which we add line code</param>

    for (auto current = main_stations_.begin(); current != main_stations_.end(); current++ ) {
        if (current->first->getCode() == code_station) {
            current->first->addBusLineCode(code_line);
        }
        else {
            if (!current->second.empty()) {
                for (auto curr = current->second.begin(); curr != current->second.end(); curr++) {
                    if ((*curr)->getCode() == code_station) {
                       (*curr)->addBusLineCode(code_line);
                    }
                }
            }
        }
    }
    for (auto current : bus_lines_) {
        current->addBusLineCode(code_line, code_station);
    }
}

void PublicTransport::newStationOnALine(BusLine* line, char direction_char, int code) {
    /// <summary>
    /// Adds new station to line, adds code of a line to all stations with code "code" in graph
    /// and adds this station as next to the previous station.
    /// </summary>
    /// <param name="line"> line which code we add </param>
    /// <param name="direction_char"> direction in which we need to add station to line </param>
    /// <param name="code"> code of a station </param>
   
    function_new_station_on_line_calls_++;
    try {
        BusStation* station = findStationByCode(code);
        if (station) {
            if (function_new_station_on_line_calls_ > 1) {
                addNextStation(new BusStation(*station));
            }
            setCurrentStation(code);
            addLineCodeToAllStations(line->getCode(), code);
            // we make a copy of the current station
            BusStation* station_copy = new BusStation(*(getCurrentStation()));
            // we add copy of the read station to the required direction of this line
            try {
                if (direction_char == 'A') line->addStationA(station_copy);
                else line->addStationB(station_copy);
            }
            catch (StationAlreadyExists* e) {
                cout << e->what() << " (sifra duplirane stanice: " << code << ", sifra linije: " << line->getCode()
                    << ") Nastavljamo sa daljim ucitavanjem stanica duz linije." << endl << endl;
                delete e;
                delete station_copy;
            }
        }
        else {
            throw new NoStationWithThatCode();
        }
    }
    catch (NoStationWithThatCode* e) {
        cout << e->what() << " (trazena sifra: " << code << ") Nastavljamo sa daljim ucitavanjem stanica na liniji." << endl << endl;
        delete e;
    }
}

bool PublicTransport::chechIfThereIsLine(const string& code) {
    /// <summary>
    /// Checks if there is already bus line with that code.
    /// </summary>
    
    bool found;
    BusLine* line = findLineByCode(code);
    if (line) found = true;
    else found = false;
    delete line;
    return found;
}

BusLine* PublicTransport::findLineByCode(const string& code) {
    /// <summary>
    /// Finds line by code and returns copy of it if it is found, otherwise returns nullptr.
    /// </summary>

    for (auto curr : bus_lines_) {
        if (curr->getCode() == code) return new BusLine(curr->getCode());
    }
    return nullptr;
}

void PublicTransport::findLinesWithCommonStations(const string& code_line) {
    /// <summary>
    /// Counts appearances of common stations on line with code "code_line" and other lines.
    /// </summary>
    
    for (auto curr : main_stations_) {
        if (curr.first->isThereThisLine(code_line)) {
            for (auto current : curr.first->getBusLinesCodes()) {
                if (current != code_line) {
                    setCurrentBusLine(current);
                    getCurrentLine()->countStation();
                }
            }
        }
    }
}

vector<BusLine*> PublicTransport::findLineWithMostSameStations() {

    int max = 0;
    vector<BusLine*> max_str;
    // finding max number
    for (auto curr : bus_lines_) {
        if (max < curr->getCounter()) max = curr->getCounter();
    }
    for (auto curr : bus_lines_) {
        if (max == curr->getCounter()) max_str.push_back(curr);
    }
    return max_str;
}

void PublicTransport::sortLines() {
    bus_lines_.sort(BusLine::Comparator());
}

set<string> PublicTransport::findCommonLinesForStations(BusStation* b1, BusStation* b2) {
    set<string> common;

    for (auto curr :b1->getBusLinesCodes()) {
        setCurrentBusLine(curr);
        if (b2->isThereThisLine(curr) && getCurrentLine()->areStationsNextToEachOther(b1, b2)) common.insert(curr);
    }
    return common;
}

void PublicTransport::setCurrentBusLine(const string& line_code) {
    
    current_bus_line_ = nullptr;
    for (auto curr : bus_lines_) {
        if (curr->getCode() == line_code) {
            current_bus_line_ = curr;
            break;
        }
    }
    if (!current_bus_line_) throw new NoLineWithThatCode();
}

void PublicTransport::resetCurrentBusLine() {
    current_bus_line_ = nullptr;
}

void PublicTransport::resetNewStationFunctionCall() {
    function_new_station_on_line_calls_ = 0;
}

// strategies

void PublicTransport::setPrintStrategy(PrintStrategies* strategy) {

    if (print_strategy_)
        delete print_strategy_;
    print_strategy_ = strategy;
}

void PublicTransport::printStrategy(int code_station, const string& code_line) const {

    PublicTransport* public_transport = const_cast<PublicTransport*> (this);
    print_strategy_->print(public_transport, code_station, code_line);
}

void PublicTransport::setLoadStrategy(LoadStrategies* strategy) {

    if (load_strategy_)
        delete load_strategy_;
    load_strategy_ = strategy;
}

void PublicTransport::loadStrategy(const string& file_path) {
    
    PublicTransport* public_transport = const_cast<PublicTransport*> (this);
    load_strategy_->load(public_transport, file_path);
}

void PublicTransport::setPathStrategy(PathStrategies* strategy) {

    if (path_strategy_)
        delete path_strategy_;
    path_strategy_ = strategy;
}

void PublicTransport::findPath(int start, int end) {
    
    PublicTransport* public_transport = const_cast<PublicTransport*> (this);
    path_strategy_->findPath(public_transport, start, end);
}
