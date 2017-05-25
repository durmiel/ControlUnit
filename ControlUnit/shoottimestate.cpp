#include "shoottimestate.h"

#include <QStateMachine>
#include <QDebug>
#include <QEvent>

ShootTimeState::ShootTimeState(QState *parent, NetworkManager *manager) : QState(parent) {
  setObjectName("ShootTimeState");
  m_timer = new QTimer(this);
  m_network_manager = manager;
}

void ShootTimeState::init() {
	m_wait_state = this->parent()->findChild<QState*>("WaitState");
	m_shoot_time_button = this->parent()->parent()->findChild<QPushButton*>("b_shoot_time");
	m_delete_button = this->parent()->parent()->findChild<QPushButton*>("b_delete");

	connect(m_timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	m_transition = new StringTransition("Timeout");
	m_transition->setTargetState(m_wait_state);
	addTransition(m_transition);
	addTransition(m_delete_button, SIGNAL(clicked()), m_wait_state);
	set_shoot_time(30);
}

void ShootTimeState::set_shoot_time(int shootTime) {
  m_shoot_time = shootTime;
  m_shoot_time_button->setText(QString("%1.%2").arg((m_shoot_time / 10) % 100).arg(m_shoot_time % 10));
}

void ShootTimeState::timerEvent() {
	set_shoot_time(--m_shoot_time);
	if (m_shoot_time == 0) {
		m_timer->stop();
		m_network_manager->send_command("turn away");
		this->machine()->postEvent(new StringEvent("Timeout"));
	}
}

void ShootTimeState::onEntry(QEvent *event) {
	qDebug() << objectName() << " onEntry";

	m_displayed_time = m_shoot_time;
	m_timer->setInterval(100);
	m_timer->start();
}

void ShootTimeState::onExit(QEvent *event)
{
  qDebug() << objectName() << " onExit";
  set_shoot_time(m_displayed_time);
  m_timer->stop();
}
