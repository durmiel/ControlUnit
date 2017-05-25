#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent) {
	m_socket = new QTcpSocket();
	m_connection_label = this->parent()->findChild<QLabel*>("l_connection");

	connect(m_socket, SIGNAL(connected()), this, SLOT(set_status_connected()));
	connect(m_socket, SIGNAL(disconnected()), this, SLOT(set_status_disconnected()));
	connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(display_error(QAbstractSocket::SocketError)));
	m_socket->connectToHost("127.0.0.1", 8888);
}

NetworkManager::~NetworkManager() {
	delete m_socket;
}

void NetworkManager::send_command(const QString &message) {
	qDebug() << message << endl;
}

void NetworkManager::set_status_connected() {
	m_connection_label->setText("Connected");
}

void NetworkManager::set_status_disconnected() {
	m_connection_label->setText("Disconnected");
}

void NetworkManager::display_error(QAbstractSocket::SocketError socket_error) {

}
