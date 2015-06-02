#include "script_management.h"


script_Dialog::script_Dialog(QWidget *parent):QDialog(parent)
{
	setupUi(this);
	resetAddBtn();//重置按钮状态
	connect(scriptEdit,SIGNAL(textChanged(const QString &)),this,SLOT(reEnable()));//必须是textChanged(const QString &)，reEnable()要是接受者的成员函数
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
	scriptEdit->setText(scriptEdit->text()+"R"+QString::number(RspinBox->value()));//追加字符
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
 *  功能描述: 重置添加按钮状态
 ----------------------------------------*/ 
void script_Dialog::resetAddBtn()
{
	AddRbtn->setDisabled(false);
	AddVbtn->setDisabled(true);
	AddLbtn->setDisabled(true);
	AddTbtn->setDisabled(true);
}

/*----------------------------------------*
 *  功能描述: 重新使能R添加按钮
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