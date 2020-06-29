#include "MPCGUI.h"

MPC_Player::MPC_Player(int playerID){
	thisPlayerID = playerID;
	cout << "player " << thisPlayerID << " created\n";
	initializePlayerData();
}

MPC_Player::MPC_Player(int playerID, int playerSecret){
		
	thisPlayerID = playerID;
	thisPlayerSecret = playerSecret;
	
	initializePlayerData();
	
	cout << "Player " << thisPlayerID << " (secret: " << thisPlayerSecret << ", ";
	cout << "listening port no: " << receiversPortNums.at(thisPlayerID - 1) << ")\n";
	cout << ">>>>>>>>>>>>>>>recent change: sleep for 10 micro seconds, test this more<<<<<<<<<<<<<<<<<<<<<<<<\n";
}

MPC_Player::~MPC_Player() {
	//cout << "player " << thisPlayerID << " distructed\n";
}

int MPC_Player::initializePlayerData() {

	myShareOfS1 = 0;
	myShareOfS2 = 0;
	myShareOfS1plusS2 = 0;
	myShareOfS1timesS2 = 0;
	myShareOfS1timesS2AfterReSharing = 0;
	
	// initializing mySharesOfDifferentSecrets
	for (int i = 0; i < numOfPlayers; i++) {
		mySharesOfDifferentSecrets.push_back(0);
	}
	
	receiversIPAddress = {"127.0.0.1", "127.0.0.1", "127.0.0.1", "127.0.0.1", "127.0.0.1"};
	receiversPortNums = {5555, 5556, 5557, 5558, 5559};

	for (int i = 0; i < numOfPlayers; i++) {
		dataHasBeenSent.push_back(0);
		dataHasBeenReceived.push_back(0);
		dataHasBeenSentInReSharing.push_back(0);
		dataHasBeenReceivedInReSharing.push_back(0);
	}

	for (int i = 0; i < numOfPlayers; i++) {
		if (i == thisPlayerID - 1) {
			dataHasBeenSent.at(i) = 1;
			dataHasBeenReceived.at(i) = 1;

			dataHasBeenSentInReSharing.at(i) = 1;
			dataHasBeenReceivedInReSharing.at(i) = 1;
		} else {
			dataHasBeenSent.at(i) = 0;
			dataHasBeenReceived.at(i) = 0;
			dataHasBeenSentInReSharing.at(i) = 0;
			dataHasBeenReceivedInReSharing.at(i) = 0;
		}
	}
	
	/* print data
	//~ if (thisPlayerID == 3 || thisPlayerID == 4 || thisPlayerID == 5) {
		//~ // players 3, 4, 5 do not send any data to other players in sharing phase
		//~ for (int i = 0; i < numOfPlayers; i++)
			//~ dataHasBeenSent.at(i) = 1;

		//~ // players 3, 4, 5 do not send any data between themselves in sharing phase
		//~ for (int i = 2; i < numOfPlayers; i++)
			//~ dataHasBeenReceived.at(i) = 1;
	//~ }

	//~ if (thisPlayerID == 1) { // player 1 receives data only from player 2
		//~ for (int i = 0; i < numOfPlayers; i++)
			//~ dataHasBeenReceived.at(i) = 1;
		//~ dataHasBeenReceived.at(1) = 0;
	//~ }
	//~ if (thisPlayerID == 2) { // player 2 receives data only from player 1
		//~ for (int i = 0; i < numOfPlayers; i++)
			//~ dataHasBeenReceived.at(i) = 1;
		//~ dataHasBeenReceived.at(0) = 0;
	//~ }

	//~ MatrixModule myMatrixModule;
	//~ cout << "dataHasBeenSent:     ";
	//~ myMatrixModule.printVector(dataHasBeenSent);

	//~ cout << "dataHasBeenReceived: ";
	//~ myMatrixModule.printVector(dataHasBeenReceived);

	//~ cout << "dataHasBeenSentInReSharing:     ";
	//~ myMatrixModule.printVector(dataHasBeenSentInReSharing);

	//~ cout << "dataHasBeenReceivedInReSharing: ";
	//~ myMatrixModule.printVector(dataHasBeenReceivedInReSharing);
	*/
	
	allDataHaveBeenSent = 0;
	allDataHaveBeenReceived = 0;

	allDataHaveBeenSentInReSharing = 0;
	allDataHaveBeenReceivedInReSharing = 0;

	//~ dataForReSharingSenderThread;
	//~ dataForReSharingReceiverThread;

	for (int i = 0; i < numOfPlayers; i++) {
		dataForReSharingSenderThread.mySharesInReSharing.push_back(0);
		dataForReSharingSenderThread.sharesOfOtherPlayersInReSharing.push_back(0); // for debugging
		dataForReSharingReceiverThread.mySharesInReSharing.push_back(0);
	}
	
	//~ dataForSharingSenderThread;
	//~ dataForSharingReceiverThread;
	for (int i = 0; i < numOfPlayers; i++) {
		dataForSharingSenderThread.mySharesOfDifferentSecrets.push_back(0);
		dataForSharingReceiverThread.mySharesOfDifferentSecrets.push_back(0);
	}
	return 1;
}

int MPC_Player::initializeDataForReSharing() {
	allDataHaveBeenSentInReSharing = 0;
	allDataHaveBeenReceivedInReSharing = 0;
	
	//~ for (int i = 0; i < numOfPlayers; i++) {
		//~ dataHasBeenSentInReSharing.push_back(0);
		//~ dataHasBeenReceivedInReSharing.push_back(0);
	//~ }
	
	for (int i = 0; i < numOfPlayers; i++) {
		//cout << "-------------here00----------------\n";
		if (i == thisPlayerID - 1) {
			dataHasBeenSentInReSharing.at(i) = 1;
			dataHasBeenReceivedInReSharing.at(i) = 1;
			//cout << "-------------here01----------------\n";
		} else {
			dataHasBeenSentInReSharing.at(i) = 0;
			dataHasBeenReceivedInReSharing.at(i) = 0;
			//cout << "-------------here02----------------\n";
		}
	}
	
	//~ MatrixModule myMatrixModule;
	//~ cout << "dataHasBeenSentInReSharing:     ";
	//~ myMatrixModule.printVector(dataHasBeenSentInReSharing);

	//~ cout << "dataHasBeenReceivedInReSharing: ";
	//~ myMatrixModule.printVector(dataHasBeenReceivedInReSharing);
	
	//~ dataForReSharingSenderThread;
	//~ dataForReSharingReceiverThread;

	for (int i = 0; i < numOfPlayers; i++) {
		dataForReSharingSenderThread.mySharesInReSharing.push_back(0);
		dataForReSharingReceiverThread.mySharesInReSharing.push_back(0);
	}
	
	return 1;
}

void MPC_Player::error(char *msg) {
	perror(msg);
	exit(1);
}

void MPC_Player::printDots(string str, string sndOrRecv, int numOfDots){
	if(countOfPrintedDots == numOfDots){
		cout << "\n";
		cout << sndOrRecv << std::flush;
		countOfPrintedDots = 1;
	}
	else{
		cout << str << std::flush;
		countOfPrintedDots++;
	}
}

