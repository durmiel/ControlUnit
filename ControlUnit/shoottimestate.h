#ifndef SHOOTTIMESTATE_H
#define SHOOTTIMESTATE_H

#include <QObject>
#include <QState>
#include <QTimer>
#include <QPushButton>
#include "StringTransition.h"

class ShootTimeState : public QState {
	Q_OBJECT

public:
	explicit ShootTimeState(QState *parent = 0);
	void init();
	void set_shoot_time(int shoot_time);

public slots:
	void timerEvent();

protected:
  void onEntry(QEvent *event);
  void onExit(QEvent *event);

private:
  QState *m_wait_state;
  QTimer *m_timer;
  int m_shoot_time;
  int m_displayed_time;
  QPushButton *m_shoot_time_button;
  QPushButton *m_delete_button;
  StringTransition *m_transition;
};

#endif // SHOOTTIMESTATE_H
