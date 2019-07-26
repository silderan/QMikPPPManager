/********************************************************************************
** Form generated from reading UI file 'DlgNewPPPProfile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGNEWPPPPROFILE_H
#define UI_DLGNEWPPPPROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include "Widgets/QSpeedTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DlgNewPPPProfile
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *pppProfileNameLineEdit;
    QLabel *label_3;
    QComboBox *bridgeComboBox;
    QLabel *label_4;
    QComboBox *localAddressComboBox;
    QLabel *label_5;
    QComboBox *remoteAddressComboBox;
    QLabel *label_2;
    QSpeedTableWidget *speedRateLimits;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptButton;

    void setupUi(QDialog *DlgNewPPPProfile)
    {
        if (DlgNewPPPProfile->objectName().isEmpty())
            DlgNewPPPProfile->setObjectName(QString::fromUtf8("DlgNewPPPProfile"));
        DlgNewPPPProfile->resize(427, 506);
        gridLayout = new QGridLayout(DlgNewPPPProfile);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(DlgNewPPPProfile);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pppProfileNameLineEdit = new QLineEdit(DlgNewPPPProfile);
        pppProfileNameLineEdit->setObjectName(QString::fromUtf8("pppProfileNameLineEdit"));

        gridLayout->addWidget(pppProfileNameLineEdit, 0, 1, 1, 1);

        label_3 = new QLabel(DlgNewPPPProfile);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        bridgeComboBox = new QComboBox(DlgNewPPPProfile);
        bridgeComboBox->setObjectName(QString::fromUtf8("bridgeComboBox"));

        gridLayout->addWidget(bridgeComboBox, 1, 1, 1, 1);

        label_4 = new QLabel(DlgNewPPPProfile);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        localAddressComboBox = new QComboBox(DlgNewPPPProfile);
        localAddressComboBox->setObjectName(QString::fromUtf8("localAddressComboBox"));

        gridLayout->addWidget(localAddressComboBox, 2, 1, 1, 1);

        label_5 = new QLabel(DlgNewPPPProfile);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        remoteAddressComboBox = new QComboBox(DlgNewPPPProfile);
        remoteAddressComboBox->setObjectName(QString::fromUtf8("remoteAddressComboBox"));

        gridLayout->addWidget(remoteAddressComboBox, 3, 1, 1, 1);

        label_2 = new QLabel(DlgNewPPPProfile);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 4, 0, 1, 2);

        speedRateLimits = new QSpeedTableWidget(DlgNewPPPProfile);
        speedRateLimits->setObjectName(QString::fromUtf8("speedRateLimits"));

        gridLayout->addWidget(speedRateLimits, 5, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        acceptButton = new QPushButton(DlgNewPPPProfile);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        horizontalLayout->addWidget(acceptButton);


        gridLayout->addLayout(horizontalLayout, 6, 0, 1, 2);


        retranslateUi(DlgNewPPPProfile);

        QMetaObject::connectSlotsByName(DlgNewPPPProfile);
    } // setupUi

    void retranslateUi(QDialog *DlgNewPPPProfile)
    {
        DlgNewPPPProfile->setWindowTitle(QApplication::translate("DlgNewPPPProfile", "Dialog", nullptr));
        label->setText(QApplication::translate("DlgNewPPPProfile", "Nombre perfl", nullptr));
        label_3->setText(QApplication::translate("DlgNewPPPProfile", "Bridge", nullptr));
        label_4->setText(QApplication::translate("DlgNewPPPProfile", "Local Addres", nullptr));
        label_5->setText(QApplication::translate("DlgNewPPPProfile", "Remote Address", nullptr));
        label_2->setText(QApplication::translate("DlgNewPPPProfile", "Velocidades", nullptr));
        acceptButton->setText(QApplication::translate("DlgNewPPPProfile", "Aceptar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgNewPPPProfile: public Ui_DlgNewPPPProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGNEWPPPPROFILE_H
