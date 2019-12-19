#pragma once

#include <QWidget>
#include "ui_WOther.h"

class WOther : public QWidget
{
	Q_OBJECT

public:
	WOther(QWidget *parent = Q_NULLPTR);
	~WOther();

private:
	Ui::WOther ui;

	bool write_main();
	bool read_main();

public slots:
	void buttonSave();
};
