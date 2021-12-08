

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
		{
			user_exit(current_user);
		}
		else if (command == GET_ALL_USERS) //all names form file
		{
			list_all_users(current_user);
		}
		else if (command == OPEN_CHATROOM) //user is the owner of the new chatroom
		{
			join_chartoom(current_user);
		}
		else if (command == LEAVE_CHATROOM) // remove user frome chatroom and update listand users
		{
			leave_chatroom(current_user);
		}
		else if (command == GET_ALL_CUNNECTED_USERS) //send back to the user a list of all conncted users
		{
			list_users(current_user);
		}
		else if (command == GET_ALL_CHATROOMS) //GET_ALL_CHATROOMS
		{

			list_chatrooms(current_user);
		}
		else if (command == GET_CHATROOM_USERS) // GET_CHATROOM_USERS
		{
			list_chatroom_users(current_user);
		}
	}
}

void Dispatcher::open_session(User* user)
{
	string userName, peerUsr, user_ip_and_port, target_ip_and_port;
	User* target;
	string with;
	User* _user;

	userName = readMsg(user->socket); //our name
	peerUsr = readMsg(user->socket); // Teh user name of teh target user

	for (user_iter = user_map.begin() ; user_iter != user_map.end() ; users_iter++)
	{
		_user = users_iter->second;
		if (_user->socket == user->socket)
		{
			//if their is a match between teh connected user to one of teh users in teh map->
			//initialize _user and break
			break;
		}
	}
	targer = users_map[peerUsr];
	if (target->name != peerUsr)
	{
		writeCommand(user->socket, OPEN_SESSION_ERROR);
			return;
	}
	if ((_user->connectionStatus == false) && (userName.compare(peerUsr) != 0)) //targer user was found
	{
		targer_ip_and_port = target->socket->desrIpAndPort();
		//target_ip_and_port = target->socket->destIpAndPoer();


	}
}