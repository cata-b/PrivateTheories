#pragma once

#include <QWidget>
#include <QAbstractTableModel>
#include "ui_UserListWindow.h"
#include "StandardClearanceTableModel.h"

class UserListWindow : public QWidget
{
Q_OBJECT

public:
	UserListWindow(StandardClearanceTableModel* table_model, QWidget* parent = Q_NULLPTR);

public slots:
	void repository_changed();

private:
	StandardClearanceTableModel* table_model;
	Ui::UserListWindow ui;
};
