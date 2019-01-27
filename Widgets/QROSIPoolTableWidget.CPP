#include "QROSIPoolTableWidget.h"

QROSIPoolTableWidget::QROSIPoolTableWidget(QWidget *papi) : QROSDataTableWidget(papi)
{

}


int QROSIPoolTableWidget::rowOf(const ROSDataBase &rosData)
{
	return QROSDataTableWidget::rowOf(PoolName, static_cast<const ROSIPPool &>(rosData).poolName());
}

ROSDataBase *QROSIPoolTableWidget::getRosData(int row)
{
	return Q_NULLPTR;
}
