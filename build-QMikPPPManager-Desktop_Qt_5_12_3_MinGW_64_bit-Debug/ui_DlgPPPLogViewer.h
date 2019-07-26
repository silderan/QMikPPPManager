/********************************************************************************
** Form generated from reading UI file 'DlgPPPLogViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPPPLOGVIEWER_H
#define UI_DLGPPPLOGVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgPPPLogViewer
{
public:
    QGridLayout *gridLayout;
    QPushButton *compactLogsButton;
    QLabel *infoLabel;
    QTableWidget *logsTable;

    void setupUi(QDialog *DlgPPPLogViewer)
    {
        if (DlgPPPLogViewer->objectName().isEmpty())
            DlgPPPLogViewer->setObjectName(QString::fromUtf8("DlgPPPLogViewer"));
        DlgPPPLogViewer->resize(863, 596);
        gridLayout = new QGridLayout(DlgPPPLogViewer);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        compactLogsButton = new QPushButton(DlgPPPLogViewer);
        compactLogsButton->setObjectName(QString::fromUtf8("compactLogsButton"));

        gridLayout->addWidget(compactLogsButton, 1, 1, 1, 1);

        infoLabel = new QLabel(DlgPPPLogViewer);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(infoLabel->sizePolicy().hasHeightForWidth());
        infoLabel->setSizePolicy(sizePolicy);

        gridLayout->addWidget(infoLabel, 1, 0, 1, 1);

        logsTable = new QTableWidget(DlgPPPLogViewer);
        logsTable->setObjectName(QString::fromUtf8("logsTable"));
        logsTable->horizontalHeader()->setStretchLastSection(true);
        logsTable->verticalHeader()->setDefaultSectionSize(26);

        gridLayout->addWidget(logsTable, 0, 0, 1, 2);


        retranslateUi(DlgPPPLogViewer);

        QMetaObject::connectSlotsByName(DlgPPPLogViewer);
    } // setupUi

    void retranslateUi(QDialog *DlgPPPLogViewer)
    {
        DlgPPPLogViewer->setWindowTitle(QApplication::translate("DlgPPPLogViewer", "Visor de registros", nullptr));
        compactLogsButton->setText(QApplication::translate("DlgPPPLogViewer", "Compactar", nullptr));
        infoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DlgPPPLogViewer: public Ui_DlgPPPLogViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGPPPLOGVIEWER_H
