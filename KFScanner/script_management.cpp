#include "script_management.h"


script_Dialog::script_Dialog(QWidget *parent):QDialog(parent)
{
	setupUi(this);
	resetAddBtn();//���ð�ť״̬
	connect(scriptEdit,SIGNAL(textChanged(const QString &)),this,SLOT(reEnable()));//������textChanged(const QString &)��reEnable()Ҫ�ǽ����ߵĳ�Ա����
}


script_Dialog::~script_Dialog(void)
{
}


void script_Dialog::on_AddRbtn_clicked()
{
	AddRbtn->setDisabled(true);
	AddVbtn->setDisabled(false);
	AddLbtn->setDisabled(false);
	AddTbtn->setDisabled(false);
	scriptEdit->setText(scriptEdit->text()+"R"+QString::number(RspinBox->value()));//׷���ַ�
}
void script_Dialog::on_AddVbtn_clicked()
{
	scriptEdit->setText(scriptEdit->text()+"V"+QString::number(VhorizontalSlider->value()));
}
void script_Dialog::on_AddLbtn_clicked()
{
	scriptEdit->setText(scriptEdit->text()+"L"+QString::number(LhorizontalSlider->value()));
}
void script_Dialog::on_AddTbtn_clicked()
{
	scriptEdit->setText(scriptEdit->text()+"T"+QString::number(TspinBox->value()));
}

/*----------------------------------------*
 *  ��������: ������Ӱ�ť״̬
 ----------------------------------------*/ 
void script_Dialog::resetAddBtn()
{
	AddRbtn->setDisabled(false);
	AddVbtn->setDisabled(true);
	AddLbtn->setDisabled(true);
	AddTbtn->setDisabled(true);
}

/*----------------------------------------*
 *  ��������: ����ʹ��R��Ӱ�ť
 ----------------------------------------*/ 
void script_Dialog::reEnable()
{
	if (scriptEdit->text()=="R")
	{
		scriptEdit->clear();
	}
	if (scriptEdit->text().isEmpty())
	{
		resetAddBtn();
	}
}