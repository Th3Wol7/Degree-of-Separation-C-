/*
 * Person.h
 *  Created on: Dec 17, 2022
 *      @Author: Tyrien Gilpin
 */
#ifndef MODEL_PERSON_H_
#define MODEL_PERSON_H_
#include <string>
#include <list>
using namespace std;

class Person {
private:
	string firstName;
	string lastName;
	string Phone;
	string email;
	string community;
	string school;
	string employer;
	string privacy;
	list<string> activity;

public:
	Person() {
		this->firstName = "N/A";
		this->lastName = "N/A";
		this->Phone = "N/A";
		this->email = "N/A";
		this->community = "N/A";
		this->school = "N/A";
		this->employer = "N/A";
		this->privacy = "-";
		this->activity = list<string>();
	}

	// Primary Constructor
	Person(string firstName, string lastName, string phone, string email,
			string community, string school, string employer, string privacy,
			list<string> activity) {
		this->firstName = firstName;
		this->lastName = lastName;
		this->Phone = phone;
		this->email = email;
		this->community = community;
		this->school = school;
		this->employer = employer;
		this->privacy = privacy;
		this->activity = activity;
	}

	virtual ~Person() {};

	Person(const Person &obj) {
		this->firstName = obj.firstName;
		this->lastName = obj.lastName;
		this->Phone = obj.Phone;
		this->email = obj.email;
		this->community = obj.community;
		this->school = obj.school;
		this->employer = obj.employer;
		this->privacy = obj.privacy;
		this->activity = obj.activity;
	}

	string getFirstName() const {
		return firstName;
	}

	void setFirstName(string firstName) {
		this->firstName = firstName;
	}

	string getLastName() const{
		return lastName;
	}

	void setLastName(string lastName) {
		this->lastName = lastName;
	}

	string getPhone() {
		return Phone;
	}

	void setPhone(string phone) {
		this->Phone = phone;
	}

	string getEmail() {
		return email;
	}

	void setEmail(string email) {
		this->email = email;
	}

	string getCommunity() {
		return community;
	}

	void setCommunity(string community) {
		this->community = community;
	}

	string getSchool() {
		return school;
	}

	void setSchool(string school) {
		this->school = school;
	}

	string getEmployer() {
		return employer;
	}

	void setEmployer(string employer) {
		this->employer = employer;
	}

	string getPrivacy() {
		return privacy;
	}

	void setPrivacy(string privacy) {
		this->privacy = privacy;
	}

	list<string> getActivity() {
		return activity;
	}

	void setActivity(list<string> activity) {
		this->activity = activity;
	}
	string showlist(list<string> listOfElements){
		string out = "";
		for(string element:listOfElements){
			out += element + "\n";
		}
		return out;
	}

	string tostring() {
		return "\nFirstname: " + getFirstName() + "\nLastname: " + getLastName()
				+ "\nPhone: " + getPhone() + "\nEmail: " + getEmail()
				+ "\nCommunity: " + getCommunity() + "\nSchool: " + getSchool()
				+ "\nEmployer: " + getEmployer() + "\nPrivacy: " + getPrivacy();
				+ "\n Activities: \n" + showlist(getActivity());
	}
	/*
	 @Override
	 int compareTo(Person^ &obj) {
	 return this->getFirstName().compareTo(obj->getFirstName());
	 }*/

	bool operator == (const Person& obj) {
		 return this->getFirstName() == obj.firstName && this->getLastName() == obj.lastName;
	}

};

#endif /* MODEL_PERSON_H_ */
