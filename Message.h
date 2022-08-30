#pragma once
#include <string>
#include <iostream>

class Message
{
	const std::string _from;
	const std::string _to;
	const std::string _text;
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

};