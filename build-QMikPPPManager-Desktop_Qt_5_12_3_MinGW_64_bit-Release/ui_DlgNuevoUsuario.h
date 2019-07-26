/********************************************************************************
** Form generated from reading UI file 'DlgNuevoUsuario.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGNUEVOUSUARIO_H
#define UI_DLGNUEVOUSUARIO_H

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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include "Widgets/QIPv4RangeComboBox.h"

QT_BEGIN_NAMESPACE

class Ui_DlgNuevoUsuario
{
public:
    QGridLayout *gridLayout_4;
    QLabel *lbText;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QLabel *label_15;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_16;
    QLabel *label_17;
    QComboBox *comboBox;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QComboBox *cbPerfil;
    QLabel *label_13;
    QLineEdit *lePass;
    QLabel *label;
    QToolButton *btPass;
    QLabel *label_3;
    QLineEdit *leUser;
    QIPv4RangeComboBox *cbIPPublica;
    QToolButton *btPassCopy;
    QLabel *label_2;
    QToolButton *btUserCopy;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLineEdit *leDireccion;
    QLabel *label_9;
    QLineEdit *leEmail;
    QLineEdit *leTelefonos;
    QLineEdit *leNotas;
    QLabel *label_6;
    QLabel *label_10;
    QComboBox *cbInstalador;
    QLabel *label_4;
    QComboBox *cbComercial;
    QComboBox *cbPoblacion;
    QLabel *label_14;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_5;
    QLineEdit *leNombre;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_6;
    QLabel *label_20;
    QLabel *label_18;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QTableWidget *tableWidget;
    QLabel *label_19;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *grWiFi;
    QGridLayout *gridLayout_3;
    QLineEdit *leSSID;
    QLineEdit *leWPass;
    QLabel *label_12;
    QLabel *label_11;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btCopyContactInfo;
    QPushButton *btCrear;
    QPushButton *btCerrar;
    QCheckBox *checkBox;
    QLabel *label_21;
    QCheckBox *checkBox_2;

    void setupUi(QDialog *DlgNuevoUsuario)
    {
        if (DlgNuevoUsuario->objectName().isEmpty())
            DlgNuevoUsuario->setObjectName(QString::fromUtf8("DlgNuevoUsuario"));
        DlgNuevoUsuario->resize(1222, 538);
        gridLayout_4 = new QGridLayout(DlgNuevoUsuario);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lbText = new QLabel(DlgNuevoUsuario);
        lbText->setObjectName(QString::fromUtf8("lbText"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbText->sizePolicy().hasHeightForWidth());
        lbText->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lbText->setPalette(palette);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lbText->setFont(font);

        gridLayout_4->addWidget(lbText, 7, 0, 1, 7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 1, 0, 5, 3);

        groupBox_3 = new QGroupBox(DlgNuevoUsuario);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setCheckable(true);
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_15, 0, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_5->addWidget(lineEdit, 0, 1, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox_3);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout_5->addWidget(lineEdit_2, 1, 1, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox_3);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout_5->addWidget(lineEdit_3, 2, 1, 1, 1);

        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_16, 1, 0, 1, 1);

        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_17, 2, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 3, 3, 2, 2);

        comboBox = new QComboBox(DlgNuevoUsuario);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_4->addWidget(comboBox, 2, 5, 1, 2);

        groupBox = new QGroupBox(DlgNuevoUsuario);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cbPerfil = new QComboBox(groupBox);
        cbPerfil->setObjectName(QString::fromUtf8("cbPerfil"));

        gridLayout->addWidget(cbPerfil, 2, 1, 1, 3);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_13, 3, 0, 1, 1);

        lePass = new QLineEdit(groupBox);
        lePass->setObjectName(QString::fromUtf8("lePass"));
        lePass->setMaxLength(20);

        gridLayout->addWidget(lePass, 1, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        btPass = new QToolButton(groupBox);
        btPass->setObjectName(QString::fromUtf8("btPass"));

        gridLayout->addWidget(btPass, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        leUser = new QLineEdit(groupBox);
        leUser->setObjectName(QString::fromUtf8("leUser"));

        gridLayout->addWidget(leUser, 0, 1, 1, 2);

        cbIPPublica = new QIPv4RangeComboBox(groupBox);
        cbIPPublica->setObjectName(QString::fromUtf8("cbIPPublica"));

        gridLayout->addWidget(cbIPPublica, 3, 1, 1, 3);

        btPassCopy = new QToolButton(groupBox);
        btPassCopy->setObjectName(QString::fromUtf8("btPassCopy"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/iconos/Copy-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        btPassCopy->setIcon(icon);

        gridLayout->addWidget(btPassCopy, 1, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        btUserCopy = new QToolButton(groupBox);
        btUserCopy->setObjectName(QString::fromUtf8("btUserCopy"));
        btUserCopy->setIcon(icon);

        gridLayout->addWidget(btUserCopy, 0, 3, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 3);

        groupBox_2 = new QGroupBox(DlgNuevoUsuario);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        leDireccion = new QLineEdit(groupBox_2);
        leDireccion->setObjectName(QString::fromUtf8("leDireccion"));

        gridLayout_2->addWidget(leDireccion, 2, 1, 1, 4);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_9, 9, 0, 1, 1);

        leEmail = new QLineEdit(groupBox_2);
        leEmail->setObjectName(QString::fromUtf8("leEmail"));

        gridLayout_2->addWidget(leEmail, 4, 3, 1, 2);

        leTelefonos = new QLineEdit(groupBox_2);
        leTelefonos->setObjectName(QString::fromUtf8("leTelefonos"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leTelefonos->sizePolicy().hasHeightForWidth());
        leTelefonos->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(leTelefonos, 3, 3, 1, 2);

        leNotas = new QLineEdit(groupBox_2);
        leNotas->setObjectName(QString::fromUtf8("leNotas"));

        gridLayout_2->addWidget(leNotas, 9, 1, 1, 4);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);

        cbInstalador = new QComboBox(groupBox_2);
        cbInstalador->setObjectName(QString::fromUtf8("cbInstalador"));
        cbInstalador->setEditable(true);

        gridLayout_2->addWidget(cbInstalador, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        cbComercial = new QComboBox(groupBox_2);
        cbComercial->setObjectName(QString::fromUtf8("cbComercial"));
        cbComercial->setEditable(true);

        gridLayout_2->addWidget(cbComercial, 0, 3, 1, 2);

        cbPoblacion = new QComboBox(groupBox_2);
        cbPoblacion->setObjectName(QString::fromUtf8("cbPoblacion"));
        sizePolicy.setHeightForWidth(cbPoblacion->sizePolicy().hasHeightForWidth());
        cbPoblacion->setSizePolicy(sizePolicy);
        cbPoblacion->setEditable(true);

        gridLayout_2->addWidget(cbPoblacion, 3, 1, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_14, 0, 2, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_8, 4, 2, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy4);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_7, 3, 2, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        leNombre = new QLineEdit(groupBox_2);
        leNombre->setObjectName(QString::fromUtf8("leNombre"));

        gridLayout_2->addWidget(leNombre, 1, 1, 1, 4);


        gridLayout_4->addWidget(groupBox_2, 0, 3, 2, 4);

        groupBox_4 = new QGroupBox(DlgNuevoUsuario);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setEnabled(false);
        groupBox_4->setCheckable(true);
        gridLayout_6 = new QGridLayout(groupBox_4);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_20, 0, 2, 1, 1);

        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_18, 0, 0, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox_4);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout_6->addWidget(lineEdit_4, 0, 1, 1, 1);

        lineEdit_5 = new QLineEdit(groupBox_4);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        gridLayout_6->addWidget(lineEdit_5, 0, 3, 1, 1);

        tableWidget = new QTableWidget(groupBox_4);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout_6->addWidget(tableWidget, 2, 0, 1, 4);

        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout_6->addWidget(label_19, 1, 0, 1, 4);


        gridLayout_4->addWidget(groupBox_4, 3, 6, 3, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_4, 5, 5, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout_4->addItem(verticalSpacer_3, 6, 0, 1, 7);

        grWiFi = new QGroupBox(DlgNuevoUsuario);
        grWiFi->setObjectName(QString::fromUtf8("grWiFi"));
        sizePolicy1.setHeightForWidth(grWiFi->sizePolicy().hasHeightForWidth());
        grWiFi->setSizePolicy(sizePolicy1);
        grWiFi->setCheckable(true);
        gridLayout_3 = new QGridLayout(grWiFi);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        leSSID = new QLineEdit(grWiFi);
        leSSID->setObjectName(QString::fromUtf8("leSSID"));

        gridLayout_3->addWidget(leSSID, 0, 1, 1, 1);

        leWPass = new QLineEdit(grWiFi);
        leWPass->setObjectName(QString::fromUtf8("leWPass"));

        gridLayout_3->addWidget(leWPass, 1, 1, 1, 1);

        label_12 = new QLabel(grWiFi);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_12, 1, 0, 1, 1);

        label_11 = new QLabel(grWiFi);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_11, 0, 0, 1, 1);


        gridLayout_4->addWidget(grWiFi, 3, 5, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 5, 3, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btCopyContactInfo = new QPushButton(DlgNuevoUsuario);
        btCopyContactInfo->setObjectName(QString::fromUtf8("btCopyContactInfo"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(btCopyContactInfo->sizePolicy().hasHeightForWidth());
        btCopyContactInfo->setSizePolicy(sizePolicy5);

        horizontalLayout->addWidget(btCopyContactInfo);

        btCrear = new QPushButton(DlgNuevoUsuario);
        btCrear->setObjectName(QString::fromUtf8("btCrear"));

        horizontalLayout->addWidget(btCrear);

        btCerrar = new QPushButton(DlgNuevoUsuario);
        btCerrar->setObjectName(QString::fromUtf8("btCerrar"));

        horizontalLayout->addWidget(btCerrar);


        gridLayout_4->addLayout(horizontalLayout, 8, 0, 1, 7);

        checkBox = new QCheckBox(DlgNuevoUsuario);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout_4->addWidget(checkBox, 4, 5, 1, 1);

        label_21 = new QLabel(DlgNuevoUsuario);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_21, 2, 4, 1, 1);

        checkBox_2 = new QCheckBox(DlgNuevoUsuario);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setEnabled(false);

        gridLayout_4->addWidget(checkBox_2, 2, 3, 1, 1);

        QWidget::setTabOrder(leUser, btUserCopy);
        QWidget::setTabOrder(btUserCopy, lePass);
        QWidget::setTabOrder(lePass, btPass);
        QWidget::setTabOrder(btPass, btPassCopy);
        QWidget::setTabOrder(btPassCopy, cbPerfil);
        QWidget::setTabOrder(cbPerfil, cbIPPublica);
        QWidget::setTabOrder(cbIPPublica, cbInstalador);
        QWidget::setTabOrder(cbInstalador, leNombre);
        QWidget::setTabOrder(leNombre, leDireccion);
        QWidget::setTabOrder(leDireccion, cbPoblacion);
        QWidget::setTabOrder(cbPoblacion, leTelefonos);
        QWidget::setTabOrder(leTelefonos, leEmail);
        QWidget::setTabOrder(leEmail, leSSID);
        QWidget::setTabOrder(leSSID, leNotas);
        QWidget::setTabOrder(leNotas, btCrear);
        QWidget::setTabOrder(btCrear, btCerrar);

        retranslateUi(DlgNuevoUsuario);

        cbPoblacion->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(DlgNuevoUsuario);
    } // setupUi

    void retranslateUi(QDialog *DlgNuevoUsuario)
    {
        DlgNuevoUsuario->setWindowTitle(QApplication::translate("DlgNuevoUsuario", "Dialog", nullptr));
        lbText->setText(QApplication::translate("DlgNuevoUsuario", "Info Text", nullptr));
        groupBox_3->setTitle(QApplication::translate("DlgNuevoUsuario", "VozIP", nullptr));
        label_15->setText(QApplication::translate("DlgNuevoUsuario", "Tel\303\251fono", nullptr));
        label_16->setText(QApplication::translate("DlgNuevoUsuario", "Usuario", nullptr));
        label_17->setText(QApplication::translate("DlgNuevoUsuario", "Contrase\303\261a", nullptr));
        groupBox->setTitle(QApplication::translate("DlgNuevoUsuario", "Identificaci\303\263n sistema", nullptr));
        label_13->setText(QApplication::translate("DlgNuevoUsuario", "IP P\303\272blica", nullptr));
        label->setText(QApplication::translate("DlgNuevoUsuario", "Usuario", nullptr));
        btPass->setText(QApplication::translate("DlgNuevoUsuario", "crear", nullptr));
        label_3->setText(QApplication::translate("DlgNuevoUsuario", "Perfil", nullptr));
        btPassCopy->setText(QApplication::translate("DlgNuevoUsuario", "...", nullptr));
        label_2->setText(QApplication::translate("DlgNuevoUsuario", "Contrase\303\261a", nullptr));
        btUserCopy->setText(QApplication::translate("DlgNuevoUsuario", "...", nullptr));
        groupBox_2->setTitle(QApplication::translate("DlgNuevoUsuario", "Identificaci\303\263n del cliente", nullptr));
        label_9->setText(QApplication::translate("DlgNuevoUsuario", "Notas", nullptr));
        label_6->setText(QApplication::translate("DlgNuevoUsuario", "Poblaci\303\263n", nullptr));
        label_10->setText(QApplication::translate("DlgNuevoUsuario", "Instalador", nullptr));
        label_4->setText(QApplication::translate("DlgNuevoUsuario", "Nombre", nullptr));
        label_14->setText(QApplication::translate("DlgNuevoUsuario", "Vendedor", nullptr));
        label_8->setText(QApplication::translate("DlgNuevoUsuario", "Email", nullptr));
        label_7->setText(QApplication::translate("DlgNuevoUsuario", "Tel\303\251fonos", nullptr));
        label_5->setText(QApplication::translate("DlgNuevoUsuario", "Direcci\303\263n", nullptr));
        groupBox_4->setTitle(QApplication::translate("DlgNuevoUsuario", "Red Local", nullptr));
        label_20->setText(QApplication::translate("DlgNuevoUsuario", "DMZ", nullptr));
        label_18->setText(QApplication::translate("DlgNuevoUsuario", "IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DlgNuevoUsuario", "Protocolo", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DlgNuevoUsuario", "Puertos p\303\272blicos", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("DlgNuevoUsuario", "Puertos privados", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("DlgNuevoUsuario", "IP Local", nullptr));
        label_19->setText(QApplication::translate("DlgNuevoUsuario", "Puertos", nullptr));
        grWiFi->setTitle(QApplication::translate("DlgNuevoUsuario", "Usa WiFi", nullptr));
        label_12->setText(QApplication::translate("DlgNuevoUsuario", "Contrase\303\261a", nullptr));
        label_11->setText(QApplication::translate("DlgNuevoUsuario", "SSID", nullptr));
        btCopyContactInfo->setText(QApplication::translate("DlgNuevoUsuario", "Copiar datos", nullptr));
        btCrear->setText(QApplication::translate("DlgNuevoUsuario", "Crear usuario", nullptr));
        btCerrar->setText(QApplication::translate("DlgNuevoUsuario", "Cerrar", nullptr));
        checkBox->setText(QApplication::translate("DlgNuevoUsuario", "Requiere IP p\303\272blica", nullptr));
        label_21->setText(QApplication::translate("DlgNuevoUsuario", "S/N ONT", nullptr));
        checkBox_2->setText(QApplication::translate("DlgNuevoUsuario", "FTTH", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgNuevoUsuario: public Ui_DlgNuevoUsuario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGNUEVOUSUARIO_H
