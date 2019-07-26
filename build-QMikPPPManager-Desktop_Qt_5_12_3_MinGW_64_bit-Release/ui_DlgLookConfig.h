/********************************************************************************
** Form generated from reading UI file 'DlgLookConfig.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGLOOKCONFIG_H
#define UI_DLGLOOKCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgLookConfig
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpinBox *textSizeSpinBox;
    QLabel *label_3;
    QSpinBox *rowHeightSpinBox;
    QLabel *label_2;
    QPushButton *acceptButton;
    QPushButton *cancelButton;
    QTableWidget *coloursTable;
    QGroupBox *styleGroupBox;
    QGridLayout *gridLayout_2;
    QPushButton *textFontButton;
    QPushButton *textColorButton;
    QPushButton *backColorButton;
    QSpinBox *textRedSpinBox;
    QSpinBox *backRedSpinBox;
    QSpinBox *textGreenSpinBox;
    QSpinBox *backGreenSpinBox;
    QSpinBox *textBlueSpinBox;
    QSpinBox *backBlueSpinBox;
    QCheckBox *boldCheckBox;
    QCheckBox *italicCheckBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *DlgLookConfig)
    {
        if (DlgLookConfig->objectName().isEmpty())
            DlgLookConfig->setObjectName(QString::fromUtf8("DlgLookConfig"));
        DlgLookConfig->resize(831, 408);
        gridLayout_3 = new QGridLayout(DlgLookConfig);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(DlgLookConfig);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textSizeSpinBox = new QSpinBox(groupBox);
        textSizeSpinBox->setObjectName(QString::fromUtf8("textSizeSpinBox"));
        textSizeSpinBox->setMinimum(3);

        gridLayout->addWidget(textSizeSpinBox, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        rowHeightSpinBox = new QSpinBox(groupBox);
        rowHeightSpinBox->setObjectName(QString::fromUtf8("rowHeightSpinBox"));
        rowHeightSpinBox->setMinimum(6);

        gridLayout->addWidget(rowHeightSpinBox, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 2);

        acceptButton = new QPushButton(DlgLookConfig);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        gridLayout_3->addWidget(acceptButton, 3, 0, 1, 1);

        cancelButton = new QPushButton(DlgLookConfig);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout_3->addWidget(cancelButton, 3, 1, 1, 1);

        coloursTable = new QTableWidget(DlgLookConfig);
        if (coloursTable->columnCount() < 2)
            coloursTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        coloursTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        coloursTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (coloursTable->rowCount() < 6)
            coloursTable->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        coloursTable->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        coloursTable->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        coloursTable->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        coloursTable->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        coloursTable->setVerticalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        coloursTable->setVerticalHeaderItem(5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        coloursTable->setItem(0, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        coloursTable->setItem(0, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        coloursTable->setItem(1, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        coloursTable->setItem(1, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        coloursTable->setItem(2, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        coloursTable->setItem(2, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        coloursTable->setItem(3, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        coloursTable->setItem(3, 1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        coloursTable->setItem(4, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        coloursTable->setItem(4, 1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        coloursTable->setItem(5, 0, __qtablewidgetitem18);
        coloursTable->setObjectName(QString::fromUtf8("coloursTable"));
        coloursTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        coloursTable->setShowGrid(true);

        gridLayout_3->addWidget(coloursTable, 0, 2, 4, 1);

        styleGroupBox = new QGroupBox(DlgLookConfig);
        styleGroupBox->setObjectName(QString::fromUtf8("styleGroupBox"));
        styleGroupBox->setEnabled(false);
        gridLayout_2 = new QGridLayout(styleGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        textFontButton = new QPushButton(styleGroupBox);
        textFontButton->setObjectName(QString::fromUtf8("textFontButton"));

        gridLayout_2->addWidget(textFontButton, 0, 0, 1, 1);

        textColorButton = new QPushButton(styleGroupBox);
        textColorButton->setObjectName(QString::fromUtf8("textColorButton"));

        gridLayout_2->addWidget(textColorButton, 1, 0, 1, 1);

        backColorButton = new QPushButton(styleGroupBox);
        backColorButton->setObjectName(QString::fromUtf8("backColorButton"));

        gridLayout_2->addWidget(backColorButton, 1, 1, 1, 1);

        textRedSpinBox = new QSpinBox(styleGroupBox);
        textRedSpinBox->setObjectName(QString::fromUtf8("textRedSpinBox"));
        textRedSpinBox->setMaximum(255);

        gridLayout_2->addWidget(textRedSpinBox, 2, 0, 1, 1);

        backRedSpinBox = new QSpinBox(styleGroupBox);
        backRedSpinBox->setObjectName(QString::fromUtf8("backRedSpinBox"));
        backRedSpinBox->setMaximum(255);

        gridLayout_2->addWidget(backRedSpinBox, 2, 1, 1, 1);

        textGreenSpinBox = new QSpinBox(styleGroupBox);
        textGreenSpinBox->setObjectName(QString::fromUtf8("textGreenSpinBox"));
        textGreenSpinBox->setMaximum(255);

        gridLayout_2->addWidget(textGreenSpinBox, 3, 0, 1, 1);

        backGreenSpinBox = new QSpinBox(styleGroupBox);
        backGreenSpinBox->setObjectName(QString::fromUtf8("backGreenSpinBox"));
        backGreenSpinBox->setMaximum(255);

        gridLayout_2->addWidget(backGreenSpinBox, 3, 1, 1, 1);

        textBlueSpinBox = new QSpinBox(styleGroupBox);
        textBlueSpinBox->setObjectName(QString::fromUtf8("textBlueSpinBox"));
        textBlueSpinBox->setMaximum(255);

        gridLayout_2->addWidget(textBlueSpinBox, 4, 0, 1, 1);

        backBlueSpinBox = new QSpinBox(styleGroupBox);
        backBlueSpinBox->setObjectName(QString::fromUtf8("backBlueSpinBox"));
        backBlueSpinBox->setMaximum(255);

        gridLayout_2->addWidget(backBlueSpinBox, 4, 1, 1, 1);

        boldCheckBox = new QCheckBox(styleGroupBox);
        boldCheckBox->setObjectName(QString::fromUtf8("boldCheckBox"));

        gridLayout_2->addWidget(boldCheckBox, 5, 0, 1, 1);

        italicCheckBox = new QCheckBox(styleGroupBox);
        italicCheckBox->setObjectName(QString::fromUtf8("italicCheckBox"));

        gridLayout_2->addWidget(italicCheckBox, 5, 1, 1, 1);


        gridLayout_3->addWidget(styleGroupBox, 1, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 2);


        retranslateUi(DlgLookConfig);

        QMetaObject::connectSlotsByName(DlgLookConfig);
    } // setupUi

    void retranslateUi(QDialog *DlgLookConfig)
    {
        DlgLookConfig->setWindowTitle(QApplication::translate("DlgLookConfig", "Configuraci\303\263n Apariencia", nullptr));
        groupBox->setTitle(QApplication::translate("DlgLookConfig", "Apariencia", nullptr));
        label_3->setText(QApplication::translate("DlgLookConfig", "Altura filas", nullptr));
        label_2->setText(QApplication::translate("DlgLookConfig", "Tama\303\261o texto", nullptr));
        acceptButton->setText(QApplication::translate("DlgLookConfig", "Aceptar", nullptr));
        cancelButton->setText(QApplication::translate("DlgLookConfig", "Cancelar", nullptr));
        QTableWidgetItem *___qtablewidgetitem = coloursTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DlgLookConfig", "Alta/Baja", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = coloursTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DlgLookConfig", "Estado", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = coloursTable->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("DlgLookConfig", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = coloursTable->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("DlgLookConfig", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = coloursTable->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("DlgLookConfig", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = coloursTable->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("DlgLookConfig", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = coloursTable->verticalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("DlgLookConfig", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = coloursTable->verticalHeaderItem(5);
        ___qtablewidgetitem7->setText(QApplication::translate("DlgLookConfig", "6", nullptr));

        const bool __sortingEnabled = coloursTable->isSortingEnabled();
        coloursTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem8 = coloursTable->item(0, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("DlgLookConfig", "Alta", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = coloursTable->item(0, 1);
        ___qtablewidgetitem9->setText(QApplication::translate("DlgLookConfig", "Conectado", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = coloursTable->item(1, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("DlgLookConfig", "Baja temporal", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = coloursTable->item(1, 1);
        ___qtablewidgetitem11->setText(QApplication::translate("DlgLookConfig", "Desconectado", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = coloursTable->item(2, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("DlgLookConfig", "Baja administrativa", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = coloursTable->item(3, 0);
        ___qtablewidgetitem13->setText(QApplication::translate("DlgLookConfig", "Baja t\303\251cnica", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = coloursTable->item(4, 0);
        ___qtablewidgetitem14->setText(QApplication::translate("DlgLookConfig", "Baja indefinida", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = coloursTable->item(5, 0);
        ___qtablewidgetitem15->setText(QApplication::translate("DlgLookConfig", "Baja definitiva, antena retirada", nullptr));
        coloursTable->setSortingEnabled(__sortingEnabled);

        styleGroupBox->setTitle(QApplication::translate("DlgLookConfig", "Estilos", nullptr));
        textFontButton->setText(QApplication::translate("DlgLookConfig", "Fuente texto", nullptr));
        textColorButton->setText(QApplication::translate("DlgLookConfig", "Color Texto", nullptr));
        backColorButton->setText(QApplication::translate("DlgLookConfig", "Color fondo", nullptr));
        textRedSpinBox->setPrefix(QApplication::translate("DlgLookConfig", "Rojo ", nullptr));
        backRedSpinBox->setPrefix(QApplication::translate("DlgLookConfig", "Rojo ", nullptr));
        textGreenSpinBox->setPrefix(QApplication::translate("DlgLookConfig", "Verde ", nullptr));
        backGreenSpinBox->setPrefix(QApplication::translate("DlgLookConfig", "Verde ", nullptr));
        textBlueSpinBox->setPrefix(QApplication::translate("DlgLookConfig", "Azul ", nullptr));
        backBlueSpinBox->setPrefix(QApplication::translate("DlgLookConfig", "Azul ", nullptr));
        boldCheckBox->setText(QApplication::translate("DlgLookConfig", "Negrita", nullptr));
        italicCheckBox->setText(QApplication::translate("DlgLookConfig", "Cursiva", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgLookConfig: public Ui_DlgLookConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGLOOKCONFIG_H
