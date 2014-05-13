/********************************************************************************
** Form generated from reading UI file 'miningpage.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MININGPAGE_H
#define UI_MININGPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MiningPage
{
public:
    QGridLayout *gridLayout;
    QLabel *typeLabel;
    QLabel *threadsLabel;
    QLabel *scantimeLabel;
    QPushButton *startButton;
    QComboBox *typeBox;
    QSpinBox *threadsBox;
    QSpinBox *scantimeBox;
    QCheckBox *debugCheckBox;
    QLabel *serverLabel;
    QLabel *portLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLineEdit *serverLine;
    QLineEdit *portLine;
    QLineEdit *usernameLine;
    QLineEdit *passwordLine;
    QFrame *line;
    QCustomPlot *qChart;
    QListWidget *list;
    QLabel *shareCount;
    QLabel *mineSpeedLabel;

    void setupUi(QWidget *MiningPage)
    {
        if (MiningPage->objectName().isEmpty())
            MiningPage->setObjectName(QString::fromUtf8("MiningPage"));
        MiningPage->resize(948, 551);
        gridLayout = new QGridLayout(MiningPage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        typeLabel = new QLabel(MiningPage);
        typeLabel->setObjectName(QString::fromUtf8("typeLabel"));

        gridLayout->addWidget(typeLabel, 0, 0, 1, 1);

        threadsLabel = new QLabel(MiningPage);
        threadsLabel->setObjectName(QString::fromUtf8("threadsLabel"));
        threadsLabel->setEnabled(true);

        gridLayout->addWidget(threadsLabel, 0, 1, 1, 1);

        scantimeLabel = new QLabel(MiningPage);
        scantimeLabel->setObjectName(QString::fromUtf8("scantimeLabel"));
        scantimeLabel->setEnabled(true);
        scantimeLabel->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(scantimeLabel, 0, 2, 1, 1);

        startButton = new QPushButton(MiningPage);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(startButton, 0, 3, 1, 1);

        typeBox = new QComboBox(MiningPage);
        typeBox->setObjectName(QString::fromUtf8("typeBox"));
        typeBox->setEditable(false);

        gridLayout->addWidget(typeBox, 1, 0, 1, 1);

        threadsBox = new QSpinBox(MiningPage);
        threadsBox->setObjectName(QString::fromUtf8("threadsBox"));
        threadsBox->setEnabled(true);
        threadsBox->setMinimum(1);
        threadsBox->setMaximum(99);
        threadsBox->setSingleStep(1);
        threadsBox->setValue(16);

        gridLayout->addWidget(threadsBox, 1, 1, 1, 1);

        scantimeBox = new QSpinBox(MiningPage);
        scantimeBox->setObjectName(QString::fromUtf8("scantimeBox"));
        scantimeBox->setEnabled(true);
        scantimeBox->setMinimum(1);
        scantimeBox->setValue(5);

        gridLayout->addWidget(scantimeBox, 1, 2, 1, 1);

        debugCheckBox = new QCheckBox(MiningPage);
        debugCheckBox->setObjectName(QString::fromUtf8("debugCheckBox"));

        gridLayout->addWidget(debugCheckBox, 1, 3, 1, 1);

        serverLabel = new QLabel(MiningPage);
        serverLabel->setObjectName(QString::fromUtf8("serverLabel"));
        serverLabel->setEnabled(true);

        gridLayout->addWidget(serverLabel, 2, 0, 1, 1);

        portLabel = new QLabel(MiningPage);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));
        portLabel->setEnabled(true);

        gridLayout->addWidget(portLabel, 2, 1, 1, 1);

        usernameLabel = new QLabel(MiningPage);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        usernameLabel->setEnabled(true);

        gridLayout->addWidget(usernameLabel, 2, 2, 1, 1);

        passwordLabel = new QLabel(MiningPage);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setEnabled(true);

        gridLayout->addWidget(passwordLabel, 2, 3, 1, 1);

        serverLine = new QLineEdit(MiningPage);
        serverLine->setObjectName(QString::fromUtf8("serverLine"));
        serverLine->setEnabled(true);

        gridLayout->addWidget(serverLine, 3, 0, 1, 1);

        portLine = new QLineEdit(MiningPage);
        portLine->setObjectName(QString::fromUtf8("portLine"));
        portLine->setEnabled(true);
        portLine->setProperty("value", QVariant(8669));

        gridLayout->addWidget(portLine, 3, 1, 1, 1);

        usernameLine = new QLineEdit(MiningPage);
        usernameLine->setObjectName(QString::fromUtf8("usernameLine"));
        usernameLine->setEnabled(true);

        gridLayout->addWidget(usernameLine, 3, 2, 1, 1);

        passwordLine = new QLineEdit(MiningPage);
        passwordLine->setObjectName(QString::fromUtf8("passwordLine"));
        passwordLine->setEnabled(true);

        gridLayout->addWidget(passwordLine, 3, 3, 1, 1);

        line = new QFrame(MiningPage);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setMinimumSize(QSize(0, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 4, 0, 1, 4);

        qChart = new QCustomPlot(MiningPage);
        qChart->setObjectName(QString::fromUtf8("qChart"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(qChart->sizePolicy().hasHeightForWidth());
        qChart->setSizePolicy(sizePolicy2);
        qChart->setAcceptDrops(false);

        gridLayout->addWidget(qChart, 5, 0, 1, 4);

        list = new QListWidget(MiningPage);
        list->setObjectName(QString::fromUtf8("list"));
        list->setAutoScrollMargin(100000);
        list->setDragDropMode(QAbstractItemView::DragOnly);
        list->setSelectionMode(QAbstractItemView::NoSelection);
        list->setMovement(QListView::Snap);
        list->setBatchSize(10);

        gridLayout->addWidget(list, 6, 0, 1, 4);

        shareCount = new QLabel(MiningPage);
        shareCount->setObjectName(QString::fromUtf8("shareCount"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        shareCount->setFont(font);

        gridLayout->addWidget(shareCount, 7, 0, 1, 1);

        mineSpeedLabel = new QLabel(MiningPage);
        mineSpeedLabel->setObjectName(QString::fromUtf8("mineSpeedLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(mineSpeedLabel->sizePolicy().hasHeightForWidth());
        mineSpeedLabel->setSizePolicy(sizePolicy3);
        mineSpeedLabel->setFont(font);
        mineSpeedLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(mineSpeedLabel, 7, 2, 1, 1);

        QWidget::setTabOrder(startButton, typeBox);
        QWidget::setTabOrder(typeBox, threadsBox);
        QWidget::setTabOrder(threadsBox, scantimeBox);
        QWidget::setTabOrder(scantimeBox, serverLine);
        QWidget::setTabOrder(serverLine, portLine);
        QWidget::setTabOrder(portLine, usernameLine);
        QWidget::setTabOrder(usernameLine, passwordLine);
        QWidget::setTabOrder(passwordLine, debugCheckBox);
        QWidget::setTabOrder(debugCheckBox, list);

        retranslateUi(MiningPage);

        typeBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MiningPage);
    } // setupUi

    void retranslateUi(QWidget *MiningPage)
    {
        MiningPage->setWindowTitle(QApplication::translate("MiningPage", "Mining", 0, QApplication::UnicodeUTF8));
        typeLabel->setText(QApplication::translate("MiningPage", "Type", 0, QApplication::UnicodeUTF8));
        threadsLabel->setText(QApplication::translate("MiningPage", "Threads", 0, QApplication::UnicodeUTF8));
        scantimeLabel->setText(QApplication::translate("MiningPage", "Scantime", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MiningPage", "Start Mining", 0, QApplication::UnicodeUTF8));
        typeBox->clear();
        typeBox->insertItems(0, QStringList()
         << QApplication::translate("MiningPage", "Solo Mining", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MiningPage", "Pool Mining", 0, QApplication::UnicodeUTF8)
        );
        debugCheckBox->setText(QApplication::translate("MiningPage", "Debug Logging", 0, QApplication::UnicodeUTF8));
        serverLabel->setText(QApplication::translate("MiningPage", "Server", 0, QApplication::UnicodeUTF8));
        portLabel->setText(QApplication::translate("MiningPage", "Port", 0, QApplication::UnicodeUTF8));
        usernameLabel->setText(QApplication::translate("MiningPage", "Payout Address", 0, QApplication::UnicodeUTF8));
        passwordLabel->setText(QApplication::translate("MiningPage", "Password", 0, QApplication::UnicodeUTF8));
        serverLine->setText(QString());
        portLine->setText(QString());
        usernameLine->setText(QString());
        passwordLine->setText(QApplication::translate("MiningPage", "x", 0, QApplication::UnicodeUTF8));
        shareCount->setText(QString());
        mineSpeedLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MiningPage: public Ui_MiningPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MININGPAGE_H
