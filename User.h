#pragma once
#include <iostream>

using namespace std;

class User {
	const int userId;
	char* name = nullptr;
	int ticketsBought = 0;
	int* ticketIds = 0;
	int age = 0;
	static int noUsers;

	const static int MIN_ACCEPTED_AGE;

public: 
	User() : userId(++noUsers) {

	}

	User(char* name, int* tickets, int ticketCount, int age) : userId(++noUsers) {
		this->setName(name);
		this->setTickets(tickets, ticketCount);
		this->setAge(age);
	}

	User(const User& u) : userId(u.userId) {
		this->name = u.name;
		this->age = u.age;
		if (u.ticketIds != nullptr) {
			this->ticketIds = new int[u.ticketsBought];
			for (int i = 0; i < u.ticketsBought; i++) {
				this->ticketIds[i] = u.ticketIds[i];
			}
		}
		this->ticketsBought = u.ticketsBought;
	}

	~User() {
		delete[] this->ticketIds;
	}

	char* getName() {
		return this->name;
	}

	int getTicketsBought() {
		return this->ticketsBought;
	}

	int getAge() {
		return this->age;
	}

	int* getTickets() {
		if (this->ticketIds == nullptr) {
			return nullptr;
		}
		int* copy = new int[this->ticketsBought];
		for (int i = 0; i < this->ticketsBought; i++) {
			copy[i] = this->ticketIds[i];
		}
		return copy;
	}

	int getId() {
		return this->userId;
	}

	void setName(char* name) {
		if (strlen(name) < 2) {
			throw "too short";
		}
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	void setAge(int age) {
		if (age < MIN_ACCEPTED_AGE) {
			throw "too young to register";
		}
		this->age = age;
	}

	void setTickets(int* tickets, int ticketNo) {
		if (tickets == nullptr) {
			throw "provide valid array";
		}
		for (int i = 0; i < ticketNo; i++) {
			if (tickets[i] <= 0) {
				throw "invalid ticket id!";
			}
		}
		delete[] this->ticketIds;
		this->ticketIds = new int[ticketNo];
		for (int i = 0; i < ticketNo; i++) {
			this->ticketIds[i] = tickets[i];
		}
		this->ticketsBought = ticketNo;
	}

	void addTicket(int ticketid) {
		int* tix = new int[this->ticketsBought + 1];
		for (int i = 0; i < this->ticketsBought; i++) {
			tix[i] = this->ticketIds[i];
		}
		tix[this->ticketsBought] = ticketid;
		delete[] this->ticketIds;
		this->ticketIds = tix;
		this->ticketsBought++;
	}

	void dismissTicket(int ticketId) {
		int index = -1;
		for (int i = 0; i < this->ticketsBought; i++) {
			if (this->ticketIds[i] == ticketId) {
				index = i;
			}
		}
		if (index == -1) {
			cout << "No ticket with id " << ticketId << " found!";
			return;
		}
		for (int i = index; i < this->ticketsBought - 1; i++) {
			this->ticketIds[i] = this->ticketIds[i + 1];
		}

		int* tix = new int[this->ticketsBought - 1];
		for (int i = 0; i < this->ticketsBought - 1; i++) {
			tix[i] = this->ticketIds[i];
		}
		delete[] this->ticketIds;
		this->ticketIds = tix;
		this->ticketsBought--;
	}

	bool operator==(User u) {
		return this->ticketsBought == u.ticketsBought;
	}

	User operator!() {
		User copy = *this;
		for (int i = 0; i < this->ticketsBought; i++) {
			copy.ticketIds[i] = -1;
		}
		return copy;
	}

	void operator=(const User& u)
	{
		if (this == &u) {
			return;
		}

		delete[] this->name;
		this->name = new char[strlen(u.name) + 1];
		strcpy_s(this->name, strlen(u.name) + 1, u.name);
		this->age = u.age;
		this->ticketsBought = u.ticketsBought;
		delete[] this->ticketIds;
		this->ticketIds = new int[u.ticketsBought];
		for (int i = 0; i < u.ticketsBought; i++) {
			this->ticketIds[i] = u.ticketIds[i];
		}
	}


};

int User::noUsers = 0;
const int User::MIN_ACCEPTED_AGE = 12;

void operator<<(ostream& out, User u) {
	out << endl << "User info:";
	out << endl << "ID: " << u.getId();
	out << endl << "Name: " << u.getName();
	out << endl << "age: " << u.getAge();
	out << endl << "Number of tickets bought: " << u.getTicketsBought();
	if (u.getTicketsBought() > 0) {
		int* tix = u.getTickets();
		out << endl << "Ticket IDs: ";
		for (int i = 0; i < u.getTicketsBought(); i++) {
			out << tix[i] << " ";
		}
	}
	else {
		return;
	}
}

void operator>>(istream& in, User& u) {
	cout << endl << "Enter name: ";
	char input[100];
	in >> input;
	delete[] u.getName();
	u.setName(input);
	cout << endl << "Enter age: ";
	int age;
	in >> age;
	u.setAge(age);
	cout << "Enter number of tickets bought: ";
	int number;
	in >> number;
	int* tix = new int[number];
	delete[] u.getTickets();
	cout << "Enter ticket IDs: ";
	for (int i = 0; i < number; i++) {
		in >> tix[i];
	}
	u.setTickets(tix, number);
}
