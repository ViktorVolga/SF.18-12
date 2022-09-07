#include "Chat.h"

Chat::Chat() //конструктор
{
	std::vector<User> _users; //Храним всех пользователей в векторе
	std::unique_ptr<User> _currentUser = nullptr; //текущий пользватель
	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out); //for saving users in the file
	
	if (!user_file) { //if file isnt exist - creat it
		user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);
	}
	get_users_from_file();
	if (!message_file) { //if file isnt exist - creat it
		message_file = std::fstream("messages.txt", std::ios::in | std::ios::out | std::ios::trunc);
	}
	get_messages_from_file();	
	message_file.close();
}

void Chat::start()
{
	_chatWorking = true;
	
}

void Chat::menu()
{
	_currentUser = nullptr;
	std::cout << std::endl; //разрыв строки для красоты
	std::cout << "Main menu" << std::endl;
	std::cout << "1 - logIn | 2 - registracion | 3 - quit" << std::endl;
	unsigned int choice(0); // переменная для выбора
	std::cin >> choice; //пользователь вводит что хочет
	switch (choice) //оператор выбора
	{
		case 1:
			login(); //запускает процесс авторизации
			break;
		case 2:
			registracion(); //запускает процесс регистрации
			break;
		case 3:
			_chatWorking = false; // выключает чат
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
	while (_currentUser == nullptr) //До тех пор пока не залогинится пользователь
	{
		try
		{
			//проверяем есть ли такой логин
			_currentUser = getUserByLogin(login);
		}
		catch (Badlogin& bu)
		{
			bu.Show();
			_currentUser = nullptr;
			//если нету - ловим исключение и присваиваем nullptr текущему пользователю
		}
		if (chekUserPass(login, pass) == false && _currentUser != nullptr)
		{
			//если пользователь есть но введен неправильный пароль
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
			//Если пользователь не зарегестрирован
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
			// Если ни один пользователь не зарегестрирован еще
		{
			registracion();
		}
		if (chekUserPass(login, pass) == true)
		{
			//Если введен правльный логин и пароль
			userMenu();
			break;
		}
	}
}

void Chat::registracion()
//регистрация
{
	std::cout << std::endl;
	std::cout << "registracion started" << std::endl;
	std::cout << "please enter login" << std::endl;
	std::string login, pass, name;
	std::cin >> login;
	if (_users.size() != 0)
		//Если есть хотя бы один зарегестрированный пользователь
		//Проверяем занят ли логин
	{
		try
		{
			_currentUser = getUserByLogin(login);
		}
		catch (Badlogin)
		{
			//логин свободен - ловим исключние и присваиваем нуль птр текущему пользователю
			_currentUser = nullptr;
		}

	}
	while (_currentUser != nullptr)
	{
		//Пока мы в регистрации но пытаемся зарегестрировать уже использующийся логин
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
		//Если логин свободен
		std::cout << "please enter your password" << std::endl;
		std::cin >> pass;
		std::cout << "please enter your name" << std::endl;
		std::cin >> name;
		User a(name, login, pass);
		_users.push_back(a); //отправляем в вектор нового пользователя
		push_new_user(a); //put new user to the file
	}
}

std::unique_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (size_t i = 0; i < _users.size(); ++i) //пробегаем по всем юзерам
	{
		if (login == _users[i].getLogin())
		{
			//возвращаем указатель если есть такой логин
			return std::make_unique<User>(_users[i]);
		}
	}
	//генерируем исключение если не найден пользователь
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
	push_new_message_to_file(a);
	
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



void Chat::push_new_user(User& a) {  // put new user to the users.txt
	if (user_file) {
		user_file.seekg(0, std::ios_base::end); //going to the end
		user_file << a;            //writing user to the file
	}
	else {
		user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);
		std::cout << "File user.txt now opened, please close it and try again" << std::endl;		
	}	
} 

void Chat::get_users_from_file() { //get all users from users.txt
	std::string text; //initializating needed string	
	std::getline(user_file, text); //reading all users to the string text
	std::string name, login, pass; //initializating needed string	
	int count = 0;
	while (count < text.length()) {
		for (int i = 0; i < text.length(); i++)
		{
			if (text[count] != ' ') {
				
				name.push_back(text[count]);
				count++;
			}
			else {
				count++;
				break;
			}
		}
		for (int i = 0; i < text.length(); i++)
		{
			if (text[count] != ' ') {
				
				login.push_back(text[count]);
				count++;
			}
			else {
				count++;
				break;
			}
		}
		for (int i = 0; i < text.length(); i++)
		{
			if (text[count] != ' ') {
				
				pass.push_back(text[count]);
				if (count == text.length())
					break;
				count++;
			}
			else {
				if (count == text.length())
					break;
				count++;
				break;
			}
		}
		User a(name, login, pass); //create new USER
		_users.push_back(a); //put user to the vector
		name.erase(); //clearing string
		login.erase(); //clearing string
		pass.erase(); //clearing string
	}
}

void Chat::push_new_message_to_file(Message& a) { 
	if (message_file) { //if message_file is exist
		message_file.seekp(0, std::ios_base::end); //going to the end
		message_file << a; //writing message to the file
	}
	else {
		message_file = std::fstream("messages.txt", std::ios::in | std::ios::out | std::ios::trunc); //create message file
		
		message_file << a;  //writing message to the file
	}
}

void Chat::get_messages_from_file() { //get all messages to the file
	std::string get, from, to, message; 
	std::vector<std::string> _lines; //useing vector for saving strings
	while (getline(message_file, get)) { //while message_file not end
		_lines.push_back(get); //adding strings to the vector
	}		
	for (const auto l : _lines) { //parsing
		int count = 0;
		while (l[count] != ' ') { 
			from.push_back(l[count++]);
		}
		count++;
		while (l[count] != ' ') {
			to.push_back(l[count++]);
		}
		count++;
		while (count < (l.length() - 2)) {
			message.push_back(l[count++]);
		}
		Message a(from, to, message);
		_messages.push_back(a);	
		from.clear();
		to.clear();
		message.clear();
	}
}
	
	
	


