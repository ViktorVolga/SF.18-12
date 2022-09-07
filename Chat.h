#pragma once
#pragma once
#include <vector>
#include "user.h"
#include "Message.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

class Chat
{
	std::vector<User> _users; // Хранилище чата - хранит Юзеров 
	std::vector<Message> _messages;		// Хранит сообщения
public:
	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
	std::fstream message_file = std::fstream("messages.txt", std::ios::in | std::ios::out);
	std::unique_ptr<User> _currentUser = nullptr; // Указатель на текущего пользователя
	bool _chatWorking{ true }; // Индикатор работы чата
	explicit Chat();//конструктор
	void start(); //Начало
	void menu(); //Главное меню
	void login(); // Логин
	void registracion(); //Регистрация
	std::unique_ptr<User> getUserByLogin(const std::string& login) const; //проверка юзера в векторе
	bool checkLogin(const std::string& login); // проверка логина
	bool chekUserPass(const std::string& login, const std::string& pass) const; //проверка логина и пароля 
	void userMenu(); // меню пользователя
	void readMessages(); // чтение сообщений
	void createMessage(); // создание сообщений
	void push_new_user(User& a); //pushing new user to user.txt
	void get_users_from_file(); //get user from user.txt	
	void push_new_message_to_file(Message& a); //pushing new message to the message file;
	void get_messages_from_file(); //geating messages from file
	
};

class Badlogin // Для исключений класс
{
private:
	std::string _login; // ловит строку с логином  который уже есть (При регистрации проверка)
public:
	Badlogin(std::string login) : _login(login) {};
	void Show() // функция выводит сообщение при поимке исключения.
	{
		std::cout << "Bad User catched. Police already going ( joke =) )" << std::endl;
		std::cout << "this login is not reggistered: " << _login << std::endl;
	}
};