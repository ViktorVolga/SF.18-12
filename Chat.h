#pragma once
#include <vector>
#include "user.h"
#include "Message.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>

class Chat
{
	std::vector<User> _users; // ��������� ���� - ������ ������ 
	std::vector<Message> _messages;		// ������ ���������
public:	
	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
	std::unique_ptr<User> _currentUser = nullptr; // ��������� �� �������� ������������
	bool _chatWorking{ true }; // ��������� ������ ����
	explicit Chat();//�����������
	void start(); //������
	void menu(); //������� ����
	void login(); // �����
	void registracion(); //�����������
	std::unique_ptr<User> getUserByLogin(const std::string& login) const; //�������� ����� � �������
	bool checkLogin(const std::string& login); // �������� ������
	bool chekUserPass(const std::string& login, const std::string& pass) const; //�������� ������ � ������ 
	void userMenu(); // ���� ������������
	void readMessages(); // ������ ���������
	void createMessage(); // �������� ���������
	void get_user(); //get user from user.txt
	void get_users(); //get Users from users.txt
};

class Badlogin // ��� ���������� �����
{
private:
	std::string _login; // ����� ������ � �������  ������� ��� ���� (��� ����������� ��������)
public:
	Badlogin(std::string login) : _login(login) {};
	void Show() // ������� ������� ��������� ��� ������ ����������.
	{
		std::cout << "Bad User catched. Police already going ( joke =) )" << std::endl;
		std::cout << "this login is not reggistered: " << _login << std::endl;
	}
};