/********************************************************************************
** Form generated from reading UI file 'DlgPPPProfiles.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPPPPROFILES_H
#define UI_DLGPPPPROFILES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include "Widgets/QPPPProfilesTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DlgPPPProfiles
{
public:
    QGridLayout *gridLayout;
    QPushButton *acceptButton;
    QToolButton *addButton;
    QPPPProfilesTableWidget *profilesTable;
    QSpacerItem *horizontalSpacer;
    QToolButton *delButton;

    void setupUi(QDialog *DlgPPPProfiles)
    {
        if (DlgPPPProfiles->objectName().isEmpty())
            DlgPPPProfiles->setObjectName(QString::fromUtf8("DlgPPPProfiles"));
        DlgPPPProfiles->resize(955, 720);
        gridLayout = new QGridLayout(DlgPPPProfiles);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        acceptButton = new QPushButton(DlgPPPProfiles);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(acceptButton->sizePolicy().hasHeightForWidth());
        acceptButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(acceptButton, 2, 0, 1, 1);

        addButton = new QToolButton(DlgPPPProfiles);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout->addWidget(addButton, 0, 1, 1, 1);

        profilesTable = new QPPPProfilesTableWidget(DlgPPPProfiles);
        profilesTable->setObjectName(QString::fromUtf8("profilesTable"));
        profilesTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(profilesTable, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(428, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        delButton = new QToolButton(DlgPPPProfiles);
        delButton->setObjectName(QString::fromUtf8("delButton"));

        gridLayout->addWidget(delButton, 0, 2, 1, 1);


        retranslateUi(DlgPPPProfiles);

        QMetaObject::connectSlotsByName(DlgPPPProfiles);
    } // setupUi

    void retranslateUi(QDialog *DlgPPPProfiles)
    {
        DlgPPPProfiles->setWindowTitle(QApplication::translate("DlgPPPProfiles", "PPP Profiles", nullptr));
        acceptButton->setText(QApplication::translate("DlgPPPProfiles", "Aceptar", nullptr));
        addButton->setText(QApplication::translate("DlgPPPProfiles", "+", nullptr));
        delButton->setText(QApplication::translate("DlgPPPProfiles", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgPPPProfiles: public Ui_DlgPPPProfiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGPPPPROFILES_H
