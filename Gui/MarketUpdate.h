#pragma once

#include <QWidget>
#include "ui_MarketUpdate.h"

class MarketUpdate : public QWidget
{
	Q_OBJECT

public:
	MarketUpdate(QWidget *parent = Q_NULLPTR);
	~MarketUpdate();

	//检查更新 返回0为没有更新 返回1为需要更新 返回2为需要强制更新 返回-1为异常
	int check();
	void update();
	void runApp();

private:
	Ui::MarketUpdate ui;
	
	QString m_url;

public slots:
	void onCheck();
	void onUpdate();
};
