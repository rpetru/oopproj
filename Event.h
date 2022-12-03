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
	Event() : eventId(-1) {

	}

	Event(string name, string loc, int* seatsRow, int row) : eventId(++noEvents) {
		this->setName(name);
		this->setLocation(loc);
		this->setSeats(seatsRow, row);
	}

	Event(const Event& e) : eventId(e.eventId) {
		this->eventName = e.eventName;
		this->location = e.location;
		this->seatsPerRow = new int[e.rows];
		for (int i = 0; i < e.rows; i++) {
			this->seatsPerRow[i] = e.seatsPerRow[i];
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
		int* copy = new int[this->rows];
		for (int i = 0; i < this->rows; i++) {
			copy[i] = this->seatsPerRow[i];
		}
		return copy;
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

	//freeRow
	//addRow
	//editRow
};

int Event::noEvents = 0;
const int Event::MIN_ACCEPTED_NAME_LENGTH = 5;
const int Event::MIN_ACCEPTED_LOCATION_LENGTH = 7;

