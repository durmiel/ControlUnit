#ifndef PREPARATIONTIMESTATE_H
#define PREPARATIONTIMESTATE_H

#include <QObject>
#include <QState>
#include <QTimer>
#include <QPushButton>
#include "StringTransition.h"
#include "NetworkManager.h"

class PreparationTimeState : public QState {
	Q_OBJECT

public:
	explicit PreparationTimeState(QState *parent = 0, NetworkManager *manager = 0);
	void init();
	void set_preparation_time(int preparationTime);

public slots:
	void timerEvent();

protected:
	void onEntry(QEvent *event);
	void onExit(QEvent *event);

private:
	QTimer *m_timer;
	QState *m_shoot_state;
	QState *m_wait_state;
	int m_preparation_time;
	int m_displayed_time;
	StringTransition *m_transition;
	QPushButton *m_preparation_time_button;
	QPushButton *m_delete_button;
	NetworkManager *m_network_manager;
};

#endif // PREPARATIONTIMESTATE_H
