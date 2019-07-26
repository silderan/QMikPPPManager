/********************************************************************************
** Form generated from reading UI file 'DlgConfiguracion.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGCONFIGURACION_H
#define UI_DLGCONFIGURACION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_DlgConfiguracion
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QTableWidget *listaInstaladores;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *delProfileButton;
    QTableWidget *profilesTable;
    QToolButton *addProfileButton;
    QGroupBox *grRangosIP;
    QGridLayout *gridLayout_2;
    QToolButton *delStaticRangeButton;
    QSpacerItem *horizontalSpacer_3;
    QTableWidget *staticIPv4Table;
    QToolButton *addStaticRangeButton;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btAceptar;
    QPushButton *btCancelar;

    void setupUi(QDialog *DlgConfiguracion)
    {
        if (DlgConfiguracion->objectName().isEmpty())
            DlgConfiguracion->setObjectName(QString::fromUtf8("DlgConfiguracion"));
        DlgConfiguracion->resize(1465, 683);
        gridLayout = new QGridLayout(DlgConfiguracion);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(DlgConfiguracion);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        listaInstaladores = new QTableWidget(groupBox);
        if (listaInstaladores->columnCount() < 2)
            listaInstaladores->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        listaInstaladores->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        listaInstaladores->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        listaInstaladores->setObjectName(QString::fromUtf8("listaInstaladores"));
        listaInstaladores->horizontalHeader()->setStretchLastSection(true);
        listaInstaladores->verticalHeader()->setMinimumSectionSize(15);
        listaInstaladores->verticalHeader()->setDefaultSectionSize(26);

        gridLayout_3->addWidget(listaInstaladores, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(DlgConfiguracion);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        delProfileButton = new QToolButton(groupBox_2);
        delProfileButton->setObjectName(QString::fromUtf8("delProfileButton"));

        gridLayout_4->addWidget(delProfileButton, 0, 2, 1, 1);

        profilesTable = new QTableWidget(groupBox_2);
        if (profilesTable->columnCount() < 2)
            profilesTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        profilesTable->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        profilesTable->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        profilesTable->setObjectName(QString::fromUtf8("profilesTable"));
        profilesTable->setWordWrap(false);
        profilesTable->setCornerButtonEnabled(false);
        profilesTable->horizontalHeader()->setDefaultSectionSize(200);
        profilesTable->horizontalHeader()->setStretchLastSection(true);
        profilesTable->verticalHeader()->setMinimumSectionSize(30);
        profilesTable->verticalHeader()->setDefaultSectionSize(30);

        gridLayout_4->addWidget(profilesTable, 1, 0, 1, 3);

        addProfileButton = new QToolButton(groupBox_2);
        addProfileButton->setObjectName(QString::fromUtf8("addProfileButton"));

        gridLayout_4->addWidget(addProfileButton, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);

        grRangosIP = new QGroupBox(DlgConfiguracion);
        grRangosIP->setObjectName(QString::fromUtf8("grRangosIP"));
        gridLayout_2 = new QGridLayout(grRangosIP);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        delStaticRangeButton = new QToolButton(grRangosIP);
        delStaticRangeButton->setObjectName(QString::fromUtf8("delStaticRangeButton"));

        gridLayout_2->addWidget(delStaticRangeButton, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        staticIPv4Table = new QTableWidget(grRangosIP);
        if (staticIPv4Table->columnCount() < 3)
            staticIPv4Table->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        staticIPv4Table->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        staticIPv4Table->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        staticIPv4Table->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        staticIPv4Table->setObjectName(QString::fromUtf8("staticIPv4Table"));

        gridLayout_2->addWidget(staticIPv4Table, 1, 0, 1, 3);

        addStaticRangeButton = new QToolButton(grRangosIP);
        addStaticRangeButton->setObjectName(QString::fromUtf8("addStaticRangeButton"));

        gridLayout_2->addWidget(addStaticRangeButton, 0, 1, 1, 1);


        gridLayout->addWidget(grRangosIP, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btAceptar = new QPushButton(DlgConfiguracion);
        btAceptar->setObjectName(QString::fromUtf8("btAceptar"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btAceptar->sizePolicy().hasHeightForWidth());
        btAceptar->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(btAceptar);

        btCancelar = new QPushButton(DlgConfiguracion);
        btCancelar->setObjectName(QString::fromUtf8("btCancelar"));
        sizePolicy.setHeightForWidth(btCancelar->sizePolicy().hasHeightForWidth());
        btCancelar->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(btCancelar);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 3);


        retranslateUi(DlgConfiguracion);

        btAceptar->setDefault(true);


        QMetaObject::connectSlotsByName(DlgConfiguracion);
    } // setupUi

    void retranslateUi(QDialog *DlgConfiguracion)
    {
        DlgConfiguracion->setWindowTitle(QApplication::translate("DlgConfiguracion", "Configuraci\303\263n", nullptr));
        groupBox->setTitle(QApplication::translate("DlgConfiguracion", "Empleados", nullptr));
        QTableWidgetItem *___qtablewidgetitem = listaInstaladores->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DlgConfiguracion", "Instaladores", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = listaInstaladores->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DlgConfiguracion", "Vendedores", nullptr));
        groupBox_2->setTitle(QApplication::translate("DlgConfiguracion", "Configuraci\303\263n perfiles", nullptr));
        delProfileButton->setText(QApplication::translate("DlgConfiguracion", " - ", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = profilesTable->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("DlgConfiguracion", "Nombre", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = profilesTable->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("DlgConfiguracion", "Grupo/Tipo", nullptr));
        addProfileButton->setText(QApplication::translate("DlgConfiguracion", "+", nullptr));
        grRangosIP->setTitle(QApplication::translate("DlgConfiguracion", "Rangos IPs est\303\241ticas", nullptr));
        delStaticRangeButton->setText(QApplication::translate("DlgConfiguracion", " - ", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = staticIPv4Table->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("DlgConfiguracion", "De", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = staticIPv4Table->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("DlgConfiguracion", "Hasta", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = staticIPv4Table->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("DlgConfiguracion", "Grupo perfiles", nullptr));
        addStaticRangeButton->setText(QApplication::translate("DlgConfiguracion", "+", nullptr));
        btAceptar->setText(QApplication::translate("DlgConfiguracion", "Aceptar", nullptr));
        btCancelar->setText(QApplication::translate("DlgConfiguracion", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgConfiguracion: public Ui_DlgConfiguracion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGCONFIGURACION_H