//------------------------------------------------Main Send and Receive Functions------------------------
string MPC_Player::sendDataToOtherPlayerOnThread(string sendingData, string receieverIP, int receieverPortNum) {

	int sockfd, portno = receieverPortNum, n;

	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[1025]; //data buffer of 1K

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//fcntl(sockfd, F_SETFL, O_NONBLOCK); // set to non-blocking [http://beej.us/guide/bgnet/output/html/multipage/fcntlman.html]

	///------------------------------------------------------ August 18{
    //~ struct timeval timeout;      
    //~ timeout.tv_sec = 10;
    //~ timeout.tv_usec = 0;

    //~ if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
        //~ error("setsockopt failed\n");

    //~ if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
        //~ error("setsockopt failed\n");
	///------------------------------------------------------ August 18}
	
	if (sockfd < 0)
		error("ERROR opening socket");

	server = gethostbyname(receieverIP.c_str());
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	memmove((char *) &serv_addr.sin_addr.s_addr, (char *) server->h_addr,
			server->h_length);

	serv_addr.sin_port = htons(portno);

	//~ cout << "Thread 1:sending to " << receieverIP << ":" << receieverPortNum << "==>";
	//~ cout << "Thread 1:sending to " << receieverIP << ":" << receieverPortNum << "\n";
	while (1) {
		int connectionResult = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
		if (connectionResult == 0) {
			//cout << "Conn established with " << inet_ntoa(serv_addr.sin_addr) << ":" << ntohs(serv_addr.sin_port) <<".\n";
			//cout << "\nThread 1:sending to " << inet_ntoa(serv_addr.sin_addr) << ":" << ntohs(serv_addr.sin_port) <<": OK.\n";
			
			break;
		} else {
			//~ if(debugModeSendReceivePorts == 1)
				//~ cout << "Thread 1: sending data to IP:port --> " << receieverIP << ":" << receieverPortNum << " ...\n";
			//~ sleep(waitingTimeInThreads);
			
			//--------------------------------------------------just for printing dots	
			if(debugModePrintingDots == 1)
				printDots("ss1", "send", totalNumOfDots);
			//--------------------------------------------------just for printing dots	
			//sleep(waitingTimeInThreads);
			usleep(waitingTimeInThreadsMicroSec);
		}
	}

	memset(buffer, 0, sizeof(buffer));

	strcpy(buffer, sendingData.c_str());
	n = write(sockfd, buffer, strlen(buffer));

	if (n < 0) {
		error("ERROR in sending data");
		return "data not delivered";
	}

	char buffer2[1025];
	memset(buffer2, 0, sizeof(buffer2));
	//~ n = read(sockfd, buffer2, 1025); // see the below on August 19, for handling the small bug in p2p networking	
	//~ ///------------------------------------------------------ August 19{
	//struct timeval tv = {5, 0};
	//struct timeval tv = {timeIntervalForAcknowledgment, 0}; // seconds
	struct timeval tv = {0, 5};							  // micro seconds
	//setsockopt(cli_socket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
	int elapsedTimeForAcknowledgement = 0;
	while(elapsedTimeForAcknowledgement < totalWaitingTimeForAcknowledgment) {
		// int n = read(sockfd, buffer, 1025);
		int n = read(sockfd, buffer2, 1025);
		
		if (n <= 0) {
			// nothing received from client in last 5 seconds
			//~ cout << "\nnothing received from client in last 5 seconds, trying again..."
				 //~ << "elapsedTimeForAcknowledgement: " << elapsedTimeForAcknowledgement
				 //~ << "" << endl;
			elapsedTimeForAcknowledgement += timeIntervalForAcknowledgment;
			//cout << "\nnothing received from client in last 5 seconds, exiting program...\n";
			//exit(-1);
			break;
		}
	}
	//cout << "------------------------acknowlegdement: " << buffer2 << endl;
	if (n < 0) {
		error("\nERROR reading from socket, acknowlegdement failed.");
		cout << "\n---------------data not delivered:(:(:(:(:(:(:(-------------------\n\n";
		return "data not delivered";
	}
	
	//~ struct timeval tv = {5, 0};
	//~ //setsockopt(cli_socket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
	//~ setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
	//~ char tmpBuffer[1025];
	//~ int cut;
	//~ string bufferString;
	//~ while((cut = bufferString.find("\r\n")) == -1) {
		//~ //int numBytes = recv(cli_socket, tmpBuffer, 100, 0));
		//~ //int numBytes = read(sockfd, buffer, 1025);
		//~ int numBytes = read(sockfd, buffer2, 1025);

		//~ /// Edit: recv does not return EAGAIN else, it return -1 on error.
		//~ /// and in case of timeout, errno is set to EAGAIN or EWOULDBLOCK

		//~ if (numBytes <= 0) {
			//~ // nothing received from client in last 5 seconds
			//~ cout << "\nnothing received from client in last 5 seconds, trying again...\n";
			//~ //cout << "\nnothing received from client in last 5 seconds, exiting program...\n";
			//~ //exit(-1);
			//~ break;
		//~ }

		//~ // bufferString.append(tmpBuffer, numBytes);
		//~ bufferString.append(buffer2, numBytes);
	//~ }
	
	///------------------------------------------------------ August 19}
	
	
	///-----------------------------------------------------------------August 18{
	//~ time_t start, end;
	//~ double elapsed;  // seconds
	//~ start = time(NULL);
	//~ int terminate = 1;
	//~ while (terminate) {
		//~ end = time(NULL);
		//~ elapsed = difftime(end, start);
		//~ if (elapsed >= 5.0 /* seconds */)
			//~ terminate = 0;
		//~ else{  // No need to sleep when 90.0 seconds elapsed.
			//~ usleep(50000);
			//~ n = read(sockfd, buffer2, 1025);
			//~ cout << "\n---------------waiting for receiver acknowledgement...:|:|:|:|\n\n";
		//~ }
	//~ }
	//~ printf("done..\n");
	///-----------------------------------------------------------------August 18}
	
	
	
	
	/*
	//~ if(debugModeP2Ppart == 1)
	//~ cout << "\nTrd 1:sending "<< buffer <<" to " << inet_ntoa(serv_addr.sin_addr) << ":" 
											   //~ << ntohs(serv_addr.sin_port)
		 //~ <<"----acknowlegdement: " << buffer2 << endl;
	//~ // or
	//~ cout << "\nTrd1:sndng <"<< buffer <<"> to " << "--:" 
											   //~ << ntohs(serv_addr.sin_port)
		 //~ <<"----aknwlgdmnt: " << buffer2 << endl;
	*/
	
	//cout << "--------send data: closing socket.\n";
	close(sockfd);

	//return buffer;
	return buffer2;
}

vector<string> MPC_Player::receiveDataFromOtherPlayerOnThread(int listenOnPortNum) {

	vector < string > receivedDataAllPlayers;
	for (int i = 0; i < numOfPlayers; i++) {
		receivedDataAllPlayers.push_back("");
	}
	
	int numOfParticipatedPlayers = 1;

	int opt = TRUE;
	int master_socket, addrlen, new_socket, client_socket[4], max_clients = 4,
			activity, i, valread, sd;
	int max_sd;
	struct sockaddr_in address;

	char buffer[1025];

	//set of socket descriptors
	fd_set readfds;

	//a message
	//~ char *message = "";

	//initialise all client_socket[] to 0 so not checked
	for (i = 0; i < max_clients; i++) {
		client_socket[i] = 0;
	}

	//create a master socket
	if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit (EXIT_FAILURE);
	}

	//set master socket to allow multiple connections , this is just a good habit, it will work without this
	if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt,
			sizeof(opt)) < 0) {
		perror("setsockopt");
		exit (EXIT_FAILURE);
	}

	//type of socket created
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(listenOnPortNum);

	//bind the socket to localhost port number listenOnPortNum
	if (bind(master_socket, (struct sockaddr *) &address, sizeof(address))
			< 0) {
		perror("bind failed:(");
		exit (EXIT_FAILURE);
	}

	//cout << "Listening on port: " << listenOnPortNum << "...\n";

	//try to specify maximum of 4 pending connections for the master socket
	if (listen(master_socket, 4) < 0) {
		perror("listen");
		exit (EXIT_FAILURE);
	}

	//accept the incoming connection
	addrlen = sizeof(address);
	//puts("Waiting for connections ...");

	cout << "Thread 2: receiving data on port: " << listenOnPortNum << "...\n";
	while (1) {
		if(debugModeSendReceivePorts == 1)
			cout << "Thread 2: receiving data on port: " << listenOnPortNum << "...\n";
		
		//--------------------------------------------------just for printing dots	
		if(debugModePrintingDots == 1)
			printDots("rr1", "receive", totalNumOfDots);
		//--------------------------------------------------just for printing dots
		//clear the socket set
		FD_ZERO(&readfds);

		//add master socket to set
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;

		//add child sockets to set
		for (i = 0; i < max_clients; i++) {
			//socket descriptor
			sd = client_socket[i];

			//if valid socket descriptor then add to read list
			if (sd > 0)
				FD_SET(sd, &readfds);

			//highest file descriptor number, need it for the select function
			if (sd > max_sd)
				max_sd = sd;
		}

		//wait for an activity on one of the sockets , timeout is 1 second , so wait for 1 second
		struct timeval tv;
		tv.tv_sec = 1; // time interval of 1 second
		tv.tv_usec = 0;
		activity = select(max_sd + 1, &readfds, NULL, NULL, &tv);

		if ((activity < 0) && (errno != EINTR)) {
			printf("select error");
		}

		//If something happened on the master socket , then its an incoming connection
		if (FD_ISSET(master_socket, &readfds)) {
			if ((new_socket = accept(master_socket,
					(struct sockaddr *) &address, (socklen_t*) &addrlen)) < 0) {
				perror("accept");
				exit (EXIT_FAILURE);
			}

			//inform user of socket number - used in send and receive commands
			if(debugModeConnectionEstablished == 1)
				printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
			numOfParticipatedPlayers++;

			//add new socket to array of sockets
			for (i = 0; i < max_clients; i++) {
				//if position is empty
				if (client_socket[i] == 0) {
					client_socket[i] = new_socket;
					break;
				}
			}
		}

		//else its some IO operation on some other socket :)
		for (i = 0; i < max_clients; i++) {
			sd = client_socket[i];

			if (FD_ISSET(sd, &readfds)) {
				memset(buffer, 0, sizeof(buffer));
				//Check if it was for closing , and also read the incoming message
				if ((valread = read(sd, buffer, 1024)) == 0) {
					//Somebody disconnected , get his details and print
					getpeername(sd, (struct sockaddr*) &address,
							(socklen_t*) &addrlen);

					//Close the socket and mark as 0 in list for reuse
					close(sd);
					client_socket[i] = 0;
				}

				//Echo back the message that came in
				else {

					//--------------------------------------------------------------------- August 15{
					//
					//~ for (int i = 0; i < numOfPlayers; i++) {
						//~ receivedDataAllPlayers.push_back("");
					//~ }
					//~ cout << "------------Here is the received data: " << buffer << endl;
					string bufferStr = buffer;
					for (int i = 0; i < numOfPlayers; i++) {
						string tempStr = "player " + std::to_string(i + 1);
						
						if (bufferStr.find(tempStr) != std::string::npos) {
							if(dataHasBeenReceived.at(i) == 0){
								//~ cout << "\n--------------received value: <" << bufferStr
									 //~ << ">--------from: "<< tempStr << ""
									 //~ << "--------tempStr: "<< tempStr << "\n";
								//~ cout << "--------dataHasBeenReceived.at("<<i<<"): " <<dataHasBeenReceived.at(i)<<"\n";
								
								
								//~ cout << "-----------receive result - Sharing: "
									 //~ << dataHasBeenReceived.at(0) << ", "
									 //~ << dataHasBeenReceived.at(1) << ", "
									 //~ << dataHasBeenReceived.at(2) << ", "
									 //~ << dataHasBeenReceived.at(3) << ", "
									 //~ << dataHasBeenReceived.at(4);
								//~ cout << "  ===>>: " << allDataHaveBeenReceived << endl;
								
								dataHasBeenReceived.at(i) = 1;
								//~ cout << "--------dataHasBeenReceived.at("<<i<<"): " <<dataHasBeenReceived.at(i)<<"\n";
								
								receivedDataAllPlayers.at(i) = buffer;
																 
								string playerIDStr = "player " + std::to_string(thisPlayerID);
								char buffer2[1025];
								memset(buffer2, 0, sizeof(buffer2));
								string acknowlegdement = playerIDStr + ": data received";
								strcpy(buffer2, acknowlegdement.c_str());
								send(sd, buffer2, strlen(buffer2), 0);
								
								// checking if all data have been receieved
								allDataHaveBeenReceived = 1;
								for (int i = 0; i < numOfPlayers; i++) {
									allDataHaveBeenReceived =
											allDataHaveBeenReceived
													&& dataHasBeenReceived.at(i);
								}
								
								//~ cout << "-----------receive result - Sharing: "
									 //~ << dataHasBeenReceived.at(0) << ", "
									 //~ << dataHasBeenReceived.at(1) << ", "
									 //~ << dataHasBeenReceived.at(2) << ", "
									 //~ << dataHasBeenReceived.at(3) << ", "
									 //~ << dataHasBeenReceived.at(4);
								//~ cout << "  ===>>: " << allDataHaveBeenReceived << endl;
							}
							else{
								string playerIDStr = "player " + std::to_string(thisPlayerID);
								char buffer2[1025];
								memset(buffer2, 0, sizeof(buffer2));
								string acknowlegdement = playerIDStr + ": data already received";
								strcpy(buffer2, acknowlegdement.c_str());
								send(sd, buffer2, strlen(buffer2), 0);
							}
						}
					}
					//
					//--------------------------------------------------------------------- August 15}
					
					// checking if all data have been receieved
					allDataHaveBeenReceived = 1;
					for (int i = 0; i < numOfPlayers; i++) {
						allDataHaveBeenReceived = allDataHaveBeenReceived && dataHasBeenReceived.at(i);
					}



					/*
					//cout << "------------Here is the received data: " << buffer << endl;
					receivedDataAllPlayers.push_back(buffer);
					string playerIDStr = "player " + std::to_string(thisPlayerID);
					char buffer2[1025];
					memset(buffer2, 0, sizeof(buffer2));
					string acknowlegdement = playerIDStr + ": data received";
					strcpy(buffer2, acknowlegdement.c_str());
					send(sd, buffer2, strlen(buffer2), 0);

					////////////////////////////////////////////
					string bufferStr = buffer;
					//cout << "---------------------------bufferStr: " << bufferStr <<endl;
					//for (int i = 0; i < numOfPlayers - 1; i++) {
					for (int iii = 0; iii < numOfPlayers; iii++) {
						string tempStr = "player " + std::to_string(iii + 1);
						//cout << "---------------------------tempStr: " << tempStr <<endl;
						if (bufferStr.find(tempStr) != std::string::npos) {
							//cout << "---------------------------tempStr: " << tempStr <<endl;
							dataHasBeenReceived.at(iii) = 1;
							//cout << "-----------data has been received from player "<< iii + 1 << "\n";
						}
					}

					// checking if all data have been receieved
					allDataHaveBeenReceived = 1;
					for (int ii = 0; ii < numOfPlayers; ii++) {
						allDataHaveBeenReceived = allDataHaveBeenReceived && dataHasBeenReceived.at(ii);
					}
					if(debugModeDataSentReceived == 1){
						cout << "-----------dataHasBeenReceived: "
							 << dataHasBeenReceived.at(0) << ", "
							 << dataHasBeenReceived.at(1) << ", "
							 << dataHasBeenReceived.at(2) << ", "
							 << dataHasBeenReceived.at(3) << ", "
							 << dataHasBeenReceived.at(4);
						cout << "  ===>>: " << allDataHaveBeenReceived << endl;
					}
					*/
				}
			}
		}
		if (allDataHaveBeenReceived == 1) {
			if(debugModeP2Ppart == 1)
				cout << "data of all players received, closing the socket...\n";
			close(master_socket);
			break;
		}
	}
	//~ cout << "\n------------------------receivedDataAllPlayers.size(): " << receivedDataAllPlayers.size() << "\n";
	return receivedDataAllPlayers;
}

