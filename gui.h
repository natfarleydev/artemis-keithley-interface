#ifndef GTKMM_GUI_H
#define GTKMM_GUI_H

#include <gtkmm.h>
#include "keithley_functions.h"

class HelloWorld : public Gtk::Window	{

public:

	HelloWorld();

	virtual ~HelloWorld();

protected:

	// The Keithley device
	KeithleyDevice kdevice;

	// The file name
	string filename;

	//Signal handlers:
	void on_button_clicked(Glib::ustring data);
	void on_button1_clicked(Glib::ustring data);

	void on_menu_file_new_generic();
	void on_menu_file_quit();
	void on_menu_others();

	void on_menu_choices_one();
	void on_menu_choices_two();

	void on_menu_file_new_clicked();
	void on_menu_file_open_clicked();
	//void on_menu_file_save_clicked();
	void on_menu_help_about_clicked();

	//Member widgets:
	

	//Child widgets:
	Gtk::VBox m_box1;
	Gtk::Table m_table;

	Gtk::Button m_button1, m_button2, m_button_file, m_button_folder;

	Gtk::Adjustment m_adjustment_amp;
	Gtk::SpinButton m_spinbutton_amp;
	Gtk::Adjustment m_adjustment_fluence;
	Gtk::SpinButton m_spinbutton_fluence;
	Gtk::Adjustment m_adjustment_fluence_exp;
	Gtk::SpinButton m_spinbutton_fluence_exp;

	Gtk::Frame m_frame_currentpulse;
	Gtk::Label m_label_currentpulse;
	Gtk::Frame m_frame_currentfile;
	Gtk::Label m_label_currentfile;

	Gtk::VButtonBox m_buttonbox;

	Glib::RefPtr<Gtk::UIManager> m_refUIManager;
	Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
	Glib::RefPtr<Gtk::RadioAction> m_refChoiceOne, m_refChoiceTwo;

};

#endif