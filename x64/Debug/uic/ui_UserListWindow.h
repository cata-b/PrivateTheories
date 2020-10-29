/********************************************************************************
** Form generated from reading UI file 'UserListWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERLISTWINDOW_H
#define UI_USERLISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserListWindow
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *standardTableView;

    void setupUi(QWidget *UserListWindow)
    {
        if (UserListWindow->objectName().isEmpty())
            UserListWindow->setObjectName(QString::fromUtf8("UserListWindow"));
        UserListWindow->resize(637, 364);
        verticalLayout = new QVBoxLayout(UserListWindow);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        standardTableView = new QTableView(UserListWindow);
        standardTableView->setObjectName(QString::fromUtf8("standardTableView"));
        standardTableView->horizontalHeader()->setCascadingSectionResizes(false);

        verticalLayout->addWidget(standardTableView);


        retranslateUi(UserListWindow);

        QMetaObject::connectSlotsByName(UserListWindow);
    } // setupUi

    void retranslateUi(QWidget *UserListWindow)
    {
        UserListWindow->setWindowTitle(QCoreApplication::translate("UserListWindow", "UserListWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserListWindow: public Ui_UserListWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERLISTWINDOW_H