//------------------------------------------------Sharing Phase Functions------------------------
thread_data MPC_Player::sendingDataThreadFunc(thread_data my_data) {

	vector<int> sharesOfMySecret = my_data.sharesOfMySecret;
	//MatrixModule myMod;
	//cout << "------------------sharesOfMySecret: ";
	//myMod.printVector(sharesOfMySecret);

	//cout << "------------------sending in sharing phase started\n";
	while (allDataHaveBeenSent == 0) {
		
		//cout << "-----------dataHasBeenSent: "
		//~ cout << "-----------send   result - Sharing: "
			 //~ << dataHasBeenSent.at(0) << ", "
			 //~ << dataHasBeenSent.at(1) << ", "
			 //~ << dataHasBeenSent.at(2) << ", "
			 //~ << dataHasBeenSent.at(3) << ", "
			 //~ << dataHasBeenSent.at(4);
		//~ cout << "  ===>> : " << allDataHaveBeenSent << endl;
		
		for (int i = 0; i < numOfPlayers; i++) {
			if (dataHasBeenSent.at(i) == 0) {
				string sendResult = "";
				string sendStr = "";
				sendStr = "player " + std::to_string(thisPlayerID);
				sendStr = sendStr + ": "
						+ std::to_string(sharesOfMySecret.at(i));
				//~ cout << "\n--------sending <" << sendStr << "> to " << receiversIPAddress.at(i) << ":"
					   //~ << receiversPortNums.at(i) << "----result: " << sendResult << endl;
				
				sendResult = sendDataToOtherPlayerOnThread(sendStr,
						receiversIPAddress.at(i), receiversPortNums.at(i));

				//~ cout << "\n--------sending <" << sendStr << "> to " << receiversIPAddress.at(i) << ":"
					   //~ << receiversPortNums.at(i) << "----result: " << sendResult << endl;

				if (sendResult == "player 1: data received" && receiversPortNums.at(i) == 5555) {
					dataHasBeenSent.at(0) = 1;
					//cout << "-----------data has been sent to player 1\n";
				}

				if (sendResult == "player 2: data received" && receiversPortNums.at(i) == 5556) {
					dataHasBeenSent.at(1) = 1;
					//cout << "-----------data has been sent to player 2\n";
				}

				if (sendResult == "player 3: data received" && receiversPortNums.at(i) == 5557) {
					dataHasBeenSent.at(2) = 1;
					//cout << "-----------data has been sent to player 3\n";
				}

				if (sendResult == "player 4: data received" && receiversPortNums.at(i) == 5558) {
					dataHasBeenSent.at(3) = 1;
					//cout << "-----------data has been sent to player 4\n";
				}

				if (sendResult == "player 5: data received" && receiversPortNums.at(i) == 5559) {
					dataHasBeenSent.at(4) = 1;
					//cout << "-----------data has been sent to player 5\n";
				}
			}
		}

		allDataHaveBeenSent = 1;
		for (int i = 0; i < numOfPlayers; i++) {
			allDataHaveBeenSent = allDataHaveBeenSent && dataHasBeenSent.at(i);
		}
		
		//cout << "-----------dataHasBeenSent: "
		//~ cout << "-----------send   result - Sharing: "
			 //~ << dataHasBeenSent.at(0) << ", "
			 //~ << dataHasBeenSent.at(1) << ", "
			 //~ << dataHasBeenSent.at(2) << ", "
			 //~ << dataHasBeenSent.at(3) << ", "
			 //~ << dataHasBeenSent.at(4);
		//~ cout << "  ===>> : " << allDataHaveBeenSent << endl;

		if (allDataHaveBeenSent == 1)
			break;
	}
	//cout << "------------------sending in sharing phase ended\n";

	return my_data;
}

