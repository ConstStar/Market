#pragma once

#include <QWidget>
#include "ui_WFeedback.h"

class WFeedback : public QWidget
{
	Q_OBJECT

public:
	WFeedback(QWidget* parent = Q_NULLPTR);
	~WFeedback();

private:
	Ui::WFeedback ui;

	bool read_data();
	bool get_email(QString& emailStr, QString& passwd, QString& smtp, int& port, bool& ssl);

public slots:
	void buttonSend();
};

