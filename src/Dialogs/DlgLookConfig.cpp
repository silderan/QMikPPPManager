/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#include "DlgLookConfig.h"
#include "ui_DlgLookConfig.h"

#include <QFontDialog>
#include <QColorDialog>

#include <ConfigData/QConfigData.h>

DlgLookConfig::DlgLookConfig(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgLookConfig)
{
	ui->setupUi(this);

	ui->rowHeightSpinBox->setValue( gGlobalConfig.tableCellLook().m_rowHeight );
	ui->textSizeSpinBox->setValue( gGlobalConfig.tableCellLook().m_fontSize );

	updateTableCellLook();
	connect( ui->coloursTable, SIGNAL(itemSelectionChanged()), this, SLOT(onItemSelected()) );
	connect( ui->textSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateTableFontSize(int)) );
	connect( ui->rowHeightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateTableRowHeight(int)) );

	connect( ui->textRedSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCurrentCellLook(int)) );
	connect( ui->textGreenSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCurrentCellLook(int)) );
	connect( ui->textBlueSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCurrentCellLook(int)) );

	connect( ui->backRedSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCurrentCellLook(int)) );
	connect( ui->backGreenSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCurrentCellLook(int)) );
	connect( ui->backBlueSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCurrentCellLook(int)) );

	ui->coloursTable->resizeColumnsToContents();
	onItemSelected();
}

DlgLookConfig::~DlgLookConfig()
{
	delete ui;
}

void DlgLookConfig::updateCellLook(QTableWidgetItem *item, const CellLook &cellLook)
{
	QFont font = item->font();
	font.setItalic( cellLook.m_fontItalic );
	font.setBold( cellLook.m_fontBold );
	font.setFamily( cellLook.m_fontFamily );
	item->setFont( font );
	item->setForeground( QBrush(cellLook.m_foreColor) );
	item->setBackground( QBrush(cellLook.m_backColor) );
}

void DlgLookConfig::updateCellLook(int row, int col, const CellLook &cellLook)
{
	updateCellLook( ui->coloursTable->item(row, col), cellLook );
}

void DlgLookConfig::updateTableCellLook()
{
	updateTableRowHeight();
	updateTableRowHeight();

	updateCellLook( 0, 0, gGlobalConfig.tableCellLook().m_enabled );
	updateCellLook( 1, 0, gGlobalConfig.tableCellLook().m_disabledTemporary );
	updateCellLook( 2, 0, gGlobalConfig.tableCellLook().m_disabledNoPay );
	updateCellLook( 3, 0, gGlobalConfig.tableCellLook().m_disabledTechnically );
	updateCellLook( 4, 0, gGlobalConfig.tableCellLook().m_disabledUndefined );
	updateCellLook( 5, 0, gGlobalConfig.tableCellLook().m_disabledDevicesNoRetired );
	updateCellLook( 6, 0, gGlobalConfig.tableCellLook().m_disabledDevicesRetired );

	updateCellLook( 0, 1, gGlobalConfig.tableCellLook().m_connected );
	updateCellLook( 1, 1, gGlobalConfig.tableCellLook().m_disconnected );
}

void DlgLookConfig::retrieveCellLook(QTableWidgetItem *item, CellLook &cellLook)
{
	cellLook.m_fontFamily	= item->font().family();
	cellLook.m_fontBold		= item->font().bold();
	cellLook.m_fontItalic	= item->font().italic();

	cellLook.m_foreColor	= item->foreground().color();
	cellLook.m_backColor	= item->background().color();
}

void DlgLookConfig::retrieveTableCellLook()
{
	gGlobalConfig.tableCellLook().m_rowHeight = ui->rowHeightSpinBox->value();
	gGlobalConfig.tableCellLook().m_fontSize = ui->textSizeSpinBox->value();

	retrieveCellLook(ui->coloursTable->item(0, 0), gGlobalConfig.tableCellLook().m_enabled );
	retrieveCellLook(ui->coloursTable->item(1, 0), gGlobalConfig.tableCellLook().m_disabledTemporary );
	retrieveCellLook(ui->coloursTable->item(2, 0), gGlobalConfig.tableCellLook().m_disabledNoPay );
	retrieveCellLook(ui->coloursTable->item(3, 0), gGlobalConfig.tableCellLook().m_disabledTechnically);
	retrieveCellLook(ui->coloursTable->item(4, 0), gGlobalConfig.tableCellLook().m_disabledUndefined );
	retrieveCellLook(ui->coloursTable->item(5, 0), gGlobalConfig.tableCellLook().m_disabledDevicesNoRetired );
	retrieveCellLook(ui->coloursTable->item(6, 0), gGlobalConfig.tableCellLook().m_disabledDevicesRetired );

	retrieveCellLook(ui->coloursTable->item(0, 1), gGlobalConfig.tableCellLook().m_connected );
	retrieveCellLook(ui->coloursTable->item(1, 1), gGlobalConfig.tableCellLook().m_disconnected );
}