thread_data MPC_Player::receivingDataThreadFunc(thread_data my_data) {

	//cout << "------------------receiving in sharing phase started\n";
	while (allDataHaveBeenReceived == 0) {

		//cout << "-----------dataHasBeenReceived: "
		//~ cout << "-----------receive result - Sharing: "
			 //~ << dataHasBeenReceived.at(0) << ", "
			 //~ << dataHasBeenReceived.at(1) << ", "
			 //~ << dataHasBeenReceived.at(2) << ", "
			 //~ << dataHasBeenReceived.at(3) << ", "
			 //~ << dataHasBeenReceived.at(4);
		//~ cout << "  ===>>: " << allDataHaveBeenReceived << endl;

		vector<int> myReceivedSharesInSharing; //vector for saving received shares
		for (int i = 0; i < numOfPlayers; i++) {
			myReceivedSharesInSharing.push_back(0);
			//my_data.mySharesOfDifferentSecrets.push_back(0);
		}

		// checking if all data have been receieved
		allDataHaveBeenReceived = 1;
		for (int i = 0; i < numOfPlayers; i++) {
			allDataHaveBeenReceived = allDataHaveBeenReceived && dataHasBeenReceived.at(i);
		}

		if (allDataHaveBeenReceived == 1)
			break;

		//for (int i = 0; i < numOfPlayers; i++) {
			//vector < string > receivedData;
		if (allDataHaveBeenReceived == 0){
			vector < string > receivedData;
			receivedData = receiveDataFromOtherPlayerOnThread(receiversPortNums.at(thisPlayerID - 1));
			
			// because string received from player 1 and 2 contains a number in it we need to check if it contains "player 2"
			//for (int i = 0; i < numOfPlayers - 1; i++){
			//for (int i = 0; i < receivedData.size(); i++) {
			//for (int i = 0; i < numOfPlayers; i++) {
			//for (int i = 0; i < numOfPlayers - 1; i++) {
			for (int i = 0; i < numOfPlayers; i++) {
				string str1 = receivedData.at(i);
				//cout << "\n------------------------------receivedData.at("<<i<<"): "<< receivedData.at(i) << endl;
				if (str1.find("player 1") != std::string::npos) {
					//dataHasBeenReceived.at(0) = 1;
					try{
						dataHasBeenReceived.at(0) = 1;
					} catch(const std::exception& e){
						cout << "\n\n\ngot it\n\n\n";
						std::cout << e.what();
					}
					
					//cout << "-----------data has been received from player 1\n";

					str1.erase(0, 9); // here we remove ID of other player to get his share out of his sent string
					myShareOfS1 = std::stoi(str1);
					//my_data->myShareOfS1 = myShareOfS1;
					my_data.myShareOfS1 = myShareOfS1;
					my_data.mySharesOfDifferentSecrets.at(0) = myShareOfS1;
					//cout << "---myShareOfS1: " << myShareOfS1 << endl;
					//cout << "---my_data.mySharesOfDifferentSecrets.at(0): " << my_data.mySharesOfDifferentSecrets.at(0) << endl;
				}

				if (str1.find("player 2") != std::string::npos) {
					//dataHasBeenReceived.at(1) = 1;
					
					try{
						dataHasBeenReceived.at(1) = 1;
					} catch(const std::exception& e){
						cout << "\n\n\ngot it\n\n\n";
						std::cout << e.what();
					}
					
					//cout << "-----------data has been received from player 2\n";

					str1.erase(0, 9); // here we remove ID of other player to get his share out of his sent string
					myShareOfS2 = std::stoi(str1);
					//my_data->myShareOfS2 = myShareOfS2;
					my_data.myShareOfS2 = myShareOfS2;
					my_data.mySharesOfDifferentSecrets.at(1) = myShareOfS2;
					//cout << "---myShareOfS2: " << myShareOfS2 << endl;
					//cout << "---my_data.mySharesOfDifferentSecrets.at(1): " << my_data.mySharesOfDifferentSecrets.at(1) << endl;
				}

				if (str1.find("player 3") != std::string::npos) {
					//dataHasBeenReceived.at(2) = 1;
					try{
						dataHasBeenReceived.at(2) = 1;
					} catch(const std::exception& e){
						cout << "\n\n\ngot it\n\n\n";
						std::cout << e.what();
					}
					
					//cout << "-----------data has been received from player 3\n";
					
					str1.erase(0, 9); // here we remove ID of other player to get his share out of his sent string
					int myShareOfS3 = std::stoi(str1);
					my_data.mySharesOfDifferentSecrets.at(2) = myShareOfS3;
					//cout << "---myShareOfS3: " << myShareOfS3 << endl;
					//cout << "---my_data.mySharesOfDifferentSecrets.at(2): " << my_data.mySharesOfDifferentSecrets.at(2) << endl;
				}

				if (str1.find("player 4") != std::string::npos) {
					//dataHasBeenReceived.at(3) = 1;
					try{
						dataHasBeenReceived.at(3) = 1;
					} catch(const std::exception& e){
						cout << "\n\n\ngot it\n\n\n";
						std::cout << e.what();
					}
					//cout << "-----------data has been received from player 4\n";
					
					str1.erase(0, 9); // here we remove ID of other player to get his share out of his sent string
					int myShareOfS4 = std::stoi(str1);
					my_data.mySharesOfDifferentSecrets.at(3) = myShareOfS4;
					//cout << "---myShareOfS4: " << myShareOfS4 << endl;
					//cout << "---my_data.mySharesOfDifferentSecrets.at(3): " << my_data.mySharesOfDifferentSecrets.at(3) << endl;
				}

				if (str1.find("player 5") != std::string::npos) {
					//dataHasBeenReceived.at(4) = 1;
					try{
						dataHasBeenReceived.at(4) = 1;
					} catch(const std::exception& e){
						cout << "\n\n\ngot it\n\n\n";
						std::cout << e.what();
					}
					//cout << "-----------data has been received from player 5\n";
					
					str1.erase(0, 9); // here we remove ID of other player to get his share out of his sent string
					int myShareOfS5 = std::stoi(str1);
					my_data.mySharesOfDifferentSecrets.at(4) = myShareOfS5;
					//cout << "---myShareOfS5: " << myShareOfS5 << endl;
					//cout << "---my_data.mySharesOfDifferentSecrets.at(4): " << my_data.mySharesOfDifferentSecrets.at(4) << endl;
				}
			}
			
			// checking if all data have been receieved
			allDataHaveBeenReceived = 1;
			for (int i = 0; i < numOfPlayers; i++) {
				allDataHaveBeenReceived = allDataHaveBeenReceived && dataHasBeenReceived.at(i);
			}

			//cout << "-----------dataHasBeenReceived: "
			//~ cout << "-----------receive result - Sharing: "
				 //~ << dataHasBeenReceived.at(0) << ", "
				 //~ << dataHasBeenReceived.at(1) << ", "
				 //~ << dataHasBeenReceived.at(2) << ", "
				 //~ << dataHasBeenReceived.at(3) << ", "
				 //~ << dataHasBeenReceived.at(4);
			//~ cout << "  ===>>: " << allDataHaveBeenReceived << endl;
			
			if (allDataHaveBeenReceived == 1) {
				break;
			}
		}
		//} //for (int i = 0; i < numOfPlayers; i++)
		if (allDataHaveBeenReceived == 1) {
			break;
		}
	}
	
	//~ MatrixModule myMatrixModule;
	//~ cout << "\n----------my_data.mySharesOfDifferentSecrets: ";
	//~ myMatrixModule.printVector(my_data.mySharesOfDifferentSecrets);
	
	// returning received data to sharing function, so it cntinues ...
	dataForSharingReceiverThread.mySharesOfDifferentSecrets = my_data.mySharesOfDifferentSecrets;
	
	//cout << "------------------receiving in sharing phase ended\n";

	return my_data;
}

