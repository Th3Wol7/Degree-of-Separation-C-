/*
 * main.cpp
 *
 *  Created on: Dec 17, 2022
 *      Author: Tyrien Gilpin
 */
#include <iostream>
#include <fstream> //includes ofstream and ifstream
#include <list>

#include "SocialNetwork.h"
#include "Person.h"


using namespace std;

 void findUser(Person user, SocialNetwork network, string fName, string lName) {
	map<Person, set<Person>> mp = network.getSocialNet().getSNS();
	for (auto person = mp.begin(); person != mp.end(); person++) {
		Person person1 = person->first;
		if(person1.getFirstName() == fName && person1.getLastName() == lName) {
			user = person1;
		}
	}
}

int main() {
	string fName, lName;
	int choice;
	SocialNetwork *network = new SocialNetwork();
	Person *user= new Person(), *target = new Person();
	network->getSocialNet().createNetwork();
	cout << "============Welcome to Social Connect=========" << endl;

	cout << "Enter the first name of a user:";
	cin >> fName;

	cout << "\nEnter the first name of a user:";
	cin >> lName;
	findUser(*user, *network, fName, lName);

	while (user == NULL) {
		cerr << "\nInvalid input. Try again";
		cout << "\nEnter the first name of a user:";
		cin >> fName;

		cout << "\nEnter the first name of a user:";
		cin >> lName;
		findUser(*user, *network, fName, lName);
	}

	cout << "\nHi" << fName << " " << lName
			<< " what would you like to do today?";
	cout << "\n[Select the number that corresponds to you choice of action:]";
	cout
			<< "1.View User details.\n2.View User Friends.\n3.View User Activities."
			<< "4.See Friend Suggestions.\n5.See Activity Suggestions."
			<< "6.Calculate Degree of Separation." << endl;

	cin >> choice;
	while (choice != 8 && choice != 1 && choice != 2 && choice != 4
			&& choice != 5 && choice != 6 && choice != 7) {
		cout << "Invalid selection. Try again!\n";
		cout
				<< "1.View User details.\n2.View User Friends.\n3.View User Activities."
				<< "4.See Friend Suggestions.\n5.See Activity Suggestions."
				<< "6.Calculate Degree of Separation." << endl;
		cin >> choice;

	}

	switch (choice) {
	case 1:
		cout << "*************User Details**************";
		user->tostring();
	break;
	case 2:
		cout << "*************User Friends**************\n";
		//auto friends = network->getSocialNet().getSNS().find(*user);
		for (Person person : network->getSocialNet().getSNS().find(*user)->second) {
			cout << person.getFirstName() << " " << person.getLastName()
					<< endl;
		}
	break;
	case 3:
		cout << "*************User Activities**************\n";
		cout << user->showlist(user->getActivity());
	break;
	case 4:
		cout << "*************Friend Suggestions**************\n";
		for (Person person : network->suggestFriends(*user)) {
			cout << person.getFirstName() << " " << person.getLastName()
					<< endl;
		}
		break;
	case 5:
		cout << "*************Activity Suggestions**************\n";
		cout << user->showlist(network->suggestActivities(*user));
		break;
	case 6:
		cout << "To find the degree of separation between the current user and"
				<< " someone else in the network.\nEnter the first name of the target: "
				<< endl;
		cin >> fName;
		cout << "Enter target's last name: " << endl;
		cin >> lName;
		findUser(*target, *network, fName, lName);

		while (user == NULL && fName != "-1" && lName != "-1") {
			cerr << "\nInvalid input. Try again (press -1 to quit)";
			cout << "\nEnter the first name of a user:";
			cin >> fName;

			cout << "\nEnter the first name of a user:";
			cin >> lName;
			findUser(*target, *network, fName, lName);
		}
		if (target != NULL && network != NULL) {
			cout << "*************Degree of Separation**************\n";
			network->degreeOfSeperation(*user, *target);
		}
		break;
	}

	return 0;
}