void DlgLookConfig::onItemSelected()
{
	QTableWidgetItem *item;
	if( (item = ui->coloursTable->currentItem()) && !item->text().isEmpty() )
	{
		ui->styleGroupBox->setEnabled(true);

		QFont font = item->font();
		QColor fore = item->foreground().color();
		QColor back = item->background().color();

		ui->italicCheckBox->setChecked( font.italic() );
		ui->boldCheckBox->setChecked( font.bold() );

		ui->textRedSpinBox->setValue( fore.red() );
		ui->textGreenSpinBox->setValue( fore.green() );
		ui->textBlueSpinBox->setValue( fore.blue() );

		ui->backRedSpinBox->setValue( back.red() );
		ui->backGreenSpinBox->setValue( back.green() );
		ui->backBlueSpinBox->setValue( back.blue() );
	}
	else
		ui->styleGroupBox->setEnabled(false);
}

void DlgLookConfig::updateCellLook(QTableWidgetItem *item)
{
	item->setBackground( QColor(qRgb(ui->backRedSpinBox->value(),
									 ui->backGreenSpinBox->value(),
									 ui->backBlueSpinBox->value())) );

	item->setForeground( QColor(qRgb(ui->textRedSpinBox->value(),
									 ui->textGreenSpinBox->value(),
									 ui->textBlueSpinBox->value())) );
}

void DlgLookConfig::updateTableFontSize(int size)
{
	QFont tableFont = ui->coloursTable->font();
	tableFont.setPixelSize(size);
	ui->coloursTable->setFont(tableFont);
}

void DlgLookConfig::updateTableRowHeight(int /*size*/)
{
	ui->coloursTable->verticalHeader()->setDefaultSectionSize(ui->rowHeightSpinBox->value());
}

void DlgLookConfig::updateCurrentCellLook(int /*value*/)
{
	if( ui->coloursTable->currentItem() )
		updateCellLook(ui->coloursTable->currentItem());
}

void DlgLookConfig::on_boldCheckBox_clicked()
{
	if( ui->coloursTable->currentItem() && !ui->coloursTable->currentItem()->text().isEmpty() )
	{
		QFont font = ui->coloursTable->currentItem()->font();
		font.setBold( ui->boldCheckBox->isChecked() );
		ui->coloursTable->currentItem()->setFont(font);
	}
}

void DlgLookConfig::on_italicCheckBox_clicked()
{
	if( ui->coloursTable->currentItem() && !ui->coloursTable->currentItem()->text().isEmpty() )
	{
		QFont font = ui->coloursTable->currentItem()->font();
		font.setItalic( ui->italicCheckBox->isChecked() );
		ui->coloursTable->currentItem()->setFont(font);
	}
}

void DlgLookConfig::on_textFontButton_clicked()
{
	if( ui->coloursTable->currentItem() && !ui->coloursTable->currentItem()->text().isEmpty() )
		ui->coloursTable->currentItem()->setFont( QFontDialog::getFont(Q_NULLPTR, ui->coloursTable->currentItem()->font(), this) );
}

void DlgLookConfig::on_textColorButton_clicked()
{
	if( ui->coloursTable->currentItem() && !ui->coloursTable->currentItem()->text().isEmpty() )
		ui->coloursTable->currentItem()->setForeground( QColorDialog::getColor(ui->coloursTable->currentItem()->foreground().color(), this) );
}

void DlgLookConfig::on_backColorButton_clicked()
{
	if( ui->coloursTable->currentItem() && !ui->coloursTable->currentItem()->text().isEmpty() )
		ui->coloursTable->currentItem()->setBackground( QColorDialog::getColor(ui->coloursTable->currentItem()->background().color(), this) );
}

void DlgLookConfig::on_acceptButton_clicked()
{
	retrieveTableCellLook();
	accept();
}

void DlgLookConfig::on_cancelButton_clicked()
{
	reject();
}
