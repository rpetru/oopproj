#pragma once
#include <iostream>

using namespace std;

enum TicketType {REGULAR, VIP, HIDDEN};

class Ticket {
private:
	const int ticketId;
	double price = 0;
	TicketType type = TicketType::REGULAR;
	bool valid = 0;

	static int noTickets;

public:
	Ticket() : ticketId(++noTickets) {

	}

	Ticket(double price, TicketType type, bool valid) : ticketId(++noTickets) {
		this->setPrice(price);
		this->setType(type);
		this->setValidation(valid);
	}

	Ticket(const Ticket& t) : ticketId(t.ticketId) {
		this->price = t.price;
		this->type = t.type;
		this->valid = t.valid;
	}

	~Ticket() {

	}

	double getPrice() {
		return this->price;
	}

	TicketType getType() {
		return this->type;
	}

	int getId() {
		return this->ticketId;
	}

	bool isValid() {
		return this->valid;
	}

	void setPrice(double price) {
		if (price < 0) {
			throw "invalid price";
		}
		this->price = price;
	}

	void setType(TicketType type) {
		if (type != TicketType::REGULAR && type != TicketType::VIP && type != TicketType::HIDDEN) {
			this->type = TicketType::REGULAR;
		}
		this->type = type;
	}

	void setValidation(bool validation) {
		this->valid = validation;
	}

	void applyDiscount(int perc) {
		this->price -= this->price * perc / 100;
	}

	void markAsInvitation() {
		this->price = -999;
		this->type == TicketType::HIDDEN;
		this->valid = 1;
	}

	void operator=(const Ticket& t)
	{
		if (this == &t) {
			return;
		}

		this->price = t.price;
		this->type = t.type;
		this->valid = t.valid;;
	}

	friend Ticket operator*(Ticket t, double perc);
	friend Ticket operator*(double perc, Ticket t);
};

int Ticket::noTickets = 0;

Ticket operator*(Ticket t, double perc) {
	Ticket result = t;
	result.price += result.price * perc / 100;
	return result;
}

Ticket operator*(double perc, Ticket t) {
	Ticket result = t;
	result.price +=  result.price * perc / 100;
	return result;
}

void operator<<(ostream& out, Ticket t) {
	out << endl << "Ticket info:";
	out << endl << "ID: " << t.getId();
	out << endl << "Price: " << t.getPrice();

	if (t.getType() == TicketType::REGULAR) {
		out << endl << "Ticket type: regular";
	}
	if (t.getType() == TicketType::VIP) {
		out << endl << "Ticket type: vip";
	}
	if (t.getType() == TicketType::HIDDEN) {
		out << endl << "Ticket type: hidden";
	}
	

	if (t.isValid()) {
		out << endl << "Tiket is valid!";
	}
	else {
		out << endl << "Careful! Ticket is not valid!";
	}
}

void operator>>(istream& in, Ticket& t) {
	cout << endl << "Enter price: ";
	double price;
	in >> price;
	t.setPrice(price);
	cout << endl << "Enter type (regular, hidden, vip): ";
	string hi;
	in >> hi;
	if (hi == "vip") {
		t.setType(TicketType::VIP);
	}
	else if (hi == "hidden") {
		t.setType(TicketType::HIDDEN);
	}
	else {
		t.setType(TicketType::REGULAR);
	}
	cout << endl << "Is the ticket valid? (y/n) ";
	in >> hi;
	if (hi == "y") {
		t.setValidation(1);
	}
	else {
		t.setValidation(0);
	}
	
}
