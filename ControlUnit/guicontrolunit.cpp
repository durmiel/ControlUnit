#include "guicontrolunit.h"
#include "ui_guicontrolunit.h"

GuiControlUnit::GuiControlUnit(QWidget *parent) : QMainWindow(parent), ui(new Ui::GuiControlUnit) {
	ui->setupUi(this);

	// Create the state machine and its states
	m_network_manager = new NetworkManager(this);
	m_machine = new QStateMachine(this);
	m_idle = new IdleState(m_machine);
	m_wait = new WaitState(m_machine);
	m_shoot = new ShootTimeState(m_machine);
	m_pretime = new PreparationTimeState(m_machine);
	
	m_idle->init();
	m_wait->init();
	m_pretime->init();
	m_shoot->init();

	// connect buttons
	connect(ui->b_runs, SIGNAL(clicked()), this, SLOT(set_number_of_runs()));
	connect(ui->b_preparation_time, SIGNAL(clicked()), this, SLOT(set_preparation_time()));
	connect(ui->b_shoot_time, SIGNAL(clicked()), this, SLOT(set_shoot_time()));
	connect(ui->b_automatic, SIGNAL(clicked()), this, SLOT(toggle_automatic_mode()));

	// Set Inital state and stat the state machine
	m_machine->setInitialState(m_idle);
	m_machine->start();
}

GuiControlUnit::~GuiControlUnit() {
	delete ui;
}

void GuiControlUnit::set_number_of_runs() {
	InputDialog *input = new InputDialog(this);
	connect(input, &InputDialog::user_input, this, &GuiControlUnit::get_user_input);
	input->set_title("Anzahl der Durchläufe:", 1);
	input->show();
}

void GuiControlUnit::set_preparation_time() {
	InputDialog *input = new InputDialog(this);
	connect(input, &InputDialog::user_input, this, &GuiControlUnit::get_user_input);
	input->set_title("Vorlaufzeit:", 2);
	input->show();
}

void GuiControlUnit::set_shoot_time() {
	InputDialog *input = new InputDialog(this);
	connect(input, &InputDialog::user_input, this, &GuiControlUnit::get_user_input);
	input->set_title("Schießzeit:", 3);
	input->show();
}

void GuiControlUnit::get_user_input(int user_selection, int user_input) {
	switch (user_selection) {
		case 1:
			m_wait->set_number_of_runs(user_input);
			break;
		case 2:
			m_pretime->set_preparation_time(user_input);
			break;
		case 3:
			m_shoot->set_shoot_time(user_input * 10);
			break;
		default:
			break;
	}
}

void GuiControlUnit::toggle_automatic_mode() {
  m_wait->toggle_automatic_mode();
}
