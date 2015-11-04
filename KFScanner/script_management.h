 #pragma once
#include "ui_script_management.h"
#include <QDialog>

using namespace std;
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
	void on_newScriptBtn_clicked();
	void on_deleteBtn_clicked();
	void updateScript();//当lineedit有变化时触发，会自动trim脚本使其有效
	void readScript();//combo box变化时触发
private:
	void resetAddBtn();
	QString trimScript(QString script);
	bool scriptExist(QString filename);
	void init_scriptList();
signals:
	///////除非需要自动建立连接，否则不要使用on_开头的名字定义函数
	void onNewScriptBtn(const QString & filename);//定义一个信号，不需要实现
	void onDeleteBtn(int index);
};