//------------------------------------------------ReSharing Phase Functions------------------------
vector<string> MPC_Player::receiveDataFromOtherPlayerInReSharing(int listenOnPortNum) {
	vector < string > receivedDataInReSharingAllPlayers = {"", "", "", "", ""};

	int opt = TRUE;
	int master_socket, addrlen, new_socket, client_socket[4], max_clients = 4,
			activity, i, valread, sd;
	int max_sd;
	struct sockaddr_in address;

	char buffer[1025];

	//set of socket descriptors
	fd_set readfds;

	//a message
	//~ char *message = "";

	//initialise all client_socket[] to 0 so not checked
	for (i = 0; i < max_clients; i++) {
		client_socket[i] = 0;
	}

	//create a master socket
	if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit (EXIT_FAILURE);
	}

	//set master socket to allow multiple connections , this is just a good habit, it will work without this
	if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt,
			sizeof(opt)) < 0) {
		perror("setsockopt");
		exit (EXIT_FAILURE);
	}

	//type of socket created
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(listenOnPortNum);

	//bind the socket to localhost port number listenOnPortNum
	if (bind(master_socket, (struct sockaddr *) &address, sizeof(address))
			< 0) {
		perror("bind failed:(");
		exit (EXIT_FAILURE);
	}

	//cout << "Listening on port: " << listenOnPortNum << "...\n";

	//try to specify maximum of 4 pending connections for the master socket
	if (listen(master_socket, 4) < 0) {
		perror("listen");
		exit (EXIT_FAILURE);
	}

	//accept the incoming connection
	addrlen = sizeof(address);
	//puts("Waiting for connections ...");

	//~ cout << "Thread 2: receiving data on port: " << listenOnPortNum << "...\n";
	
	while (1) {
		//cout << "Thread 2: receiving data on port: " << listenOnPortNum << "...\n";
		
		//--------------------------------------------------just for printing dots
		if(debugModePrintingDots == 1)
			printDots("rr2", "receive", totalNumOfDots);
		//--------------------------------------------------just for printing dots
		
		//clear the socket set
		FD_ZERO(&readfds);

		//add master socket to set
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;

		//add child sockets to set
		for (i = 0; i < max_clients; i++) {
			//socket descriptor
			sd = client_socket[i];

			//if valid socket descriptor then add to read list
			if (sd > 0)
				FD_SET(sd, &readfds);

			//highest file descriptor number, need it for the select function
			if (sd > max_sd)
				max_sd = sd;
		}

		//wait for an activity on one of the sockets , timeout is 1 second , so wait for 1 second
		struct timeval tv;
		tv.tv_sec = 1; // time interval of 1 second
		tv.tv_usec = 0;
		activity = select(max_sd + 1, &readfds, NULL, NULL, &tv);

		if ((activity < 0) && (errno != EINTR)) {
			printf("select error");
		}

		//If something happened on the master socket , then its an incoming connection
		if (FD_ISSET(master_socket, &readfds)) {
			if ((new_socket = accept(master_socket,
					(struct sockaddr *) &address, (socklen_t*) &addrlen)) < 0) {
				perror("accept");
				exit (EXIT_FAILURE);
			}

			//inform user of socket number - used in send and receive commands
			//printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
			//numOfParticipatedPlayers++;

			//add new socket to array of sockets
			for (i = 0; i < max_clients; i++) {
				//if position is empty
				if (client_socket[i] == 0) {
					client_socket[i] = new_socket;
					break;
				}
			}
		}

		//else its some IO operation on some other socket :)
		for (i = 0; i < max_clients; i++) {
			sd = client_socket[i];
			if (FD_ISSET(sd, &readfds)) {
				memset(buffer, 0, sizeof(buffer));
				//Check if it was for closing , and also read the incoming message
				if ((valread = read(sd, buffer, 1024)) == 0) {
					//Somebody disconnected , get his details and print
					getpeername(sd, (struct sockaddr*) &address,
							(socklen_t*) &addrlen);

					//Close the socket and mark as 0 in list for reuse
					close(sd);
					client_socket[i] = 0;
				}

				//Echo back the message that came in
				else {
					
					//--------------------------------------------------------------------- August 15{
					//
					//~ for (int i = 0; i < numOfPlayers; i++) {
						//~ receivedDataInReSharingAllPlayers.push_back("");
					//~ }
					
					string bufferStr = buffer;
					for (int i = 0; i < numOfPlayers; i++) {
						//cout <<"\n*************************iiiiiii*****************************"<< i << "\n";
						string player1 = "player 1";
						if (bufferStr.find(player1) != std::string::npos){
							//cout <<"\n*************************player 1*****************************" << "\n";
						}
						
						
						string tempStr = "player " + std::to_string(i + 1);
						
						//if (bufferStr.find(tempStr) != std::string::npos && dataHasBeenReceivedInReSharing.at(i) == 0) {
						if (bufferStr.find(tempStr) != std::string::npos) {
							if(dataHasBeenReceivedInReSharing.at(i) == 0){
								//~ cout << "\n--------------received value: <" << bufferStr
									 //~ << ">--------from: "<< tempStr << ""
									 //~ << "--------tempStr: "<< tempStr << "\n";
								//~ cout << "--------dataHasBeenReceivedInReSharing.at("<<i<<"): " <<dataHasBeenReceivedInReSharing.at(i)<<"\n";
								
								
								//~ cout << "-----------receive result - ReSharing: "
									 //~ << dataHasBeenReceivedInReSharing.at(0) << ", "
									 //~ << dataHasBeenReceivedInReSharing.at(1) << ", "
									 //~ << dataHasBeenReceivedInReSharing.at(2) << ", "
									 //~ << dataHasBeenReceivedInReSharing.at(3) << ", "
									 //~ << dataHasBeenReceivedInReSharing.at(4);
								//~ cout << "  ===>>: " << allDataHaveBeenReceivedInReSharing << endl;
								
								dataHasBeenReceivedInReSharing.at(i) = 1;
								//~ cout << "--------dataHasBeenReceivedInReSharing.at("<<i<<"): " <<dataHasBeenReceivedInReSharing.at(i)<<"\n";
								
								receivedDataInReSharingAllPlayers.at(i) = buffer;
																 
								string playerIDStr = "player " + std::to_string(thisPlayerID);
								char buffer2[1025];
								memset(buffer2, 0, sizeof(buffer2));
								string acknowlegdement = playerIDStr + ": data received";
								strcpy(buffer2, acknowlegdement.c_str());
								send(sd, buffer2, strlen(buffer2), 0);
								
								// checking if all data have been receieved
								allDataHaveBeenReceivedInReSharing = 1;
								for (int i = 0; i < numOfPlayers; i++) {
									allDataHaveBeenReceivedInReSharing =
											allDataHaveBeenReceivedInReSharing
													&& dataHasBeenReceivedInReSharing.at(i);
								}
								
								//~ cout << "-----------receive result - ReSharing: "
									 //~ << dataHasBeenReceivedInReSharing.at(0) << ", "
									 //~ << dataHasBeenReceivedInReSharing.at(1) << ", "
									 //~ << dataHasBeenReceivedInReSharing.at(2) << ", "
									 //~ << dataHasBeenReceivedInReSharing.at(3) << ", "
									 //~ << dataHasBeenReceivedInReSharing.at(4);
								//~ cout << "  ===>>: " << allDataHaveBeenReceivedInReSharing << endl;
							}
							else{
								string playerIDStr = "player " + std::to_string(thisPlayerID);
								char buffer2[1025];
								memset(buffer2, 0, sizeof(buffer2));
								string acknowlegdement = playerIDStr + ": data already received";
								strcpy(buffer2, acknowlegdement.c_str());
								send(sd, buffer2, strlen(buffer2), 0);
							}
						}
					}
					//
					//--------------------------------------------------------------------- August 15}
					
					
					/*
					//cout << "------------Here is the received data: " << buffer << endl;
					receivedDataInReSharingAllPlayers.push_back(buffer);
					string playerIDStr = "player " + std::to_string(thisPlayerID);
					char buffer2[1025];
					memset(buffer2, 0, sizeof(buffer2));
					string acknowlegdement = playerIDStr + ": data received";
					strcpy(buffer2, acknowlegdement.c_str());
					send(sd, buffer2, strlen(buffer2), 0);
					
					////////////////////////////////////////////
					
					string bufferStr = buffer;
					//cout << "---------------------------bufferStr: " << bufferStr <<endl;
					//for (int i = 0; i < numOfPlayers - 1; i++){
					for (int i = 0; i < numOfPlayers; i++) {
						string tempStr = "player " + std::to_string(i + 1);
						//~ cout << "------------------bufferStr: " << bufferStr;
						//~ cout << "-------tempStr: " << tempStr;
						//~ cout << "-------i: " << i <<endl;
						//~ cout << "------------------dataHasBeenReceivedInReSharing.at(" << i <<") = "
							 //~ << dataHasBeenReceivedInReSharing.at(i)<<endl;
						if (bufferStr.find(tempStr) != std::string::npos) {
							//~ cout << "---------------------------tempStr: " << tempStr <<endl;
							dataHasBeenReceivedInReSharing.at(i) = 1;
							//~ cout << "-----------data has been received from player "<< i + 1 << "\n";
							//~ cout << "--------------tempStr: " << tempStr
								 //~ <<"--------data has been received from player "<< i + 1 << "\n";
							cout << "--------------tempStr: " << tempStr
								 <<"--------bufferStr: "<< bufferStr << "\n";
								 
			 				cout << "-----------receive result - ReSharing: "
								 << dataHasBeenReceivedInReSharing.at(0) << ", "
								 << dataHasBeenReceivedInReSharing.at(1) << ", "
								 << dataHasBeenReceivedInReSharing.at(2) << ", "
								 << dataHasBeenReceivedInReSharing.at(3) << ", "
								 << dataHasBeenReceivedInReSharing.at(4);
							cout << "  ===>>: " << allDataHaveBeenReceivedInReSharing << endl;
						}
						//~ cout << "------------------dataHasBeenReceivedInReSharing.at(" << i <<") = "
							 //~ <<dataHasBeenReceivedInReSharing.at(i)<<endl;
					}
					*/
					
					// checking if all data have been receieved
					allDataHaveBeenReceivedInReSharing = 1;
					for (int i = 0; i < numOfPlayers; i++) {
						allDataHaveBeenReceivedInReSharing =
								allDataHaveBeenReceivedInReSharing
										&& dataHasBeenReceivedInReSharing.at(i);
					}
				}
			}
			
			//~ if(debugModeDataSentReceived == 1){
				//~ //cout << "-----------dataHasBeenReceivedInReSharing: "
				//~ cout << "-----------receive result - ReSharing: "
					 //~ << dataHasBeenReceivedInReSharing.at(0) << ", "
					 //~ << dataHasBeenReceivedInReSharing.at(1) << ", "
					 //~ << dataHasBeenReceivedInReSharing.at(2) << ", "
					 //~ << dataHasBeenReceivedInReSharing.at(3) << ", "
					 //~ << dataHasBeenReceivedInReSharing.at(4);
				//~ cout << "  ===>>: " << allDataHaveBeenReceivedInReSharing << endl;
			//~ }
			
			//cout << "\n----------here:(:(:(----------receive result - ReSharing: "<< allDataHaveBeenReceivedInReSharing <<"\n";
		}
		if (allDataHaveBeenReceivedInReSharing == 1) {
			//cout << "data of all players received, closing the socket...\n";
			close(master_socket);
			break;
		}
	}
	
	
	//-----------------------------------------------prining the content of receivedDataInReSharingAllPlayers
	//~ cout << "\n";
	//~ cout << "----------receivedDataInReSharingAllPlayers: ";
	//~ //for (int i = 0; i < receivedDataInReSharingAllPlayers.size(); i++){
	//~ for (unsigned i = 0; i < receivedDataInReSharingAllPlayers.size(); i++){
		//~ try {
			//~ cout << receivedDataInReSharingAllPlayers.at(i) << "   ";
		//~ } catch (const std::exception& e) { // caught by reference to base
			//~ std::cout << " a standard exception was caught, with message '"
					  //~ << e.what() << "'\n";
		//~ }
	//~ }
	//~ cout << "\n";

	//~ cout << "\n------------------------receivedDataInReSharingAllPlayers.size(): " 
		 //~ << receivedDataInReSharingAllPlayers.size() << "\n";
	
	//cout << "------------------end of receiveDataFromOtherPlayerInReSharing-------\n";
	return receivedDataInReSharingAllPlayers;
}

thread_data MPC_Player::senderThreadFuncInReSharing(thread_data my_data) {

	//~ PolynomialModule myPoly;
	//~ MatrixModule myMatrixModule;

	vector<int> sharesOfPlayers = my_data.sharesOfOtherPlayersInReSharing;
	
	if(debugModeSendReceiveThreads == 1)
		cout << "------------------sending in resharing phase started\n";
		
	while (allDataHaveBeenSentInReSharing == 0) {
			
			//--------------------------------------------------just for printing dots
			if(debugModePrintingDots == 1)
				printDots("ss2", "send", totalNumOfDots);
			//--------------------------------------------------just for printing dots	
		
		//~ if (debugModeDataSentReceived == 1){
			//~ //cout << "-----------dataHasBeenSentInReSharing: "
			//~ cout << "\n-----------send result - ReSharing: "
				 //~ << dataHasBeenSentInReSharing.at(0) << ", "
				 //~ << dataHasBeenSentInReSharing.at(1) << ", "
				 //~ << dataHasBeenSentInReSharing.at(2) << ", "
				 //~ << dataHasBeenSentInReSharing.at(3) << ", "
				 //~ << dataHasBeenSentInReSharing.at(4);
			//~ cout << "  ===>> : " << allDataHaveBeenSentInReSharing << endl;
		//~ }
		
		for (int i = 0; i < numOfPlayers; i++) {
			//~ string sendResult = "";
			//~ string sendStr = "";
			if (dataHasBeenSentInReSharing.at(i) == 0) {
				string sendResult = "";
				string sendStr = "";
				
				sendStr = "player " + std::to_string(thisPlayerID);
				sendStr = sendStr + ": " + std::to_string(sharesOfPlayers.at(i));
				
				//~ cout << "\n--------sending <" << sendStr << "> to " << receiversIPAddress.at(i) << ":"
									   //~ << receiversPortNums.at(i) << "----result: " << sendResult << endl;
									   
				sendResult = sendDataToOtherPlayerOnThread(sendStr, receiversIPAddress.at(i), receiversPortNums.at(i));
				
				//~ cout << "\n--------sending <" << sendStr << "> to " << receiversIPAddress.at(i) << ":"
									   //~ << receiversPortNums.at(i) << "----result: " << sendResult << endl;
				
				//~ if(debugModeSendReceiveThreads == 1)
					//~ cout << "\n---------------sendResult: " << sendResult << endl;
				if (sendResult == "player 1: data received" && receiversPortNums.at(i) == 5555) {
					dataHasBeenSentInReSharing.at(0) = 1;
					
					//~ if(debugModeSendReceiveThreads == 1)
						//~ cout << "-----------ReSharing: data has been sent to player 1\n";
				}

				if (sendResult == "player 2: data received" && receiversPortNums.at(i) == 5556) {
					dataHasBeenSentInReSharing.at(1) = 1;
					
					//~ if(debugModeSendReceiveThreads == 1)
						//~ cout << "-----------ReSharing: data has been sent to player 2\n";
				}

				if (sendResult == "player 3: data received" && receiversPortNums.at(i) == 5557) {
					dataHasBeenSentInReSharing.at(2) = 1;
					
					//~ if(debugModeSendReceiveThreads == 1)
						//~ cout << "-----------ReSharing: data has been sent to player 3\n";
				}
				if (sendResult == "player 4: data received" && receiversPortNums.at(i) == 5558) {
					dataHasBeenSentInReSharing.at(3) = 1;
					
					//~ if(debugModeSendReceiveThreads == 1)
						//~ cout << "-----------ReSharing: data has been sent to player 4\n";
				}

				if (sendResult == "player 5: data received" && receiversPortNums.at(i) == 5559) {
					dataHasBeenSentInReSharing.at(4) = 1;
					
					//~ if(debugModeSendReceiveThreads == 1)
						//~ cout << "-----------ReSharing: data has been sent to player 5\n";
				}
			}
			//--------------------------------------------------just for printing dots
			if(debugModePrintingDots == 1)
				printDots("ss3", "send", totalNumOfDots);
			//--------------------------------------------------just for printing dots
			
			allDataHaveBeenSentInReSharing = 1;
			for (int i = 0; i < numOfPlayers; i++) {
				allDataHaveBeenSentInReSharing = allDataHaveBeenSentInReSharing && dataHasBeenSentInReSharing.at(i);
			}
			
			//~ cout << "\n-----------send result - ReSharing: "
				 //~ << dataHasBeenSentInReSharing.at(0) << ", "
				 //~ << dataHasBeenSentInReSharing.at(1) << ", "
				 //~ << dataHasBeenSentInReSharing.at(2) << ", "
				 //~ << dataHasBeenSentInReSharing.at(3) << ", "
				 //~ << dataHasBeenSentInReSharing.at(4);
			//~ cout << "  ===>> : " << allDataHaveBeenSentInReSharing << endl;
			
		}

		if (allDataHaveBeenSentInReSharing == 1)
			break;
	}
	
	if(debugModeSendReceiveThreads == 1)
		cout << "------------------sending in resharing phase ended\n";

	return my_data;
}

