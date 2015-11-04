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
	void updateScript();//��lineedit�б仯ʱ���������Զ�trim�ű�ʹ����Ч
	void readScript();//combo box�仯ʱ����
private:
	void resetAddBtn();
	QString trimScript(QString script);
	bool scriptExist(QString filename);
	void init_scriptList();
signals:
	///////������Ҫ�Զ��������ӣ�����Ҫʹ��on_��ͷ�����ֶ��庯��
	void onNewScriptBtn(const QString & filename);//����һ���źţ�����Ҫʵ��
	void onDeleteBtn(int index);
};

