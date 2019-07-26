/********************************************************************************
** Form generated from reading UI file 'DlgNewROSAPIUser.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGNEWROSAPIUSER_H
#define UI_DLGNEWROSAPIUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DlgNewROSAPIUser
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *userNameLineEdit;
    QLabel *label_2;
    QComboBox *grupNameComboBox;
    QLabel *label_3;
    QComboBox *userLevelComboBox;
    QLabel *label_4;
    QLineEdit *userPassLineEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptButton;

    void setupUi(QDialog *DlgNewROSAPIUser)
    {
        if (DlgNewROSAPIUser->objectName().isEmpty())
            DlgNewROSAPIUser->setObjectName(QString::fromUtf8("DlgNewROSAPIUser"));
        DlgNewROSAPIUser->resize(241, 175);
        gridLayout = new QGridLayout(DlgNewROSAPIUser);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(DlgNewROSAPIUser);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        userNameLineEdit = new QLineEdit(DlgNewROSAPIUser);
        userNameLineEdit->setObjectName(QString::fromUtf8("userNameLineEdit"));

        gridLayout->addWidget(userNameLineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(DlgNewROSAPIUser);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        grupNameComboBox = new QComboBox(DlgNewROSAPIUser);
        grupNameComboBox->setObjectName(QString::fromUtf8("grupNameComboBox"));

        gridLayout->addWidget(grupNameComboBox, 1, 1, 1, 1);

        label_3 = new QLabel(DlgNewROSAPIUser);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        userLevelComboBox = new QComboBox(DlgNewROSAPIUser);
        userLevelComboBox->setObjectName(QString::fromUtf8("userLevelComboBox"));

        gridLayout->addWidget(userLevelComboBox, 2, 1, 1, 1);

        label_4 = new QLabel(DlgNewROSAPIUser);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        userPassLineEdit = new QLineEdit(DlgNewROSAPIUser);
        userPassLineEdit->setObjectName(QString::fromUtf8("userPassLineEdit"));

        gridLayout->addWidget(userPassLineEdit, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(198, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        acceptButton = new QPushButton(DlgNewROSAPIUser);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        horizontalLayout->addWidget(acceptButton);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 2);


        retranslateUi(DlgNewROSAPIUser);

        QMetaObject::connectSlotsByName(DlgNewROSAPIUser);
    } // setupUi

    void retranslateUi(QDialog *DlgNewROSAPIUser)
    {
        DlgNewROSAPIUser->setWindowTitle(QApplication::translate("DlgNewROSAPIUser", "Dialog", nullptr));
        label->setText(QApplication::translate("DlgNewROSAPIUser", "Nombre", nullptr));
        label_2->setText(QApplication::translate("DlgNewROSAPIUser", "Grupo", nullptr));
        label_3->setText(QApplication::translate("DlgNewROSAPIUser", "Nivel /Tipo", nullptr));
        label_4->setText(QApplication::translate("DlgNewROSAPIUser", "Contrase\303\261a", nullptr));
        acceptButton->setText(QApplication::translate("DlgNewROSAPIUser", "Aceptar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgNewROSAPIUser: public Ui_DlgNewROSAPIUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGNEWROSAPIUSER_H
