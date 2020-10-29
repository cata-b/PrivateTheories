#include "SelectRepositoryDialog.h"
#include <QBoxlayout>
#include <QLabel>
#include <QMessageBox>

#include "SetDebugNew.h"
using namespace std;

void SelectRepositoryDialog::selection_change(int index)
{
	filename_edit->setEnabled(_filename_options.contains(index));
}

void SelectRepositoryDialog::ok_click()
{
	if (_filename_options.contains(combo_box->currentIndex()) && filename_edit->text() == "")
	{
		QMessageBox prompt;
		prompt.setText("No file name set.");
		prompt.exec();
	}
	else
		close();
}

SelectRepositoryDialog::SelectRepositoryDialog(QString Title, QList<QString> PossibleOptions,
                                               QList<int> FilenameOptions, QWidget* parent) : QDialog(parent)
{
	setWindowTitle(Title);
	QVBoxLayout* main_layout = new QVBoxLayout(this);
	setLayout(main_layout);

	combo_box = new QComboBox(this);
	for (const auto& option : PossibleOptions)
		combo_box->addItem(option);
	_filename_options = FilenameOptions;
	combo_box->setCurrentIndex(0);
	main_layout->addWidget(combo_box);

	QHBoxLayout* edit_layout = new QHBoxLayout(this);
	filename_edit = new QLineEdit(this);
	filename_edit->setPlaceholderText("file.txt");
	edit_layout->addWidget(new QLabel(QString("File name: ")));
	edit_layout->addWidget(filename_edit);
	main_layout->addLayout(edit_layout);

	selection_change(0);

	ok_button = new QPushButton(QString("OK"), this);
	main_layout->addWidget(ok_button);

	connect(combo_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
	        &SelectRepositoryDialog::selection_change);
	connect(ok_button, &QPushButton::clicked, this, &SelectRepositoryDialog::ok_click);
}

int SelectRepositoryDialog::GetSelected()
{
	return combo_box->currentIndex();
}

QString SelectRepositoryDialog::GetFileName()
{
	auto text = filename_edit->text();
	if (text == "")
		return filename_edit->placeholderText();
	return text;
}
