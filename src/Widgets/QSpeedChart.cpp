/**************************************************************************

  Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

  This file is part of BasicSNMP

  BasicSNMP is free software: you can redistribute it and/or modify
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

**************************************************************************/
#include "QSpeedChart.h"

QT_CHARTS_USE_NAMESPACE

QSpeedChart::QSpeedChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
	: QChart(QChart::ChartTypeCartesian, parent, wFlags)
	, mX(0)
{
	setDownloadPencil(Qt::blue, 1);
	setUploadPencil(Qt::red, 1);

	addSeries(mDownloadLine.series);
	addSeries(mUploadLine.series);

	addAxis(mDownloadLine.axisX, Qt::AlignBottom);
	addAxis(mUploadLine.axisX, Qt::AlignBottom);
	addAxis(mDownloadLine.axisY, Qt::AlignLeft);
	addAxis(mUploadLine.axisY, Qt::AlignLeft);

	mUploadLine.axisY->hide();
	mUploadLine.axisX->hide();

	mDownloadLine.setup();
	mUploadLine.setup();

	legend()->hide();
	setMargins( QMargins() );
}

void QSpeedChart::addSpeeds(qreal dwKbps, qreal upKbps)
{
	mDownloadLine.axisX->setMax(++mX);
	mUploadLine.axisX->setMax(mX);

	mDownloadLine.series->append(mX, dwKbps);
	mUploadLine.series->append(mX, upKbps);

	dwKbps = qMax(dwKbps, upKbps);
	if( dwKbps > mDownloadLine.axisY->max() )
	{
		mDownloadLine.axisY->setMax(dwKbps);
		mUploadLine.axisY->setMax(dwKbps);
	}
}

QSpeedChartWidget::QSpeedChartWidget(QWidget *)
	: _qChartWidget(mSpeedChart = new QSpeedChart)
{
//	QTimer *t = new QTimer();
//	setRenderHint(QPainter::Antialiasing);
//	t->setInterval(1000);
//	t->start();
//	connect(t, &QTimer::timeout, [this] { this->addSpeeds(qrand() % 100, qrand() % 100); } );
}
