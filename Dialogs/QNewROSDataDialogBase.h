#ifndef QFANCYDIALOG_H
#define QFANCYDIALOG_H

#include <QDialog>
#include <functional>
#include <QLineEdit>
#include <QComboBox>

#include "ROSData/ROSDataBasics.h"
#include "ROSData/ROSPPPProfile.h"

class QNewROSDataDialogBase : public QDialog
{

public:
	explicit QNewROSDataDialogBase(QWidget *papi);

	virtual void setROSData(ROSDataBase &rosData) = 0;
	virtual bool getROSData(ROSDataBase &rosData) const = 0;

	void raiseWarning(const QString &info, const QString &field) const;

	template<typename T>
	bool setTextToMember(const QString &fieldText, T &rosData, std::function<bool(T &, const QString &)> setFnc, const QString &fieldName = QString()) const
	{
		if( setFnc(rosData, fieldText) )
			return true;
		raiseWarning( rosData.lastError(), fieldName );
		return false;
	}

	template <class T>
	void tryAccept()
	{
		T tmp("");
		if( getROSData(tmp) )
			accept();
	}

	bool exec(ROSDataBase &rosData);
};

#define fancySetTextToMember(__fieldText, __rosData, __className, __setFnc, __fieldName) (setTextToMember<__className>( __fieldText, static_cast<__className&>(__rosData), &__className::__setFnc, __fieldName))

#endif // QFANCYDIALOG_H
