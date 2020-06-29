#ifndef MPC_Player_H
#define MPC_Player_H

#include "MPC_Common_Headers.h"
#include "MPC_Common_Functions.h"
#include "MPC_Common_Data.h"
#include "PrimeNumModule.h"
#include "MatrixModule.h"
#include "PolynomialModule.h"
#include "MPCCalculation.h"
#include "DataProcessing.h"

class MPCGUI;

class MPC_Player {
private:
	int thisPlayerSecret;
public:
	int thisPlayerID;
	int myShareOfS1;
	int myShareOfS2;
	int myShareOfS1plusS2;
	int myShareOfS1timesS2;
	int myShareOfS1timesS2AfterReSharing;
	
	vector <int> mySharesOfDifferentSecrets;

	string myTextViewContent = ""; //for puting the text view content of the GUI
	Glib::ustring m_message;
	mutable std::mutex m_Mutex;

	//int waitingTimeInThreads = 1; // this is waiting time for using in threads, it is in seconds.
	int timeIntervalForRepeatingSend = 5; //seconds
	int totalWaitingTimeForSend = 20; // seconds
	
	int timeIntervalForAcknowledgment = 1; //seconds
	//int totalWaitingTimeForAcknowledgment = 3; // seconds
	int totalWaitingTimeForAcknowledgment = 20; // micro seconds
	
	int countOfPrintedDots;
	int thisPlayerPortNum;  // = ThisPlayerPortNumber;
	
	std::vector<string> receiversIPAddress;
	std::vector<int> receiversPortNums;

	std::vector<int> dataHasBeenSent;
	std::vector<int> dataHasBeenReceived;

	std::vector<int> dataHasBeenSentInReSharing;
	std::vector<int> dataHasBeenReceivedInReSharing;

	int allDataHaveBeenSent;
	int allDataHaveBeenReceived;

	int allDataHaveBeenSentInReSharing;
	int allDataHaveBeenReceivedInReSharing;
	
	struct thread_data dataForSharingSenderThread, dataForSharingReceiverThread;
	struct thread_data dataForReSharingSenderThread, dataForReSharingReceiverThread;

public:
	//MPC_Player();
	MPC_Player(int playerID);
	MPC_Player(int playerID, int playerSecret);
	~MPC_Player();

	int initializePlayerData();
	int initializeDataForReSharing();

	void error(char *msg);
	void printDots(string str, string sndOrRecv, int numOfDots);
	
	string sendDataToOtherPlayerOnThread(string sendingData, string receieverIP, int receieverPortNum);
	vector<string> receiveDataFromOtherPlayerOnThread(int listenOnPortNum);

	thread_data sendingDataThreadFunc(thread_data my_data);

	thread_data receivingDataThreadFunc(thread_data my_data);

	vector<string> receiveDataFromOtherPlayerInReSharing(int listenOnPortNum);

	thread_data senderThreadFuncInReSharing(thread_data my_data);

	thread_data receiverThreadFuncInReSharing(thread_data my_data);

	vector<int> calculatePlayerShares(int playerSecret);

	//int doSharing();
	//int doSharing(int mySecret);
	vector <int> doSharing(int mySecret);

	int doReSharing(int newSecretShare);
	
	int evaluateAnArbitraryFunction();
	
	int addionOfAll5Secrets();
	int multiplicationOfAll5Secrets();
	
	int anArbitraryFunction1();
	int anArbitraryFunction2();
	int anArbitraryFunction3(int aaa, int bbb);

	
	int additionGate(int ithS, int jthS);
	int multiplicationGate(int ithS, int jthS);
	
	int additionGate(int shareOfPlayerI, int shareOfPlayerJ, int shareOfAHelperPlayer);
	
	void startMPC(MPCGUI* caller);

	void startMPC(MPCGUI* caller, gui_data my_gui_data);
	
	void startMPCConsoleMode();

	void get_data(Glib::ustring* message) const;

	void printProtocolInfo();

};

#endif   //MPC_Player_H
