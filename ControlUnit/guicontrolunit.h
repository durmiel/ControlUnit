#ifndef GUICONTROLUNIT_H
#define GUICONTROLUNIT_H

#include <QMainWindow>
#include <QStateMachine>

#include "inputdialog.h"
#include "idlestate.h"
#include "waitstate.h"
#include "preparationtimestate.h"
#include "shoottimestate.h"
#include "NetworkManager.h"

namespace Ui {
	class GuiControlUnit;
}

class GuiControlUnit : public QMainWindow {
	Q_OBJECT

public:
	explicit GuiControlUnit(QWidget *parent = 0);
	~GuiControlUnit();

public slots:
	void set_number_of_runs();
	void set_preparation_time();
	void set_shoot_time();

private slots:
	void get_user_input(int user_selection, int user_input);
	void toggle_automatic_mode();

private:
	Ui::GuiControlUnit *ui;
	QStateMachine *m_machine;
	IdleState *m_idle;
	WaitState *m_wait;
	PreparationTimeState *m_pretime;
	ShootTimeState *m_shoot;
	NetworkManager *m_network_manager;
};

#endif // GUICONTROLUNIT_H
