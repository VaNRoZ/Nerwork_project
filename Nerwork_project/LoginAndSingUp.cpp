#include "LoginAndSignUp.h"
#include "Protocol.h"
#include <fstream>

LoginAndSignUp::LoginAndSignUp()
{
	dispatcher = new Dispatcher(getAllUsers());
	sockets = NULL;
	status = false;
	//ofstream writeToFile;
	//writeToFile.open("users.txt");
	//writeToFile.close();
}

LoginAndSignUp::~LoginAndSignUp() {

}

void LoginAndSingUp