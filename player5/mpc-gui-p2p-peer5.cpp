// compile:
//use this:         g++ -std=c++11 *.cpp -o mpc-gui-p2p-peer5 `pkg-config gtkmm-3.0 --cflags --libs`
//old version of code:         g++ -std=c++11 mpc-gui-p2p-peer1.cpp -o mpc-gui-p2p-peer1 `pkg-config gtkmm-3.0 --cflags --libs`
// run: 
//    ./mpc-gui-p2p-peer5


//#include "MPCGUI.h"
#include "MPC_Player.h"

int main(int argc, char *argv[]) {
	srand(time(0)); // for generating random numbers
	std::system("clear");
    string playerIDString = "player --mmm--";// + std::to_string(thisPlayerID);
    //cout << playerIDString << "\n";
	
	//--------------------------------------------------- GUI without Glade //start
	  //~ auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example5");

	  //~ //MPCGUI window;
	  //~ MPCGUI window(5);  // 5 means player 5

	  //~ //Shows the window and returns when it is closed.
	  //~ return app->run(window);
	//--------------------------------------------------- GUI without Glade //end
	
	
	//--------------------------------------------------- MPCConsoleMode //start
	//~ MPC_Player *myPlayer = new MPC_Player(1); // 1 means player 1
	//~ myPlayer->startMPCConsoleMode();
	
	//~ MPC_Player myPlayer(1); // 1 means player 1
	//~ myPlayer.startMPCConsoleMode();
	
	MPC_Player myPlayer(5, 2); // 5 means player 5
	myPlayer.startMPCConsoleMode();
	//--------------------------------------------------- MPCConsoleMode //end
	
	cout << "\nEnd" << endl;

	return 0;
}
