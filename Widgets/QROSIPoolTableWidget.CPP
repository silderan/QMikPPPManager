#include "QROSIPoolTableWidget.h"

QROSIPoolTableWidget::QROSIPoolTableWidget(QWidget *papi) : QTableWidgetBase(papi)
{

}


int QROSIPoolTableWidget::rowOf(const ROSDataBase &rosData)
{
	return QTableWidgetBase::rowOf(PoolName, static_cast<const ROSIPPool &>(rosData).poolName());
}

ROSDataBase *QROSIPoolTableWidget::getRosData(int row)
{
}
