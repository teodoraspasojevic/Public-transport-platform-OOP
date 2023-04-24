#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
using namespace std;

class NoStationWithThatCode : public exception {
public: 
	NoStationWithThatCode() : exception("Error: Trazena je stanica koja nije uneta u sistem.") {};
};

class NoLineWithThatCode : public exception {
public:
	NoLineWithThatCode() : exception("Error: Trazena je linija koja nije uneta u sistem.") {};
};

class FileNotOpenedCorrectly : public exception {
public:
	FileNotOpenedCorrectly() : exception("Error: Fajl nije uspesno otvoren.") {};
};

class StationAlreadyExists : public exception {
public:
	StationAlreadyExists() : exception("Error: Postojao je duplikat jedne stanice.") {};
};

class LineAlreadyExists : public exception {
public:
	LineAlreadyExists() : exception("Error: Postojao je duplikat jedne linije.") {};
};

class NoPath : public exception {
public:
	NoPath() : exception("Error: Ne postoji putanja izmedju dva cvora.") {};
};

class SameStation : public exception {
public:
	SameStation() : exception("Uneli ste sifre iste stanice, samo za razlicite smerove. Predjite na drugu stranu ulice.:)") {};
};

#endif 