thread_data MPC_Player::receiverThreadFuncInReSharing(thread_data my_data) {

	vector<int> mySharesInReSharing;
	for (int i = 0; i < numOfPlayers; i++) {
		mySharesInReSharing.push_back(0);
	}

	//cout << "------------------mySharesInReSharing.size(): " << mySharesInReSharing.size() << endl;
	
	if(debugModeSendReceiveThreads == 1)
		cout << "------------------receiving in resharing phase started\n";
	while (allDataHaveBeenReceivedInReSharing == 0) {
		
		if (debugModeDataSentReceived == 1){
			//cout << "-----------dataHasBeenReceivedInReSharing: "
			cout << "-----------receive result - ReSharing: "
				 << dataHasBeenReceivedInReSharing.at(0) << ", "
				 << dataHasBeenReceivedInReSharing.at(1) << ", "
				 << dataHasBeenReceivedInReSharing.at(2) << ", "
				 << dataHasBeenReceivedInReSharing.at(3) << ", "
				 << dataHasBeenReceivedInReSharing.at(4);
			cout << "  ===>> : " << allDataHaveBeenReceivedInReSharing << endl;
		}
		
		// checking if all data have been receieved
		allDataHaveBeenReceivedInReSharing = 1;
		for (int i = 0; i < numOfPlayers; i++) {
			allDataHaveBeenReceivedInReSharing =
					allDataHaveBeenReceivedInReSharing
							&& dataHasBeenReceivedInReSharing.at(i);
		}

		if (allDataHaveBeenReceivedInReSharing == 1)
			break;

		//~ for (int i = 0; i < numOfPlayers; i++) {
			//~ vector < string > receivedData;
		if (allDataHaveBeenReceivedInReSharing == 0){
			vector < string > receivedData;
			receivedData = receiveDataFromOtherPlayerInReSharing(receiversPortNums.at(thisPlayerID - 1));

			// in resharing all players exchange data, so we need to extract the secret shares out of exchanged strings
			// that's the reason for using "str1.erase(0, 9);" in the following codes
			//for (int i = 0; i < numOfPlayers - 1; i++) {
			//for (int i = 0; i < numOfPlayers; i++) {
			//for (int i = 0; i < numOfPlayers - 1; i++) {
			for (int i = 0; i < numOfPlayers; i++) {
				string str1 = receivedData.at(i);
				//cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^receivedData.at("<< i << "):" << receivedData.at(i) << endl;
				if (str1.find("player 1") != std::string::npos) { // this means that the data has come from player 1
					dataHasBeenReceivedInReSharing.at(0) = 1;
					
					if (debugModeDataSentReceived == 1)
						cout << "-----------data has been received from player 1\n";

					str1.erase(0, 9);
					int shareOfPlayer1InReSharingForMe = std::stoi(str1);
					mySharesInReSharing.at(0) = shareOfPlayer1InReSharingForMe;
					
					if (debugModeDataSentReceived == 1)
						cout << "shareOfPlayer1InReSharingForMe: " << shareOfPlayer1InReSharingForMe << endl;
				}

				if (str1.find("player 2") != std::string::npos) { // this means that the data has come from player 2
					dataHasBeenReceivedInReSharing.at(1) = 1;
					
					if (debugModeDataSentReceived == 1)
						cout << "-----------data has been received from player 2\n";

					str1.erase(0, 9);
					int shareOfPlayer2InReSharingForMe = std::stoi(str1);
					mySharesInReSharing.at(1) = shareOfPlayer2InReSharingForMe;
					
					if (debugModeDataSentReceived == 1)
						cout << "shareOfPlayer2InReSharingForMe: " << shareOfPlayer2InReSharingForMe << endl;
				}

				if (str1.find("player 3") != std::string::npos) { // this means that the data has come from player 3
					dataHasBeenReceivedInReSharing.at(2) = 1;
					
					if (debugModeDataSentReceived == 1)
						cout << "-----------data has been received from player 3\n";

					str1.erase(0, 9);
					int shareOfPlayer3InReSharingForMe = std::stoi(str1);
					mySharesInReSharing.at(2) = shareOfPlayer3InReSharingForMe;
					
					if (debugModeDataSentReceived == 1)
						cout << "shareOfPlayer3InReSharingForMe: " << shareOfPlayer3InReSharingForMe << endl;
				}

				if (str1.find("player 4") != std::string::npos) { // this means that the data has been come from player 4
					dataHasBeenReceivedInReSharing.at(3) = 1;
					
					if (debugModeDataSentReceived == 1)
						cout << "-----------data has been received from player 4\n";

					str1.erase(0, 9);
					int shareOfPlayer4InReSharingForMe = std::stoi(str1);
					mySharesInReSharing.at(3) = shareOfPlayer4InReSharingForMe;
					
					if (debugModeDataSentReceived == 1)
						cout << "shareOfPlayer4InReSharingForMe: " << shareOfPlayer4InReSharingForMe << endl;
				}

				if (str1.find("player 5") != std::string::npos) { // this means that the data has been come from player 5
					dataHasBeenReceivedInReSharing.at(4) = 1;
					
					if (debugModeDataSentReceived == 1)
						cout << "-----------data has been received from player 5\n";

					str1.erase(0, 9);
					int shareOfPlayer5InReSharingForMe = std::stoi(str1);
					mySharesInReSharing.at(4) = shareOfPlayer5InReSharingForMe;
					
					if (debugModeDataSentReceived == 1)
						cout << "shareOfPlayer5InReSharingForMe: " << shareOfPlayer5InReSharingForMe << endl;
				}
			}
			
			// checking if all data have been receieved
			allDataHaveBeenReceivedInReSharing = 1;
			for (int i = 0; i < numOfPlayers; i++) {
				allDataHaveBeenReceivedInReSharing = allDataHaveBeenReceivedInReSharing && dataHasBeenReceivedInReSharing.at(i);
			}
			
			if (debugModeDataSentReceived == 1){
				//cout << "-----------dataHasBeenReceivedInReSharing: "
				cout << "-----------receive result - ReSharing: "
					 << dataHasBeenReceivedInReSharing.at(0) << ", "
					 << dataHasBeenReceivedInReSharing.at(1) << ", "
					 << dataHasBeenReceivedInReSharing.at(2) << ", "
					 << dataHasBeenReceivedInReSharing.at(3) << ", "
					 << dataHasBeenReceivedInReSharing.at(4);
				cout << "  ===>> : " << allDataHaveBeenReceivedInReSharing << endl;
			}
			if (allDataHaveBeenReceivedInReSharing == 1) {
				break;
			}
			//}
			//~ if (allDataHaveBeenReceivedInReSharing == 1) { //revise this part
				//~ break;
			//~ }
		}
		//~ } //for (int i = 0; i < numOfPlayers; i++)
		
		if (allDataHaveBeenReceivedInReSharing == 1) {
			break;
		}
	}

	// returning received data to resharing function, so it cntinues ...
	dataForReSharingReceiverThread.mySharesInReSharing = mySharesInReSharing;
	
	if(debugModeSendReceiveThreads == 1)
		cout << "------------------receiving in resharing phase ended\n";

	return my_data;
}


vector<int> MPC_Player::calculatePlayerShares(int playerSecret) {
	PolynomialModule myPoly;
	MatrixModule myMatrixModule;
	//vector <int> mySecretPoly = myPoly.GetRandCoeff(threshold + 1, thisPlayerSecret, p);
	vector<int> mySecretPoly = myPoly.GetRandCoeff(threshold + 1, playerSecret, p);
	cout << "-----My secret polynomial: ";
	myPoly.PrintPoly(mySecretPoly);

	vector<int> sharesOfMySecret;
	for (int i = 0; i < numOfPlayers; i++) {
		int shareOfPlayeri = myPoly.evaluatePolynomial(mySecretPoly, i + 1, p);
		sharesOfMySecret.push_back(shareOfPlayeri);
	}
	cout << "-----sharesOfMySecret: ";
	myMatrixModule.printVector(sharesOfMySecret);

	return sharesOfMySecret;
}

vector <int> MPC_Player::doSharing(int mySecret) {
//int MPC_Player::doSharing(int mySecret) {
	//initializePlayerData();
	struct thread_data dataForSendingThread, dataForRecevingThread;

	vector <int> myShares = calculatePlayerShares(mySecret);
	
	dataForSendingThread.sharesOfMySecret = myShares;
		
	std::thread sendThread;
	sendThread = std::thread(&MPC_Player::sendingDataThreadFunc, this, dataForSendingThread);
	
	std::thread receiveThread;
	receiveThread = std::thread(&MPC_Player::receivingDataThreadFunc, this, std::ref(dataForSharingReceiverThread));
	
	sendThread.join();
	receiveThread.join();
	//cout << "------------sharing threads joined---------------\n";
	
	for (int i = 0; i < numOfPlayers; i++){
		//cout << "---dataForSharingReceiverThread.mySharesOfDifferentSecrets.at(i): " << dataForSharingReceiverThread.mySharesOfDifferentSecrets.at(i) << endl;
		mySharesOfDifferentSecrets.at(i) = dataForSharingReceiverThread.mySharesOfDifferentSecrets.at(i);
	}
	
	mySharesOfDifferentSecrets.at(thisPlayerID - 1) = myShares.at(thisPlayerID - 1);
	
	//~ MatrixModule myMatrixModule;
	//~ cout << "\n----------mySharesOfDifferentSecrets: ";
	//~ myMatrixModule.printVector(mySharesOfDifferentSecrets);
	
	return mySharesOfDifferentSecrets;
}

