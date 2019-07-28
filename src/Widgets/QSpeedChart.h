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
#ifndef QSPEEDCHART_H
#define QSPEEDCHART_H

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QTimer>
#include <QValueAxis>

#ifdef QT_CHARTS_NAMESPACE
using _qCharts = QT_CHARTS_NAMESPACE::QChart;
using _qChartWidget = QT_CHARTS_NAMESPACE::QChartView;
using _qLineSeries = QT_CHARTS_NAMESPACE::QLineSeries;
using _qValueAxis = QT_CHARTS_NAMESPACE::QValueAxis;
#else
using _qCharts = QChart;
using _qChartWidget = QChartView;
using _qLineSeries = QLineSeries;
using _qValueAxis = QValueAxis;
#endif

class QSpeedChart : public _qCharts
{
	Q_OBJECT

	struct _line
	{
		_qLineSeries *series;
		_qValueAxis *axisX;
		_qValueAxis *axisY;
		_line()
			: series(new _qLineSeries())
			, axisX(new _qValueAxis())
			, axisY(new _qValueAxis())
		{
		}
		void setup()
		{
			series->attachAxis(axisX);
			series->attachAxis(axisY);
			axisX->setTickCount(1);

			axisX->setRange(0, 0);
			axisY->setRange(0, 0);
		}
	};
	_line mDownloadLine;
	_line mUploadLine;

	qreal mX;

public:
	explicit QSpeedChart(QGraphicsItem *parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::Widget);

	void setDownloadPencil(const QColor &clr, int width)	{ QPen p(clr); p.setWidth(width); mDownloadLine.series->setPen(p); }
	void setUploadPencil(const QColor &clr, int width)		{ QPen p(clr); p.setWidth(width); mUploadLine.series->setPen(p);	}
	void addSpeeds(qreal dwKbps, qreal upKbps);
};

class QSpeedChartWidget : public _qChartWidget
{
	QSpeedChart *mSpeedChart;

public:
	QSpeedChartWidget(QWidget * = Q_NULLPTR);
	void addSpeeds(qreal dwKbps, qreal upKbps)
	{
		mSpeedChart->addSpeeds(dwKbps, upKbps);
	}
};

#endif // QSPEEDCHART_H
