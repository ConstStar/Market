#pragma once

#include <QWidget>
#include "ui_WWordLook.h"

class WWordLook : public QWidget
{
	Q_OBJECT

public:
	WWordLook(QString text,QWidget *parent = Q_NULLPTR);
	~WWordLook();

private:
	Ui::WWordLook ui;

	void init();

	QString m_text;
	bool m_useHtml;
};
