/*
 * SocialNetworkService.h
 *
 *  Created on: Dec 17, 2022
 *      Author: Tyrien Gilpin
 */

#ifndef NETWORK_SOCIALNETWORKSERVICE_H_
#define NETWORK_SOCIALNETWORKSERVICE_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Person.h"
#include "PersonNode.h"
#include <map>
using namespace std;

class SocialNetworkService {
private:
	map<Person, set<Person>> SNS = map<Person, set<Person>>();
	// you might want to write a helper method; you might want to make it recursive;
	// and you might want to read about in-order tree

public:
	virtual ~SocialNetworkService() {
	}
	;

	map<Person, set<Person>> getSNS() {
		return SNS;
	}

	void setSNS(map<Person, set<Person>> SNS) {
		this->SNS = SNS;
	}

	// This method retrieves user data from the file database and create the network with connections
	void createNetwork() {
		string line, line2;
		// Open the file
		ifstream file("..resource Files/PersonFile.csv");
		ifstream file2("..resource Files/Activities.csv");

		if (file.is_open() && file.is_open()) {
			// Read each line of the file
			while (getline(file, line)) {
				// Split the line by comma
				stringstream linestream(line);
				string value;
				list<string> values;
				list<string> activities = { };
				while (getline(linestream, value, ',')) {
					values.push_back(value);
				}
				// Create a Person object using the values
				string firstName = values.front();
				values.pop_front();
				string lastName = values.front();
				values.pop_front();
				string phone = values.front();
				values.pop_front();
				string email = values.front();
				values.pop_front();
				string community = values.front();
				values.pop_front();
				string school = values.front();
				values.pop_front();
				string employer = values.front();
				values.pop_front();
				string privacy = values.front();
				values.pop_front();
				while (getline(file2, line2)) {
					// Split the line by comma
					stringstream linestream2(line2);
					string value2;
					list<string> values2;
					while (getline(linestream2, value2, ',')) {
						values2.push_back(value2);
					}
					// Extract the first and last name from the first value
					string firstName2 = values2.front();
					values2.pop_front();
					size_t pos = values2.front().find(' ');
					string lastName2 = values2.front().substr(0, pos);
					values2.pop_front();
					// Create a list of activities
					activities = { };
					if (firstName2 == firstName && lastName2 == lastName) {
						activities.push_back(values2.front().substr(pos + 1));
						// Create a Person object using the extracted values

					}

					Person person(firstName, lastName, phone, email, community,
							school, employer, privacy, activities);
					// Use the Person object
					//getSNS().insert({person, }); NTS: Incomplete
					cout << person.tostring() << endl;
				}
				// Close the file
				file.close();
				file2.close();
			}
		}else {
			cout << "Unable to open file" << endl;
		}

	}

	// This method returns a collection of the users that are
	// immediate friends of the user passed to the method
set<Person> userFriends(Person user) {
	return getSNS().find(user)->second;
}

// Stores a person in map and adds the list of his/her friends to the
// node in the network
void addPerson(Person user) {
	SNS.insert( {user, set<Person>()});
}

// remove a person from the network
void removePerson(Person user) {
	getSNS().erase(user);
	// For each person in the network
	for (auto iterator = getSNS().begin(); iterator != getSNS().end(); iterator++) {
		for (Person friend1 : iterator->second) {// for each of their friends
			if (friend1.getFirstName() == user.getFirstName() &&
					friend1.getLastName() == user.getLastName()) {// if their friends is the user being removed,
				iterator->second.erase(user);// remove the user as that persons friend

			}
		}
	}
}

// This methods makes a connection between two friends in the Social network
void addFriend(Person user, Person friend1) {
	// Checking the existence of both friends in the Map- Might not be necessary
	if (getSNS().find(user) == getSNS().end()) {
		addPerson(user);
	}
	if (getSNS().find(friend1) == getSNS().end()) {
		addPerson(friend1);
	}

	// Creating link between the two persons in the network by adding a friend
	// to the collections of friends assigned to the user node data value
	getSNS().find(user)->second.insert(friend1);
	getSNS().find(friend1)->second.insert(user);
}

void removeFriend(Person user, Person friend1) {
	// Checking the existence of both friends in the Map- Might not be necessary
	if (getSNS().find(user) == getSNS().end()) {
		addPerson(user);
	}
	if (getSNS().find(friend1) == getSNS().end()) {
		addPerson(friend1);
	}

	// removing link between the two persons in the network by adding a friend
	// to the collections of friends assigned to the user node data value
	getSNS().find(user)->second.erase(friend1);
	getSNS().find(friend1)->second.erase(user);
}

}
;

#endif /* NETWORK_SOCIALNETWORKSERVICE_H_ */
