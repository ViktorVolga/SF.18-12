#pragma once
#include <string>

class User
{
	std::string _name;
	std::string _logIn;
	std::string _password;
public:
	explicit User(const std::string& name, const std::string& logIn, const std::string& password) : _name(name), _logIn(logIn), _password(password) {};
	const std::string& getLogin() const;
	const std::string& getPass() const;
	friend std::fstream &operator>>(std::fstream& is, User& obj);
};