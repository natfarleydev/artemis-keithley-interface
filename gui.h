#ifndef GTKMM_GUI_H
#define GTKMM_GUI_H

#include <gtkmm.h>
#include <gtkmm/box.h>
#include "keithley_functions.h"

class HelloWorld : public Gtk::Window	{

public:

	HelloWorld();

	virtual ~HelloWorld();

protected:

	// The Keithley device
	KeithleyDevice kdevice;

	// The file name
	string filenamebeamoff, filenamebeamon;

	//Signal handlers:
	void on_button_clicked(Glib::ustring data);
	void on_button1_clicked(Glib::ustring data);
	void on_button2_clicked(Glib::ustring data);
	void on_button_ivcurve_clicked(Glib::ustring data);

	void on_menu_file_new_generic();
	void on_menu_file_quit();
	void on_menu_others();

	void on_menu_choices_one();
	void on_menu_choices_two();

	void on_menu_file_new_clicked();
	void on_menu_file_newbeamon_clicked();
	void on_menu_file_open_clicked();
	//void on_menu_file_save_clicked();
	void on_menu_help_about_clicked();

	//Member widgets:
	

	//Child widgets:
	Gtk::VBox m_box1;
	Gtk::Table m_table;

	Gtk::Button m_button1, m_button2, m_button_file, m_button_folder;

	Gtk::HBox m_box_fluence;
	Gtk::Adjustment m_adjustment_amp;
	Gtk::SpinButton m_spinbutton_amp;
	Gtk::Adjustment m_adjustment_fluence;
	Gtk::SpinButton m_spinbutton_fluence;
	Gtk::Label m_label_fluence;
	Gtk::Adjustment m_adjustment_fluence_exp;
	Gtk::SpinButton m_spinbutton_fluence_exp;
	Gtk::Label m_label_fluence_exp;
	Gtk::Adjustment m_adjustment_datum_number;
	Gtk::SpinButton m_spinbutton_datum_number;
	Gtk::Label m_label_datum_number;
	Gtk::HBox m_box_datum_number;
	Gtk::Button m_button_ivcurve;

	Gtk::Frame m_frame_currentbeamofffile;
	Gtk::Label m_label_currentbeamofffile;
	Gtk::Frame m_frame_currentbeamonfile;
	Gtk::Label m_label_currentbeamonfile;

	Gtk::VButtonBox m_buttonbox;

	Glib::RefPtr<Gtk::UIManager> m_refUIManager;
	Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
	Glib::RefPtr<Gtk::RadioAction> m_refChoiceOne, m_refChoiceTwo;

};

#endif