// this gui does not use glade...
#ifndef MPC_GUI02_H
#define MPC_GUI02_H

#include "MPC_Common_Headers.h"
#include "MPC_Player.h"

class MPCGUI: public Gtk::Window {
public:
	//MPCGUI();
	MPCGUI(int playerID);
	virtual ~MPCGUI();
	void notify();
	void onExitClick();
private:
	// Signal handlers.
	void on_start_button_clicked();
	void update_start_stop_buttons();
	void update_widgets();
	// Dispatcher handler.
	void on_notification_from_worker_thread();

	// helper functions:
	bool is_number(const std::string& s);

	// Member data.
	Gtk::HBox m_HBox;
	Gtk::HBox m_HBox1;
	Gtk::VBox m_VBox;
	Gtk::VBox m_VBox3;
	Gtk::Label m_Label;
	Gtk::Label m_Label3;
	Gtk::Entry m_Entry;
	Gtk::ButtonBox m_ButtonBox;
	Gtk::Button m_ButtonStart;
	Gtk::Button m_ButtonStop;
	Gtk::Button m_ButtonReset;
	Gtk::Button m_ButtonQuit;
	Gtk::ScrolledWindow m_ScrolledWindow;
	Gtk::TextView m_TextView;

	Glib::Dispatcher m_Dispatcher;
	MPC_Player myPlayer; //Player plays the rule of a worker thread
};
#endif   //MPC_GUI02_H
