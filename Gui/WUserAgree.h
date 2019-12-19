#pragma once

#include <QWidget>
#include "ui_WUserAgree.h"

class WUserAgree : public QWidget
{
	Q_OBJECT

public:
	WUserAgree(QWidget *parent = Q_NULLPTR);
	~WUserAgree();

private:
	Ui::WUserAgree ui;
};
