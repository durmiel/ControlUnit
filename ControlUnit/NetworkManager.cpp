#include "NetworkManager.h"
#include <QHostAddress>
#include <QMessageBox>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent) {
	m_socket = new QTcpSocket();
	m_timer = new QTimer(this);
	m_connection_label = this->parent()->findChild<QLabel*>("l_connection");
	m_start = this->parent()->findChild<QPushButton*>("b_start");
	read_configuration();

	connect(m_socket, SIGNAL(connected()), this, SLOT(set_status_connected()));
	connect(m_socket, SIGNAL(disconnected()), this, SLOT(set_status_disconnected()));
	connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(display_error(QAbstractSocket::SocketError)));
	m_socket->connectToHost(m_ip, 8888);
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
	m_start->setEnabled(true);
}

void NetworkManager::set_status_disconnected() {
	m_socket->connectToHost(m_ip, 8888);
	m_timer->start(1000);
	try {
		m_connection_label->setText("Disconnected");
		m_start->setEnabled(false);
	}
	catch (const std::exception&) {

	}
}

void NetworkManager::display_error(QAbstractSocket::SocketError socket_error) {

}

void NetworkManager::timerEvent() {
	if (m_socket->state() != QAbstractSocket::SocketState::ConnectedState) {
		read_configuration();
		m_socket->connectToHost(m_ip, 8888);
		m_timer->start(1000);
	}
}

bool NetworkManager::isConnected() {
	if (m_socket->state() == QAbstractSocket::SocketState::ConnectedState) {
		return true;
	}
	else {
		return false;
	}
}

void NetworkManager::read_configuration() {
	QDomDocument document;
	QString errorString;
	int errorLine;
	int errorColumn;

	QFile file(m_config_path);

	if (!document.setContent(&file, &errorString, &errorLine, &errorColumn)) {
		QMessageBox error;
		error.setText(tr("Parse error at line %1, column %2.\n%3").arg(errorLine).arg(errorColumn).arg(errorString));
		error.setWindowTitle("Duellanlage");
		error.show();
		return;
	}
	QDomElement root = document.documentElement();
	if (QString::compare(root.tagName(), "Duellanlage") != 0) {
		QMessageBox error;
		error.setText("The file is not a Duellanlage file!!");
		error.setWindowTitle("Duellanlage");
		error.show();
		return;
	}

	QDomElement version = root.firstChildElement("Version");
	if ((version.hasAttribute("version")) && (version.attribute("version") != "1.0.0")) {
		QMessageBox error;
		error.setText("The file is not a correct version!!");
		error.setWindowTitle("Duellanlage");
		error.show();
		return;
	}

	QDomElement ip = root.firstChildElement("IP");
	if (ip.hasAttribute("ip")) {
		m_ip = ip.attribute("ip");
	}
}
