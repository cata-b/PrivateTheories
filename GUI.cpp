#include "GUI.h"


#include <QtWidgets/QMainWindow>

#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>

#include <QPieSeries>
#include <QPieSlice>

#include "SelectRepositoryDialog.h"

#include "UserListWindow.h"

#include <QHBoxLayout>
#include <QMessageBox>

#include "SetDebugNew.h"

using namespace std;

void GUI::set_up_chart()
{
	QChartView* chart_view = new QChartView(chart = new QChart());
	chart_view->setRenderHint(QPainter::Antialiasing);
	QChart::AnimationOptions animation_options = QChart::AnimationOptions(QChart::AnimationOption::AllAnimations);
	chart->setAnimationOptions(animation_options);
	chart->setAnimationDuration(chart->animationDuration() / 1.5);
	chart->legend()->setAlignment(Qt::AlignRight);
	ui.chart_tab_layout->addWidget(chart_view);
}

void GUI::finish_up_ui()
{
	set_up_chart();
	auto standard_save_button_text_size = ui.standard_save_button->fontMetrics().size(
		Qt::TextShowMnemonic, ui.standard_save_button->text());
	ui.standard_save_button->setMaximumWidth(standard_save_button_text_size.width() * 2);
	ui.senior_table->setHorizontalHeaderLabels(
		QStringList() << "ID" << "Measurement" << "Image Clarity" << "Quantity" << "Photograph");
	ui.standard_table->setHorizontalHeaderLabels(
		QStringList() << "ID" << "Measurement" << "Image Clarity" << "Quantity" << "Photograph");
	ui.standard_user_table->setHorizontalHeaderLabels(
		QStringList() << "ID" << "Measurement" << "Image Clarity" << "Quantity" << "Photograph");
	refresh_senior_table();
}

void GUI::refresh_table(QTableWidget& table, const std::vector<Evidence>& data)
{
	table.clearContents();
	table.setRowCount(data.size());
	int row = 0;
	for (const auto& evidence : data)
	{
		QTableWidgetItem* id_item = new QTableWidgetItem(QString::fromStdString(evidence.ID()));
		id_item->setFlags(id_item->flags() & ~Qt::ItemIsEditable);
		table.setItem(row, 0, id_item);

		QTableWidgetItem* measurement_item = new QTableWidgetItem(QString::fromStdString(evidence.MeasurementString()));
		measurement_item->setFlags(measurement_item->flags() & ~Qt::ItemIsEditable);
		table.setItem(row, 1, measurement_item);

		QTableWidgetItem* clarity_item = new QTableWidgetItem(
			QString::fromStdString(to_string(evidence.ImageClarityLevel())));
		clarity_item->setFlags(clarity_item->flags() & ~Qt::ItemIsEditable);
		table.setItem(row, 2, clarity_item);

		QTableWidgetItem* quantity_item = new QTableWidgetItem(QString::fromStdString(to_string(evidence.Quantity())));
		quantity_item->setFlags(quantity_item->flags() & ~Qt::ItemIsEditable);
		table.setItem(row, 3, quantity_item);

		QTableWidgetItem* photograph_item = new QTableWidgetItem(QString::fromStdString(evidence.Photograph()));
		photograph_item->setFlags(photograph_item->flags() & ~Qt::ItemIsEditable);
		table.setItem(row, 4, photograph_item);

		row++;
	}
}

void GUI::refresh_senior_table()
{
	SeniorClearanceController::CommandResult& result = _senior_clearance_controller->RunCommand("list");
	refresh_table(*ui.senior_table, *result.Data);
	delete result.Data;
	delete&result;
}

void GUI::refresh_standard_tables()
{
	SeniorClearanceController::CommandResult& senior_result = _senior_clearance_controller->RunCommand("list");
	refresh_table(*ui.standard_table, *senior_result.Data);
	delete senior_result.Data;
	delete&senior_result;

	StandardClearanceController::CommandResult& user_result = _standard_clearance_controller->RunCommand("mylist");
	refresh_table(*ui.standard_user_table, *user_result.ListResult);
	delete user_result.ListResult;
	delete&user_result;
}

void GUI::show_error(QString error)
{
	QMessageBox::warning(this, "Error", error);
}

QStringList GUI::get_senior_form_data()
{
	return QStringList{
		ui.ID_field->text(),
		ui.measurement_field->text(),
		ui.clarity_field->text(),
		ui.quantity_field->text(),
		ui.photograph_field->text()
	};
}

void GUI::tabwidget_tab_changed(int index)
{
	if (index == 0) // senior tab
		refresh_senior_table();
	else if (index == 1) // standard tab
		refresh_standard_tables();
	else // chart
		refresh_chart();
}

GUI::~GUI()
{
	delete _standard_clearance_controller;
	delete _senior_clearance_controller;
}

void GUI::undo_button_click()
{
	try
	{
		delete&_senior_clearance_controller->RunCommand("undo");
		if (ui.main_tab_widget->currentIndex() == 0) // senior
			refresh_senior_table();
		else if (ui.main_tab_widget->currentIndex() == 1) // standard
			refresh_standard_tables();
		else // chart
			refresh_chart();
	}
	catch (exception& exception)
	{
		show_error(exception.what());
	}
}

