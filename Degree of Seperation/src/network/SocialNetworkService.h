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
#include <vector>
#include <algorithm>
#include <map>

#include "Person.h"
#include "PersonNode.h"

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
	/*
	 * The time complexity of the createNetwork() method is O(n^2), where n is the number of people
	 * in the network. This is because the outer while loop iterates over all people in the network,
	 * and the inner while loop iterates over all friends of each person.
	 * The space complexity is also O(n^2), as the number of people and the number of friends
	 * each person has are both potentially n. In the worst case, where each person has n-1 friends,
	 * the space complexity would be O(n^2).
	 */
	void createNetwork() {
		ifstream inFileStream1, inFileStream2, inFileStream3, inFileStream4;
		Person person, person2;
		try {
			// Open the files
			inFileStream1.open("..resource Files/PersonFile.csv");
			inFileStream2.open("..resource Files/Friends.csv");
			// Read each line of the people file
			string line;
			while (getline(inFileStream1, line)) {
				// Read the values for the current person
				list<string> values;
				istringstream iss(line);
				string value;
				while (getline(iss, value, ',')) {
					values.push_back(value);
				}  // Create a Person object using the values
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

				// Read the activities for the current person
				list<string> activities;
				inFileStream4.open("..resource Files/Activities.csv");
				while (getline(inFileStream4, line)) {
					list<string> values;
					istringstream iss(line);
					string value;
					while (getline(iss, value, ',')) {
						values.push_back(value);
					}
					if (firstName == values.front()) {
						for (auto &value : values) {
							activities.push_back(value);
						}
						break;
					}
				}
				inFileStream4.close();
				// Create a Person object for the current person
				Person person = Person(firstName, lastName, phone, email,
						community, school, employer, privacy, activities);
				// Read the friends list for the current person
				set<Person> friends;
				// Read each line of the friends file
				while (getline(inFileStream2, line)) {
					list<string> friendsList;
					istringstream iss(line);
					string value;
					while (getline(iss, value, ',')) {
						friendsList.push_back(value);
					}
					// If the first name of the line is equal to that of the current person
					if (friendsList.front() == person.getFirstName()) {
						// Open the people file again
						inFileStream3.open("..resource Files/PersonFile.csv");
						while (getline(inFileStream3, line)) {
							list<string> values;
							istringstream iss(line);
							string value;
							while (getline(iss, value, ',')) {
								values.push_back(value);
							}
							// If the first name and last name of the line match a friend of the current person
							if (values.front() == friendsList[1]
									&& values[1] == friendsList[2]) {
								// Create a Person object for the current friend
								string firstName2 = values.front();
								values.pop_front();
								string lastName2 = values.front();
								values.pop_front();
								string phone2 = values.front();
								values.pop_front();
								string email2 = values.front();
								values.pop_front();
								string community2 = values.front();
								values.pop_front();
								string school2 = values.front();
								values.pop_front();
								string employer2 = values.front();
								values.pop_front();
								string privacy2 = values.front();
								values.pop_front();
								list<string> activity;
								activity.push_back(values.front());

								Person person2 = Person(firstName2, lastName2,
										phone2, email2, community2, school2,
										employer2, privacy2, activity);

								// Add the current friend to the list of friends
								friends.insert(person2);
								break;
							}
						}
						inFileStream3.close();
					}
				}

				// Add the current person and their friends to the network
				getSNS().insert( { person, friends });
			}
			inFileStream1.close();
		} catch (exception &e) {
			cout << e.what() << endl;
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
		SNS.insert( { user, set<Person>() });
	}

// remove a person from the network
	void removePerson(Person user) {
		getSNS().erase(user);
		// For each person in the network
		for (auto iterator = getSNS().begin(); iterator != getSNS().end();
				iterator++) {
			for (Person friend1 : iterator->second) { // for each of their friends
				if (friend1.getFirstName() == user.getFirstName()
						&& friend1.getLastName() == user.getLastName()) { // if their friends is the user being removed,
					iterator->second.erase(user); // remove the user as that persons friend

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
