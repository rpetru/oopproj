#include <iostream>
#include "Event.h"
#include "Ticket.h"
#include "User.h"

using namespace std;

int main() {

	int tickets[] = { 1,2,3,4,5 };
	int seats[] = { 10, 15, 20, 30, 40 };
	Ticket t1(20, TicketType::HIDDEN, 1);
	cout << t1;

	Event e1("event1", "location1", seats, 5);
	//cout << endl;
	//cout << e1;
	//Event e2;
	//e2 = e1;
	//cout << endl << e2;

	char user[] = "petru";

	User u1(user, tickets, 5, 20);
	cout <<	endl << u1;

	u1.dismissTicket(2);
	cout << endl << u1;

	//Event e3;
	//cin >> e3;
	//cout << endl << e3;

	/*e1.addRow(50);
	cout << e1;

	cout << endl << (int)e1;

	cout << endl << e1(1, 3);*/

	User u2 = u1;

	if (u1 == u2) {
		cout << endl << "same amount of tix bought";
	}

	cout << !u1;

	//t1 = t1 * 10;
	//cout << ++t1;
	return 0;
}