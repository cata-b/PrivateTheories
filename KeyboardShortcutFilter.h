#pragma once

#include <QObject>
#include "SeniorClearanceController.h"
#include <QEvent>
#include <QApplication>

class KeyboardShortcutFilter : public QObject
{
Q_OBJECT

private:
	SeniorClearanceController* controller;
	QApplication* application;

signals:
	void undo();
	void redo();

public:
	KeyboardShortcutFilter(QApplication* Application, SeniorClearanceController* Controller, QObject* parent);
	bool eventFilter(QObject* object, QEvent* event) override;
	~KeyboardShortcutFilter();
};
