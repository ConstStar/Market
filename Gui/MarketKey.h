#pragma once

#include <QWidget>
#include "ui_MarketKey.h"

class MarketKey : public QWidget
{
	Q_OBJECT

public:
	MarketKey(QWidget *parent = Q_NULLPTR);
	~MarketKey();

	void writeKey();

private:
	Ui::MarketKey ui;

public slots:
	void onPushButton();
	void onUserAgree();
};
