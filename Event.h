#pragma once
#include<iostream>

using namespace std;

class Event {
private:
	const int eventId;
	string eventName = "tbd";
	string location = "tbd";
	int* seatsPerRow = nullptr;
	int rows = 0;

	static int noEvents;
	const static int MIN_ACCEPTED_NAME_LENGTH;
	const static int MIN_ACCEPTED_LOCATION_LENGTH;

public:
	Event() : eventId(++noEvents) {

	}

	Event(string name, string loc, int* seatsRow, int row) : eventId(++noEvents) {
		this->setName(name);
		this->setLocation(loc);
		this->setSeats(seatsRow, row);
	}

	Event(const Event& e) : eventId(e.eventId) {
		this->eventName = e.eventName;
		this->location = e.location;
		if (e.seatsPerRow != nullptr) {
			this->seatsPerRow = new int[e.rows];
			for (int i = 0; i < e.rows; i++) {
				this->seatsPerRow[i] = e.seatsPerRow[i];
			}
		}
		this->rows = e.rows;
	}

	~Event() {
		delete[] this->seatsPerRow;
	}

	string getName() {
		return this->eventName;
	}

	string getLocation() {
		return this->location;
	}

	int getRows() {
		return this->rows;
	}

	int* getSeatsPerRow() {
		if (this->seatsPerRow == nullptr) {
			return nullptr;
		}
		int* copy = new int[this->rows];
		for (int i = 0; i < this->rows; i++) {
			copy[i] = this->seatsPerRow[i];
		}
		return copy;
	}

	int getId() {
		return this->eventId;
	}

	void setName(string name) {
		if (name.length() < MIN_ACCEPTED_NAME_LENGTH) {
			throw "name too short";
		}
		this->eventName = name;
	}

	void setLocation(string loc) {
		if (loc.length() < MIN_ACCEPTED_LOCATION_LENGTH) {
			throw "location too short";
		}
		this->location = loc;
	}

	void setSeats(int* seatRow, int row) {
		if (seatRow == nullptr) {
			throw "provide valid array";
		}
		delete[] this->seatsPerRow;
		this->seatsPerRow = new int[row];
		for (int i = 0; i < row; i++) {
			this->seatsPerRow[i] = seatRow[i];
		}
		this->rows = row;
	}

	void addRow(int row) {
		int* rowz = new int[this->rows + 1];
		for (int i = 0; i < this->rows; i++) {
			rowz[i] = this->seatsPerRow[i];
		}
		rowz[this->rows] = row;
		delete[] this->seatsPerRow;
		this->seatsPerRow = rowz;
		this->rows++;
	}

	int getTotalSeats() {
		int total = 0;
		for (int i = 0; i < this->rows; i++) {
			total += this->seatsPerRow[i];
		}
		return total;
	}

	explicit operator int() {
		return this->getTotalSeats();
	}

	int operator()(int indexStart, int indexEnd) {
		if (indexStart < 0 || indexEnd < 0 || indexStart >= this->rows || indexEnd >= this->rows || indexEnd < indexStart) {
			throw "invalid indexes";
		}
		int sum = 0;
		for (int i = indexStart; i <= indexEnd; i++) {
			sum += this->seatsPerRow[i];
		}
		return sum;
	}

	void operator=(const Event& e)
	{
		if (this == &e) {
			return;
		}

		this->eventName = e.eventName;
		this->location = e.location;
		this->rows = e.rows;
		delete[] this->seatsPerRow;
		this->seatsPerRow = new int[e.rows];
		for (int i = 0; i < e.rows; i++) {
			this->seatsPerRow[i] = e.seatsPerRow[i];
		}
	}
};

int Event::noEvents = 0;
const int Event::MIN_ACCEPTED_NAME_LENGTH = 5;
const int Event::MIN_ACCEPTED_LOCATION_LENGTH = 7;

void operator<<(ostream& out, Event e) {
	out << endl << "Event info:";
	out << endl << "ID: " << e.getId();
	out << endl << "Event name: " << e.getName();
	out << endl << "Event location: " << e.getLocation();
	out << endl << "Number of rows: " << e.getRows();
	if (e.getRows() > 0) {
		int* seats = e.getSeatsPerRow();
		out << endl << "Seats per row: ";
		for (int i = 0; i < e.getRows(); i++) {
			out << seats[i] << " ";
		}
	}
	else {
		return;
	}
}

void operator>>(istream& in, Event& e) {
	cout << endl << "Enter name: ";
	string input;
	in >> input;
	e.setName(input);
	cout << endl << "Enter location: ";
	in >> input;
	e.setLocation(input);
	cout << "Enter number of rows: ";
	int number;
	in >> number;
	int* rows = new int[number];
	delete[] e.getSeatsPerRow();
	cout << "Enter seats per row: ";
	for (int i = 0; i < number; i++) {
		in >> rows[i];
	}
	e.setSeats(rows, number);
}

