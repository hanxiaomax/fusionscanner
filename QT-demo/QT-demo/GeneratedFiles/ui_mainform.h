/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created: Tue Apr 7 10:28:17 2015
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "glviewer.h"

QT_BEGIN_NAMESPACE

class Ui_mainFormClass
{
public:
    QAction *resetCam;
    QAction *ConnectKinect;
    QAction *Scan;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *pipline_2;
    QGridLayout *pipline;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *show_depBtn;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    glviewer *GRBviewer;
    glviewer *Fusionviewer;
    glviewer *depthviewer_4;
    glviewer *Dviewer;
    QGroupBox *output;
    QGridLayout *gridLayout_4;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout_2;
    QToolBox *toolBox_2;
    QWidget *page_3;
    QWidget *page_4;
    QGroupBox *groupBox_3;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainFormClass)
    {
        if (mainFormClass->objectName().isEmpty())
            mainFormClass->setObjectName(QString::fromUtf8("mainFormClass"));
        mainFormClass->resize(849, 695);
        resetCam = new QAction(mainFormClass);
        resetCam->setObjectName(QString::fromUtf8("resetCam"));
        ConnectKinect = new QAction(mainFormClass);
        ConnectKinect->setObjectName(QString::fromUtf8("ConnectKinect"));
        Scan = new QAction(mainFormClass);
        Scan->setObjectName(QString::fromUtf8("Scan"));
        centralWidget = new QWidget(mainFormClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        pipline_2 = new QGroupBox(centralWidget);
        pipline_2->setObjectName(QString::fromUtf8("pipline_2"));
        pipline_2->setFlat(false);
        pipline_2->setCheckable(false);
        pipline = new QGridLayout(pipline_2);
        pipline->setSpacing(6);
        pipline->setContentsMargins(11, 11, 11, 11);
        pipline->setObjectName(QString::fromUtf8("pipline"));
        pipline->setHorizontalSpacing(2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(pipline_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        show_depBtn = new QPushButton(pipline_2);
        show_depBtn->setObjectName(QString::fromUtf8("show_depBtn"));

        horizontalLayout->addWidget(show_depBtn);

        pushButton_2 = new QPushButton(pipline_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(pipline_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_5 = new QPushButton(pipline_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout->addWidget(pushButton_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_4 = new QPushButton(pipline_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);


        pipline->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(pipline_2);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        GRBviewer = new glviewer(groupBox_2);
        GRBviewer->setObjectName(QString::fromUtf8("GRBviewer"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GRBviewer->sizePolicy().hasHeightForWidth());
        GRBviewer->setSizePolicy(sizePolicy);
        GRBviewer->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(GRBviewer, 1, 0, 1, 1);

        Fusionviewer = new glviewer(groupBox_2);
        Fusionviewer->setObjectName(QString::fromUtf8("Fusionviewer"));
        sizePolicy.setHeightForWidth(Fusionviewer->sizePolicy().hasHeightForWidth());
        Fusionviewer->setSizePolicy(sizePolicy);
        Fusionviewer->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(Fusionviewer, 0, 1, 1, 1);

        depthviewer_4 = new glviewer(groupBox_2);
        depthviewer_4->setObjectName(QString::fromUtf8("depthviewer_4"));
        sizePolicy.setHeightForWidth(depthviewer_4->sizePolicy().hasHeightForWidth());
        depthviewer_4->setSizePolicy(sizePolicy);
        depthviewer_4->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(depthviewer_4, 0, 0, 1, 1);

        Dviewer = new glviewer(groupBox_2);
        Dviewer->setObjectName(QString::fromUtf8("Dviewer"));
        sizePolicy.setHeightForWidth(Dviewer->sizePolicy().hasHeightForWidth());
        Dviewer->setSizePolicy(sizePolicy);
        Dviewer->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(Dviewer, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        output = new QGroupBox(centralWidget);
        output->setObjectName(QString::fromUtf8("output"));
        gridLayout_4 = new QGridLayout(output);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(6);
        gridLayout_4->setContentsMargins(9, 1, 9, 1);
        textEdit = new QTextEdit(output);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_4->addWidget(textEdit, 0, 0, 1, 1);


        verticalLayout->addWidget(output);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 15);
        verticalLayout->setStretch(2, 2);

        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 9, -1, -1);
        toolBox_2 = new QToolBox(centralWidget);
        toolBox_2->setObjectName(QString::fromUtf8("toolBox_2"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 204, 343));
        toolBox_2->addItem(page_3, QString::fromUtf8("Page 1"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 204, 343));
        toolBox_2->addItem(page_4, QString::fromUtf8("Page 2"));

        verticalLayout_2->addWidget(toolBox_2);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));

        verticalLayout_2->addWidget(groupBox_3);

        verticalLayout_2->setStretch(0, 2);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        mainFormClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainFormClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 849, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        mainFormClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainFormClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainFormClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainFormClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        mainFormClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(ConnectKinect);
        menuFile->addAction(Scan);
        mainToolBar->addAction(resetCam);

        retranslateUi(mainFormClass);

        toolBox_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainFormClass);
    } // setupUi

    void retranslateUi(QMainWindow *mainFormClass)
    {
        mainFormClass->setWindowTitle(QApplication::translate("mainFormClass", "mainForm", 0, QApplication::UnicodeUTF8));
        resetCam->setText(QApplication::translate("mainFormClass", "\351\207\215\347\275\256\347\233\270\346\234\272", 0, QApplication::UnicodeUTF8));
        ConnectKinect->setText(QApplication::translate("mainFormClass", "\350\277\236\346\216\245kinect", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ConnectKinect->setToolTip(QApplication::translate("mainFormClass", "<html><head/><body><p>\350\277\236\346\216\245kinect\350\256\276\345\244\207\357\274\214\345\256\214\346\210\220\345\210\235\345\247\213\345\214\226</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        Scan->setText(QApplication::translate("mainFormClass", "\345\274\200\345\247\213\346\211\253\346\217\217", 0, QApplication::UnicodeUTF8));
        pipline_2->setTitle(QApplication::translate("mainFormClass", "\346\211\253\346\217\217-\345\273\272\346\250\241\346\265\201\346\260\264\347\272\277", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("mainFormClass", "RGB", 0, QApplication::UnicodeUTF8));
        show_depBtn->setText(QApplication::translate("mainFormClass", "\346\267\261\345\272\246\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("mainFormClass", "\350\241\250\351\235\242\351\207\215\345\273\272", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("mainFormClass", "\344\270\211\347\273\264\346\250\241\345\236\213", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("mainFormClass", "\346\211\253\346\217\217\350\243\205\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("mainFormClass", "\350\275\257\344\273\266\351\207\215\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("mainFormClass", "OpenGL\350\247\206\347\252\227", 0, QApplication::UnicodeUTF8));
        output->setTitle(QApplication::translate("mainFormClass", "\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        toolBox_2->setItemText(toolBox_2->indexOf(page_3), QApplication::translate("mainFormClass", "Page 1", 0, QApplication::UnicodeUTF8));
        toolBox_2->setItemText(toolBox_2->indexOf(page_4), QApplication::translate("mainFormClass", "Page 2", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("mainFormClass", "\347\212\266\346\200\201\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("mainFormClass", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainFormClass: public Ui_mainFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
