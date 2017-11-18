#include "preparationtimestate.h"

#include <QDebug>
#include <QStateMachine>
#include <QState>
#include <QEvent>

PreparationTimeState::PreparationTimeState(QState *parent, NetworkManager *manager) : QState(parent) {
  setObjectName("PreparationTimeState");
  m_timer = new QTimer(this);
  m_network_manager = manager;
}

void PreparationTimeState::init() {
	m_shoot_state = this->parent()->findChild<QState*>("ShootTimeState");
	m_wait_state = this->parent()->findChild<QState*>("WaitState");
	m_preparation_time_button = this->parent()->parent()->findChild<QPushButton*>("b_preparation_time");
	m_delete_button = this->parent()->parent()->findChild<QPushButton*>("b_delete");
	connect(m_timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	m_transition = new StringTransition("Timeout");
	m_transition->setTargetState(m_shoot_state);
	addTransition(m_transition);
	addTransition(m_delete_button, SIGNAL(clicked()), m_wait_state);
	set_preparation_time(3);
}

void PreparationTimeState::set_preparation_time(int preparationTime)
{
  m_preparation_time = preparationTime;
  m_preparation_time_button->setText(QString("%1").arg(m_preparation_time));
}

void PreparationTimeState::timerEvent() {
	set_preparation_time(--m_preparation_time);
	if (m_preparation_time == 0) {
		m_timer->stop();
		m_network_manager->send_command("out");
		this->machine()->postEvent(new StringEvent("Timeout"));
	}
}

void PreparationTimeState::onEntry(QEvent *event)
{
  qDebug() << objectName() << " onEntry";

  m_displayed_time = m_preparation_time;
  m_timer->setInterval(1000);
  m_timer->start();
}

void PreparationTimeState::onExit(QEvent *event)
{
  qDebug() << objectName() << " onExit";

  set_preparation_time(m_displayed_time);
  m_timer->stop();
}