int MPC_Player::doReSharing(int newSecretShare) {
	PolynomialModule myPolyModule;
	MatrixModule myMatrixModule;
	
	// generate an h poly
	vector<int> myHpoly = myPolyModule.generateRandomPolynomial(threshold, newSecretShare, p);
	//vector <int> myHpoly= {newSecretShare, 1, 1};
	//~ cout << "myHpoly: ";
	//~ myPolyModule.PrintPoly(myHpoly);

	// calculate all players' shares
	vector<int> sharesOfPlayers;
	for (int i = 0; i < numOfPlayers; i++) {
		int shareOfPlayerI = myPolyModule.evaluatePolynomial(myHpoly, i + 1, p);
		sharesOfPlayers.push_back(shareOfPlayerI);
	}
	//~ cout << "\n-------------------------------------sharesOfPlayers.size(): " << sharesOfPlayers.size() << endl;
	//~ cout << "\n-------shares of players in resharing (using h poly): ";
	//~ myMatrixModule.printVector(sharesOfPlayers);
	
	//putting players data in struct to pass them to thread for sending to them:
	dataForReSharingSenderThread.sharesOfOtherPlayersInReSharing = sharesOfPlayers;
	//~ myMatrixModule.printVector(dataForReSharingSenderThread.sharesOfOtherPlayersInReSharing);
	
	
	initializeDataForReSharing(); ///------------------------------------this is important
	std::thread senderThreadInReSharing(&MPC_Player::senderThreadFuncInReSharing, this, dataForReSharingSenderThread);
	
	/* good, but data is not exchanged correctly, before testing async again */
	std::thread receiverThreadInReSharing(&MPC_Player::receiverThreadFuncInReSharing, this,
											std::ref(dataForReSharingReceiverThread));
	
	/* good, but data is not exchanged correctly, before testing async again*/
	senderThreadInReSharing.join();
	receiverThreadInReSharing.join();
	//cout << "-----receiverThreadInReSharing joined\n";
	//cout << "-----senderThreadInReSharing  and  receiverThreadInReSharing joined\n";
	
	/*
	auto f1 = std::async(&MPC_Player::senderThreadFuncInReSharing, this,  dataForReSharingSenderThread);
	auto f2 = std::async(&MPC_Player::receiverThreadFuncInReSharing, this, dataForReSharingReceiverThread);

	auto res1 = f1.get();
	auto res2 = f2.get();
	
	auto status = f2.wait_for(std::chrono::seconds(0));
	if (status == std::future_status::ready)
		cout << "thread finished\n";
	else
		cout << "thread still running\n";

	//dataForSendingThread = res1;
	//dataForRecevingThread = res2;
	//cout << "-------------dataForRecevingThread.myShareOfS2: " << res2.myShareOfS2 << endl;
	*/
	
	
	dataForReSharingReceiverThread.mySharesInReSharing.at(thisPlayerID - 1) = sharesOfPlayers.at(thisPlayerID - 1);
	
	//~ cout << "----------my column vector: ";
	//~ myMatrixModule.printVector(dataForReSharingReceiverThread.mySharesInReSharing);
	

	// get first row of VDM Inverse
	vector < vector<int> > VDMmatrix = myMatrixModule.genegareVandermoneMatrix(numOfPlayers);

	// calculating VDM Inverse
	vector < vector<int> > VDMinverse =
			myMatrixModule.calculateMatrixInverseModpVectorMode(VDMmatrix);

	// get 1st row of vdm inverse:
	vector<int> VDMInverse_1stRow = VDMinverse[0];
	
	
	//~ cout << "----------first row of VDM Inverse: ";
	//~ myMatrixModule.printVector(VDMInverse_1stRow);

	// multiply VDMInverse_1stRow by column vector
	// the result value is my share of s1 times s2
	// by at least 3 of such values s1*s2 can be recovered
	/**/
	
	int newSecretShareAfterReSharing = myMatrixModule.multiplyVectorByVectorModp(VDMInverse_1stRow,
												dataForReSharingReceiverThread.mySharesInReSharing);
	
	return newSecretShareAfterReSharing;
}


//-----------------------------------------------------------------------
void MPC_Player::startMPCConsoleMode() {
	evaluateAnArbitraryFunction();
}

int MPC_Player::evaluateAnArbitraryFunction(){
	
	/*
	// share shares of secret and calculate
	//int myFinalShare = doSharing(my_gui_data.playerSecret);
	//myShareOfS1timesS2 = doSharing(thisPlayerSecret);
	
	//vector <int> shareResult1 = doSharing(thisPlayerSecret);
	
	
	//~ cout << "shareResult1: ";
	//~ myMatrixModule.printVector(shareResult1);
	//~ cout << "\n";
	//~ vector <int>  shareResult2 = doSharing(2);
	//~ cout << "shareResult2: ";
	//~ myMatrixModule.printVector(shareResult2);
	
	//~ vector <int>  shareResult3 = doSharing(3);
	//~ cout << "shareResult3: ";
	//~ myMatrixModule.printVector(shareResult3);
	
	
	//myShareOfS1timesS2AfterReSharing = doReSharing(myShareOfS1timesS2);
	
	//cout << "MPC: end of process, Press Ctrl+C to exit or Close GUI...";

	//~ cout << "myFinalShare of S1+S2: " << myShareOfS1plusS2 << "\n";
	//~ cout << "myFinalShare of S1*S2: " << myShareOfS1timesS2AfterReSharing << "\n";
	*/
	
	
	
	vector <int> mySharesTemp = doSharing(thisPlayerSecret);
	
	MatrixModule myMatrixModule;
	cout << "-----mySharesOfDifferentSecrets: ";
	myMatrixModule.printVector(mySharesOfDifferentSecrets);
	cout << "------------------------------------Sharing finished\n\n";
	
	
	//~ addionOfAll5Secrets();
	multiplicationOfAll5Secrets();
	
	//~ int func1Result = anArbitraryFunction1();
	//~ int func2Result = anArbitraryFunction2();
	//~ anArbitraryFunction3(func1Result, func2Result);
	
	//~ // calling additionGate
	//~ int sumOfs1s1 = additionGate(5, 5);
	//~ // calling multiplicationGate
	//~ int prodOfs1s1 = multiplicationGate(5, 5);
	//~ cout << "\n---------------------------sumOfs1s1: " << sumOfs1s1 << endl;
	//~ cout << "\n---------------------------prodOfs1s1: " << prodOfs1s1 << endl;
	
	return 1;
}

int MPC_Player::addionOfAll5Secrets(){
	int sumOfAllSecrets = 0;
	
	for (int i = 0; i < numOfPlayers; i++)
		sumOfAllSecrets = (sumOfAllSecrets + mySharesOfDifferentSecrets.at(i)) % p;
	
	cout << "------------------sumOfAllSecrets: " << sumOfAllSecrets << endl;
	
	return sumOfAllSecrets;
}

int MPC_Player::multiplicationOfAll5Secrets(){
	
	int temp, multiplicationOfAllSecrets;
	multiplicationOfAllSecrets = mySharesOfDifferentSecrets.at(0);
	
	for (int i = 1; i < numOfPlayers; i++){
		temp = (multiplicationOfAllSecrets * mySharesOfDifferentSecrets.at(i)) % p;
		
		//~ initializeDataForReSharing();
		multiplicationOfAllSecrets = doReSharing(temp);
		cout << "------------------multiplicationOfAllSecrets step by step: " << multiplicationOfAllSecrets << endl;
	}
	
	cout << "------------------multiplicationOfAllSecrets: " << multiplicationOfAllSecrets << endl;
	
	return multiplicationOfAllSecrets;
}

/* this can be deleted
int MPC_Player::multiplicationOfAll5Secrets(){
	
	int s1s2, s1s2s3, s1s2s3s4, s1s2s3s4s5, temp;
	
	temp  = (mySharesOfDifferentSecrets.at(0) * mySharesOfDifferentSecrets.at(1)) % p;
	
	initializeDataForReSharing();
	s1s2 = doReSharing(temp);
	cout << "\n------------------------------------multiplicationOfAll5Secrets: reSharing finished 1\n";
	cout << "------------------s1s2: " << s1s2 << endl;
	
	temp  = (s1s2 * mySharesOfDifferentSecrets.at(2)) % p;
	
	initializeDataForReSharing();
	s1s2s3 = doReSharing(temp);
	cout << "\n------------------------------------multiplicationOfAll5Secrets: reSharing finished 2\n";
	cout << "------------------s1s2s3: " << s1s2s3 << endl;
	
	
	return 1;
}
*/

