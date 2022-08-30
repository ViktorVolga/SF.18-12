#include "user.h"
#include "Chat.h"

const std::string& User::getLogin() const
{
	return _logIn;
}

const std::string& User::getPass() const
{
	return _password;
}

std::fstream& operator>>(std::fstream& is, User& obj) {
	is >> obj._name;
	is >> obj._logIn;
	is >> obj._password;
	return is;
}