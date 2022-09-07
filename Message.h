#pragma once
#include <string>
#include <iostream>
#include <fstream>


class Message
{
	std::string _from;
	std::string _to;
	std::string _text;
public:
	Message(const std::string& from, const std::string& to, const std::string& text) :
		_from(from), _to(to), _text(text) {};
	void read()
	{
		std::cout << std::endl;
		std::cout << "Message from: " << _from << std::endl;
		std::cout << "Message to: " << _to << std::endl;
		std::cout << "Message text: " << _text << std::endl;
	}
	const std::string& getFrom() const
	{
		return _from;
	}
	const std::string& get_To() const
	{
		return _to;
	}

	friend std::fstream& operator>>(std::fstream& is, Message& obj) {
		is >> obj._from;
		is >> obj._to;
		is >> obj._text;
		return is;
	}

	friend std::ostream& operator<<(std::fstream& os, Message& obj) {
		os << obj._from;
		os << ' ';
		os << obj._to;
		os << ' ';
		os << obj._text << "/n" << std::endl;
		return os;
	}

};