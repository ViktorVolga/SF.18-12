#include <iostream>
#include "Chat.h"



int main()
{
	Chat chat;
	chat.menu();
	chat.start();
	while (chat._chatWorking)
	{
		chat.menu();
		chat.userMenu();
	}

	return 0;
}