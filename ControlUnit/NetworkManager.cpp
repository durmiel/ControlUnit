#include "NetworkManager.h"
#include <QHostAddress>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent) {
	m_socket = new QTcpSocket();
	m_timer = new QTimer(this);
	m_connection_label = this->parent()->findChild<QLabel*>("l_connection");

	connect(m_socket, SIGNAL(connected()), this, SLOT(set_status_connected()));
	connect(m_socket, SIGNAL(disconnected()), this, SLOT(set_status_disconnected()));
	connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(display_error(QAbstractSocket::SocketError)));
	m_socket->connectToHost(QHostAddress::LocalHost, 8888);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	m_timer->setSingleShot(true);
	m_timer->start(100);
}

NetworkManager::~NetworkManager() {
	m_socket->close();
	delete m_socket;
}

void NetworkManager::send_command(const QString &message) {
	m_socket->write(message.toUtf8());
}

void NetworkManager::set_status_connected() {
	m_connection_label->setText("Connected");
}

void NetworkManager::set_status_disconnected() {
	m_socket->connectToHost(QHostAddress::LocalHost, 8888);
	m_timer->start(1000);
	try {
		m_connection_label->setText("Disconnected");
	}
	catch (const std::exception&) {

	}
}

void NetworkManager::display_error(QAbstractSocket::SocketError socket_error) {

}

void NetworkManager::timerEvent() {
	if (m_socket->state() != QAbstractSocket::SocketState::ConnectedState) {
		m_socket->connectToHost(QHostAddress::LocalHost, 8888);
		m_timer->start(1000);
	}
}
