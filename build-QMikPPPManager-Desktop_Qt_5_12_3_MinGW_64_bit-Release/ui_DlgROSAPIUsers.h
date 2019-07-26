/********************************************************************************
** Form generated from reading UI file 'DlgROSAPIUsers.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGROSAPIUSERS_H
#define UI_DLGROSAPIUSERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "Widgets/QROSAPIUserTableWidget.h"
#include "Widgets/QROSAPIUsersGroupTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DlgROSAPIUsers
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *addGroupButton;
    QToolButton *delGroupButton;
    QROSAPIUsersGroupTableWidget *groupsTable;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QToolButton *delUserButton;
    QROSAPIUserTableWidget *usersTable;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *addUserButton;

    void setupUi(QDialog *DlgROSAPIUsers)
    {
        if (DlgROSAPIUsers->objectName().isEmpty())
            DlgROSAPIUsers->setObjectName(QString::fromUtf8("DlgROSAPIUsers"));
        DlgROSAPIUsers->resize(666, 757);
        verticalLayout = new QVBoxLayout(DlgROSAPIUsers);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(DlgROSAPIUsers);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(602, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        addGroupButton = new QToolButton(groupBox);
        addGroupButton->setObjectName(QString::fromUtf8("addGroupButton"));

        gridLayout->addWidget(addGroupButton, 0, 1, 1, 1);

        delGroupButton = new QToolButton(groupBox);
        delGroupButton->setObjectName(QString::fromUtf8("delGroupButton"));

        gridLayout->addWidget(delGroupButton, 0, 2, 1, 1);

        groupsTable = new QROSAPIUsersGroupTableWidget(groupBox);
        groupsTable->setObjectName(QString::fromUtf8("groupsTable"));
        groupsTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(groupsTable, 1, 0, 1, 3);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(DlgROSAPIUsers);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        delUserButton = new QToolButton(groupBox_2);
        delUserButton->setObjectName(QString::fromUtf8("delUserButton"));

        gridLayout_2->addWidget(delUserButton, 0, 2, 1, 1);

        usersTable = new QROSAPIUserTableWidget(groupBox_2);
        usersTable->setObjectName(QString::fromUtf8("usersTable"));
        usersTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout_2->addWidget(usersTable, 1, 0, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(428, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        addUserButton = new QToolButton(groupBox_2);
        addUserButton->setObjectName(QString::fromUtf8("addUserButton"));

        gridLayout_2->addWidget(addUserButton, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(DlgROSAPIUsers);

        QMetaObject::connectSlotsByName(DlgROSAPIUsers);
    } // setupUi

    void retranslateUi(QDialog *DlgROSAPIUsers)
    {
        DlgROSAPIUsers->setWindowTitle(QApplication::translate("DlgROSAPIUsers", "Usuarios y grupos ROS API", nullptr));
        groupBox->setTitle(QApplication::translate("DlgROSAPIUsers", "Grupos de usuarios", nullptr));
        addGroupButton->setText(QApplication::translate("DlgROSAPIUsers", "+", nullptr));
        delGroupButton->setText(QApplication::translate("DlgROSAPIUsers", "-", nullptr));
        groupBox_2->setTitle(QApplication::translate("DlgROSAPIUsers", "Usuarios", nullptr));
        delUserButton->setText(QApplication::translate("DlgROSAPIUsers", "-", nullptr));
        addUserButton->setText(QApplication::translate("DlgROSAPIUsers", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgROSAPIUsers: public Ui_DlgROSAPIUsers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGROSAPIUSERS_H
