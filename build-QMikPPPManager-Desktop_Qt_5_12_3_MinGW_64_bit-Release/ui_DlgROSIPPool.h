/********************************************************************************
** Form generated from reading UI file 'DlgROSIPPool.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGROSIPPOOL_H
#define UI_DLGROSIPPOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgROSIPPool
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *closeButton;
    QToolButton *addButton;
    QToolButton *delButton;
    QTreeWidget *poolTree;

    void setupUi(QDialog *DlgROSIPPool)
    {
        if (DlgROSIPPool->objectName().isEmpty())
            DlgROSIPPool->setObjectName(QString::fromUtf8("DlgROSIPPool"));
        DlgROSIPPool->resize(400, 300);
        gridLayout = new QGridLayout(DlgROSIPPool);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        closeButton = new QPushButton(DlgROSIPPool);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(closeButton, 2, 0, 1, 1);

        addButton = new QToolButton(DlgROSIPPool);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout->addWidget(addButton, 0, 1, 1, 1);

        delButton = new QToolButton(DlgROSIPPool);
        delButton->setObjectName(QString::fromUtf8("delButton"));

        gridLayout->addWidget(delButton, 0, 2, 1, 1);

        poolTree = new QTreeWidget(DlgROSIPPool);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        poolTree->setHeaderItem(__qtreewidgetitem);
        poolTree->setObjectName(QString::fromUtf8("poolTree"));

        gridLayout->addWidget(poolTree, 1, 0, 1, 3);


        retranslateUi(DlgROSIPPool);

        QMetaObject::connectSlotsByName(DlgROSIPPool);
    } // setupUi

    void retranslateUi(QDialog *DlgROSIPPool)
    {
        DlgROSIPPool->setWindowTitle(QApplication::translate("DlgROSIPPool", "Dialog", nullptr));
        closeButton->setText(QApplication::translate("DlgROSIPPool", "Cerrar", nullptr));
        addButton->setText(QApplication::translate("DlgROSIPPool", "+", nullptr));
        delButton->setText(QApplication::translate("DlgROSIPPool", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgROSIPPool: public Ui_DlgROSIPPool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGROSIPPOOL_H
