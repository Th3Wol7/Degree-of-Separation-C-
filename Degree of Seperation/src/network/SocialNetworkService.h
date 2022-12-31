/*
 * SocialNetworkService.h
 *
 *  Created on: Dec 17, 2022
 *      Author: Tyrien Gilpin
 */

#ifndef NETWORK_SOCIALNETWORKSERVICE_H_
#define NETWORK_SOCIALNETWORKSERVICE_H_

#include "Person.h"
#include "PersonNode.h"
#include <map>
using namespace std;

class SocialNetworkService
{
private:
	map<Person, set<Person>> SNS = map<Person, set<Person>>();
	// you might want to write a helper method; you might want to make it recursive;
	// and you might want to read about in-order tree

public:
	virtual ~SocialNetworkService(){};

	map<Person, set<Person>> getSNS(){
		return SNS;
	}

	void setSNS(map<Person, set<Person>> SNS) {
		this->SNS = SNS;
	}

	// This method retrieves user data from the file database and create the network with connections
	void createNetwork() {

	}

	// This method returns a collection of the users that are
	// immediate friends of the user passed to the method
	set<Person> userFriends(Person user){
		return getSNS().find(user)->second;
	}

	// Stores a person in map and adds the list of his/her friends to the
	// node in the network
	void addPerson(Person user) {
		SNS.insert({ user, set<Person>()});
	}

	// remove a person from the network
	void removePerson(Person user) {
		getSNS().erase(user);
		// For each person in the network
		for (auto iterator = getSNS().begin(); iterator != getSNS().end(); iterator++) {
		 	for (Person friend1 : iterator->second) {// for each of their friends
				if (friend1.getFirstName() == user.getFirstName() &&
					friend1.getLastName() == user.getLastName()){// if their friends is the user being removed,
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

};

#endif /* NETWORK_SOCIALNETWORKSERVICE_H_ */
