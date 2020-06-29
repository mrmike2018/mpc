#include "MPCGUI.h"

MPCGUI::MPCGUI(int playerID) :
		m_ButtonStart("Start"), m_ButtonStop("Stop"), m_ButtonReset("Reset"), m_Label(
				"This Player Secret: "), m_Label3("Log:"), myPlayer(playerID) {
	//set_title("MPC GUI");
	set_title("MPC GUI - Player " + std::to_string(playerID));
	set_border_width(7);
	//set_position(Gtk::WIN_POS_CENTER);
	//set_default_size(800, 600);
	set_default_size(600, 400);
	add(m_HBox);
	m_HBox.add(m_VBox);

	// Add the TextView, inside a ScrolledWindow.
	m_ScrolledWindow.add(m_TextView);

	// Only show the scrollbars when they are necessary.
	m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

	m_HBox1.pack_start(m_Label, Gtk::PACK_SHRINK);
	m_HBox1.pack_start(m_Entry, Gtk::PACK_SHRINK);
	m_VBox.pack_start(m_HBox1, Gtk::PACK_SHRINK);

	m_TextView.set_editable(false);

	// Add the buttons to the ButtonBox.
	m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

	m_ButtonBox.pack_start(m_ButtonStart, Gtk::PACK_SHRINK);
	m_ButtonBox.pack_start(m_ButtonStop, Gtk::PACK_SHRINK);
	m_ButtonBox.pack_start(m_ButtonReset, Gtk::PACK_SHRINK);
	//m_ButtonBox.pack_start(m_ButtonQuit, Gtk::PACK_SHRINK);
	m_ButtonBox.set_border_width(5);
	m_ButtonBox.set_spacing(5);
	//m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
	m_ButtonBox.set_layout(Gtk::BUTTONBOX_CENTER);
	m_VBox3.pack_start(m_Label3, Gtk::PACK_SHRINK);
	m_VBox3.pack_start(m_ScrolledWindow);
	m_HBox.pack_start(m_VBox3);

	// Connect the signal handlers to the buttons.
	m_ButtonStart.signal_clicked().connect(
			sigc::mem_fun(*this, &MPCGUI::on_start_button_clicked));

	// Connect the handler to the dispatcher.
	m_Dispatcher.connect(
			sigc::mem_fun(*this, &MPCGUI::on_notification_from_worker_thread));

	// Create a text buffer mark for use in update_widgets().
	auto buffer = m_TextView.get_buffer();
	buffer->create_mark("last_line", buffer->end(), /* left_gravity= */true);

	update_start_stop_buttons();

	show_all_children();
}

//----------------------------------------------------------------------
void MPCGUI::update_start_stop_buttons() {
}

//----------------------------------------------------------------------
void MPCGUI::on_start_button_clicked() {
	
	struct gui_data myGuiData;

	string textEntryContent = m_Entry.get_text();

	// players 3, 4, 5 just help in calculations
	if (myPlayer.thisPlayerID == 3 || myPlayer.thisPlayerID == 4
			|| myPlayer.thisPlayerID == 5)
		myPlayer.startMPC(this, myGuiData);
	else if (!is_number(textEntryContent))
		m_Entry.set_text("please enter a number"); //cout << "please enter a number\n";
	else {
		int thisPlayerSecret = std::stoi(textEntryContent);
		myGuiData.playerSecret = thisPlayerSecret;

		//myPlayer.startMPC(this);
		myPlayer.startMPC(this, myGuiData);
	}
	//myPlayer.doSharing(4);
}

//----------------------------------------------------------------------
bool MPCGUI::is_number(const std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}

//----------------------------------------------------------------------
void MPCGUI::update_widgets() {
	Glib::ustring message_from_worker_thread;
	myPlayer.get_data(&message_from_worker_thread);

	if (message_from_worker_thread != m_TextView.get_buffer()->get_text()) {
		auto buffer = m_TextView.get_buffer();
		buffer->set_text(message_from_worker_thread);

		// Scroll the last inserted line into view. That's somewhat complicated.
		Gtk::TextIter iter = buffer->end();
		iter.set_line_offset(0); // Beginning of last line
		auto mark = buffer->get_mark("last_line");
		buffer->move_mark(mark, iter);
		m_TextView.scroll_to(mark);
		// TextView::scroll_to(iter) is not perfect.
		// We do need a TextMark to always get the last line into view.
	}
}

//----------------------------------------------------------------------
void MPCGUI::on_notification_from_worker_thread() {
	update_widgets();
}

//----------------------------------------------------------------------
void MPCGUI::notify() {
// notify() is called from ExampleWorker::do_work(). It is executed in the worker
// thread. It triggers a call to on_notification_from_worker_thread(), which is
// executed in the GUI thread.
	m_Dispatcher.emit();
}

//----------------------------------------------------------------------
void MPCGUI::onExitClick() {

	exit(0);
}

//----------------------------------------------------------------------
MPCGUI::~MPCGUI() {
//  If the program window is exited using the window manager to close
//  its window, then exit cleanly anyway

	onExitClick();
}
