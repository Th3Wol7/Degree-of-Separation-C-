/*
 * SocialNetwork.h
 *
 *  Created on: Dec 17, 2022
 *  Author: Tyrien Gilpin
 *  Generic contains method -> https://thispointer.com/c-list-find-contains-how-to-search-an-element-in-stdlist/
 */

#ifndef NETWORK_SOCIALNETWORK_H_
#define NETWORK_SOCIALNETWORK_H_

#include <iostream>
#include "SocialNetworkService.h"
#include "BreadthFirstSearch.h"
#include <string>
#include <list>
#include<algorithm>
#include <map>
using namespace std;

class SocialNetwork {
private:
	SocialNetworkService socialNet;

public:
	SocialNetwork() {
		this->socialNet = SocialNetworkService();
	}

	SocialNetwork(SocialNetworkService sns) {
		socialNet = sns;
	}

	virtual ~SocialNetwork() {
		cout << "Social Network Destructor called" << endl;
	}

	// Getters & Setters
	SocialNetworkService getSocialNet() {
		return socialNet;
	}

	//***********************Helper Methods**************************/
	// This method returns a list of all the friends of a person in the network
	list<Person> findFriends(Person user) {					// Working
		set<Person> currentFriends = getSocialNet().getSNS().find(user)->second;// storing user's current friends
		list<Person> result(currentFriends.begin(), currentFriends.end());
		return result;
		//return list<Person> firstLevel(currentFriends.begin(), currentFriends.end());
	}

	// This method checks if one person is a friend of the other
	bool friendsMatch(Person user, Person friend1) {				// working
		if (!findFriends(user).empty()) {		// If user has friends then...
			for (Person person : findFriends(user)) {
				if (friend1.getFirstName() == person.getFirstName()
						&& friend1.getLastName() == person.getLastName()) {
					return true;
				}
			}
		}
		return false;
	}

	//This method checks if a string is contained within a list of Strings
	bool contains(list<string> listOfElements, string element) {
		transform(element.begin(), element.end(), element.begin(), ::tolower);
		for (string element1 : listOfElements) {
			transform(element1.begin(), element1.end(), element1.begin(),
					::tolower);
			if (element == element1) {
				return true;
			}

		}
		return false;
	}

	//***********************Functional Methods**************************/
	// This suggest list of users to the current user based on similar employer, school or community.
	list<Person> suggestFriends(Person user) {
		list<Person> suggestedFriends = list<Person>();
		try {
			for (auto iterator = getSocialNet().getSNS().begin();
					iterator != getSocialNet().getSNS().end(); iterator++) {
				// if person in the network is of same community, school or employer as user
				Person key = iterator->first;
				if (user.getCommunity() == key.getCommunity()
						|| key.getEmployer() == user.getEmployer()
						|| key.getSchool() == user.getSchool()) {
					// if current person in network is not on users friends list
					// then add the user to the suggested friends list
					if (friendsMatch(user, iterator->first) == false) {
						if (user.getFirstName() == key.getFirstName()
								&& user.getLastName() == key.getLastName()) {
							suggestedFriends.remove(key);
						} else {
							suggestedFriends.push_back(key);
						}
					}
				}
			}
		} catch (const char *msg) {
			cout << msg << endl;
		} catch (...) {
			cout << "Exception Thrown in Social Network class suggestFriends method";
		}
		return suggestedFriends;
	}

	list<string> suggestActivities(Person user) {
		list<string> activitySuggestions = list<string>();
		try {
			for (auto iterator = getSocialNet().getSNS().begin();
					iterator != getSocialNet().getSNS().end(); iterator++) {
				Person key = iterator->first;
				if (key.getCommunity() == user.getCommunity()
						|| key.getEmployer() == user.getEmployer()
						|| key.getSchool() == user.getSchool()) {
					if (!user.getActivity().empty()) {
						for (string entryActivity : key.getActivity()) {// for each network user activity
							if (contains(user.getActivity(), entryActivity)== false) {	// if on users activity list
								if (contains(activitySuggestions, entryActivity) == false) {	// if activity is not already added to suggested activity list
									activitySuggestions.push_back(entryActivity);
								}
							}
						}
					} else {
						for (string entryActivity : key.getActivity()) { // for every string in the user
							if (contains(activitySuggestions, entryActivity) == false) {	// if activity is not already added to suggested activity list
								activitySuggestions.push_back(entryActivity);
							}
						}
					}
				}
			}

		} catch (const char *msg) {
			cout << msg << endl;
		} catch (...) {
			cout
					<< "Exception Thrown in the Social Network Class Suggest activities method";
		}
		return activitySuggestions;
	}

	// Returns the degree of separation between users in the social
	string degreeOfSeperation(Person user, Person user2) {
		string output = "";
		if (friendsMatch(user, user2) == true) {
			output += "Degree of separation between " + user.getFirstName()
					+ " & " + user2.getFirstName()
					+ " is 1. Because they are direct friends" + "\n";
			return output;
		} else {
			// If any of of the users friends is a friend of user2 return 2 degrees of
			// separation because they both have a mutual friend that they is 1 degree from them
			if (!findFriends(user).empty()) {	// If user has friends then...
				for (Person person : findFriends(user)) {
					for (Person person2 : getSocialNet().getSNS().find(user2)->second) {
						if (person2.getFirstName() == person.getFirstName()
								&& person2.getLastName() == person.getLastName()) {
							output += "Degree of separation between "
									  + user.getFirstName() + " & "
									  + user2.getFirstName()
									  + " is 2 because they share a mutual friend.\nDegree:\n2";
							return output;
						}
					}
				}
			}

			map<PersonNode, set<PersonNode>> RBTree = map<PersonNode,set<PersonNode>>();
			for (auto iterator = getSocialNet().getSNS().begin();
					iterator != getSocialNet().getSNS().end(); iterator++) {
				PersonNode NodeA = PersonNode(iterator->first);
				for (Person src : iterator->second) {
					NodeA.addNeighbour(PersonNode(src));
				}
				//RBTree.insert(pair<PersonNode, set<PersonNode>>(NodeA, NodeA.getFriends()));
				RBTree.insert({NodeA, NodeA.getFriends()});
				//RBTree[NodeA] = NodeA.getFriends();	//Populate map with person and his friends
			}

			PersonNode nodeC = PersonNode(user);
			for (Person src1 : getSocialNet().getSNS().find(user)->second) {
				nodeC.addNeighbour(PersonNode(src1));
			}
			PersonNode nodeB = PersonNode(user2);
			for (Person src2 : getSocialNet().getSNS().find(user2)->second) {
				nodeB.addNeighbour(PersonNode(src2));
			}

			return BreadthFirstSearch(nodeC, nodeB, RBTree).separationDegree();
		}
	}

	// This method determine the average degree of separation of the nodes in the
	// tree
	int averageDegreeOfSeperation() {
		return 0;
	}

};

#endif /* NETWORK_SOCIALNETWORK_H_ */
