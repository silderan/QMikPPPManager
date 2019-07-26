/********************************************************************************
** Form generated from reading UI file 'QMikPPPManager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMIKPPPMANAGER_H
#define UI_QMIKPPPMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "Widgets/QROSSecretTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_QMikPPPManager
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QPushButton *connectButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QPushButton *advancedConfigButton;
    QPushButton *pppProfilesButton;
    QPushButton *localConfigButton;
    QPushButton *pppLogsButton;
    QPushButton *apiUsersButton;
    QPushButton *connectionConfigButton;
    QROSSecretTableWidget *usersTable;
    QPushButton *addUserButton;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QComboBox *fieldFilterComboBox;
    QLineEdit *textFilterLineEdit;
    QComboBox *serviceStateFilterComboBox;
    QSpacerItem *verticalSpacer_2;
    QPushButton *disconnectButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QMikPPPManager)
    {
        if (QMikPPPManager->objectName().isEmpty())
            QMikPPPManager->setObjectName(QString::fromUtf8("QMikPPPManager"));
        QMikPPPManager->resize(924, 714);
        centralWidget = new QWidget(QMikPPPManager);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(connectButton->sizePolicy().hasHeightForWidth());
        connectButton->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(connectButton, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(4);
        gridLayout->setContentsMargins(4, 8, 4, 9);
        advancedConfigButton = new QPushButton(groupBox_2);
        advancedConfigButton->setObjectName(QString::fromUtf8("advancedConfigButton"));

        gridLayout->addWidget(advancedConfigButton, 1, 1, 1, 1);

        pppProfilesButton = new QPushButton(groupBox_2);
        pppProfilesButton->setObjectName(QString::fromUtf8("pppProfilesButton"));

        gridLayout->addWidget(pppProfilesButton, 2, 0, 1, 1);

        localConfigButton = new QPushButton(groupBox_2);
        localConfigButton->setObjectName(QString::fromUtf8("localConfigButton"));

        gridLayout->addWidget(localConfigButton, 0, 0, 1, 1);

        pppLogsButton = new QPushButton(groupBox_2);
        pppLogsButton->setObjectName(QString::fromUtf8("pppLogsButton"));

        gridLayout->addWidget(pppLogsButton, 2, 1, 1, 1);

        apiUsersButton = new QPushButton(groupBox_2);
        apiUsersButton->setObjectName(QString::fromUtf8("apiUsersButton"));

        gridLayout->addWidget(apiUsersButton, 1, 0, 1, 1);

        connectionConfigButton = new QPushButton(groupBox_2);
        connectionConfigButton->setObjectName(QString::fromUtf8("connectionConfigButton"));

        gridLayout->addWidget(connectionConfigButton, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 5, 0, 1, 2);

        usersTable = new QROSSecretTableWidget(centralWidget);
        usersTable->setObjectName(QString::fromUtf8("usersTable"));

        gridLayout_3->addWidget(usersTable, 0, 2, 6, 1);

        addUserButton = new QPushButton(centralWidget);
        addUserButton->setObjectName(QString::fromUtf8("addUserButton"));

        gridLayout_3->addWidget(addUserButton, 3, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 181, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setVerticalSpacing(4);
        gridLayout_2->setContentsMargins(4, 8, 4, 8);
        fieldFilterComboBox = new QComboBox(groupBox);
        fieldFilterComboBox->setObjectName(QString::fromUtf8("fieldFilterComboBox"));

        gridLayout_2->addWidget(fieldFilterComboBox, 1, 0, 1, 1);

        textFilterLineEdit = new QLineEdit(groupBox);
        textFilterLineEdit->setObjectName(QString::fromUtf8("textFilterLineEdit"));
        sizePolicy.setHeightForWidth(textFilterLineEdit->sizePolicy().hasHeightForWidth());
        textFilterLineEdit->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(textFilterLineEdit, 0, 0, 1, 1);

        serviceStateFilterComboBox = new QComboBox(groupBox);
        serviceStateFilterComboBox->setObjectName(QString::fromUtf8("serviceStateFilterComboBox"));

        gridLayout_2->addWidget(serviceStateFilterComboBox, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 180, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 4, 0, 1, 2);

        disconnectButton = new QPushButton(centralWidget);
        disconnectButton->setObjectName(QString::fromUtf8("disconnectButton"));
        sizePolicy.setHeightForWidth(disconnectButton->sizePolicy().hasHeightForWidth());
        disconnectButton->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(disconnectButton, 0, 1, 1, 1);

        QMikPPPManager->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QMikPPPManager);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QMikPPPManager->setStatusBar(statusBar);

        retranslateUi(QMikPPPManager);

        QMetaObject::connectSlotsByName(QMikPPPManager);
    } // setupUi

    void retranslateUi(QMainWindow *QMikPPPManager)
    {
        QMikPPPManager->setWindowTitle(QApplication::translate("QMikPPPManager", "QMikPPPManager", nullptr));
        connectButton->setText(QApplication::translate("QMikPPPManager", "Conectar", nullptr));
        groupBox_2->setTitle(QApplication::translate("QMikPPPManager", "Configuraci\303\263n", nullptr));
        advancedConfigButton->setText(QApplication::translate("QMikPPPManager", "Avanzada", nullptr));
        pppProfilesButton->setText(QApplication::translate("QMikPPPManager", "Perfiles PPP", nullptr));
        localConfigButton->setText(QApplication::translate("QMikPPPManager", "Apariencia", nullptr));
        pppLogsButton->setText(QApplication::translate("QMikPPPManager", "Registros", nullptr));
        apiUsersButton->setText(QApplication::translate("QMikPPPManager", "Usuarios API", nullptr));
        connectionConfigButton->setText(QApplication::translate("QMikPPPManager", "Routers", nullptr));
        addUserButton->setText(QApplication::translate("QMikPPPManager", "A\303\261adir usuario", nullptr));
        groupBox->setTitle(QApplication::translate("QMikPPPManager", "Filtro", nullptr));
        disconnectButton->setText(QApplication::translate("QMikPPPManager", "Desconectar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QMikPPPManager: public Ui_QMikPPPManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMIKPPPMANAGER_H