//evaluateAnArbitraryFunction: OK-commented to test more difficult functions
int MPC_Player::anArbitraryFunction1(){
	// here I try to calculate s1*(s1 + s3 + s5)*s4.
	// notice players do not have each others secret,
	// they have a share of such secrets...
	
	//~ vector <int> shareResult1 = doSharing(thisPlayerSecret);
	//~ MatrixModule myMatrixModule;
	//~ cout << "\n-------mySharesOfDifferentSecrets: ";
	//~ myMatrixModule.printVector(mySharesOfDifferentSecrets);
	//~ cout << "\n------------------------------------func1: sharing finished\n";
	
	int sumOfS1S3S5 = 0;
	sumOfS1S3S5 = (mySharesOfDifferentSecrets.at(0) + mySharesOfDifferentSecrets.at(2)) % p;
	sumOfS1S3S5 = (sumOfS1S3S5 + mySharesOfDifferentSecrets.at(4)) % p;
	//~ cout << "\n------------------sumOfS1S3S5: " << sumOfS1S3S5;// << endl;
	
	int s1TimesSumOfS1S3S5 = (mySharesOfDifferentSecrets.at(0) * sumOfS1S3S5) % p;
	//~ cout << "\n------------------s1TimesSumOfS1S3S5: " << s1TimesSumOfS1S3S5 ;//<< endl;
	
	//~ initializeDataForReSharing();
	int s1TimesSumOfS1S3S5AfterReSharing = doReSharing(s1TimesSumOfS1S3S5);
	//~ cout << "\n------------------s1TimesSumOfS1S3S5AfterReSharing: " << s1TimesSumOfS1S3S5AfterReSharing << endl;
	cout << "\n------------------------------------func1: reSharing finished 1\n";
	
	int s1TimesSumOfS1S3S5TimesS4 = (s1TimesSumOfS1S3S5AfterReSharing * mySharesOfDifferentSecrets.at(3)) % p;
	//~ cout << "\n------------------s1TimesSumOfS1S3S5TimesS4: " << s1TimesSumOfS1S3S5TimesS4;// << endl;
	
	//~ initializeDataForReSharing();
	int s1TimesSumOfS1S3S5TimesS4AfterResharing = doReSharing(s1TimesSumOfS1S3S5TimesS4);
	
	//~ cout << "\n------------------s1TimesSumOfS1S3S5TimesS4AfterResharing: " << s1TimesSumOfS1S3S5TimesS4AfterResharing;// << endl;
	cout << "\n------------------------------------func1: reSharing finished 2\n";
	return s1TimesSumOfS1S3S5TimesS4AfterResharing;
}

//evaluateAnArbitraryFunction: resharing not works good
int MPC_Player::anArbitraryFunction2(){
	// a more difficult function
	// here I try to calculate s1 * s2 * (s1 + s3 + s5) * (s4 + s5).
	// notice players do not have each others secret,
	// they have a share of such secrets...
	
	//~ vector <int> shareResult1 = doSharing(thisPlayerSecret);
	//~ MatrixModule myMatrixModule;
	//~ cout << "\n-------mySharesOfDifferentSecrets: ";
	//~ myMatrixModule.printVector(mySharesOfDifferentSecrets);
	//~ cout << "\n------------------------------------sharing finished----------------------------------------\n\n";
	
	int s1Timess2 = (mySharesOfDifferentSecrets.at(0) * mySharesOfDifferentSecrets.at(1)) % p;
	//~ cout << "------------------s1Timess2: " << s1Timess2 << endl;
	
	//~ initializeDataForReSharing();
	int s1Timess2AfterReSharing = doReSharing(s1Timess2);
	cout << "\n------------------------------------func2: reSharing finished 1\n";
	//~ cout << "------------------s1Timess2AfterReSharing: " << s1Timess2AfterReSharing << endl;
	
	int sumOfS1S3S5 = 0;
	sumOfS1S3S5 = (mySharesOfDifferentSecrets.at(0) + mySharesOfDifferentSecrets.at(2)) % p;
	sumOfS1S3S5 = (sumOfS1S3S5 + mySharesOfDifferentSecrets.at(4)) % p;
	//~ cout << "------------------sumOfS1S3S5: " << sumOfS1S3S5 << endl;
	
	int s1Timess2TimesSumOfS1S3S5 = (s1Timess2AfterReSharing * sumOfS1S3S5) % p;
	//~ cout << "------------------s1Timess2TimesSumOfS1S3S5: " << s1Timess2TimesSumOfS1S3S5 << endl;
	
	//~ initializeDataForReSharing();
	int s1Timess2TimesSumOfS1S3S5AfterReSharing = doReSharing(s1Timess2TimesSumOfS1S3S5);
	cout << "\n------------------------------------func2: reSharing finished 2\n";
	//~ cout << "------------------s1Timess2TimesSumOfS1S3S5AfterReSharing: " << s1Timess2TimesSumOfS1S3S5AfterReSharing << endl;
	
	int sumOfs4s5 = (mySharesOfDifferentSecrets.at(3) + mySharesOfDifferentSecrets.at(4)) % p;
	int s1Timess2TimesSumOfS1S3S5TimessumOfs4s5 = (s1Timess2TimesSumOfS1S3S5AfterReSharing * sumOfs4s5) % p;
	//~ cout << "------------------s1Timess2TimesSumOfS1S3S5TimessumOfs4s5: " << s1Timess2TimesSumOfS1S3S5TimessumOfs4s5 << endl;
	
	//~ initializeDataForReSharing();
	int s1Timess2TimesSumOfS1S3S5TimessumOfs4s5AfterResharing = doReSharing(s1Timess2TimesSumOfS1S3S5TimessumOfs4s5);
	cout << "\n------------------------------------func2: reSharing finished 3\n";
	//~ cout << "------------------s1Timess2TimesSumOfS1S3S5TimessumOfs4s5AfterResharing: " << s1Timess2TimesSumOfS1S3S5TimessumOfs4s5AfterResharing << endl;
	
	return s1Timess2TimesSumOfS1S3S5TimessumOfs4s5AfterResharing;
}

int MPC_Player::anArbitraryFunction3(int aaa, int bbb){
	//later a very difficult function will be tested here...
	
	int sum = (aaa + bbb) % p;
	
	int product = (aaa * bbb) % p;
	
	//~ initializeDataForReSharing();
	int productAfterResharing = doReSharing(product);
	cout << "\n------------------------------------func3: reSharing finished 1\n";
	cout << "--------------------------func3 sum result: " << sum << endl;
	cout << "--------------------------func3 product result: " << productAfterResharing << endl;
	
	return 111;
}

int MPC_Player::additionGate(int ithS, int jthS){
	int sumOfSiSj;
	
	try {
		sumOfSiSj = (mySharesOfDifferentSecrets.at(ithS - 1) + mySharesOfDifferentSecrets.at(jthS - 1)) % p;
    } catch (const std::exception& e) {
        std::cout << "Something is wrong in additionGate. Make Sure Sharing has been done before."
                  << "Exception message: '"<< e.what() << "'\n";
    }
	
	return sumOfSiSj;
}

int MPC_Player::multiplicationGate(int ithS, int jthS){
	int productOfSiSjTemp, productOfSiSj;
	
	try {
		productOfSiSjTemp = (mySharesOfDifferentSecrets.at(ithS - 1) * mySharesOfDifferentSecrets.at(jthS - 1)) % p;
    } catch (const std::exception& e) {
        std::cout << "Something is wrong in multiplicationGate. Make Sure Sharing has been done before."
                  << "Exception message: '"<< e.what() << "'\n";
    }
	
	productOfSiSj = doReSharing(productOfSiSjTemp);
	
	return productOfSiSj;
}


//int additionGate(int shareOfPlayerI, int shareOfPlayerJ, int shareOfAHelperPlayer){
//int additionGate(int playerI, int playerJ, int aHelperPlayer){
int MPC_Player::additionGate(int idOfPlayerWithSi, int idOfPlayerWithSj, int idOfaHelperPlayer){ // later delete this
	/* how addition gate should work:
	 * we do not have secrets of other players, but we can have shares of their secrets or ask them to send their shares
	 * addition gate will work on shares of secrets
	 * it has two inputs (like two wires), but for returning the final result, we need a third share to be able to do
	 * lagrange interpolation and recover addition of two secrets.
	 * we call this third share "shareOfAHelperPlayer" in this code
	 * 
	 * variables:
	 * mySharesOfDifferentSecrets
	 * 
	 * calculate myShareOfSiPlusSj
	 * get PlayerJShareOfSiPlusSj
	 * get aHelperPlayerShareOfSiPlusSj
	 * do lagrange interpolation on them, the result is: Si+Sj. return it.
	 */
	 
	 // calculate myShareOfSiPlusSj
	 //int myShareOfSiPlusSj = mySharesOfDifferentSecrets.at(idOfPlayerWithSi) + mySharesOfDifferentSecrets.at(idOfPlayerWithSj);
	 
	 // get PlayerJShareOfSiPlusSj
	 
	 // get aHelperPlayerShareOfSiPlusSj
	 
	 // do lagrange interpolation
	 
	 // return result
	 
	 return 1;
}

/*void MPC_Player::startMPC(MPCGUI* caller) {
 {
 std::lock_guard<std::mutex> lock(m_Mutex);
 m_message = "";
 } // The mutex is unlocked here by lock's destructor.
 //~ for (int i = 0; i< 10 ; i++){
 //~ std::ostringstream ostr;
 //~ ostr << i << "\n";
 //~ m_message += ostr.str();

 //~ caller->notify();
 //~ }
 //caller->notify();

 int myFinalShare = doSharing();
 std::ostringstream ostr;
 ostr << "myFinalShare: " << myFinalShare << "\n";
 m_message += ostr.str();

 caller->notify();
 }
 */

//-----------------------------------------------------------------------
void MPC_Player::startMPC(MPCGUI* caller, gui_data my_gui_data) {
	{
		std::lock_guard < std::mutex > lock(m_Mutex);
		m_message = "";
	} // The mutex is unlocked here by lock's destructor.
	std::ostringstream ostr;

	//~ // share shares of secret and calculate
	//~ //int myFinalShare = doSharing(my_gui_data.playerSecret);
	//~ myShareOfS1timesS2 = doSharing(my_gui_data.playerSecret);
	//~ myShareOfS1timesS2AfterReSharing = doReSharing(myShareOfS1timesS2);
	//~ cout << "MPC: end of process, Press Ctrl+C to exit or Close GUI...";

	//~ ostr << "myFinalShare of S1+S2: " << myShareOfS1plusS2 << "\n";
	//~ ostr << "myFinalShare of S1*S2: " << myShareOfS1timesS2AfterReSharing
			//~ << "\n";
	//~ m_message += ostr.str();

	//~ caller->notify();
}

void MPC_Player::get_data(Glib::ustring* message) const {
	std::lock_guard < std::mutex > lock(m_Mutex);
	if (message)
		*message = m_message;
}

void MPC_Player::printProtocolInfo() {
	cout << "Welcome to our MPC implementation!" << endl;
	cout << "Prime p: " << p << endl;
	cout << "Number of players: " << NumOfPlayers << endl;
}
