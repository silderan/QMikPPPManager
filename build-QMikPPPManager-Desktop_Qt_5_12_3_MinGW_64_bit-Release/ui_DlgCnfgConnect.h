/********************************************************************************
** Form generated from reading UI file 'DlgCnfgConnect.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGCNFGCONNECT_H
#define UI_DLGCNFGCONNECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_DlgCnfgConnect
{
public:
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptButton;
    QPushButton *cancelButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *userLineEdit;
    QLabel *label_2;
    QLineEdit *passLineEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *addButton;
    QToolButton *delButton;
    QTableWidget *hostsTable;
    QGroupBox *radiusGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_5;
    QSpinBox *radiusPort;
    QLabel *label_7;
    QLabel *label_4;
    QLineEdit *radiusUserName;
    QLineEdit *radiusURL;
    QLineEdit *radiusUserPass;
    QLineEdit *radiusDataBase;

    void setupUi(QDialog *DlgCnfgConnect)
    {
        if (DlgCnfgConnect->objectName().isEmpty())
            DlgCnfgConnect->setObjectName(QString::fromUtf8("DlgCnfgConnect"));
        DlgCnfgConnect->resize(898, 547);
        gridLayout_3 = new QGridLayout(DlgCnfgConnect);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer = new QSpacerItem(336, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 2, 0, 1, 1);

        acceptButton = new QPushButton(DlgCnfgConnect);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        gridLayout_3->addWidget(acceptButton, 2, 1, 1, 1);

        cancelButton = new QPushButton(DlgCnfgConnect);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout_3->addWidget(cancelButton, 2, 2, 1, 1);

        groupBox = new QGroupBox(DlgCnfgConnect);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        userLineEdit = new QLineEdit(groupBox);
        userLineEdit->setObjectName(QString::fromUtf8("userLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(userLineEdit->sizePolicy().hasHeightForWidth());
        userLineEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(userLineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        passLineEdit = new QLineEdit(groupBox);
        passLineEdit->setObjectName(QString::fromUtf8("passLineEdit"));
        sizePolicy.setHeightForWidth(passLineEdit->sizePolicy().hasHeightForWidth());
        passLineEdit->setSizePolicy(sizePolicy);
        passLineEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passLineEdit, 0, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        addButton = new QToolButton(groupBox);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        horizontalLayout->addWidget(addButton);

        delButton = new QToolButton(groupBox);
        delButton->setObjectName(QString::fromUtf8("delButton"));

        horizontalLayout->addWidget(delButton);


        gridLayout->addLayout(horizontalLayout, 0, 4, 1, 1);

        hostsTable = new QTableWidget(groupBox);
        hostsTable->setObjectName(QString::fromUtf8("hostsTable"));

        gridLayout->addWidget(hostsTable, 1, 0, 1, 5);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 3);

        radiusGroupBox = new QGroupBox(DlgCnfgConnect);
        radiusGroupBox->setObjectName(QString::fromUtf8("radiusGroupBox"));
        gridLayout_2 = new QGridLayout(radiusGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(radiusGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 6, 1, 1);

        label_3 = new QLabel(radiusGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_5 = new QLabel(radiusGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 0, 4, 1, 1);

        radiusPort = new QSpinBox(radiusGroupBox);
        radiusPort->setObjectName(QString::fromUtf8("radiusPort"));
        radiusPort->setMinimum(1);
        radiusPort->setMaximum(65535);

        gridLayout_2->addWidget(radiusPort, 0, 7, 1, 1);

        label_7 = new QLabel(radiusGroupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 0, 8, 1, 1);

        label_4 = new QLabel(radiusGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);

        radiusUserName = new QLineEdit(radiusGroupBox);
        radiusUserName->setObjectName(QString::fromUtf8("radiusUserName"));
        sizePolicy.setHeightForWidth(radiusUserName->sizePolicy().hasHeightForWidth());
        radiusUserName->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(radiusUserName, 0, 1, 1, 1);

        radiusURL = new QLineEdit(radiusGroupBox);
        radiusURL->setObjectName(QString::fromUtf8("radiusURL"));

        gridLayout_2->addWidget(radiusURL, 0, 5, 1, 1);

        radiusUserPass = new QLineEdit(radiusGroupBox);
        radiusUserPass->setObjectName(QString::fromUtf8("radiusUserPass"));
        sizePolicy.setHeightForWidth(radiusUserPass->sizePolicy().hasHeightForWidth());
        radiusUserPass->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(radiusUserPass, 0, 3, 1, 1);

        radiusDataBase = new QLineEdit(radiusGroupBox);
        radiusDataBase->setObjectName(QString::fromUtf8("radiusDataBase"));

        gridLayout_2->addWidget(radiusDataBase, 0, 9, 1, 1);


        gridLayout_3->addWidget(radiusGroupBox, 1, 0, 1, 3);

        QWidget::setTabOrder(userLineEdit, passLineEdit);
        QWidget::setTabOrder(passLineEdit, addButton);
        QWidget::setTabOrder(addButton, delButton);
        QWidget::setTabOrder(delButton, hostsTable);
        QWidget::setTabOrder(hostsTable, radiusUserName);
        QWidget::setTabOrder(radiusUserName, radiusUserPass);
        QWidget::setTabOrder(radiusUserPass, radiusURL);
        QWidget::setTabOrder(radiusURL, radiusPort);
        QWidget::setTabOrder(radiusPort, radiusDataBase);
        QWidget::setTabOrder(radiusDataBase, acceptButton);
        QWidget::setTabOrder(acceptButton, cancelButton);

        retranslateUi(DlgCnfgConnect);

        QMetaObject::connectSlotsByName(DlgCnfgConnect);
    } // setupUi

    void retranslateUi(QDialog *DlgCnfgConnect)
    {
        DlgCnfgConnect->setWindowTitle(QApplication::translate("DlgCnfgConnect", "Configuraci\303\263n routers", nullptr));
        acceptButton->setText(QApplication::translate("DlgCnfgConnect", "Aceptar", nullptr));
        cancelButton->setText(QApplication::translate("DlgCnfgConnect", "Cancelar", nullptr));
        groupBox->setTitle(QApplication::translate("DlgCnfgConnect", "Servidores PPP", nullptr));
        label->setText(QApplication::translate("DlgCnfgConnect", "Usuario", nullptr));
        label_2->setText(QApplication::translate("DlgCnfgConnect", "Contrase\303\261a", nullptr));
        addButton->setText(QApplication::translate("DlgCnfgConnect", "+", nullptr));
        delButton->setText(QApplication::translate("DlgCnfgConnect", "-", nullptr));
        radiusGroupBox->setTitle(QApplication::translate("DlgCnfgConnect", "Radius", nullptr));
        label_6->setText(QApplication::translate("DlgCnfgConnect", "Puerto", nullptr));
        label_3->setText(QApplication::translate("DlgCnfgConnect", "Usuario", nullptr));
        label_5->setText(QApplication::translate("DlgCnfgConnect", "IP", nullptr));
        label_7->setText(QApplication::translate("DlgCnfgConnect", "Nombre Base de datos", nullptr));
        label_4->setText(QApplication::translate("DlgCnfgConnect", "Contrase\303\261a", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgCnfgConnect: public Ui_DlgCnfgConnect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGCNFGCONNECT_H
