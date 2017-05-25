#ifndef WAITSTATE_H
#define WAITSTATE_H

#include <QState>
#include <QPushButton>
#include <QSignalTransition>
#include <QStateMachine>
#include "StringTransition.h"

class WaitState : public QState {
	Q_OBJECT
public:
  explicit WaitState(QState *parent = 0);
  void init();
  void set_number_of_runs(int runs);
  void toggle_automatic_mode();

public slots:
	void delete_clicked();

protected:
  void onEntry(QEvent *event) override;
  void onExit(QEvent *event) override;

private:
  int m_runs;
  int m_backup_runs;
  QPushButton *m_runs_button;
  QPushButton *m_automatic_button;
  QPushButton *m_start_button;
  QPushButton *m_delete_button;
  bool m_automatic_mode;
  bool m_first_round;
  QState *m_preparation_state;
  QState *m_idle_state;
  StringTransition *m_to_idle_state;
  StringTransition *m_to_preparation_state;
};

#endif // WAITSTATE_H
