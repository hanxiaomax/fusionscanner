#include "script_management.h"
#include <iostream>
#include <QMessageBox>
#include <fstream>
#include <io.h>
#include <stdio.h>
#include <QTextCodec> 
#include <QDebug>
using namespace std;


////TODO:ʹ��������ʽȷ��lineedit��������ȷ


script_Dialog::script_Dialog(QWidget *parent):QDialog(parent)
{
	setupUi(this);
	resetAddBtn();//���ð�ť״̬
	init_scriptList();

	connect(scriptEdit,SIGNAL(textChanged(const QString &)),this,SLOT(updateScript()));//������textChanged(const QString &)��updateScript()Ҫ�ǽ����ߵĳ�Ա����
	connect(script_cb,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(readScript()));//�����˵����ĺ����ű��ַ���
}


script_Dialog::~script_Dialog(void)
{
}

/*------------------------------------------------------------------*
 *  ��������: ����½���ť������Ĳۺ���
 *	����ļ��Ƿ���ڣ�д��ű��ַ����������ļ��������źŸ��������
 -------------------------------------------------------------------*/ 
void script_Dialog::on_newScriptBtn_clicked()
{
	
	if (filenameEdit->text().isEmpty())
		QMessageBox::warning(this,tr("����"), tr("�������ļ���"),QMessageBox::Yes);
	else{
		try{
			
			QString filename = filenameEdit->text();
			ifstream fin("scripts/"+filename.toStdString()+".txt");//�����ж��ļ��Ƿ����
			if (!fin)//���������
			{
				if (!scriptEdit->text().isEmpty())
				{
					string fn ="scripts/"+filename.toStdString()+".txt";
					ofstream f(fn);
					if (f)
					{					
						f<<scriptEdit->text().toStdString();//д��ű�
						script_cb->addItem(filename);
						QMessageBox::warning(this,tr("�ɹ�"), tr("�ű������ɹ�"),QMessageBox::Yes);
						emit onNewScriptBtn(filename+".txt");//�����źţ������½����ļ�������������ϸ���
					}
					else
					{
						QMessageBox::warning(this,tr("ʧ��"), tr("��֧��������"),QMessageBox::Yes);
					}
				}
				else
					QMessageBox::warning(this,tr("����"), tr("û�п���д��Ľű�"),QMessageBox::Yes);
			}
			else{
				QMessageBox::warning(this,tr("����"), tr("����ͬ���ű�"),QMessageBox::Yes);
			}
		}
		catch(...){
			QMessageBox::warning(this,tr("����"), tr("д���ļ�����"),QMessageBox::Yes);
		}
	}
	
}

/*-------------------------------------------*
 *  ��������: ���ɾ����ť������Ĳۺ���
 --------------------------------------------*/ 
void script_Dialog::on_deleteBtn_clicked()
{
	string filename = script_cb->currentText().toStdString();
	try{
		if (filename!=".")
		{
			remove(("scripts/"+filename).c_str());//����Ҫת����һ��Cָ����ʽ����Ϊremove��C�ĺ���
			script_cb->removeItem(script_cb->currentIndex());
			emit onDeleteBtn(script_cb->currentIndex());
			scriptEdit->clear();
		}
	}
	catch(...)
	{
		QMessageBox::warning(this,tr("����"), tr("�޷�ɾ����ǰ�ļ�"),QMessageBox::Yes);
	}
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
/*------------------------------------------------*
 *  ��������:	����ű��ַ�����ʹ��ĩβ�������ַ�
 *	����ֵ��	QString �Ƴ������ַ���Ľ�� 
 -------------------------------------------------*/ 
QString script_Dialog::trimScript(QString script)
{
	QString lastChar=script.right(1);//�������һ���ַ�
	if (lastChar=="R"||lastChar=="V"||lastChar=="L"||lastChar=="T")
	{
		return script.left(script.length()-1);//ɾ�����һ���ַ�
	}
	return script;
}
/*------------------------------------------------------------------*
 *  ��������: ��LineEdit���༭ʱ�����´��������֣���Ϊ��ʱ���ð���
 ------------------------------------------------------------------*/ 
void script_Dialog::updateScript()
{
	scriptEdit->setText(trimScript(scriptEdit->text()));
	if (scriptEdit->text().isEmpty())
		resetAddBtn();
}


/*------------------------------------------------------------------*
 *  ��������: ����scripts�ļ�����ȫ���ļ���������ʼ��combo box
 *  �ο����ϣ�http://blog.csdn.net/xuejiren/article/details/37040827
 -------------------------------------------------------------------*/ 
void script_Dialog::init_scriptList()
{
	vector<string> files; 
	long   hFile   =   0;  
	string path = "scripts/";//Ҫ���ҵ�Ŀ¼
	struct _finddata_t fileinfo;  //�ṹ�壬����ļ���Ϣ
	string p;  
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{  
			files.push_back(fileinfo.name);//���ҵ����ļ������뵽files��
			
		}while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile);  
	}
	script_cb->clear();
	for (int i = 0 ; i<files.size() ; i++)//һ����ӵ�combo box
	{
		if (!(files[i]==".."))//����Ŀ¼..,����.
			script_cb->addItem(files[i].c_str());
	}
}

/*--------------------------------------------*
 *  ��������: SLOT ���л�combox��ʱ�����ű�
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