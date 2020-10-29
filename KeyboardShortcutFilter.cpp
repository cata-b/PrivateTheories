#include "KeyboardShortcutFilter.h"
#include <QKeyEvent>
#include <QWidget>
#include <QLineEdit>

KeyboardShortcutFilter::KeyboardShortcutFilter(QApplication* Application, SeniorClearanceController* Controller,
                                               QObject* parent)
	: QObject(parent), controller(Controller), application(Application)
{
}

bool KeyboardShortcutFilter::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() != QEvent::KeyPress)
		return false;
	QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
	auto name = application->focusWidget()->metaObject()->className();
	if (QString(application->focusWidget()->metaObject()->className()) != "QLineEdit")
	{
		if (keyEvent->modifiers() == Qt::KeyboardModifier::ControlModifier)
			if (keyEvent->key() == Qt::Key_Z)
			emit undo();
			else if (keyEvent->key() == Qt::Key_Y)
			emit redo();
	}
	return false;
}

KeyboardShortcutFilter::~KeyboardShortcutFilter()
{
}
