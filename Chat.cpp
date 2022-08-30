#include "Chat.h"




Chat::Chat() //�����������
{
	std::vector<User> _users; //������ ���� ������������� � �������
	std::unique_ptr<User> _currentUser = nullptr; //������� �����������
	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out); //for saving users in the file
	if (!user_file) { //if file isnt exist - creat it
		user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc); 
	}
	else {
		User user("v", "q", "1");
		user_file >> user;
		
	}
}

void Chat::start()
{
	_chatWorking = true;
}

void Chat::menu()
{
	_currentUser = nullptr;
	std::cout << std::endl; //������ ������ ��� �������
	std::cout << "Main menu" << std::endl;
	std::cout << "1 - logIn | 2 - registracion | 3 - quit" << std::endl;
	unsigned int choice(0); // ���������� ��� ������
	std::cin >> choice; //������������ ������ ��� �����
	switch (choice) //�������� ������
	{
	case 1:
		login(); //��������� ������� �����������
		break;
	case 2:
		registracion(); //��������� ������� �����������
		break;
	case 3:
		_chatWorking = false; // ��������� ���
		break;
	default:
		break;
	}
}

void Chat::login()
{
	std::string login, pass;
	std::cout << std::endl;
	std::cout << "Enter your login" << std::endl;
	std::cin >> login;
	std::cout << "Enter your password" << std::endl;
	std::cin >> pass;
	while (_currentUser == nullptr) //�� ��� ��� ���� �� ����������� ������������
	{
		try
		{
			//��������� ���� �� ����� �����
			_currentUser = getUserByLogin(login);
		}
		catch (Badlogin& bu)
		{
			bu.Show();
			_currentUser = nullptr;
			//���� ���� - ����� ���������� � ����������� nullptr �������� ������������
		}
		if (chekUserPass(login, pass) == false && _currentUser != nullptr)
		{
			//���� ������������ ���� �� ������ ������������ ������
			std::cout << std::endl;
			std::cout << "password is wrong " << std::endl;
			std::cout << "please Enter (1) for registracion" << std::endl;
			std::cout << "or Enter (anyKey) to repiat" << std::endl;
			char choice{ '0' };
			std::cin >> choice;
			if (choice == '1')
			{
				registracion();
			}
			else
			{
				Chat::login();
			}
		}
		if (_currentUser == nullptr)
		{
			//���� ������������ �� ���������������
			std::cout << std::endl;
			std::cout << "please Enter (1) for registracion" << std::endl;
			std::cout << "or Enter (anyKey) to repiat login" << std::endl;
			char choice{ '0' };
			std::cin >> choice;
			if (choice == '1')
			{
				registracion();
			}
			else
			{
				Chat::login();
			}
		}
		if (_users.size() == 0)
			// ���� �� ���� ������������ �� ��������������� ���
		{
			registracion();
		}
		if (chekUserPass(login, pass) == true)
		{
			//���� ������ ��������� ����� � ������
			userMenu();
			break;
		}
	}
}

void Chat::registracion()
//�����������
{
	std::cout << std::endl;
	std::cout << "registracion started" << std::endl;
	std::cout << "please enter login" << std::endl;
	std::string login, pass, name;
	std::cin >> login;
	if (_users.size() != 0)
		//���� ���� ���� �� ���� ������������������ ������������
		//��������� ����� �� �����
	{
		try
		{
			_currentUser = getUserByLogin(login);
		}
		catch (Badlogin)
		{
			//����� �������� - ����� ��������� � ����������� ���� ��� �������� ������������
			_currentUser = nullptr;
		}

	}
	while (_currentUser != nullptr)
	{
		//���� �� � ����������� �� �������� ���������������� ��� �������������� �����
		std::cout << std::endl;
		std::cout << "current login already busy" << std::endl;
		std::cout << "if you already has registracion enter (1)" << std::endl;
		std::cout << "or enter (2) if you want to registr new login" << std::endl;
		unsigned int choice{ 2 };
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			Chat::login();
			break;
		case 2:
			std::cout << "please enter new login" << std::endl;
			std::cin >> login;
			try
			{
				_currentUser = getUserByLogin(login);
			}
			catch (Badlogin)
			{
				_currentUser = nullptr;
			}
			break;
		default:
			break;
		}
	}
	if (_currentUser == nullptr)
	{
		//���� ����� ��������
		std::cout << "please enter your password" << std::endl;
		std::cin >> pass;
		std::cout << "please enter your name" << std::endl;
		std::cin >> name;
		User a(name, login, pass);
		_users.push_back(a); //���������� � ������ ������ ������������
	}

}

std::unique_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (size_t i = 0; i < _users.size(); ++i) //��������� �� ���� ������
	{
		if (login == _users[i].getLogin())
		{
			//���������� ��������� ���� ���� ����� �����
			return std::make_unique<User>(_users[i]);
		}
	}
	//���������� ���������� ���� �� ������ ������������
	throw Badlogin(login);
}

void Chat::userMenu()
{
	while (_currentUser != nullptr)
	{
		unsigned int choice(3);
		std::cout << std::endl;
		std::cout << "User's menu" << std::endl;
		std::cout << "1 - read messages | 2 - create message | 3 - quit" << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			readMessages();
			break;
		case 2:
			createMessage();
			break;
		case 3:
			_currentUser = nullptr;
			break;
		default:
			break;
		}
	}
}

void Chat::readMessages()
{
	for (size_t i = 0; i < _messages.size(); ++i)
	{
		if (_messages[i].get_To() == _currentUser->getLogin())
		{
			_messages[i].read();
		}
		if (_messages[i].get_To() == "all")
		{
			_messages[i].read();
		}
	}
}

void Chat::createMessage()
{
	std::string from, to, text;
	std::cout << "Enter recepient's login" << std::endl;
	std::cin >> to;
	while (checkLogin(to) == false)
	{
		std::cout << std::endl;
		std::cout << "login not founded" << std::endl;
		std::cout << "please try again" << std::endl;
		std::cout << "Enter recepient's login" << std::endl;
		std::cin >> to;
	}

	std::cout << "Enter message:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, text);
	from = _currentUser->getLogin();
	Message a(from, to, text);
	_messages.push_back(a);
}

bool Chat::checkLogin(const std::string& login)
{
	if (login == "all")
	{
		return true;
	}
	for (size_t i = 0; i < _users.size(); ++i)
	{
		if (_users[i].getLogin() == login)
		{
			return true;
		}
	}
	return false;
}

bool Chat::chekUserPass(const std::string& login, const std::string& pass) const
{
	for (size_t i = 0; i < _users.size(); ++i)
	{
		if (pass == _users[i].getPass() && login == _users[i].getLogin())
		{
			return true;
		}
	}
	return false;
}

void Chat::get_user() { //get users from users.txt
	

}

void Chat::get_users() { //get users from users.txt

}

