#pragma once
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

class SelectRepositoryDialog : public QDialog
{
private:
	QComboBox* combo_box;
	QPushButton* ok_button;
	QLineEdit* filename_edit;
	QList<int> _filename_options;

private slots:
	void selection_change(int index);
	void ok_click();

public:
	SelectRepositoryDialog(QString Title, QList<QString> Options, QList<int> FilenameOptions,
	                       QWidget* parent = nullptr);
	int GetSelected();
	QString GetFileName();
};
