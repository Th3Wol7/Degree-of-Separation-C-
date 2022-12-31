/*
 * PersonNode.h
 *
 *  Created on: Dec 17, 2022
 *      Author: gilpi
 */

#ifndef MODEL_PERSONNODE_H_
#define MODEL_PERSONNODE_H_

#include <string>
#include <set>
#include "Person.h"
#include <iostream>
using namespace std;

class PersonNode {
private:
	Person data;
	bool visited;
	set<PersonNode> friends;
	PersonNode *previous;

public:
	PersonNode(Person user) {
		this->data = user;
		this->visited = false;
		this->friends = set<PersonNode>();
		this->previous = NULL;
	}

	PersonNode(Person user, set<Person> neighbours) {
		this->data = user;
		this->friends = adjacent(neighbours);
		this->visited = false;
		this->previous = NULL;
	}

	~PersonNode() {
		cout << "\nDestructor called" << endl;
	}
	;

	void addNeighbour(PersonNode node) {
		friends.insert(node);
	}

	set<PersonNode> adjacent(set<Person> neighbours) {
		set<PersonNode> converted = set<PersonNode>();
		for (Person person : neighbours) {
			converted.insert(PersonNode(person));
		}
		return converted;
	}

	Person getData() const {
		return this->data;
	}

	void setData(Person data) {
		this->data = data;
	}

	bool isVisited() {
		return visited;
	}

	void setVisited(bool visited) {
		this->visited = visited;
	}

	set<PersonNode> getFriends() {
		return friends;
	}

	void setFriends(set<PersonNode> friends) {
		this->friends = friends;
	}

	PersonNode* getPrevious() {
		return previous;
	}

	void setPrevious(PersonNode *previous) {
		this->previous = previous;
	}

	void showFriends(set<PersonNode> friends1) {
		cout << "[";
		for (PersonNode node : friends1) {
			cout << node.getData().tostring();
		}
		cout << "]";
	}
	void Display() {
		cout << "\nPersonNode: " << getData().tostring() << "\nVisited: "
				<< isVisited() << "\nFriends: ";
		showFriends(getFriends());
		cout << "\nPrevious: " << getPrevious();
	}

	//This method works the same as implementing the methods of the comparable
	//interface in Java when extended by a class
	bool operator == (const PersonNode& obj) {
			 return getData().getFirstName() == obj.getData().getFirstName();
					 this->getData().getLastName() == obj.getData().getLastName();
	}

};

#endif /* MODEL_PERSONNODE_H_ */
