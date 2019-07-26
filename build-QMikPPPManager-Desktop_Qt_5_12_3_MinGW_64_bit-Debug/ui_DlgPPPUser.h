/********************************************************************************
** Form generated from reading UI file 'DlgPPPUser.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPPPUSER_H
#define UI_DLGPPPUSER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "Widgets/QFancyComboBox.h"
#include "Widgets/QPortForwardTableWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DlgPPPUser
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *voipGroupBox;
    QGridLayout *gridLayout_5;
    QLabel *label_16;
    QLineEdit *voipServerLineEdit;
    QLineEdit *voipPhoneNumber;
    QLineEdit *voipUserPass;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *label_24;
    QLineEdit *voipUserName;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *copyInfoButton;
    QPushButton *applyDataButton;
    QPushButton *clientLogsButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer;
    QGroupBox *lanGroupBox;
    QGridLayout *gridLayout_6;
    QToolButton *delPortButton;
    QLineEdit *lanIPLineEdit;
    QPortForwardTableWidget *lanPortsTableWidget;
    QToolButton *addPortButton;
    QLabel *label_20;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *lanDMZLineEdit;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout;
    QGroupBox *wifi2GroupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_11;
    QLineEdit *wifi2SSIDLineEdit;
    QLabel *label_22;
    QLineEdit *wifi2WPALineEdit;
    QGroupBox *wifi5GroupBox;
    QGridLayout *gridLayout_7;
    QLabel *label_12;
    QLineEdit *wifi5SSIDLineEdit;
    QLabel *label_14;
    QLineEdit *wifi5WPALineEdit;
    QCheckBox *needsPublicIPCheckBox;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *pppUserPassLineEdit;
    QLabel *label;
    QLabel *label_13;
    QLineEdit *pppUserNameLineEdit;
    QFancyComboBox *pppProfileComboBox;
    QLabel *label_3;
    QToolButton *pppUserPassCreateButton;
    QToolButton *pppUserNameCopyButton;
    QToolButton *pppUserPassCopyButton;
    QLabel *label_2;
    QFancyComboBox *staticIPComboBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QFancyComboBox *installerComboBox;
    QLabel *label_4;
    QLineEdit *clientNameLineEdit;
    QLabel *label_5;
    QLineEdit *clientAddressLineEdit;
    QLabel *label_6;
    QFancyComboBox *clientCityComboBox;
    QLabel *label_7;
    QLineEdit *clientPhonesLineEdit;
    QLabel *label_8;
    QLineEdit *clientEmailLineEdit;
    QLabel *label_9;
    QTextEdit *clientNotesTextEdit;
    QTextEdit *installNotesTextEdit;
    QLabel *label_21;
    QLabel *infoLabel;
    QCheckBox *ftthCheckBox;
    QLabel *label_25;
    QSpacerItem *verticalSpacer_2;
    QComboBox *ontSNComboBox;

    void setupUi(QDialog *DlgPPPUser)
    {
        if (DlgPPPUser->objectName().isEmpty())
            DlgPPPUser->setObjectName(QString::fromUtf8("DlgPPPUser"));
        DlgPPPUser->resize(1353, 734);
        gridLayout_4 = new QGridLayout(DlgPPPUser);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        voipGroupBox = new QGroupBox(DlgPPPUser);
        voipGroupBox->setObjectName(QString::fromUtf8("voipGroupBox"));
        voipGroupBox->setCheckable(true);
        gridLayout_5 = new QGridLayout(voipGroupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_16 = new QLabel(voipGroupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_16, 1, 0, 1, 1);

        voipServerLineEdit = new QLineEdit(voipGroupBox);
        voipServerLineEdit->setObjectName(QString::fromUtf8("voipServerLineEdit"));

        gridLayout_5->addWidget(voipServerLineEdit, 3, 1, 1, 1);

        voipPhoneNumber = new QLineEdit(voipGroupBox);
        voipPhoneNumber->setObjectName(QString::fromUtf8("voipPhoneNumber"));

        gridLayout_5->addWidget(voipPhoneNumber, 0, 1, 1, 1);

        voipUserPass = new QLineEdit(voipGroupBox);
        voipUserPass->setObjectName(QString::fromUtf8("voipUserPass"));

        gridLayout_5->addWidget(voipUserPass, 2, 1, 1, 1);

        label_15 = new QLabel(voipGroupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_15, 0, 0, 1, 1);

        label_17 = new QLabel(voipGroupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_17, 2, 0, 1, 1);

        label_24 = new QLabel(voipGroupBox);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_24, 3, 0, 1, 1);

        voipUserName = new QLineEdit(voipGroupBox);
        voipUserName->setObjectName(QString::fromUtf8("voipUserName"));

        gridLayout_5->addWidget(voipUserName, 1, 1, 1, 1);


        gridLayout_4->addWidget(voipGroupBox, 0, 9, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        copyInfoButton = new QPushButton(DlgPPPUser);
        copyInfoButton->setObjectName(QString::fromUtf8("copyInfoButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(copyInfoButton->sizePolicy().hasHeightForWidth());
        copyInfoButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(copyInfoButton);

        applyDataButton = new QPushButton(DlgPPPUser);
        applyDataButton->setObjectName(QString::fromUtf8("applyDataButton"));

        horizontalLayout->addWidget(applyDataButton);

        clientLogsButton = new QPushButton(DlgPPPUser);
        clientLogsButton->setObjectName(QString::fromUtf8("clientLogsButton"));

        horizontalLayout->addWidget(clientLogsButton);


        gridLayout_4->addLayout(horizontalLayout, 10, 0, 1, 13);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 0, 8, 2, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_4, 3, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 8, 0, 1, 13);

        lanGroupBox = new QGroupBox(DlgPPPUser);
        lanGroupBox->setObjectName(QString::fromUtf8("lanGroupBox"));
        lanGroupBox->setCheckable(true);
        gridLayout_6 = new QGridLayout(lanGroupBox);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        delPortButton = new QToolButton(lanGroupBox);
        delPortButton->setObjectName(QString::fromUtf8("delPortButton"));

        gridLayout_6->addWidget(delPortButton, 1, 5, 1, 1);

        lanIPLineEdit = new QLineEdit(lanGroupBox);
        lanIPLineEdit->setObjectName(QString::fromUtf8("lanIPLineEdit"));

        gridLayout_6->addWidget(lanIPLineEdit, 0, 1, 1, 1);

        lanPortsTableWidget = new QPortForwardTableWidget(lanGroupBox);
        lanPortsTableWidget->setObjectName(QString::fromUtf8("lanPortsTableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lanPortsTableWidget->sizePolicy().hasHeightForWidth());
        lanPortsTableWidget->setSizePolicy(sizePolicy1);

        gridLayout_6->addWidget(lanPortsTableWidget, 2, 0, 1, 6);

        addPortButton = new QToolButton(lanGroupBox);
        addPortButton->setObjectName(QString::fromUtf8("addPortButton"));

        gridLayout_6->addWidget(addPortButton, 1, 4, 1, 1);

        label_20 = new QLabel(lanGroupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_20, 0, 2, 1, 1);

        label_18 = new QLabel(lanGroupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_18, 0, 0, 1, 1);

        label_19 = new QLabel(lanGroupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy2);
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout_6->addWidget(label_19, 1, 0, 1, 4);

        lanDMZLineEdit = new QLineEdit(lanGroupBox);
        lanDMZLineEdit->setObjectName(QString::fromUtf8("lanDMZLineEdit"));

        gridLayout_6->addWidget(lanDMZLineEdit, 0, 3, 1, 1);


        gridLayout_4->addWidget(lanGroupBox, 4, 8, 2, 5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 7, 2, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_3, 2, 9, 2, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        wifi2GroupBox = new QGroupBox(DlgPPPUser);
        wifi2GroupBox->setObjectName(QString::fromUtf8("wifi2GroupBox"));
        wifi2GroupBox->setCheckable(true);
        gridLayout_3 = new QGridLayout(wifi2GroupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_11 = new QLabel(wifi2GroupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy3);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_11, 0, 0, 1, 1);

        wifi2SSIDLineEdit = new QLineEdit(wifi2GroupBox);
        wifi2SSIDLineEdit->setObjectName(QString::fromUtf8("wifi2SSIDLineEdit"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(wifi2SSIDLineEdit->sizePolicy().hasHeightForWidth());
        wifi2SSIDLineEdit->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(wifi2SSIDLineEdit, 0, 1, 1, 1);

        label_22 = new QLabel(wifi2GroupBox);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy3.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(label_22, 1, 0, 1, 1);

        wifi2WPALineEdit = new QLineEdit(wifi2GroupBox);
        wifi2WPALineEdit->setObjectName(QString::fromUtf8("wifi2WPALineEdit"));
        sizePolicy4.setHeightForWidth(wifi2WPALineEdit->sizePolicy().hasHeightForWidth());
        wifi2WPALineEdit->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(wifi2WPALineEdit, 1, 1, 1, 1);


        verticalLayout->addWidget(wifi2GroupBox);

        wifi5GroupBox = new QGroupBox(DlgPPPUser);
        wifi5GroupBox->setObjectName(QString::fromUtf8("wifi5GroupBox"));
        wifi5GroupBox->setCheckable(true);
        gridLayout_7 = new QGridLayout(wifi5GroupBox);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_12 = new QLabel(wifi5GroupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy3.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy3);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_12, 1, 0, 1, 1);

        wifi5SSIDLineEdit = new QLineEdit(wifi5GroupBox);
        wifi5SSIDLineEdit->setObjectName(QString::fromUtf8("wifi5SSIDLineEdit"));
        sizePolicy4.setHeightForWidth(wifi5SSIDLineEdit->sizePolicy().hasHeightForWidth());
        wifi5SSIDLineEdit->setSizePolicy(sizePolicy4);

        gridLayout_7->addWidget(wifi5SSIDLineEdit, 1, 1, 1, 1);

        label_14 = new QLabel(wifi5GroupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy3.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy3);

        gridLayout_7->addWidget(label_14, 2, 0, 1, 1);

        wifi5WPALineEdit = new QLineEdit(wifi5GroupBox);
        wifi5WPALineEdit->setObjectName(QString::fromUtf8("wifi5WPALineEdit"));
        sizePolicy4.setHeightForWidth(wifi5WPALineEdit->sizePolicy().hasHeightForWidth());
        wifi5WPALineEdit->setSizePolicy(sizePolicy4);

        gridLayout_7->addWidget(wifi5WPALineEdit, 2, 1, 1, 1);


        verticalLayout->addWidget(wifi5GroupBox);


        gridLayout_4->addLayout(verticalLayout, 0, 11, 4, 2);

        needsPublicIPCheckBox = new QCheckBox(DlgPPPUser);
        needsPublicIPCheckBox->setObjectName(QString::fromUtf8("needsPublicIPCheckBox"));
        sizePolicy.setHeightForWidth(needsPublicIPCheckBox->sizePolicy().hasHeightForWidth());
        needsPublicIPCheckBox->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(needsPublicIPCheckBox, 1, 10, 1, 1);

        groupBox = new QGroupBox(DlgPPPUser);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pppUserPassLineEdit = new QLineEdit(groupBox);
        pppUserPassLineEdit->setObjectName(QString::fromUtf8("pppUserPassLineEdit"));
        pppUserPassLineEdit->setMaxLength(20);

        gridLayout->addWidget(pppUserPassLineEdit, 1, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_13, 3, 0, 1, 1);

        pppUserNameLineEdit = new QLineEdit(groupBox);
        pppUserNameLineEdit->setObjectName(QString::fromUtf8("pppUserNameLineEdit"));

        gridLayout->addWidget(pppUserNameLineEdit, 0, 1, 1, 2);

        pppProfileComboBox = new QFancyComboBox(groupBox);
        pppProfileComboBox->setObjectName(QString::fromUtf8("pppProfileComboBox"));

        gridLayout->addWidget(pppProfileComboBox, 2, 1, 1, 3);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pppUserPassCreateButton = new QToolButton(groupBox);
        pppUserPassCreateButton->setObjectName(QString::fromUtf8("pppUserPassCreateButton"));

        gridLayout->addWidget(pppUserPassCreateButton, 1, 2, 1, 1);

        pppUserNameCopyButton = new QToolButton(groupBox);
        pppUserNameCopyButton->setObjectName(QString::fromUtf8("pppUserNameCopyButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/iconos/Copy-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pppUserNameCopyButton->setIcon(icon);

        gridLayout->addWidget(pppUserNameCopyButton, 0, 3, 1, 1);

        pppUserPassCopyButton = new QToolButton(groupBox);
        pppUserPassCopyButton->setObjectName(QString::fromUtf8("pppUserPassCopyButton"));
        pppUserPassCopyButton->setIcon(icon);

        gridLayout->addWidget(pppUserPassCopyButton, 1, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        staticIPComboBox = new QFancyComboBox(groupBox);
        staticIPComboBox->setObjectName(QString::fromUtf8("staticIPComboBox"));

        gridLayout->addWidget(staticIPComboBox, 3, 1, 1, 3);


        gridLayout_4->addWidget(groupBox, 0, 0, 3, 7);

        groupBox_2 = new QGroupBox(DlgPPPUser);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);

        installerComboBox = new QFancyComboBox(groupBox_2);
        installerComboBox->setObjectName(QString::fromUtf8("installerComboBox"));
        installerComboBox->setEditable(true);

        gridLayout_2->addWidget(installerComboBox, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        clientNameLineEdit = new QLineEdit(groupBox_2);
        clientNameLineEdit->setObjectName(QString::fromUtf8("clientNameLineEdit"));
        sizePolicy4.setHeightForWidth(clientNameLineEdit->sizePolicy().hasHeightForWidth());
        clientNameLineEdit->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(clientNameLineEdit, 1, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        clientAddressLineEdit = new QLineEdit(groupBox_2);
        clientAddressLineEdit->setObjectName(QString::fromUtf8("clientAddressLineEdit"));
        sizePolicy4.setHeightForWidth(clientAddressLineEdit->sizePolicy().hasHeightForWidth());
        clientAddressLineEdit->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(clientAddressLineEdit, 2, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        clientCityComboBox = new QFancyComboBox(groupBox_2);
        clientCityComboBox->setObjectName(QString::fromUtf8("clientCityComboBox"));
        clientCityComboBox->setEditable(true);

        gridLayout_2->addWidget(clientCityComboBox, 3, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_7, 4, 0, 1, 1);

        clientPhonesLineEdit = new QLineEdit(groupBox_2);
        clientPhonesLineEdit->setObjectName(QString::fromUtf8("clientPhonesLineEdit"));
        sizePolicy4.setHeightForWidth(clientPhonesLineEdit->sizePolicy().hasHeightForWidth());
        clientPhonesLineEdit->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(clientPhonesLineEdit, 4, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_8, 5, 0, 1, 1);

        clientEmailLineEdit = new QLineEdit(groupBox_2);
        clientEmailLineEdit->setObjectName(QString::fromUtf8("clientEmailLineEdit"));
        sizePolicy4.setHeightForWidth(clientEmailLineEdit->sizePolicy().hasHeightForWidth());
        clientEmailLineEdit->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(clientEmailLineEdit, 5, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout_2->addWidget(label_9, 6, 0, 1, 1);

        clientNotesTextEdit = new QTextEdit(groupBox_2);
        clientNotesTextEdit->setObjectName(QString::fromUtf8("clientNotesTextEdit"));

        gridLayout_2->addWidget(clientNotesTextEdit, 6, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 5, 0, 1, 8);

        installNotesTextEdit = new QTextEdit(DlgPPPUser);
        installNotesTextEdit->setObjectName(QString::fromUtf8("installNotesTextEdit"));

        gridLayout_4->addWidget(installNotesTextEdit, 7, 8, 1, 5);

        label_21 = new QLabel(DlgPPPUser);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy3.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy3);
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_21, 4, 2, 1, 1);

        infoLabel = new QLabel(DlgPPPUser);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        sizePolicy4.setHeightForWidth(infoLabel->sizePolicy().hasHeightForWidth());
        infoLabel->setSizePolicy(sizePolicy4);
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        infoLabel->setPalette(palette);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        infoLabel->setFont(font);

        gridLayout_4->addWidget(infoLabel, 9, 0, 1, 13);

        ftthCheckBox = new QCheckBox(DlgPPPUser);
        ftthCheckBox->setObjectName(QString::fromUtf8("ftthCheckBox"));
        ftthCheckBox->setEnabled(false);
        sizePolicy.setHeightForWidth(ftthCheckBox->sizePolicy().hasHeightForWidth());
        ftthCheckBox->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(ftthCheckBox, 4, 0, 1, 2);

        label_25 = new QLabel(DlgPPPUser);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_4->addWidget(label_25, 6, 8, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 7, 0, 1, 8);

        ontSNComboBox = new QComboBox(DlgPPPUser);
        ontSNComboBox->setObjectName(QString::fromUtf8("ontSNComboBox"));

        gridLayout_4->addWidget(ontSNComboBox, 4, 3, 1, 5);

        QWidget::setTabOrder(pppUserNameLineEdit, pppUserNameCopyButton);
        QWidget::setTabOrder(pppUserNameCopyButton, pppUserPassLineEdit);
        QWidget::setTabOrder(pppUserPassLineEdit, pppUserPassCreateButton);
        QWidget::setTabOrder(pppUserPassCreateButton, pppUserPassCopyButton);
        QWidget::setTabOrder(pppUserPassCopyButton, pppProfileComboBox);
        QWidget::setTabOrder(pppProfileComboBox, staticIPComboBox);
        QWidget::setTabOrder(staticIPComboBox, ftthCheckBox);
        QWidget::setTabOrder(ftthCheckBox, ontSNComboBox);
        QWidget::setTabOrder(ontSNComboBox, installerComboBox);
        QWidget::setTabOrder(installerComboBox, clientNameLineEdit);
        QWidget::setTabOrder(clientNameLineEdit, clientAddressLineEdit);
        QWidget::setTabOrder(clientAddressLineEdit, clientCityComboBox);
        QWidget::setTabOrder(clientCityComboBox, clientPhonesLineEdit);
        QWidget::setTabOrder(clientPhonesLineEdit, clientEmailLineEdit);
        QWidget::setTabOrder(clientEmailLineEdit, voipGroupBox);
        QWidget::setTabOrder(voipGroupBox, voipPhoneNumber);
        QWidget::setTabOrder(voipPhoneNumber, voipUserName);
        QWidget::setTabOrder(voipUserName, voipUserPass);
        QWidget::setTabOrder(voipUserPass, wifi2GroupBox);
        QWidget::setTabOrder(wifi2GroupBox, wifi2SSIDLineEdit);
        QWidget::setTabOrder(wifi2SSIDLineEdit, wifi2WPALineEdit);
        QWidget::setTabOrder(wifi2WPALineEdit, lanGroupBox);
        QWidget::setTabOrder(lanGroupBox, lanIPLineEdit);
        QWidget::setTabOrder(lanIPLineEdit, lanDMZLineEdit);
        QWidget::setTabOrder(lanDMZLineEdit, addPortButton);
        QWidget::setTabOrder(addPortButton, delPortButton);
        QWidget::setTabOrder(delPortButton, lanPortsTableWidget);
        QWidget::setTabOrder(lanPortsTableWidget, copyInfoButton);
        QWidget::setTabOrder(copyInfoButton, applyDataButton);
        QWidget::setTabOrder(applyDataButton, clientLogsButton);

        retranslateUi(DlgPPPUser);

        clientCityComboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(DlgPPPUser);
    } // setupUi

    void retranslateUi(QDialog *DlgPPPUser)
    {
        DlgPPPUser->setWindowTitle(QApplication::translate("DlgPPPUser", "Dialog", nullptr));
        voipGroupBox->setTitle(QApplication::translate("DlgPPPUser", "VozIP", nullptr));
        label_16->setText(QApplication::translate("DlgPPPUser", "Usuario", nullptr));
        label_15->setText(QApplication::translate("DlgPPPUser", "Tel\303\251fono", nullptr));
        label_17->setText(QApplication::translate("DlgPPPUser", "Contrase\303\261a", nullptr));
        label_24->setText(QApplication::translate("DlgPPPUser", "Servidor", nullptr));
        copyInfoButton->setText(QApplication::translate("DlgPPPUser", "Copiar datos", nullptr));
        applyDataButton->setText(QApplication::translate("DlgPPPUser", "Crear usuario", nullptr));
        clientLogsButton->setText(QApplication::translate("DlgPPPUser", "Registros", nullptr));
        lanGroupBox->setTitle(QApplication::translate("DlgPPPUser", "Red Local", nullptr));
        delPortButton->setText(QApplication::translate("DlgPPPUser", " - ", nullptr));
        addPortButton->setText(QApplication::translate("DlgPPPUser", "+", nullptr));
        label_20->setText(QApplication::translate("DlgPPPUser", "DMZ", nullptr));
        label_18->setText(QApplication::translate("DlgPPPUser", "IP", nullptr));
        label_19->setText(QApplication::translate("DlgPPPUser", "Puertos", nullptr));
        wifi2GroupBox->setTitle(QApplication::translate("DlgPPPUser", "WiFi router / punto de acceso cliente bgn (2,4 Ghz)", nullptr));
        label_11->setText(QApplication::translate("DlgPPPUser", "SSID", nullptr));
        label_22->setText(QApplication::translate("DlgPPPUser", "WPA", nullptr));
        wifi5GroupBox->setTitle(QApplication::translate("DlgPPPUser", "WiFi router / punto de acceso cliente ac (5 Ghz)", nullptr));
        label_12->setText(QApplication::translate("DlgPPPUser", "SSID", nullptr));
        label_14->setText(QApplication::translate("DlgPPPUser", "WPA", nullptr));
        needsPublicIPCheckBox->setText(QApplication::translate("DlgPPPUser", "Requiere IP p\303\272blica", nullptr));
        groupBox->setTitle(QApplication::translate("DlgPPPUser", "Identificaci\303\263n sistema", nullptr));
        label->setText(QApplication::translate("DlgPPPUser", "Usuario", nullptr));
        label_13->setText(QApplication::translate("DlgPPPUser", "IP Est\303\241tica", nullptr));
        label_3->setText(QApplication::translate("DlgPPPUser", "Perfil", nullptr));
        pppUserPassCreateButton->setText(QApplication::translate("DlgPPPUser", "crear", nullptr));
        pppUserNameCopyButton->setText(QApplication::translate("DlgPPPUser", "...", nullptr));
        pppUserPassCopyButton->setText(QApplication::translate("DlgPPPUser", "...", nullptr));
        label_2->setText(QApplication::translate("DlgPPPUser", "Contrase\303\261a", nullptr));
        groupBox_2->setTitle(QApplication::translate("DlgPPPUser", "Identificaci\303\263n del cliente", nullptr));
        label_10->setText(QApplication::translate("DlgPPPUser", "Instalador", nullptr));
        label_4->setText(QApplication::translate("DlgPPPUser", "Nombre", nullptr));
        label_5->setText(QApplication::translate("DlgPPPUser", "Direcci\303\263n", nullptr));
        label_6->setText(QApplication::translate("DlgPPPUser", "Poblaci\303\263n", nullptr));
        label_7->setText(QApplication::translate("DlgPPPUser", "Tel\303\251fonos", nullptr));
        label_8->setText(QApplication::translate("DlgPPPUser", "Email", nullptr));
        label_9->setText(QApplication::translate("DlgPPPUser", "Notas cliente", nullptr));
        label_21->setText(QApplication::translate("DlgPPPUser", "S/N ONT", nullptr));
        infoLabel->setText(QString());
        ftthCheckBox->setText(QApplication::translate("DlgPPPUser", "FTTH", nullptr));
        label_25->setText(QApplication::translate("DlgPPPUser", "Notas Instalaci\303\263n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgPPPUser: public Ui_DlgPPPUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGPPPUSER_H
