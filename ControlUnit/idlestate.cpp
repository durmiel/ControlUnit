#include "idlestate.h"

#include <QDebug>
#include <QEvent>
#include <QPushButton>

IdleState::IdleState(QState *parent, NetworkManager *manager) : QState(parent)
{
  setObjectName("IdleState");
  m_network_manager = manager;
}

void IdleState::init() {
  m_wait_state = this->parent()->findChild<QState*>("WaitState");
  QPushButton *b_start = this->parent()->parent()->findChild<QPushButton*>("b_start");
  addTransition(b_start, SIGNAL(clicked()), m_wait_state);
  QPushButton *button = this->parent()->parent()->findChild<QPushButton*>("b_runs");
  m_button_runs = new QSignalBlocker(button);
  button = this->parent()->parent()->findChild<QPushButton*>("b_preparation_time");
  m_button_preparation_time = new QSignalBlocker(button);
  button = this->parent()->parent()->findChild<QPushButton*>("b_shoot_time");
  m_button_shoot_time = new QSignalBlocker(button);
}

void IdleState::onEntry(QEvent *event)
{
  qDebug() << objectName() << " onEntry";
  m_network_manager->send_command("turn out");
  
  m_button_runs->unblock();
  m_button_preparation_time->unblock();
  m_button_shoot_time->unblock();
}

void IdleState::onExit(QEvent *event)
{
  qDebug() << objectName() << " onExit";
  m_network_manager->send_command("turn away");

  m_button_runs->reblock();
  m_button_preparation_time->reblock();
  m_button_shoot_time->reblock();
}
