#include "waitstate.h"

#include <QDebug>
#include <QEvent>

WaitState::WaitState(QState *parent) : QState(parent) {
	setObjectName("WaitState");

	m_automatic_button = this->parent()->parent()->findChild<QPushButton*>("b_automatic");
	m_runs_button = this->parent()->parent()->findChild<QPushButton*>("b_runs");
	m_delete_button = this->parent()->parent()->findChild<QPushButton*>("b_delete");
	m_start_button = this->parent()->parent()->findChild<QPushButton*>("b_start");

	m_first_round = true;
}

void WaitState::init() {
	m_automatic_mode = false;
	set_number_of_runs(1);

	// find the states for later transitions
	m_idle_state = this->parent()->findChild<QState*>("IdleState");
	m_preparation_state = this->parent()->findChild<QState*>("PreparationTimeState");

	connect(m_delete_button, SIGNAL(clicked()), this, SLOT(delete_clicked()));

	// Create transitions and add transition to the states
	m_to_idle_state = new StringTransition("IdleState");
	m_to_preparation_state = new StringTransition("PreparationTimeState");
	m_to_idle_state->setTargetState(m_idle_state);
	m_to_preparation_state->setTargetState(m_preparation_state);

	addTransition(m_to_idle_state);
	addTransition(m_to_preparation_state);
	addTransition(m_start_button, SIGNAL(clicked()), m_preparation_state);
}

void WaitState::set_number_of_runs(int runs) {
	m_runs = runs;
	m_runs_button->setText(QString("%1").arg(m_runs));
}

void WaitState::toggle_automatic_mode() {
	m_automatic_mode = ! m_automatic_mode;

	if (m_automatic_mode) {
		m_automatic_button->setStyleSheet("background-color: green");
	}
	else {
		m_automatic_button->setStyleSheet("");
	}
}

void WaitState::delete_clicked() {
	if (this->machine()->configuration().contains(this)) {
		set_number_of_runs(m_backup_runs);
		this->machine()->postEvent(new StringEvent("IdleState"));
		m_first_round = true;
	}

}

void WaitState::onEntry(QEvent *event)  {
	qDebug() << objectName() << " onEntry";

	// In the first round the number of runs are stored for restoring later the correct number
	if (m_first_round) {
		m_backup_runs = m_runs;
	}
	else {
		--m_runs;
		set_number_of_runs(m_runs);

		if (!m_automatic_mode)
		{
			m_start_button->setEnabled(true);
			m_automatic_button->setEnabled(true);
		}
	}

	// Deceision of the transition - if m_runs == 0 then automatic transition to idle state
	// if first round then wait for start, if not the first round wait every time for start button
	// if not first round and automatic button, then do automatically the transition
	if (m_runs == 0) {
		this->machine()->postEvent(new StringEvent("IdleState"));
		set_number_of_runs(m_backup_runs);
		m_first_round = true;
	}
	else {
		if (!m_first_round && m_automatic_mode) {
			this->machine()->postEvent(new StringEvent("PreparationTimeState"));
		}
		m_first_round = false;
	}
}

void WaitState::onExit(QEvent *event) {
	qDebug() << objectName() << " onExit";

	// Enable and disable start and automatic button
	if (m_first_round) {
		m_start_button->setEnabled(true);
		m_automatic_button->setEnabled(true);
	}
	else {
		m_start_button->setEnabled(false);
		m_automatic_button->setEnabled(false);
	}
}
