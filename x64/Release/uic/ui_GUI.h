/********************************************************************************
** Form generated from reading UI file 'GUI.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUIClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *main_tab_widget;
    QWidget *senior_tab;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *senior_table;
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *iDLabel;
    QLineEdit *ID_field;
    QLabel *measurementLabel;
    QLineEdit *measurement_field;
    QLabel *clarityLabel;
    QLineEdit *clarity_field;
    QLabel *quantityLabel;
    QLineEdit *quantity_field;
    QLabel *photographLabel;
    QLineEdit *photograph_field;
    QVBoxLayout *verticalLayout;
    QPushButton *senior_add_evidence_button;
    QPushButton *senior_update_evidence_button;
    QPushButton *senior_delete_evidence_button;
    QWidget *standard_tab;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *standard_table;
    QPushButton *standard_save_button;
    QTableWidget *standard_user_table;
    QGridLayout *gridLayout_2;
    QFormLayout *formLayout_2;
    QLabel *measurementLabel_2;
    QLineEdit *standard_measurement_filter_field;
    QLabel *minQuantityLabel;
    QLineEdit *standard_quantity_filter_field;
    QLabel *resultLabel;
    QLineEdit *standard_filter_result_field;
    QVBoxLayout *verticalLayout_4;
    QPushButton *open_button;
    QPushButton *open_locally_button;
    QPushButton *standard_filter_button;
    QPushButton *standard_filter_button_next;
    QWidget *chart_tab;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *chart_tab_layout;
    QHBoxLayout *horizontalLayout;
    QPushButton *undo_button;
    QPushButton *redo_button;

    void setupUi(QMainWindow *GUIClass)
    {
        if (GUIClass->objectName().isEmpty())
            GUIClass->setObjectName(QString::fromUtf8("GUIClass"));
        GUIClass->resize(685, 650);
        centralWidget = new QWidget(GUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        main_tab_widget = new QTabWidget(centralWidget);
        main_tab_widget->setObjectName(QString::fromUtf8("main_tab_widget"));
        senior_tab = new QWidget();
        senior_tab->setObjectName(QString::fromUtf8("senior_tab"));
        verticalLayout_2 = new QVBoxLayout(senior_tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        senior_table = new QTableWidget(senior_tab);
        if (senior_table->columnCount() < 5)
            senior_table->setColumnCount(5);
        senior_table->setObjectName(QString::fromUtf8("senior_table"));
        senior_table->setSelectionMode(QAbstractItemView::SingleSelection);
        senior_table->setSelectionBehavior(QAbstractItemView::SelectRows);
        senior_table->setColumnCount(5);

        verticalLayout_2->addWidget(senior_table);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        iDLabel = new QLabel(senior_tab);
        iDLabel->setObjectName(QString::fromUtf8("iDLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, iDLabel);

        ID_field = new QLineEdit(senior_tab);
        ID_field->setObjectName(QString::fromUtf8("ID_field"));
        ID_field->setClearButtonEnabled(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, ID_field);

        measurementLabel = new QLabel(senior_tab);
        measurementLabel->setObjectName(QString::fromUtf8("measurementLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, measurementLabel);

        measurement_field = new QLineEdit(senior_tab);
        measurement_field->setObjectName(QString::fromUtf8("measurement_field"));
        measurement_field->setClearButtonEnabled(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, measurement_field);

        clarityLabel = new QLabel(senior_tab);
        clarityLabel->setObjectName(QString::fromUtf8("clarityLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, clarityLabel);

        clarity_field = new QLineEdit(senior_tab);
        clarity_field->setObjectName(QString::fromUtf8("clarity_field"));
        clarity_field->setClearButtonEnabled(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, clarity_field);

        quantityLabel = new QLabel(senior_tab);
        quantityLabel->setObjectName(QString::fromUtf8("quantityLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, quantityLabel);

        quantity_field = new QLineEdit(senior_tab);
        quantity_field->setObjectName(QString::fromUtf8("quantity_field"));
        quantity_field->setClearButtonEnabled(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, quantity_field);

        photographLabel = new QLabel(senior_tab);
        photographLabel->setObjectName(QString::fromUtf8("photographLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, photographLabel);

        photograph_field = new QLineEdit(senior_tab);
        photograph_field->setObjectName(QString::fromUtf8("photograph_field"));
        photograph_field->setClearButtonEnabled(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, photograph_field);


        gridLayout->addLayout(formLayout, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        senior_add_evidence_button = new QPushButton(senior_tab);
        senior_add_evidence_button->setObjectName(QString::fromUtf8("senior_add_evidence_button"));

        verticalLayout->addWidget(senior_add_evidence_button);

        senior_update_evidence_button = new QPushButton(senior_tab);
        senior_update_evidence_button->setObjectName(QString::fromUtf8("senior_update_evidence_button"));

        verticalLayout->addWidget(senior_update_evidence_button);

        senior_delete_evidence_button = new QPushButton(senior_tab);
        senior_delete_evidence_button->setObjectName(QString::fromUtf8("senior_delete_evidence_button"));

        verticalLayout->addWidget(senior_delete_evidence_button);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        main_tab_widget->addTab(senior_tab, QString());
        standard_tab = new QWidget();
        standard_tab->setObjectName(QString::fromUtf8("standard_tab"));
        verticalLayout_5 = new QVBoxLayout(standard_tab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        standard_table = new QTableWidget(standard_tab);
        if (standard_table->columnCount() < 5)
            standard_table->setColumnCount(5);
        standard_table->setObjectName(QString::fromUtf8("standard_table"));
        standard_table->setSelectionMode(QAbstractItemView::SingleSelection);
        standard_table->setSelectionBehavior(QAbstractItemView::SelectRows);
        standard_table->setColumnCount(5);

        horizontalLayout_2->addWidget(standard_table);

        standard_save_button = new QPushButton(standard_tab);
        standard_save_button->setObjectName(QString::fromUtf8("standard_save_button"));
        standard_save_button->setFlat(false);

        horizontalLayout_2->addWidget(standard_save_button);

        standard_user_table = new QTableWidget(standard_tab);
        if (standard_user_table->columnCount() < 5)
            standard_user_table->setColumnCount(5);
        standard_user_table->setObjectName(QString::fromUtf8("standard_user_table"));
        standard_user_table->setSelectionMode(QAbstractItemView::SingleSelection);
        standard_user_table->setSelectionBehavior(QAbstractItemView::SelectRows);
        standard_user_table->setColumnCount(5);

        horizontalLayout_2->addWidget(standard_user_table);


        verticalLayout_5->addLayout(horizontalLayout_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        measurementLabel_2 = new QLabel(standard_tab);
        measurementLabel_2->setObjectName(QString::fromUtf8("measurementLabel_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, measurementLabel_2);

        standard_measurement_filter_field = new QLineEdit(standard_tab);
        standard_measurement_filter_field->setObjectName(QString::fromUtf8("standard_measurement_filter_field"));
        standard_measurement_filter_field->setClearButtonEnabled(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, standard_measurement_filter_field);

        minQuantityLabel = new QLabel(standard_tab);
        minQuantityLabel->setObjectName(QString::fromUtf8("minQuantityLabel"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, minQuantityLabel);

        standard_quantity_filter_field = new QLineEdit(standard_tab);
        standard_quantity_filter_field->setObjectName(QString::fromUtf8("standard_quantity_filter_field"));
        standard_quantity_filter_field->setClearButtonEnabled(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, standard_quantity_filter_field);

        resultLabel = new QLabel(standard_tab);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, resultLabel);

        standard_filter_result_field = new QLineEdit(standard_tab);
        standard_filter_result_field->setObjectName(QString::fromUtf8("standard_filter_result_field"));
        standard_filter_result_field->setReadOnly(true);
        standard_filter_result_field->setClearButtonEnabled(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, standard_filter_result_field);


        gridLayout_2->addLayout(formLayout_2, 1, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        open_button = new QPushButton(standard_tab);
        open_button->setObjectName(QString::fromUtf8("open_button"));

        verticalLayout_4->addWidget(open_button);

        open_locally_button = new QPushButton(standard_tab);
        open_locally_button->setObjectName(QString::fromUtf8("open_locally_button"));

        verticalLayout_4->addWidget(open_locally_button);

        standard_filter_button = new QPushButton(standard_tab);
        standard_filter_button->setObjectName(QString::fromUtf8("standard_filter_button"));

        verticalLayout_4->addWidget(standard_filter_button);

        standard_filter_button_next = new QPushButton(standard_tab);
        standard_filter_button_next->setObjectName(QString::fromUtf8("standard_filter_button_next"));

        verticalLayout_4->addWidget(standard_filter_button_next);


        gridLayout_2->addLayout(verticalLayout_4, 1, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_2);

        main_tab_widget->addTab(standard_tab, QString());
        chart_tab = new QWidget();
        chart_tab->setObjectName(QString::fromUtf8("chart_tab"));
        horizontalLayout_3 = new QHBoxLayout(chart_tab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        chart_tab_layout = new QHBoxLayout();
        chart_tab_layout->setSpacing(6);
        chart_tab_layout->setObjectName(QString::fromUtf8("chart_tab_layout"));

        horizontalLayout_3->addLayout(chart_tab_layout);

        main_tab_widget->addTab(chart_tab, QString());

        verticalLayout_3->addWidget(main_tab_widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        undo_button = new QPushButton(centralWidget);
        undo_button->setObjectName(QString::fromUtf8("undo_button"));

        horizontalLayout->addWidget(undo_button);

        redo_button = new QPushButton(centralWidget);
        redo_button->setObjectName(QString::fromUtf8("redo_button"));

        horizontalLayout->addWidget(redo_button);


        verticalLayout_3->addLayout(horizontalLayout);

        GUIClass->setCentralWidget(centralWidget);
#if QT_CONFIG(shortcut)
        iDLabel->setBuddy(ID_field);
        measurementLabel->setBuddy(measurement_field);
        clarityLabel->setBuddy(clarity_field);
        quantityLabel->setBuddy(quantity_field);
        photographLabel->setBuddy(photograph_field);
        measurementLabel_2->setBuddy(standard_measurement_filter_field);
        minQuantityLabel->setBuddy(standard_quantity_filter_field);
        resultLabel->setBuddy(standard_filter_result_field);
#endif // QT_CONFIG(shortcut)

        retranslateUi(GUIClass);
        QObject::connect(main_tab_widget, SIGNAL(currentChanged(int)), GUIClass, SLOT(tabwidget_tab_changed(int)));
        QObject::connect(undo_button, SIGNAL(clicked()), GUIClass, SLOT(undo_button_click()));
        QObject::connect(redo_button, SIGNAL(clicked()), GUIClass, SLOT(redo_button_click()));
        QObject::connect(senior_add_evidence_button, SIGNAL(clicked()), GUIClass, SLOT(senior_add_button_click()));
        QObject::connect(senior_update_evidence_button, SIGNAL(clicked()), GUIClass, SLOT(senior_update_button_click()));
        QObject::connect(senior_delete_evidence_button, SIGNAL(clicked()), GUIClass, SLOT(senior_delete_button_click()));
        QObject::connect(senior_table, SIGNAL(cellDoubleClicked(int,int)), GUIClass, SLOT(senior_table_cell_doubleclick(int,int)));
        QObject::connect(standard_save_button, SIGNAL(clicked()), GUIClass, SLOT(standard_save_button_click()));
        QObject::connect(standard_filter_button, SIGNAL(clicked()), GUIClass, SLOT(standard_filter_button_click()));
        QObject::connect(standard_filter_button_next, SIGNAL(clicked()), GUIClass, SLOT(standard_filter_button_next_click()));
        QObject::connect(open_button, SIGNAL(clicked()), GUIClass, SLOT(standard_open_button_click()));
        QObject::connect(open_locally_button, SIGNAL(clicked()), GUIClass, SLOT(standard_open_locally_button_click()));

        main_tab_widget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUIClass)
    {
        GUIClass->setWindowTitle(QCoreApplication::translate("GUIClass", "GUI", nullptr));
        iDLabel->setText(QCoreApplication::translate("GUIClass", "&ID:", nullptr));
        measurementLabel->setText(QCoreApplication::translate("GUIClass", "&Measurement:", nullptr));
        clarityLabel->setText(QCoreApplication::translate("GUIClass", "&Clarity:", nullptr));
        quantityLabel->setText(QCoreApplication::translate("GUIClass", "&Quantity:", nullptr));
        photographLabel->setText(QCoreApplication::translate("GUIClass", "&Photograph:", nullptr));
        senior_add_evidence_button->setText(QCoreApplication::translate("GUIClass", "Add", nullptr));
        senior_update_evidence_button->setText(QCoreApplication::translate("GUIClass", "Update", nullptr));
        senior_delete_evidence_button->setText(QCoreApplication::translate("GUIClass", "Delete", nullptr));
        main_tab_widget->setTabText(main_tab_widget->indexOf(senior_tab), QCoreApplication::translate("GUIClass", "Senior clearance", nullptr));
        standard_save_button->setText(QCoreApplication::translate("GUIClass", ">", nullptr));
        measurementLabel_2->setText(QCoreApplication::translate("GUIClass", "Measurement:", nullptr));
        minQuantityLabel->setText(QCoreApplication::translate("GUIClass", "Min. Quantity:", nullptr));
        resultLabel->setText(QCoreApplication::translate("GUIClass", "Result:", nullptr));
        open_button->setText(QCoreApplication::translate("GUIClass", "Open (file) in another program", nullptr));
        open_locally_button->setText(QCoreApplication::translate("GUIClass", "Open in new window", nullptr));
        standard_filter_button->setText(QCoreApplication::translate("GUIClass", "Filter", nullptr));
        standard_filter_button_next->setText(QCoreApplication::translate("GUIClass", "Next", nullptr));
        main_tab_widget->setTabText(main_tab_widget->indexOf(standard_tab), QCoreApplication::translate("GUIClass", "Standard clearance", nullptr));
        main_tab_widget->setTabText(main_tab_widget->indexOf(chart_tab), QCoreApplication::translate("GUIClass", "Chart", nullptr));
        undo_button->setText(QCoreApplication::translate("GUIClass", "Undo", nullptr));
        redo_button->setText(QCoreApplication::translate("GUIClass", "Redo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUIClass: public Ui_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
