#include "StringTransition.h"



StringTransition::StringTransition(const QString &value) {
	m_value = value;
}

bool StringTransition::eventTest(QEvent *e) {
	if (e->type() != QEvent::Type(QEvent::User + 1)) // StringEvent
		return false;
	StringEvent *se = static_cast<StringEvent*>(e);
	return (m_value == se->value);
}
