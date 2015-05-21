/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created: Tue May 19 12:17:38 2015
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <GL2Dviewer.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainformClass
{
public:
    QAction *connectKinect;
    QAction *connectlifter;
    QAction *ToolstartBtn;
    QAction *ToolstopBtn;
    QAction *TooldeleteBtn;
    QAction *actionSaveCloud;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *mainTab;
    QWidget *initiation;
    glViewer *init_viewer;
    QToolBox *init_toolbox;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *delaylabel;
    QSlider *delay_slider;
    QLabel *delay_value;
    QLabel *label;
    QHBoxLayout *horizontalLayout_7;
    QLabel *rangelabel;
    QSlider *range_slider;
    QLabel *range_value;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *full_rb;
    QRadioButton *half_rb;
    QRadioButton *hea_rb;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer;
    QPushButton *defaultBtn;
    QWidget *page_2;
    QWidget *scan;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    glViewer *fusionViewer;
    QHBoxLayout *horizontalLayout_3;
    glViewer *depthViewer;
    glViewer *RGBViewer;
    glViewer *deviceViewer;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QTextEdit *textEdit;
    QPushButton *recordBtn;
    QPushButton *stopBtn;
    QPushButton *deleteBtn;
    QPushButton *showCloudBtn;
    QWidget *reconstruction;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_2;
    glViewer *init_viewer_6;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QToolBox *toolBox;
    QWidget *page_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *page_4;
    QWidget *process;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_5;
    glViewer *init_viewer_2;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_8;
    QToolBox *toolBox_2;
    QWidget *page_5;
    QWidget *page_6;
    QWidget *page_7;
    QGroupBox *groupBox_4;
    QMenuBar *menuBar;
    QMenu *menu_2;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *mainformClass)
    {
        if (mainformClass->objectName().isEmpty())
            mainformClass->setObjectName(QString::fromUtf8("mainformClass"));
        mainformClass->resize(922, 721);
        connectKinect = new QAction(mainformClass);
        connectKinect->setObjectName(QString::fromUtf8("connectKinect"));
        connectKinect->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Resources/images/260_64.png"), QSize(), QIcon::Normal, QIcon::Off);
        connectKinect->setIcon(icon);
        connectlifter = new QAction(mainformClass);
        connectlifter->setObjectName(QString::fromUtf8("connectlifter"));
        connectlifter->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/Resources/images/2215_64.png"), QSize(), QIcon::Normal, QIcon::Off);
        connectlifter->setIcon(icon1);
        ToolstartBtn = new QAction(mainformClass);
        ToolstartBtn->setObjectName(QString::fromUtf8("ToolstartBtn"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/Resources/images/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        ToolstartBtn->setIcon(icon2);
        ToolstopBtn = new QAction(mainformClass);
        ToolstopBtn->setObjectName(QString::fromUtf8("ToolstopBtn"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/Resources/images/stop.png"), QSize(), QIcon::Normal, QIcon::On);
        ToolstopBtn->setIcon(icon3);
        TooldeleteBtn = new QAction(mainformClass);
        TooldeleteBtn->setObjectName(QString::fromUtf8("TooldeleteBtn"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/Resources/images/recycle.png"), QSize(), QIcon::Normal, QIcon::On);
        TooldeleteBtn->setIcon(icon4);
        actionSaveCloud = new QAction(mainformClass);
        actionSaveCloud->setObjectName(QString::fromUtf8("actionSaveCloud"));
        centralWidget = new QWidget(mainformClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mainTab = new QTabWidget(centralWidget);
        mainTab->setObjectName(QString::fromUtf8("mainTab"));
        mainTab->setEnabled(true);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        mainTab->setFont(font);
        mainTab->setTabPosition(QTabWidget::North);
        mainTab->setTabShape(QTabWidget::Rounded);
        mainTab->setIconSize(QSize(16, 16));
        mainTab->setElideMode(Qt::ElideRight);
        mainTab->setUsesScrollButtons(true);
        mainTab->setDocumentMode(false);
        mainTab->setTabsClosable(false);
        initiation = new QWidget();
        initiation->setObjectName(QString::fromUtf8("initiation"));
        init_viewer = new glViewer(initiation);
        init_viewer->setObjectName(QString::fromUtf8("init_viewer"));
        init_viewer->setGeometry(QRect(10, 10, 581, 557));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(init_viewer->sizePolicy().hasHeightForWidth());
        init_viewer->setSizePolicy(sizePolicy);
        init_toolbox = new QToolBox(initiation);
        init_toolbox->setObjectName(QString::fromUtf8("init_toolbox"));
        init_toolbox->setGeometry(QRect(598, 11, 289, 555));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setWeight(50);
        init_toolbox->setFont(font1);
        init_toolbox->setFrameShape(QFrame::StyledPanel);
        init_toolbox->setFrameShadow(QFrame::Sunken);
        init_toolbox->setLineWidth(1);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 211, 174));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        delaylabel = new QLabel(page);
        delaylabel->setObjectName(QString::fromUtf8("delaylabel"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        delaylabel->setFont(font2);

        horizontalLayout_6->addWidget(delaylabel);

        delay_slider = new QSlider(page);
        delay_slider->setObjectName(QString::fromUtf8("delay_slider"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(delay_slider->sizePolicy().hasHeightForWidth());
        delay_slider->setSizePolicy(sizePolicy1);
        delay_slider->setMinimumSize(QSize(25, 0));
        delay_slider->setMaximum(15);
        delay_slider->setPageStep(5);
        delay_slider->setValue(5);
        delay_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(delay_slider);

        delay_value = new QLabel(page);
        delay_value->setObjectName(QString::fromUtf8("delay_value"));
        QFont font3;
        font3.setPointSize(10);
        delay_value->setFont(font3);
        delay_value->setMargin(5);
        delay_value->setIndent(10);

        horizontalLayout_6->addWidget(delay_value);

        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font3);

        horizontalLayout_6->addWidget(label);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        rangelabel = new QLabel(page);
        rangelabel->setObjectName(QString::fromUtf8("rangelabel"));
        rangelabel->setFont(font2);

        horizontalLayout_7->addWidget(rangelabel);

        range_slider = new QSlider(page);
        range_slider->setObjectName(QString::fromUtf8("range_slider"));
        sizePolicy1.setHeightForWidth(range_slider->sizePolicy().hasHeightForWidth());
        range_slider->setSizePolicy(sizePolicy1);
        range_slider->setMaximum(2000);
        range_slider->setSingleStep(50);
        range_slider->setPageStep(500);
        range_slider->setValue(1500);
        range_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(range_slider);

        range_value = new QLabel(page);
        range_value->setObjectName(QString::fromUtf8("range_value"));
        range_value->setFont(font3);
        range_value->setMargin(5);
        range_value->setIndent(10);

        horizontalLayout_7->addWidget(range_value);

        label_2 = new QLabel(page);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font3);

        horizontalLayout_7->addWidget(label_2);


        verticalLayout_5->addLayout(horizontalLayout_7);


        verticalLayout->addLayout(verticalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        full_rb = new QRadioButton(page);
        full_rb->setObjectName(QString::fromUtf8("full_rb"));
        full_rb->setChecked(true);

        horizontalLayout->addWidget(full_rb);

        half_rb = new QRadioButton(page);
        half_rb->setObjectName(QString::fromUtf8("half_rb"));

        horizontalLayout->addWidget(half_rb);

        hea_rb = new QRadioButton(page);
        hea_rb->setObjectName(QString::fromUtf8("hea_rb"));

        horizontalLayout->addWidget(hea_rb);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(14, 268, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        defaultBtn = new QPushButton(page);
        defaultBtn->setObjectName(QString::fromUtf8("defaultBtn"));

        horizontalLayout_8->addWidget(defaultBtn);


        verticalLayout->addLayout(horizontalLayout_8);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        init_toolbox->addItem(page, QString::fromUtf8("\346\211\253\346\217\217\345\217\202\346\225\260"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 287, 475));
        init_toolbox->addItem(page_2, QString::fromUtf8("Kinfu\345\217\202\346\225\260"));
        mainTab->addTab(initiation, QString());
        scan = new QWidget();
        scan->setObjectName(QString::fromUtf8("scan"));
        gridLayout_3 = new QGridLayout(scan);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        fusionViewer = new glViewer(scan);
        fusionViewer->setObjectName(QString::fromUtf8("fusionViewer"));
        sizePolicy.setHeightForWidth(fusionViewer->sizePolicy().hasHeightForWidth());
        fusionViewer->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(fusionViewer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        depthViewer = new glViewer(scan);
        depthViewer->setObjectName(QString::fromUtf8("depthViewer"));
        sizePolicy.setHeightForWidth(depthViewer->sizePolicy().hasHeightForWidth());
        depthViewer->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(depthViewer);

        RGBViewer = new glViewer(scan);
        RGBViewer->setObjectName(QString::fromUtf8("RGBViewer"));
        sizePolicy.setHeightForWidth(RGBViewer->sizePolicy().hasHeightForWidth());
        RGBViewer->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(RGBViewer);

        deviceViewer = new glViewer(scan);
        deviceViewer->setObjectName(QString::fromUtf8("deviceViewer"));
        sizePolicy.setHeightForWidth(deviceViewer->sizePolicy().hasHeightForWidth());
        deviceViewer->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(deviceViewer);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalLayout_3->setStretch(0, 2);
        verticalLayout_3->setStretch(1, 1);

        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(scan);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_4->addWidget(textEdit, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        recordBtn = new QPushButton(scan);
        recordBtn->setObjectName(QString::fromUtf8("recordBtn"));
        recordBtn->setCheckable(true);
        recordBtn->setAutoDefault(false);
        recordBtn->setDefault(true);

        verticalLayout_2->addWidget(recordBtn);

        stopBtn = new QPushButton(scan);
        stopBtn->setObjectName(QString::fromUtf8("stopBtn"));

        verticalLayout_2->addWidget(stopBtn);

        deleteBtn = new QPushButton(scan);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));

        verticalLayout_2->addWidget(deleteBtn);

        showCloudBtn = new QPushButton(scan);
        showCloudBtn->setObjectName(QString::fromUtf8("showCloudBtn"));

        verticalLayout_2->addWidget(showCloudBtn);


        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalLayout_4->setStretch(0, 3);
        horizontalLayout_4->setStretch(1, 1);

        gridLayout_3->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        mainTab->addTab(scan, QString());
        reconstruction = new QWidget();
        reconstruction->setObjectName(QString::fromUtf8("reconstruction"));
        gridLayout_5 = new QGridLayout(reconstruction);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        init_viewer_6 = new glViewer(reconstruction);
        init_viewer_6->setObjectName(QString::fromUtf8("init_viewer_6"));
        sizePolicy.setHeightForWidth(init_viewer_6->sizePolicy().hasHeightForWidth());
        init_viewer_6->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(init_viewer_6);

        groupBox_2 = new QGroupBox(reconstruction);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        toolBox = new QToolBox(groupBox_2);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font4.setPointSize(11);
        font4.setBold(false);
        font4.setWeight(50);
        toolBox->setFont(font4);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 98, 28));
        pushButton = new QPushButton(page_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 40, 171, 71));
        pushButton_2 = new QPushButton(page_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(50, 150, 171, 71));
        toolBox->addItem(page_3, QString::fromUtf8("\346\223\215\344\275\234"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 98, 28));
        toolBox->addItem(page_4, QString::fromUtf8("\351\207\215\345\273\272\345\217\202\346\225\260"));

        gridLayout_6->addWidget(toolBox, 0, 1, 1, 1);


        horizontalLayout_2->addWidget(groupBox_2);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 1);

        gridLayout_5->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        mainTab->addTab(reconstruction, QString());
        process = new QWidget();
        process->setObjectName(QString::fromUtf8("process"));
        gridLayout_7 = new QGridLayout(process);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        init_viewer_2 = new glViewer(process);
        init_viewer_2->setObjectName(QString::fromUtf8("init_viewer_2"));
        sizePolicy.setHeightForWidth(init_viewer_2->sizePolicy().hasHeightForWidth());
        init_viewer_2->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(init_viewer_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox_3 = new QGroupBox(process);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_8 = new QGridLayout(groupBox_3);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        toolBox_2 = new QToolBox(groupBox_3);
        toolBox_2->setObjectName(QString::fromUtf8("toolBox_2"));
        QFont font5;
        font5.setPointSize(11);
        font5.setBold(false);
        font5.setWeight(50);
        toolBox_2->setFont(font5);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        page_5->setGeometry(QRect(0, 0, 98, 28));
        toolBox_2->addItem(page_5, QString::fromUtf8("\346\250\241\345\236\213\347\256\200\345\214\226"));
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        page_6->setGeometry(QRect(0, 0, 98, 28));
        toolBox_2->addItem(page_6, QString::fromUtf8("\347\224\237\346\210\220\345\256\236\344\275\223\346\250\241\345\236\213"));
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        page_7->setGeometry(QRect(0, 0, 98, 28));
        toolBox_2->addItem(page_7, QString::fromUtf8("\344\277\256\350\241\245\345\255\224\346\264\236"));

        gridLayout_8->addWidget(toolBox_2, 0, 0, 1, 1);


        verticalLayout_4->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(process);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));

        verticalLayout_4->addWidget(groupBox_4);

        verticalLayout_4->setStretch(0, 2);
        verticalLayout_4->setStretch(1, 1);

        horizontalLayout_5->addLayout(verticalLayout_4);

        horizontalLayout_5->setStretch(0, 2);
        horizontalLayout_5->setStretch(1, 1);

        gridLayout_7->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        mainTab->addTab(process, QString());

        gridLayout->addWidget(mainTab, 0, 0, 1, 1);

        mainformClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainformClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 922, 23));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        mainformClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainformClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy2);
        mainToolBar->setIconSize(QSize(32, 32));
        mainformClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainformClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        mainformClass->setStatusBar(statusBar);
        toolBar = new QToolBar(mainformClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        mainformClass->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu->menuAction());
        menu_2->addAction(ToolstartBtn);
        menu_2->addAction(ToolstopBtn);
        menu_2->addAction(TooldeleteBtn);
        menu->addAction(actionSaveCloud);
        mainToolBar->addAction(connectKinect);
        mainToolBar->addAction(connectlifter);
        mainToolBar->addSeparator();
        toolBar->addAction(ToolstartBtn);
        toolBar->addAction(ToolstopBtn);
        toolBar->addAction(TooldeleteBtn);
        toolBar->addSeparator();
        toolBar->addAction(actionSaveCloud);

        retranslateUi(mainformClass);
        QObject::connect(delay_slider, SIGNAL(valueChanged(int)), delay_value, SLOT(setNum(int)));
        QObject::connect(range_slider, SIGNAL(valueChanged(int)), range_value, SLOT(setNum(int)));

        mainTab->setCurrentIndex(0);
        init_toolbox->setCurrentIndex(1);
        toolBox->setCurrentIndex(0);
        toolBox_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainformClass);
    } // setupUi

    void retranslateUi(QMainWindow *mainformClass)
    {
        mainformClass->setWindowTitle(QApplication::translate("mainformClass", "mainform", 0, QApplication::UnicodeUTF8));
        connectKinect->setText(QApplication::translate("mainformClass", "\350\277\236\346\216\245Kinect", 0, QApplication::UnicodeUTF8));
        connectlifter->setText(QApplication::translate("mainformClass", "\350\277\236\346\216\245\345\215\207\351\231\215\345\217\260", 0, QApplication::UnicodeUTF8));
        ToolstartBtn->setText(QApplication::translate("mainformClass", "\345\274\200\345\247\213", 0, QApplication::UnicodeUTF8));
        ToolstopBtn->setText(QApplication::translate("mainformClass", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
        TooldeleteBtn->setText(QApplication::translate("mainformClass", "\346\270\205\351\231\244", 0, QApplication::UnicodeUTF8));
        actionSaveCloud->setText(QApplication::translate("mainformClass", "\344\277\235\345\255\230\347\202\271\344\272\221", 0, QApplication::UnicodeUTF8));
        delaylabel->setText(QApplication::translate("mainformClass", "\345\220\257\345\212\250\345\273\266\346\227\266", 0, QApplication::UnicodeUTF8));
        delay_value->setText(QApplication::translate("mainformClass", "5", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mainformClass", "s", 0, QApplication::UnicodeUTF8));
        rangelabel->setText(QApplication::translate("mainformClass", "\346\211\253\346\217\217\350\214\203\345\233\264", 0, QApplication::UnicodeUTF8));
        range_value->setText(QApplication::translate("mainformClass", "1500", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("mainformClass", "mm", 0, QApplication::UnicodeUTF8));
        full_rb->setText(QApplication::translate("mainformClass", "\345\205\250\350\272\253", 0, QApplication::UnicodeUTF8));
        half_rb->setText(QApplication::translate("mainformClass", "\345\215\212\350\272\253", 0, QApplication::UnicodeUTF8));
        hea_rb->setText(QApplication::translate("mainformClass", "\345\244\264\345\203\217", 0, QApplication::UnicodeUTF8));
        defaultBtn->setText(QApplication::translate("mainformClass", "\346\201\242\345\244\215\351\273\230\350\256\244", 0, QApplication::UnicodeUTF8));
        init_toolbox->setItemText(init_toolbox->indexOf(page), QApplication::translate("mainformClass", "\346\211\253\346\217\217\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        init_toolbox->setItemText(init_toolbox->indexOf(page_2), QApplication::translate("mainformClass", "Kinfu\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        mainTab->setTabText(mainTab->indexOf(initiation), QApplication::translate("mainformClass", "\345\210\235\345\247\213\345\214\226", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("mainformClass", "\346\216\247\345\210\266\345\217\260\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        recordBtn->setText(QApplication::translate("mainformClass", "\345\274\200\345\247\213", 0, QApplication::UnicodeUTF8));
        stopBtn->setText(QApplication::translate("mainformClass", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
        deleteBtn->setText(QApplication::translate("mainformClass", "\346\270\205\351\231\244", 0, QApplication::UnicodeUTF8));
        showCloudBtn->setText(QApplication::translate("mainformClass", "\346\230\276\347\244\272\347\202\271\344\272\221", 0, QApplication::UnicodeUTF8));
        mainTab->setTabText(mainTab->indexOf(scan), QApplication::translate("mainformClass", "\346\211\253\346\217\217", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        pushButton->setText(QApplication::translate("mainformClass", "\351\207\215\345\273\272", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("mainformClass", "\345\244\215\344\275\215", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("mainformClass", "\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("mainformClass", "\351\207\215\345\273\272\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        mainTab->setTabText(mainTab->indexOf(reconstruction), QApplication::translate("mainformClass", "\344\270\211\347\273\264\351\207\215\345\273\272", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("mainformClass", "\346\250\241\345\236\213\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        toolBox_2->setItemText(toolBox_2->indexOf(page_5), QApplication::translate("mainformClass", "\346\250\241\345\236\213\347\256\200\345\214\226", 0, QApplication::UnicodeUTF8));
        toolBox_2->setItemText(toolBox_2->indexOf(page_6), QApplication::translate("mainformClass", "\347\224\237\346\210\220\345\256\236\344\275\223\346\250\241\345\236\213", 0, QApplication::UnicodeUTF8));
        toolBox_2->setItemText(toolBox_2->indexOf(page_7), QApplication::translate("mainformClass", "\344\277\256\350\241\245\345\255\224\346\264\236", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("mainformClass", "\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        mainTab->setTabText(mainTab->indexOf(process), QApplication::translate("mainformClass", "\345\220\216\345\244\204\347\220\206", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("mainformClass", "\346\211\253\346\217\217", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("mainformClass", "\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("mainformClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainformClass: public Ui_mainformClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
