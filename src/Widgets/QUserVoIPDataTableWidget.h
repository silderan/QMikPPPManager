#ifndef QUSERVOIPDATATABLEWIDGET_H
#define QUSERVOIPDATATABLEWIDGET_H

#include <QTableWidget>

class QTableWidgetItem;
struct VoIPData;

class QUserVoIPDataTableWidget : public QTableWidget
{
	Q_OBJECT

	void onItemChanged(QTableWidgetItem *item);
public:
	explicit QUserVoIPDataTableWidget(QWidget *parent = nullptr);

	void addVoIPData(const VoIPData &voip);
	void delVoIPData(int row = -1);
	void setupUser(const QString &userName);

	void setup();
	QStringList sipPhones(QString &err) const;
};

#endif // QUSERVOIPDATATABLEWIDGET_H
