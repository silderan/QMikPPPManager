/**************************************************************************

  Copyright 2015-2020 Rafael Dellà Bort. silderan (at) gmail (dot) com

  This file is part of MuNeDO (Multiple Network Device Observer)

  MuNeDO is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  MuNeDO is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  and GNU Lesser General Public License. along with MuNeDO.
  If not, see <http://www.gnu.org/licenses/>.

**************************************************************************/
#ifndef DLGCREATECONFIGFILE_H
#define DLGCREATECONFIGFILE_H

#include <QDialog>

class ROSPPPSecret;

namespace Ui
{
	class DlgCreateConfigFile;
}

class DlgCreateConfigFile : public QDialog
{
	Q_OBJECT

	Ui::DlgCreateConfigFile *ui;

	const ROSPPPSecret *mRosSecret;

	void fillTemplateFiles();
	void clearTableAndOutFile();
	void appendRow(const QString &desc, const QString &name, const QString &value);
	QString value(const QString &name);

public:
	static QString templatePath();
	static QString templateFile(const QString &desc, const QString &fileName);

	explicit DlgCreateConfigFile(const ROSPPPSecret *rosSecret = nullptr, QWidget *parent = nullptr);
	~DlgCreateConfigFile();
private slots:
	void on_templateComboBox_currentIndexChanged(int index);
	void on_choosePathButton_clicked();
	void on_createButton_clicked();
};

#endif // DLGCREATECONFIGFILE_H
