#pragma once


#include <QtCharts>
#include <QChartView>

#include "SeniorClearanceController.h"
#include "StandardClearanceController.h"

#include "StandardClearanceTableModel.h"

#include "ui_GUI.h"

class GUI : public QMainWindow
{
Q_OBJECT

public:
	GUI(SeniorClearanceController* seniorClearanceController, StandardClearanceController* standardClearanceController,
	    StandardClearanceTableModel& standardTableModel, QWidget* parent = Q_NULLPTR);
	virtual ~GUI();

public slots:
	void tabwidget_tab_changed(int index);

	void undo_button_click();
	void redo_button_click();

	void senior_add_button_click();
	void senior_delete_button_click();
	void senior_update_button_click();
	void senior_table_cell_doubleclick(int row, int column);

	void standard_save_button_click();
	void standard_filter_button_click();
	void standard_filter_button_next_click();
	void standard_open_button_click();
	void standard_open_locally_button_click();

	void pie_chart_slice_hover(bool state);

signals:
	void user_list_modified();

private:
	Ui::GUIClass ui;

	SeniorClearanceController* _senior_clearance_controller;
	StandardClearanceController* _standard_clearance_controller;

	QChart* chart;
	StandardClearanceTableModel& standard_table_window_model;

	void set_up_chart();
	void finish_up_ui();
	void refresh_table(QTableWidget& table, const std::vector<Evidence>& data);
	void refresh_senior_table();
	void refresh_standard_tables();
	void refresh_chart();

	void show_error(QString error);

	QStringList get_senior_form_data();
};
