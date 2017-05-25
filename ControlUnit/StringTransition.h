#pragma once

#include <QString>
#include <QAbstractTransition>
#include <QEvent>

struct StringEvent : public QEvent
{
	StringEvent(const QString &val)
		: QEvent(QEvent::Type(QEvent::User + 1)),
		value(val) {}

	QString value;
};

class StringTransition : public QAbstractTransition
{
	Q_OBJECT

public:
	StringTransition(const QString &value);

protected:
	virtual bool eventTest(QEvent *e);
	virtual void onTransition(QEvent *) {}

private:
	QString m_value;
};
