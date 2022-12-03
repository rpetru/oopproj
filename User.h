#pragma once
#include<iostream>

class User {
	const int userId;
	char* name = nullptr;
	int ticketsBought = 0;
	int* ticketIds = 0;
	int age = 0;
	static int noUsers;

	const static int MIN_ACCEPTED_AGE;

public: 
	User() : userId(-1) {

	}

	User(char* name, int* tickets, int ticketCount, int age) : userId(++noUsers) {
		this->setName(name);
		this->setTickets(tickets, ticketCount);
		this->setAge(age);
	}

	User(const User& u) : userId(u.userId) {
		this->name = u.name;
		this->age = u.age;
		this->ticketIds = new int[u.ticketsBought];
		for (int i = 0; i < u.ticketsBought; i++) {
			this->ticketIds[i] = u.ticketIds[i];
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
		int* copy = new int[this->ticketsBought];
		for (int i = 0; i < this->ticketsBought; i++) {
			copy[i] = this->ticketIds[i];
		}
		return copy;
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
		delete[] this->ticketIds;
		this->ticketIds = new int[ticketNo];
		for (int i = 0; i < ticketNo; i++) {
			this->ticketIds[i] = tickets[i];
		}
		this->ticketsBought = ticketNo;
	}
};

int User::noUsers = 0;
const int User::MIN_ACCEPTED_AGE = 12;
