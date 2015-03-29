#ifndef QMIKPPPMANAGER_H
#define QMIKPPPMANAGER_H

#include <QMainWindow>

namespace Ui {
class QMikPPPManager;
}

class QMikPPPManager : public QMainWindow
{
	Q_OBJECT

public:
	explicit QMikPPPManager(QWidget *parent = 0);
	~QMikPPPManager();

private:
	Ui::QMikPPPManager *ui;
};

#endif // QMIKPPPMANAGER_H
