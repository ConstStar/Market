#pragma once

#include <QWidget>

#include <qstandarditemmodel.h>

#include "ui_WGroupList.h"


class WGroupList : public QWidget
{
	Q_OBJECT

public:
	WGroupList(QWidget *parent = Q_NULLPTR);
	~WGroupList();

private:
	Ui::WGroupList ui;
	QStandardItemModel *m_model;

	bool read_data();
	bool write_data();

protected:
	void closeEvent(QCloseEvent* event);

public slots:
	void buttonAddGroup();
	void onTableClicked(const QModelIndex&);
	void onCheck();
};
