#pragma once

#include <QWidget>
#include "ui_WSystem.h"

class WSystem : public QWidget
{
	Q_OBJECT

public:
	WSystem(QWidget *parent = Q_NULLPTR);
	~WSystem();

	void init();
	bool readConf();
	bool writeConf();

private:
	Ui::WSystem ui;

public slots:
	void onSave();
	void onGetKey();
	void onGetCredits();
};
