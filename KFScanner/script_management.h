#pragma once
#include "ui_script_management.h"
#include <QDialog>
class script_Dialog :
	public QDialog,public Ui::sctiptDialog
{
	Q_OBJECT
public:
	explicit script_Dialog(QWidget * parent = 0);
	~script_Dialog(void);

private slots:
	void on_AddRbtn_clicked();
	void on_AddVbtn_clicked();
	void on_AddLbtn_clicked();
	void on_AddTbtn_clicked();
	void reEnable();
private:
	//QString script
	void resetAddBtn();
};

