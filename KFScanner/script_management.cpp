#include "script_management.h"
#include <iostream>
#include <QMessageBox>
#include <fstream>
#include <io.h>
#include <stdio.h>
#include <QTextCodec> 
#include <QDebug>
using namespace std;


////TODO:使用正则表达式确保lineedit中内容正确


script_Dialog::script_Dialog(QWidget *parent):QDialog(parent)
{
	setupUi(this);
	resetAddBtn();//重置按钮状态
	init_scriptList();

	connect(scriptEdit,SIGNAL(textChanged(const QString &)),this,SLOT(updateScript()));//必须是textChanged(const QString &)，updateScript()要是接受者的成员函数
	connect(script_cb,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(readScript()));//下拉菜单更改后读入脚本字符串
}


script_Dialog::~script_Dialog(void)
{
}

/*------------------------------------------------------------------*
 *  功能描述: 点击新建按钮后出发的槽函数
 *	检查文件是否存在，写入脚本字符串，保存文件，发射信号更新主面板
 -------------------------------------------------------------------*/ 
void script_Dialog::on_newScriptBtn_clicked()
{
	
	if (filenameEdit->text().isEmpty())
		QMessageBox::warning(this,tr("警告"), tr("请输入文件名"),QMessageBox::Yes);
	else{
		try{
			
			QString filename = filenameEdit->text();
			ifstream fin("scripts/"+filename.toStdString()+".txt");//首先判断文件是否存在
			if (!fin)//如果不存在
			{
				if (!scriptEdit->text().isEmpty())
				{
					string fn ="scripts/"+filename.toStdString()+".txt";
					ofstream f(fn);
					if (f)
					{					
						f<<scriptEdit->text().toStdString();//写入脚本
						script_cb->addItem(filename);
						QMessageBox::warning(this,tr("成功"), tr("脚本创建成功"),QMessageBox::Yes);
						emit onNewScriptBtn(filename+".txt");//发生信号，传递新建的文件名并在主面板上更新
					}
					else
					{
						QMessageBox::warning(this,tr("失败"), tr("不支持中文名"),QMessageBox::Yes);
					}
				}
				else
					QMessageBox::warning(this,tr("警告"), tr("没有可以写入的脚本"),QMessageBox::Yes);
			}
			else{
				QMessageBox::warning(this,tr("警告"), tr("存在同名脚本"),QMessageBox::Yes);
			}
		}
		catch(...){
			QMessageBox::warning(this,tr("警告"), tr("写入文件出错"),QMessageBox::Yes);
		}
	}
	
}

/*-------------------------------------------*
 *  功能描述: 点击删除按钮后出发的槽函数
 --------------------------------------------*/ 
void script_Dialog::on_deleteBtn_clicked()
{
	string filename = script_cb->currentText().toStdString();
	try{
		if (filename!=".")
		{
			remove(("scripts/"+filename).c_str());//必须要转换成一个C指针形式，因为remove是C的函数
			script_cb->removeItem(script_cb->currentIndex());
			emit onDeleteBtn(script_cb->currentIndex());
			scriptEdit->clear();
		}
	}
	catch(...)
	{
		QMessageBox::warning(this,tr("警告"), tr("无法删除当前文件"),QMessageBox::Yes);
	}
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
/*------------------------------------------------*
 *  功能描述:	处理脚本字符串，使其末尾不包含字符
 *	返回值：	QString 移除无用字符后的结果 
 -------------------------------------------------*/ 
QString script_Dialog::trimScript(QString script)
{
	QString lastChar=script.right(1);//返回最后一个字符
	if (lastChar=="R"||lastChar=="V"||lastChar=="L"||lastChar=="T")
	{
		return script.left(script.length()-1);//删除最后一个字符
	}
	return script;
}
/*------------------------------------------------------------------*
 *  功能描述: 当LineEdit被编辑时，更新处理后的文字，当为空时重置按键
 ------------------------------------------------------------------*/ 
void script_Dialog::updateScript()
{
	scriptEdit->setText(trimScript(scriptEdit->text()));
	if (scriptEdit->text().isEmpty())
		resetAddBtn();
}


/*------------------------------------------------------------------*
 *  功能描述: 查找scripts文件夹下全部文件名，并初始化combo box
 *  参考资料：http://blog.csdn.net/xuejiren/article/details/37040827
 -------------------------------------------------------------------*/ 
void script_Dialog::init_scriptList()
{
	vector<string> files; 
	long   hFile   =   0;  
	string path = "scripts/";//要查找的目录
	struct _finddata_t fileinfo;  //结构体，存放文件信息
	string p;  
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{  
			files.push_back(fileinfo.name);//把找到的文件名加入到files中
			
		}while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile);  
	}
	script_cb->clear();
	for (int i = 0 ; i<files.size() ; i++)//一次添加到combo box
	{
		if (!(files[i]==".."))//跳过目录..,保留.
			script_cb->addItem(files[i].c_str());
	}
}

/*--------------------------------------------*
 *  功能描述: SLOT 当切换combox的时候读入脚本
 ---------------------------------------------*/ 
void script_Dialog::readScript()
{
	string filename = script_cb->currentText().toStdString();
	if (filename!=".")
	{
		ifstream f("scripts/"+filename);
		string script;
		f>>script;
		scriptEdit->setText(QString::fromStdString(script));
	}
}