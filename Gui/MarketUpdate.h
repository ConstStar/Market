#pragma once

#include <QWidget>
#include "ui_MarketUpdate.h"

class MarketUpdate : public QWidget
{
	Q_OBJECT

public:
	MarketUpdate(QWidget *parent = Q_NULLPTR);
	~MarketUpdate();

	//������ ����0Ϊû�и��� ����1Ϊ��Ҫ���� ����2Ϊ��Ҫǿ�Ƹ��� ����-1Ϊ�쳣
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
