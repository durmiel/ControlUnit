#pragma once

#include <QObject>
#include <QLabel>
#include <QtNetwork\QTcpSocket>
#include <QTimer>
#include <QPushButton>

class NetworkManager : public QObject {
	Q_OBJECT
public:
	explicit NetworkManager(QObject *parent = 0);
	~NetworkManager();
	void send_command(const QString & message);

public slots:
	void set_status_connected();
	void set_status_disconnected();
	void display_error(QAbstractSocket::SocketError socket_error);
	void timerEvent();
	bool isConnected();

private: 
	QTimer* m_timer;
	QTcpSocket *m_socket;
	QLabel* m_connection_label;
	QPushButton * m_start;
};
