#ifndef MPC_Common_Data_H
#define MPC_Common_Data_H

struct thread_data {
	int      thread_id;
	string   message;
	string   destinationIPAddress;
	int      destinationPortNum;
	int      dataSendingResult;
	int      mySecret;
	vector <int> sharesOfMySecret;
	int      myShareOfS1;
	int      myShareOfS2;
	
	vector <int> sharesOfOtherPlayersInReSharing; // this is used in sender thread in resharing phase
	vector <int> mySharesInReSharing; // this is used in receiver thread in resharing phase
	
	vector <int> mySharesOfDifferentSecrets;
};

struct gui_data {
	int playerSecret;
};


#define p 41     // p: the prime number, we are supposed to do computations in Zp
//~ #define p 997     // p: the prime number, we are supposed to do computations in Zp
//delete this line: #define threshold 3
//delete this line: 
#define NumOfPlayers 5

#define threshold 2
//~ int numOfPlayers = 2 * threshold + 1;
#define numOfPlayers 5// = 2 * threshold + 1;

#define debugMode 0
#define debugModeP2Ppart 0
#define debugModeSendReceivePorts 0
#define debugModeConnectionEstablished 0
#define debugModeDataSentReceived 0
#define debugModeSendReceiveThreads 0
#define debugModePrintingDots 0

#define debugModeTraceSendOnThread 0
#define debugModeTraceReceiveOnThread 0

#define totalNumOfDots 30

#define waitingTimeInThreads 1 // this is waiting time for using in threads, it is in seconds.
#define waitingTimeInThreadsMicroSec 10 // micro seconds

//#define TRUE   1
//#define FALSE  0

//~ int allDataHaveBeenSent = 0;
//~ int allDataHaveBeenReceived = 0;

//~ int allDataHaveBeenSentInReSharing = 0;
//~ int allDataHaveBeenReceivedInReSharing = 0;

//~ int allDataHaveBeenSent = 1;
//~ int allDataHaveBeenReceived = 1;

//~ int allDataHaveBeenSentInReSharing = 1;
//~ int allDataHaveBeenReceivedInReSharing = 1;
//~ #define allDataHaveBeenSent 1
//~ #define allDataHaveBeenReceived 1

//~ #define allDataHaveBeenSentInReSharing 1
//~ #define allDataHaveBeenReceivedInReSharing 1

#endif   //MPC_Common_Data_H
