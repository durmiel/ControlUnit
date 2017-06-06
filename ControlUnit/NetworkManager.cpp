#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent) {
	m_socket = new QTcpSocket();
	m_connection_label = this->parent()->findChild<QLabel*>("l_connection");

	connect(m_socket, SIGNAL(connected()), this, SLOT(set_status_connected()));
	connect(m_socket, SIGNAL(disconnected()), this, SLOT(set_status_disconnected()));
	connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(display_error(QAbstractSocket::SocketError)));
	m_socket->connectToHost("192.168.4.1", 6666);
}

NetworkManager::~NetworkManager() {
	m_socket->close();
	delete m_socket;
}

void NetworkManager::send_command(const QString &message) {
	//qDebug() << message << endl;
	m_socket->write(message.toUtf8());
}

void NetworkManager::set_status_connected() {
	m_connection_label->setText("Connected");
}

void NetworkManager::set_status_disconnected() {
	try {
		m_connection_label->setText("Disconnected");
	}
	catch (const std::exception&) {

	}
}

void NetworkManager::display_error(QAbstractSocket::SocketError socket_error) {

}
