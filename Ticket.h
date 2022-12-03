#pragma once
#include <iostream>

enum TicketType {REGULAR, VIP, HIDDEN};

class Ticket {
private:
	const int ticketId;
	double price = 0;
	TicketType type = TicketType::REGULAR;
	bool valid = 0;
	static int ticketNo;

public:
	Ticket() : ticketId(-1) {

	}

	Ticket(double price, TicketType type, bool valid) : ticketId(++ticketNo) {
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

	//applyDiscount(%)
	//markAsInvitation
};

int Ticket::ticketNo = 0;