void GUI::redo_button_click()
{
	try
	{
		delete&_senior_clearance_controller->RunCommand("redo");
		if (ui.main_tab_widget->currentIndex() == 0) // senior
			refresh_senior_table();
		else if (ui.main_tab_widget->currentIndex() == 1) // standard
			refresh_standard_tables();
		else // chart
			refresh_chart();
	}
	catch (exception& exception)
	{
		show_error(exception.what());
	}
}

void GUI::senior_add_button_click()
{
	try
	{
		delete&_senior_clearance_controller->RunCommand("add " + get_senior_form_data().join(',').toStdString());
		refresh_senior_table();
	}
	catch (exception& exception)
	{
		show_error(exception.what());
	}
}


void GUI::senior_delete_button_click()
{
	try
	{
		delete&_senior_clearance_controller->RunCommand(("delete " + ui.ID_field->text()).toStdString());
		refresh_senior_table();
	}
	catch (exception& exception)
	{
		show_error(exception.what());
	}
}

void GUI::senior_update_button_click()
{
	try
	{
		delete&_senior_clearance_controller->RunCommand("update " + get_senior_form_data().join(',').toStdString());
		refresh_senior_table();
	}
	catch (exception& exception)
	{
		show_error(exception.what());
	}
}

void GUI::senior_table_cell_doubleclick(int row, int column)
{
	ui.ID_field->setText(ui.senior_table->item(row, 0)->text());
	ui.measurement_field->setText(ui.senior_table->item(row, 1)->text());
	ui.clarity_field->setText(ui.senior_table->item(row, 2)->text());
	ui.quantity_field->setText(ui.senior_table->item(row, 3)->text());
	ui.photograph_field->setText(ui.senior_table->item(row, 4)->text());
}

void GUI::standard_save_button_click()
{
	auto selected_row = ui.standard_table->selectedItems();
	if (selected_row.isEmpty())
	{
		show_error("No evidence selected");
		return;
	}
	auto selected_ID = selected_row[0]->text();
	try
	{
		delete&_standard_clearance_controller->RunCommand("save " + selected_ID.toStdString());
		refresh_standard_tables();
		emit user_list_modified();
	}
	catch (exception& exception)
	{
		show_error(exception.what());
	}
}

void GUI::standard_filter_button_click()
{
	if (ui.standard_measurement_filter_field->text() == "" || ui.standard_quantity_filter_field->text() == nullptr)
		return;
	auto& result = _standard_clearance_controller->RunCommand(
		("list " + ui.standard_measurement_filter_field->text() + " " + ui.standard_quantity_filter_field->text()).
		toStdString());
	ui.standard_filter_result_field->setText(QString::fromStdString(to_string(*result.SingleEvidenceResult)));
	delete result.SingleEvidenceResult;
	delete&result;
}

void GUI::standard_filter_button_next_click()
{
	if (ui.standard_measurement_filter_field->text() == "" || ui.standard_quantity_filter_field->text() == nullptr)
		return;
	auto& result = _standard_clearance_controller->RunCommand("next");
	ui.standard_filter_result_field->setText(QString::fromStdString(to_string(*result.SingleEvidenceResult)));
	delete result.SingleEvidenceResult;
	delete&result;
}

void GUI::standard_open_button_click()
{
	try
	{
		_standard_clearance_controller->RunCommand("open");
	}
	catch (exception& exception)
	{
		show_error(exception.what());
	}
}

void GUI::standard_open_locally_button_click()
{
	UserListWindow* standard_window = new UserListWindow(&standard_table_window_model, this);
	standard_window->setWindowFlag(Qt::Window);
	connect(this, &GUI::user_list_modified, standard_window, &UserListWindow::repository_changed);
	standard_window->show();
}

void GUI::pie_chart_slice_hover(bool state)
{
	QPieSlice* slice = static_cast<QPieSlice*>(sender());
	slice->setExploded(state);
	slice->setLabelVisible(state);
}

void GUI::refresh_chart()
{
	chart->removeAllSeries();

	QPieSeries* series = new QPieSeries();
	SeniorClearanceController::CommandResult& result = _senior_clearance_controller->RunCommand("list");
	for (const auto& evidence : *(result.Data))
		series->append(QString::fromStdString(evidence.ID()), evidence.Quantity());
	delete result.Data;
	delete&result;

	for (auto slice : series->slices())
	{
		slice->setLabel(slice->label() + ": " + QString::number(slice->value()));
		connect(slice, &QPieSlice::hovered, this, &GUI::pie_chart_slice_hover);
	}

	chart->addSeries(series);
}


GUI::GUI(SeniorClearanceController* seniorClearanceController, StandardClearanceController* standardClearanceController,
         StandardClearanceTableModel& standardTableModel, QWidget* parent)
	: QMainWindow(parent),
	  _senior_clearance_controller(seniorClearanceController),
	  _standard_clearance_controller(standardClearanceController),
	  standard_table_window_model(standardTableModel)
{
	ui.setupUi(this);
	finish_up_ui();
}
