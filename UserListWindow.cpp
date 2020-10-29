#include "UserListWindow.h"
#include "EvidenceImageViewerDelegate.h"

UserListWindow::UserListWindow(StandardClearanceTableModel* table_model, QWidget* parent)
	: QWidget(parent), table_model(table_model)
{
	ui.setupUi(this);
	ui.standardTableView->setModel(table_model);
	ui.standardTableView->setItemDelegate(new EvidenceImageViewerDelegate(4, ui.standardTableView));
}

void UserListWindow::repository_changed()
{
	table_model->refresh();
}
