/********************************************************************************
** Form generated from reading UI file 'script_management.ui'
**
** Created: Mon Jun 1 20:43:07 2015
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRIPT_MANAGEMENT_H
#define UI_SCRIPT_MANAGEMENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_sctiptDialog
{
public:
    QGridLayout *_2;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_5;
    QSlider *LhorizontalSlider;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_4;
    QSlider *VhorizontalSlider;
    QLabel *label_6;
    QPushButton *AddTbtn;
    QSpinBox *TspinBox;
    QPushButton *AddLbtn;
    QPushButton *AddVbtn;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *AddRbtn;
    QSpinBox *RspinBox;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QLineEdit *lineEdit_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *newScriptBtn;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QPushButton *pushButton_2;
    QLineEdit *scriptEdit;
    QLabel *label_8;

    void setupUi(QDialog *sctiptDialog)
    {
        if (sctiptDialog->objectName().isEmpty())
            sctiptDialog->setObjectName(QString::fromUtf8("sctiptDialog"));
        sctiptDialog->resize(500, 227);
        sctiptDialog->setModal(true);
        _2 = new QGridLayout(sctiptDialog);
        _2->setObjectName(QString::fromUtf8("_2"));
        _2->setContentsMargins(9, -1, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(sctiptDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 1, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        LhorizontalSlider = new QSlider(groupBox_2);
        LhorizontalSlider->setObjectName(QString::fromUtf8("LhorizontalSlider"));
        LhorizontalSlider->setMinimum(-2000);
        LhorizontalSlider->setMaximum(2000);
        LhorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(LhorizontalSlider);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMargin(5);

        horizontalLayout_5->addWidget(label_7);


        gridLayout->addLayout(horizontalLayout_5, 2, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        VhorizontalSlider = new QSlider(groupBox_2);
        VhorizontalSlider->setObjectName(QString::fromUtf8("VhorizontalSlider"));
        VhorizontalSlider->setMinimum(10);
        VhorizontalSlider->setMaximum(1000);
        VhorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(VhorizontalSlider);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setMargin(5);

        horizontalLayout_4->addWidget(label_6);


        gridLayout->addLayout(horizontalLayout_4, 1, 1, 1, 1);

        AddTbtn = new QPushButton(groupBox_2);
        AddTbtn->setObjectName(QString::fromUtf8("AddTbtn"));
        AddTbtn->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Resources/images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddTbtn->setIcon(icon);

        gridLayout->addWidget(AddTbtn, 3, 3, 1, 1);

        TspinBox = new QSpinBox(groupBox_2);
        TspinBox->setObjectName(QString::fromUtf8("TspinBox"));
        TspinBox->setMaximum(1000);
        TspinBox->setSingleStep(100);
        TspinBox->setValue(1);

        gridLayout->addWidget(TspinBox, 3, 1, 1, 1);

        AddLbtn = new QPushButton(groupBox_2);
        AddLbtn->setObjectName(QString::fromUtf8("AddLbtn"));
        AddLbtn->setAutoFillBackground(false);
        AddLbtn->setIcon(icon);

        gridLayout->addWidget(AddLbtn, 2, 3, 1, 1);

        AddVbtn = new QPushButton(groupBox_2);
        AddVbtn->setObjectName(QString::fromUtf8("AddVbtn"));
        AddVbtn->setAutoFillBackground(false);
        AddVbtn->setIcon(icon);

        gridLayout->addWidget(AddVbtn, 1, 3, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 2, 2, 1, 1);

        AddRbtn = new QPushButton(groupBox_2);
        AddRbtn->setObjectName(QString::fromUtf8("AddRbtn"));
        AddRbtn->setAutoFillBackground(false);
        AddRbtn->setIcon(icon);

        gridLayout->addWidget(AddRbtn, 0, 3, 1, 1);

        RspinBox = new QSpinBox(groupBox_2);
        RspinBox->setObjectName(QString::fromUtf8("RspinBox"));
        RspinBox->setMaximum(100);
        RspinBox->setValue(1);

        gridLayout->addWidget(RspinBox, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 3, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 2, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_3->addWidget(label_9);

        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        horizontalLayout_3->addWidget(lineEdit_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        newScriptBtn = new QPushButton(groupBox_2);
        newScriptBtn->setObjectName(QString::fromUtf8("newScriptBtn"));

        horizontalLayout_3->addWidget(newScriptBtn);

        horizontalLayout_3->setStretch(1, 10);
        horizontalLayout_3->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_3);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 0, 0, 2, 1);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        comboBox = new QComboBox(groupBox_3);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 1, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_3->addWidget(pushButton_2, 2, 0, 1, 2);

        scriptEdit = new QLineEdit(groupBox_3);
        scriptEdit->setObjectName(QString::fromUtf8("scriptEdit"));

        gridLayout_3->addWidget(scriptEdit, 1, 0, 1, 3);


        gridLayout_4->addWidget(groupBox_3, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 1, 1, 1, 1);

        gridLayout_4->setColumnStretch(0, 2);

        horizontalLayout->addWidget(groupBox);


        _2->addLayout(horizontalLayout, 0, 0, 1, 1);

        QWidget::setTabOrder(RspinBox, AddRbtn);
        QWidget::setTabOrder(AddRbtn, VhorizontalSlider);
        QWidget::setTabOrder(VhorizontalSlider, AddVbtn);
        QWidget::setTabOrder(AddVbtn, LhorizontalSlider);
        QWidget::setTabOrder(LhorizontalSlider, AddLbtn);
        QWidget::setTabOrder(AddLbtn, TspinBox);
        QWidget::setTabOrder(TspinBox, AddTbtn);
        QWidget::setTabOrder(AddTbtn, lineEdit_4);
        QWidget::setTabOrder(lineEdit_4, newScriptBtn);
        QWidget::setTabOrder(newScriptBtn, comboBox);
        QWidget::setTabOrder(comboBox, scriptEdit);
        QWidget::setTabOrder(scriptEdit, pushButton_2);

        retranslateUi(sctiptDialog);
        QObject::connect(VhorizontalSlider, SIGNAL(sliderMoved(int)), label_6, SLOT(setNum(int)));
        QObject::connect(LhorizontalSlider, SIGNAL(sliderMoved(int)), label_7, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(sctiptDialog);
    } // setupUi

    void retranslateUi(QDialog *sctiptDialog)
    {
        sctiptDialog->setWindowTitle(QApplication::translate("sctiptDialog", "\350\277\220\345\212\250\350\204\232\346\234\254\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QApplication::translate("sctiptDialog", "\345\212\250\344\275\234\346\265\201\347\250\213", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("sctiptDialog", "0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("sctiptDialog", "10", 0, QApplication::UnicodeUTF8));
        AddTbtn->setText(QString());
        AddLbtn->setText(QString());
        AddVbtn->setText(QString());
        AddRbtn->setText(QString());
        label_4->setText(QApplication::translate("sctiptDialog", "\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("sctiptDialog", "\346\227\213\350\275\254\345\210\206\345\272\246", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("sctiptDialog", "\345\215\207\351\231\215\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("sctiptDialog", "\345\276\252\347\216\257\346\254\241\346\225\260", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("sctiptDialog", "\346\226\207\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        newScriptBtn->setText(QApplication::translate("sctiptDialog", "\346\226\260\345\273\272", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("sctiptDialog", "\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("sctiptDialog", "\350\277\220\345\212\250\350\204\232\346\234\254", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("sctiptDialog", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        label_8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class sctiptDialog: public Ui_sctiptDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRIPT_MANAGEMENT_H
