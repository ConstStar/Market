#pragma once

#include <QWidget>
#include "ui_WKeyWordGroup.h"

#include <qstandarditemmodel.h>
#include <qmenu.h>

class WKeyWordGroup : public QWidget
{
	Q_OBJECT

public:
	WKeyWordGroup(QWidget* parent = Q_NULLPTR);
	~WKeyWordGroup();

	void init();
	void write();

	void addList(QString str);

private:
	Ui::WKeyWordGroup ui;
	QStandardItemModel* m_model;
	QMenu* m_contextMenu;

	void contextMenuEvent(QContextMenuEvent* event);
public slots:
	void onAdd();
	void onDelete();
	void onCheck();
};
