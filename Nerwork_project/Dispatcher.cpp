

#include "Dispatcher.h"
#include "Protocol.h"

pthread_mutex_t ligin_dispatcher_mutex = PTHREAD_MUTEX_INITIALIZER;

Dispatcher::Dispatcher(vector<string> name)
{
	listner = NULL;
	users_map_mutex = PTHREAD_MUTEX_INITIALIZER;
	userd_map_size = 0;
	status = false;
	all_users_infile_vector = name;
}

void Dispatcher::add_user_to_vector(string name)
{
	all_users_infile_vector.push_back(name);
}
void Dispatcher::add_user(TCPSocket* peer, string name)
{
	if (pthread_mutex_lock(&login_dispatchr_mutex) != 0)
	{
		print("Error locking mutex");
		exit(1);
	}
	User* user = new User;

	user->socket = peer; 
	user->name = name;
	user->connectionStatus = false;
	user->connectioToUser = NULL;
	user->connectedToChatRoom = NULL;

	cout << user->name << "is new connected" << endl;

	users_map[name] = user;
	users_vector.push_back(peer);

	if (status == false)
	{
		status = true;
		this->start();
	}
	if (pthread_mutex_unlock(&login_dispatcher_mutex)!=0)
	{
		print("Error unlocking mutex");
		exit(1);
	}
}

void Dispatcher::run()
{
	int command;

	while (status == true)
	{
		User* current_user = new User();
		listener = new MultipletTCPSocketsListener();
		listener->addSockets(users_vector);
		TCPSocket* temp_sock = listener->listenToSocket(2);
		delete(listener);

		if (temp_sock != NULL)
		{
			command = readCommand(temp_sock);
			current_user->socket = temp_sock; //Initialize the socket field
		}
		else
			continue;

		if (command == 0)
		{
			//cout <<"problem" << endl;
			continue;
		}
		else if (command == OPEN_SESSINON_WITH_USER) //get the user's IP & port
		{
			open_session(current_user);

		}
		else if (command == EXIT) //user is exiting, update all chat rooms and users list
	}
}