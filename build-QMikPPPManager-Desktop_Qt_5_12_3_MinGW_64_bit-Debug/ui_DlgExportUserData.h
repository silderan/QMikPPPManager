/********************************************************************************
** Form generated from reading UI file 'DlgExportUserData.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGEXPORTUSERDATA_H
#define UI_DLGEXPORTUSERDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgExportUserData
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *exportFileButton;
    QPushButton *openFolderButton;
    QPushButton *openFileButton;
    QLineEdit *exportFileLineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *exportUsersDataButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *DlgExportUserData)
    {
        if (DlgExportUserData->objectName().isEmpty())
            DlgExportUserData->setObjectName(QString::fromUtf8("DlgExportUserData"));
        DlgExportUserData->resize(757, 94);
        verticalLayout = new QVBoxLayout(DlgExportUserData);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        exportFileButton = new QPushButton(DlgExportUserData);
        exportFileButton->setObjectName(QString::fromUtf8("exportFileButton"));

        gridLayout->addWidget(exportFileButton, 0, 0, 1, 1);

        openFolderButton = new QPushButton(DlgExportUserData);
        openFolderButton->setObjectName(QString::fromUtf8("openFolderButton"));

        gridLayout->addWidget(openFolderButton, 1, 4, 1, 1);

        openFileButton = new QPushButton(DlgExportUserData);
        openFileButton->setObjectName(QString::fromUtf8("openFileButton"));

        gridLayout->addWidget(openFileButton, 1, 3, 1, 1);

        exportFileLineEdit = new QLineEdit(DlgExportUserData);
        exportFileLineEdit->setObjectName(QString::fromUtf8("exportFileLineEdit"));

        gridLayout->addWidget(exportFileLineEdit, 0, 1, 1, 4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        exportUsersDataButton = new QPushButton(DlgExportUserData);
        exportUsersDataButton->setObjectName(QString::fromUtf8("exportUsersDataButton"));

        gridLayout->addWidget(exportUsersDataButton, 1, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(DlgExportUserData);

        QMetaObject::connectSlotsByName(DlgExportUserData);
    } // setupUi

    void retranslateUi(QDialog *DlgExportUserData)
    {
        DlgExportUserData->setWindowTitle(QApplication::translate("DlgExportUserData", "Dialog", nullptr));
        exportFileButton->setText(QApplication::translate("DlgExportUserData", "Fichero salida", nullptr));
        openFolderButton->setText(QApplication::translate("DlgExportUserData", "Abrir Carpeta contenedora", nullptr));
        openFileButton->setText(QApplication::translate("DlgExportUserData", "Abrir fichero", nullptr));
        exportUsersDataButton->setText(QApplication::translate("DlgExportUserData", "Exportar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgExportUserData: public Ui_DlgExportUserData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGEXPORTUSERDATA_H
