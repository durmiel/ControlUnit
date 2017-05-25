#ifndef IDLESTATE_H
#define IDLESTATE_H

#include <QState>
#include <QSignalBlocker>
#include "NetworkManager.h"

class IdleState : public QState {
public:
  IdleState(QState *parent = 0, NetworkManager *manager = 0);
  void init();

protected:
  void onEntry(QEvent *event);
  void onExit(QEvent *event);

private:
  QState *m_wait_state;
  QSignalBlocker *m_button_runs;
  QSignalBlocker *m_button_preparation_time;
  QSignalBlocker *m_button_shoot_time;
  NetworkManager *m_network_manager;
};

#endif // IDLESTATE_H
