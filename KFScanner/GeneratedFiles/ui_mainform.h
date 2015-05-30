/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created: Thu May 28 15:40:48 2015
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
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
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
    QAction *action_ResetKinFuParams;
    QAction *action_ResetScanParams;
    QAction *action;
    QAction *actionKinect;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_9;
    QTabWidget *mainTab;
    QWidget *initiation;
    QGridLayout *gridLayout_15;
    QToolBox *init_toolbox;
    QWidget *page;
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
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_16;
    QLabel *label_21;
    QLabel *label_29;
    QLabel *device_info;
    QLabel *label_31;
    QHBoxLayout *horizontalLayout_10;
    QLabel *ram_info;
    QLabel *label_35;
    QLabel *core_info;
    QLabel *label_33;
    QLabel *driver_info;
    QLabel *computeCap;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QSpinBox *R_segment_sb;
    QSpinBox *a_speed_sb;
    QSpinBox *speed_sb;
    QLabel *label_11;
    QSpinBox *segment_sb;
    QLabel *label_20;
    QLabel *label_9;
    QWidget *page_2;
    QGridLayout *gridLayout_14;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_13;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_13;
    QLabel *res_value_label;
    QSpacerItem *verticalSpacer_4;
    QGridLayout *gridLayout_12;
    QSpacerItem *horizontalSpacer_14;
    QLabel *size_label;
    QLabel *dims_label;
    QLabel *label_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *verticalSpacer_3;
    QGridLayout *gridLayout_9;
    QLabel *label_7;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QDoubleSpinBox *sigma_spatial_sb;
    QDoubleSpinBox *sigma_depth_sb;
    QDoubleSpinBox *sigma_k_size_sb;
    QLabel *label_6;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_10;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_5;
    QDoubleSpinBox *ICP_depthdist_sb;
    QDoubleSpinBox *ICP_dist_th_sb;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_6;
    QDoubleSpinBox *ICP_angel_th_sb;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_7;
    QGridLayout *gridLayout_11;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_8;
    QDoubleSpinBox *cam_min_move_sb;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_9;
    QDoubleSpinBox *tsdf_dist_sb;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_10;
    QDoubleSpinBox *tsdf_max_weight_sb;
    QLabel *label_19;
    QSpacerItem *horizontalSpacer_11;
    QDoubleSpinBox *raycast_factor_sb;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_12;
    QDoubleSpinBox *gradient_factor_sb;
    glViewer *init_viewer;
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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_22;
    QSpacerItem *horizontalSpacer;
    QLabel *fps;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_4;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QProgressBar *progressBar_2;
    QLabel *speed;
    QLabel *angular_speed;
    QLabel *segment;
    QLabel *R_segement;
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
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *mainformClass)
    {
        if (mainformClass->objectName().isEmpty())
            mainformClass->setObjectName(QString::fromUtf8("mainformClass"));
        mainformClass->resize(1148, 771);
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
        action_ResetKinFuParams = new QAction(mainformClass);
        action_ResetKinFuParams->setObjectName(QString::fromUtf8("action_ResetKinFuParams"));
        action_ResetScanParams = new QAction(mainformClass);
        action_ResetScanParams->setObjectName(QString::fromUtf8("action_ResetScanParams"));
        action = new QAction(mainformClass);
        action->setObjectName(QString::fromUtf8("action"));
        actionKinect = new QAction(mainformClass);
        actionKinect->setObjectName(QString::fromUtf8("actionKinect"));
        centralWidget = new QWidget(mainformClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_9 = new QHBoxLayout(centralWidget);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
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
        gridLayout_15 = new QGridLayout(initiation);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        init_toolbox = new QToolBox(initiation);
        init_toolbox->setObjectName(QString::fromUtf8("init_toolbox"));
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
        page->setGeometry(QRect(0, 0, 273, 529));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
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
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(delay_slider->sizePolicy().hasHeightForWidth());
        delay_slider->setSizePolicy(sizePolicy);
        delay_slider->setMinimumSize(QSize(25, 0));
        delay_slider->setMaximum(15);
        delay_slider->setPageStep(5);
        delay_slider->setValue(0);
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
        sizePolicy.setHeightForWidth(range_slider->sizePolicy().hasHeightForWidth());
        range_slider->setSizePolicy(sizePolicy);
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

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        groupBox_7 = new QGroupBox(page);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setFont(font3);
        gridLayout_16 = new QGridLayout(groupBox_7);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        label_21 = new QLabel(groupBox_7);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_16->addWidget(label_21, 2, 0, 1, 1);

        label_29 = new QLabel(groupBox_7);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_16->addWidget(label_29, 0, 0, 1, 1);

        device_info = new QLabel(groupBox_7);
        device_info->setObjectName(QString::fromUtf8("device_info"));
        device_info->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(device_info, 0, 1, 1, 1);

        label_31 = new QLabel(groupBox_7);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_16->addWidget(label_31, 1, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        ram_info = new QLabel(groupBox_7);
        ram_info->setObjectName(QString::fromUtf8("ram_info"));
        ram_info->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(ram_info);

        label_35 = new QLabel(groupBox_7);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(label_35);

        core_info = new QLabel(groupBox_7);
        core_info->setObjectName(QString::fromUtf8("core_info"));
        core_info->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(core_info);


        gridLayout_16->addLayout(horizontalLayout_10, 1, 1, 1, 1);

        label_33 = new QLabel(groupBox_7);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_16->addWidget(label_33, 4, 0, 1, 1);

        driver_info = new QLabel(groupBox_7);
        driver_info->setObjectName(QString::fromUtf8("driver_info"));
        driver_info->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(driver_info, 4, 1, 1, 1);

        computeCap = new QLabel(groupBox_7);
        computeCap->setObjectName(QString::fromUtf8("computeCap"));
        computeCap->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(computeCap, 2, 1, 1, 1);


        verticalLayout->addWidget(groupBox_7);

        groupBox_5 = new QGroupBox(page);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setFont(font3);
        gridLayout_2 = new QGridLayout(groupBox_5);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        R_segment_sb = new QSpinBox(groupBox_5);
        R_segment_sb->setObjectName(QString::fromUtf8("R_segment_sb"));

        gridLayout_2->addWidget(R_segment_sb, 3, 1, 1, 1);

        a_speed_sb = new QSpinBox(groupBox_5);
        a_speed_sb->setObjectName(QString::fromUtf8("a_speed_sb"));

        gridLayout_2->addWidget(a_speed_sb, 1, 1, 1, 1);

        speed_sb = new QSpinBox(groupBox_5);
        speed_sb->setObjectName(QString::fromUtf8("speed_sb"));

        gridLayout_2->addWidget(speed_sb, 0, 1, 1, 1);

        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 2, 0, 1, 1);

        segment_sb = new QSpinBox(groupBox_5);
        segment_sb->setObjectName(QString::fromUtf8("segment_sb"));

        gridLayout_2->addWidget(segment_sb, 2, 1, 1, 1);

        label_20 = new QLabel(groupBox_5);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_2->addWidget(label_20, 3, 0, 1, 1);

        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_5);

        init_toolbox->addItem(page, QString::fromUtf8("\346\211\253\346\217\217\345\217\202\346\225\260"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 202, 464));
        gridLayout_14 = new QGridLayout(page_2);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setSpacing(6);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font3);

        gridLayout_13->addWidget(label_3, 0, 0, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_13, 0, 1, 1, 1);

        res_value_label = new QLabel(page_2);
        res_value_label->setObjectName(QString::fromUtf8("res_value_label"));
        res_value_label->setFont(font3);
        res_value_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_13->addWidget(res_value_label, 0, 2, 1, 1);


        verticalLayout_6->addLayout(gridLayout_13);

        verticalSpacer_4 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setSpacing(6);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_14, 0, 1, 1, 1);

        size_label = new QLabel(page_2);
        size_label->setObjectName(QString::fromUtf8("size_label"));
        size_label->setFont(font3);
        size_label->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(size_label, 1, 2, 1, 1);

        dims_label = new QLabel(page_2);
        dims_label->setObjectName(QString::fromUtf8("dims_label"));
        dims_label->setFont(font3);
        dims_label->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(dims_label, 0, 2, 1, 1);

        label_4 = new QLabel(page_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font3);

        gridLayout_12->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(page_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font3);

        gridLayout_12->addWidget(label_5, 1, 0, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_15, 1, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_12);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_7 = new QLabel(page_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font3);

        gridLayout_9->addWidget(label_7, 1, 0, 1, 1);

        label_8 = new QLabel(page_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font3);

        gridLayout_9->addWidget(label_8, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_4, 2, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        sigma_spatial_sb = new QDoubleSpinBox(page_2);
        sigma_spatial_sb->setObjectName(QString::fromUtf8("sigma_spatial_sb"));
        sigma_spatial_sb->setFont(font3);
        sigma_spatial_sb->setMaximum(10);
        sigma_spatial_sb->setSingleStep(0.1);
        sigma_spatial_sb->setValue(4.5);

        gridLayout_9->addWidget(sigma_spatial_sb, 1, 2, 1, 1);

        sigma_depth_sb = new QDoubleSpinBox(page_2);
        sigma_depth_sb->setObjectName(QString::fromUtf8("sigma_depth_sb"));
        sigma_depth_sb->setFont(font3);
        sigma_depth_sb->setMaximum(1);
        sigma_depth_sb->setSingleStep(0.01);
        sigma_depth_sb->setValue(0.04);

        gridLayout_9->addWidget(sigma_depth_sb, 0, 2, 1, 1);

        sigma_k_size_sb = new QDoubleSpinBox(page_2);
        sigma_k_size_sb->setObjectName(QString::fromUtf8("sigma_k_size_sb"));
        sigma_k_size_sb->setFont(font3);
        sigma_k_size_sb->setMaximum(20);
        sigma_k_size_sb->setValue(7);

        gridLayout_9->addWidget(sigma_k_size_sb, 2, 2, 1, 1);

        label_6 = new QLabel(page_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font3);

        gridLayout_9->addWidget(label_6, 0, 0, 1, 1);


        verticalLayout_6->addLayout(gridLayout_9);

        verticalSpacer = new QSpacerItem(13, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_12 = new QLabel(page_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font3);

        gridLayout_10->addWidget(label_12, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_5, 0, 1, 2, 1);

        ICP_depthdist_sb = new QDoubleSpinBox(page_2);
        ICP_depthdist_sb->setObjectName(QString::fromUtf8("ICP_depthdist_sb"));
        ICP_depthdist_sb->setFont(font3);

        gridLayout_10->addWidget(ICP_depthdist_sb, 0, 2, 1, 1);

        ICP_dist_th_sb = new QDoubleSpinBox(page_2);
        ICP_dist_th_sb->setObjectName(QString::fromUtf8("ICP_dist_th_sb"));
        ICP_dist_th_sb->setFont(font3);
        ICP_dist_th_sb->setSingleStep(0.1);
        ICP_dist_th_sb->setValue(0.1);

        gridLayout_10->addWidget(ICP_dist_th_sb, 1, 2, 2, 1);

        label_13 = new QLabel(page_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font3);

        gridLayout_10->addWidget(label_13, 2, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_6, 2, 1, 2, 1);

        ICP_angel_th_sb = new QDoubleSpinBox(page_2);
        ICP_angel_th_sb->setObjectName(QString::fromUtf8("ICP_angel_th_sb"));
        ICP_angel_th_sb->setFont(font3);
        ICP_angel_th_sb->setMaximum(360);
        ICP_angel_th_sb->setSingleStep(0.01);
        ICP_angel_th_sb->setValue(30);

        gridLayout_10->addWidget(ICP_angel_th_sb, 3, 2, 2, 1);

        label_14 = new QLabel(page_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font3);

        gridLayout_10->addWidget(label_14, 4, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_7, 4, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_10);

        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(6);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_16 = new QLabel(page_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font3);

        gridLayout_11->addWidget(label_16, 0, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_8, 0, 1, 1, 1);

        cam_min_move_sb = new QDoubleSpinBox(page_2);
        cam_min_move_sb->setObjectName(QString::fromUtf8("cam_min_move_sb"));
        cam_min_move_sb->setFont(font3);

        gridLayout_11->addWidget(cam_min_move_sb, 0, 2, 1, 1);

        label_17 = new QLabel(page_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font3);

        gridLayout_11->addWidget(label_17, 1, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_9, 1, 1, 1, 1);

        tsdf_dist_sb = new QDoubleSpinBox(page_2);
        tsdf_dist_sb->setObjectName(QString::fromUtf8("tsdf_dist_sb"));
        tsdf_dist_sb->setFont(font3);
        tsdf_dist_sb->setMaximum(1);
        tsdf_dist_sb->setSingleStep(0.01);
        tsdf_dist_sb->setValue(0.04);

        gridLayout_11->addWidget(tsdf_dist_sb, 1, 2, 1, 1);

        label_15 = new QLabel(page_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font3);

        gridLayout_11->addWidget(label_15, 2, 0, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_10, 2, 1, 1, 1);

        tsdf_max_weight_sb = new QDoubleSpinBox(page_2);
        tsdf_max_weight_sb->setObjectName(QString::fromUtf8("tsdf_max_weight_sb"));
        tsdf_max_weight_sb->setFont(font3);
        tsdf_max_weight_sb->setValue(64);

        gridLayout_11->addWidget(tsdf_max_weight_sb, 2, 2, 1, 1);

        label_19 = new QLabel(page_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font3);

        gridLayout_11->addWidget(label_19, 3, 0, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_11, 3, 1, 2, 1);

        raycast_factor_sb = new QDoubleSpinBox(page_2);
        raycast_factor_sb->setObjectName(QString::fromUtf8("raycast_factor_sb"));
        raycast_factor_sb->setFont(font3);
        raycast_factor_sb->setMaximum(1);
        raycast_factor_sb->setSingleStep(0.01);
        raycast_factor_sb->setValue(0.75);

        gridLayout_11->addWidget(raycast_factor_sb, 3, 2, 2, 1);

        label_18 = new QLabel(page_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font3);

        gridLayout_11->addWidget(label_18, 4, 0, 2, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_12, 5, 1, 1, 1);

        gradient_factor_sb = new QDoubleSpinBox(page_2);
        gradient_factor_sb->setObjectName(QString::fromUtf8("gradient_factor_sb"));
        gradient_factor_sb->setFont(font3);
        gradient_factor_sb->setMaximum(1);
        gradient_factor_sb->setSingleStep(0.1);
        gradient_factor_sb->setValue(0.5);

        gridLayout_11->addWidget(gradient_factor_sb, 5, 2, 1, 1);


        verticalLayout_6->addLayout(gridLayout_11);


        verticalLayout_7->addLayout(verticalLayout_6);


        gridLayout_14->addLayout(verticalLayout_7, 0, 0, 1, 1);

        init_toolbox->addItem(page_2, QString::fromUtf8("Kinfu\345\217\202\346\225\260"));

        gridLayout_15->addWidget(init_toolbox, 0, 1, 1, 1);

        init_viewer = new glViewer(initiation);
        init_viewer->setObjectName(QString::fromUtf8("init_viewer"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(init_viewer->sizePolicy().hasHeightForWidth());
        init_viewer->setSizePolicy(sizePolicy1);

        gridLayout_15->addWidget(init_viewer, 0, 0, 1, 1);

        gridLayout_15->setColumnStretch(0, 3);
        gridLayout_15->setColumnStretch(1, 1);
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
        sizePolicy1.setHeightForWidth(fusionViewer->sizePolicy().hasHeightForWidth());
        fusionViewer->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(fusionViewer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        depthViewer = new glViewer(scan);
        depthViewer->setObjectName(QString::fromUtf8("depthViewer"));
        sizePolicy1.setHeightForWidth(depthViewer->sizePolicy().hasHeightForWidth());
        depthViewer->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(depthViewer);

        RGBViewer = new glViewer(scan);
        RGBViewer->setObjectName(QString::fromUtf8("RGBViewer"));
        sizePolicy1.setHeightForWidth(RGBViewer->sizePolicy().hasHeightForWidth());
        RGBViewer->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(RGBViewer);

        deviceViewer = new glViewer(scan);
        deviceViewer->setObjectName(QString::fromUtf8("deviceViewer"));
        sizePolicy1.setHeightForWidth(deviceViewer->sizePolicy().hasHeightForWidth());
        deviceViewer->setSizePolicy(sizePolicy1);

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
        groupBox->setFont(font2);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 36, 251, 31));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        QFont font4;
        font4.setBold(false);
        font4.setWeight(50);
        label_22->setFont(font4);

        horizontalLayout_8->addWidget(label_22);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        fps = new QLabel(layoutWidget);
        fps->setObjectName(QString::fromUtf8("fps"));
        fps->setFont(font4);

        horizontalLayout_8->addWidget(fps);


        verticalLayout_2->addWidget(groupBox);

        groupBox_6 = new QGroupBox(scan);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setFont(font2);
        gridLayout_4 = new QGridLayout(groupBox_6);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_23 = new QLabel(groupBox_6);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_4->addWidget(label_23, 1, 0, 1, 1);

        label_24 = new QLabel(groupBox_6);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_4->addWidget(label_24, 2, 0, 1, 1);

        label_25 = new QLabel(groupBox_6);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_4->addWidget(label_25, 3, 0, 1, 1);

        label_26 = new QLabel(groupBox_6);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_4->addWidget(label_26, 0, 0, 1, 1);

        label_27 = new QLabel(groupBox_6);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_4->addWidget(label_27, 4, 0, 1, 1);

        progressBar_2 = new QProgressBar(groupBox_6);
        progressBar_2->setObjectName(QString::fromUtf8("progressBar_2"));
        progressBar_2->setValue(0);
        progressBar_2->setTextVisible(false);
        progressBar_2->setTextDirection(QProgressBar::TopToBottom);

        gridLayout_4->addWidget(progressBar_2, 4, 1, 1, 1);

        speed = new QLabel(groupBox_6);
        speed->setObjectName(QString::fromUtf8("speed"));
        speed->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(speed, 0, 1, 1, 1);

        angular_speed = new QLabel(groupBox_6);
        angular_speed->setObjectName(QString::fromUtf8("angular_speed"));
        angular_speed->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(angular_speed, 1, 1, 1, 1);

        segment = new QLabel(groupBox_6);
        segment->setObjectName(QString::fromUtf8("segment"));
        segment->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(segment, 2, 1, 1, 1);

        R_segement = new QLabel(groupBox_6);
        R_segement->setObjectName(QString::fromUtf8("R_segement"));
        R_segement->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(R_segement, 3, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_6);

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
        sizePolicy1.setHeightForWidth(init_viewer_6->sizePolicy().hasHeightForWidth());
        init_viewer_6->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(init_viewer_6);

        groupBox_2 = new QGroupBox(reconstruction);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        toolBox = new QToolBox(groupBox_2);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font5.setPointSize(11);
        font5.setBold(false);
        font5.setWeight(50);
        toolBox->setFont(font5);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 346, 519));
        pushButton = new QPushButton(page_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(80, 40, 171, 71));
        pushButton_2 = new QPushButton(page_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(80, 150, 171, 71));
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
        sizePolicy1.setHeightForWidth(init_viewer_2->sizePolicy().hasHeightForWidth());
        init_viewer_2->setSizePolicy(sizePolicy1);

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
        QFont font6;
        font6.setPointSize(11);
        font6.setBold(false);
        font6.setWeight(50);
        toolBox_2->setFont(font6);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        page_5->setGeometry(QRect(0, 0, 344, 251));
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

        horizontalLayout_9->addWidget(mainTab);

        mainformClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainformClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1148, 23));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
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
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu_2->addAction(ToolstartBtn);
        menu_2->addAction(ToolstopBtn);
        menu_2->addAction(TooldeleteBtn);
        menu->addAction(actionSaveCloud);
        menu_3->addAction(action_ResetKinFuParams);
        menu_3->addAction(action_ResetScanParams);
        menu_4->addAction(action);
        menu_4->addAction(actionKinect);
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

        mainTab->setCurrentIndex(3);
        init_toolbox->setCurrentIndex(0);
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
        action_ResetKinFuParams->setText(QApplication::translate("mainformClass", "\351\207\215\347\275\256KinFu\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        action_ResetScanParams->setText(QApplication::translate("mainformClass", "\351\207\215\347\275\256\346\211\253\346\217\217\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("mainformClass", "GPU\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        actionKinect->setText(QApplication::translate("mainformClass", "Kinect\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        delaylabel->setText(QApplication::translate("mainformClass", "\345\220\257\345\212\250\345\273\266\346\227\266", 0, QApplication::UnicodeUTF8));
        delay_value->setText(QApplication::translate("mainformClass", "0", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mainformClass", "s", 0, QApplication::UnicodeUTF8));
        rangelabel->setText(QApplication::translate("mainformClass", "\346\211\253\346\217\217\350\214\203\345\233\264", 0, QApplication::UnicodeUTF8));
        range_value->setText(QApplication::translate("mainformClass", "1500", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("mainformClass", "mm", 0, QApplication::UnicodeUTF8));
        full_rb->setText(QApplication::translate("mainformClass", "\345\205\250\350\272\253", 0, QApplication::UnicodeUTF8));
        half_rb->setText(QApplication::translate("mainformClass", "\345\215\212\350\272\253", 0, QApplication::UnicodeUTF8));
        hea_rb->setText(QApplication::translate("mainformClass", "\345\244\264\345\203\217", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("mainformClass", "GPU\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("mainformClass", "\350\256\241\347\256\227\350\203\275\345\212\233", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("mainformClass", "\345\275\223\345\211\215\350\256\276\345\244\207", 0, QApplication::UnicodeUTF8));
        device_info->setText(QApplication::translate("mainformClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("mainformClass", "\346\230\276\345\255\230/\346\240\270\346\225\260", 0, QApplication::UnicodeUTF8));
        ram_info->setText(QApplication::translate("mainformClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("mainformClass", "/", 0, QApplication::UnicodeUTF8));
        core_info->setText(QApplication::translate("mainformClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("mainformClass", "CUDA\347\211\210\346\234\254", 0, QApplication::UnicodeUTF8));
        driver_info->setText(QApplication::translate("mainformClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        computeCap->setText(QApplication::translate("mainformClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("mainformClass", "\345\215\207\351\231\215\345\217\260\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("mainformClass", "\350\247\222\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("mainformClass", "\345\236\202\347\233\264\345\210\206\346\256\265", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("mainformClass", "\345\234\206\345\221\250\345\210\206\346\256\265", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("mainformClass", "\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        init_toolbox->setItemText(init_toolbox->indexOf(page), QApplication::translate("mainformClass", "\346\211\253\346\217\217\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("mainformClass", "\345\210\206\350\276\250\347\216\207", 0, QApplication::UnicodeUTF8));
        res_value_label->setText(QApplication::translate("mainformClass", "0", 0, QApplication::UnicodeUTF8));
        size_label->setText(QApplication::translate("mainformClass", "0", 0, QApplication::UnicodeUTF8));
        dims_label->setText(QApplication::translate("mainformClass", "0", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("mainformClass", "\344\275\223\347\273\264\345\272\246", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("mainformClass", "\344\275\223\345\260\272\345\257\270", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("mainformClass", "\345\217\214\350\276\271sigma\347\251\272\351\227\264", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("mainformClass", "\345\217\214\350\276\271\346\240\270\345\244\247\345\260\217", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("mainformClass", "\345\217\214\350\276\271sigma\346\267\261\345\272\246", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("mainformClass", "ICP\346\210\252\346\226\255\346\267\261\345\272\246\350\267\235\347\246\273", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("mainformClass", "ICP\350\267\235\347\246\273\351\230\200\345\200\274", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("mainformClass", "ICP\350\247\222\345\272\246\351\230\200\345\200\274(\345\272\246)", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("mainformClass", "\346\221\204\345\203\217\346\234\272\346\234\200\345\260\217\344\275\215\347\247\273", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("mainformClass", "TSDF\346\210\252\346\226\255\350\267\235\347\246\273", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("mainformClass", "TSDF\346\234\200\345\244\247\351\207\215\351\207\217", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("mainformClass", "\345\205\211\347\205\247\346\255\245\351\225\277\345\233\240\346\225\260", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("mainformClass", "\346\242\257\345\272\246\345\217\230\345\214\226\345\233\240\346\225\260", 0, QApplication::UnicodeUTF8));
        init_toolbox->setItemText(init_toolbox->indexOf(page_2), QApplication::translate("mainformClass", "Kinfu\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        mainTab->setTabText(mainTab->indexOf(initiation), QApplication::translate("mainformClass", "\345\210\235\345\247\213\345\214\226", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("mainformClass", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("mainformClass", "FPS", 0, QApplication::UnicodeUTF8));
        fps->setText(QApplication::translate("mainformClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("mainformClass", "\345\215\207\351\231\215\345\217\260\345\217\202\346\225\260\345\217\212\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("mainformClass", "\350\247\222\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("mainformClass", "\345\236\202\347\233\264\345\210\206\346\256\265", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("mainformClass", "\345\234\206\345\221\250\345\210\206\346\256\265", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("mainformClass", "\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("mainformClass", "\346\211\253\346\217\217\350\277\233\345\272\246", 0, QApplication::UnicodeUTF8));
        progressBar_2->setFormat(QApplication::translate("mainformClass", "%p%", 0, QApplication::UnicodeUTF8));
        speed->setText(QApplication::translate("mainformClass", "0", 0, QApplication::UnicodeUTF8));
        angular_speed->setText(QApplication::translate("mainformClass", "0", 0, QApplication::UnicodeUTF8));
        segment->setText(QApplication::translate("mainformClass", "3", 0, QApplication::UnicodeUTF8));
        R_segement->setText(QApplication::translate("mainformClass", "3", 0, QApplication::UnicodeUTF8));
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
        menu_3->setTitle(QApplication::translate("mainformClass", "\351\207\215\347\275\256\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        menu_4->setTitle(QApplication::translate("mainformClass", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("mainformClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainformClass: public Ui_mainformClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
