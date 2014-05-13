/********************************************************************************
** Form generated from reading UI file 'overviewpage.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OVERVIEWPAGE_H
#define UI_OVERVIEWPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OverviewPage
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *labelAlerts;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_13;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_14;
    QLabel *label;
    QLabel *labelWalletStatus;
    QSpacerItem *horizontalSpacer_11;
    QFormLayout *formLayout_5;
    QLabel *label_15;
    QLabel *labelBalance;
    QLabel *label_16;
    QLabel *labelUnconfirmed;
    QLabel *labelImmatureText;
    QLabel *labelImmature;
    QSpacerItem *verticalSpacer_6;
    QFrame *frame_9;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_15;
    QFrame *frame_8;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_17;
    QLabel *labelTransactionsStatus;
    QSpacerItem *horizontalSpacer_12;
    QListView *listTransactions;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *OverviewPage)
    {
        if (OverviewPage->objectName().isEmpty())
            OverviewPage->setObjectName(QString::fromUtf8("OverviewPage"));
        OverviewPage->resize(945, 605);
        verticalLayout_2 = new QVBoxLayout(OverviewPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelAlerts = new QLabel(OverviewPage);
        labelAlerts->setObjectName(QString::fromUtf8("labelAlerts"));
        labelAlerts->setEnabled(true);
        labelAlerts->setVisible(false);
        labelAlerts->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop:0 #F0D0A0, stop:1 #F8D488); color:#000000;"));
        labelAlerts->setWordWrap(true);
        labelAlerts->setMargin(3);

        verticalLayout_2->addWidget(labelAlerts);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        frame_3 = new QFrame(OverviewPage);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_14 = new QVBoxLayout(frame_3);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_14 = new QLabel(frame_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_14->setFont(font);

        horizontalLayout_13->addWidget(label_14);

        label = new QLabel(frame_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_13->addWidget(label);

        labelWalletStatus = new QLabel(frame_3);
        labelWalletStatus->setObjectName(QString::fromUtf8("labelWalletStatus"));
        labelWalletStatus->setStyleSheet(QString::fromUtf8("QLabel { color: red; }"));
        labelWalletStatus->setText(QString::fromUtf8("(out of sync)"));
        labelWalletStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(labelWalletStatus);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_11);


        verticalLayout_14->addLayout(horizontalLayout_13);

        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        formLayout_5->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_5->setHorizontalSpacing(12);
        formLayout_5->setVerticalSpacing(12);
        label_15 = new QLabel(frame_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_15);

        labelBalance = new QLabel(frame_3);
        labelBalance->setObjectName(QString::fromUtf8("labelBalance"));
        labelBalance->setFont(font);
        labelBalance->setCursor(QCursor(Qt::IBeamCursor));
        labelBalance->setText(QString::fromUtf8("0 PRS"));
        labelBalance->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, labelBalance);

        label_16 = new QLabel(frame_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_16);

        labelUnconfirmed = new QLabel(frame_3);
        labelUnconfirmed->setObjectName(QString::fromUtf8("labelUnconfirmed"));
        labelUnconfirmed->setFont(font);
        labelUnconfirmed->setCursor(QCursor(Qt::IBeamCursor));
        labelUnconfirmed->setText(QString::fromUtf8("0 PRS"));
        labelUnconfirmed->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, labelUnconfirmed);

        labelImmatureText = new QLabel(frame_3);
        labelImmatureText->setObjectName(QString::fromUtf8("labelImmatureText"));

        formLayout_5->setWidget(2, QFormLayout::LabelRole, labelImmatureText);

        labelImmature = new QLabel(frame_3);
        labelImmature->setObjectName(QString::fromUtf8("labelImmature"));
        labelImmature->setFont(font);
        labelImmature->setText(QString::fromUtf8("0 PRS"));
        labelImmature->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        formLayout_5->setWidget(2, QFormLayout::FieldRole, labelImmature);


        verticalLayout_14->addLayout(formLayout_5);


        verticalLayout_13->addWidget(frame_3);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout_13->addItem(verticalSpacer_6);

        frame_9 = new QFrame(OverviewPage);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        frame_9->setFrameShape(QFrame::NoFrame);
        frame_9->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_9);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        verticalLayout_13->addWidget(frame_9);


        horizontalLayout_12->addLayout(verticalLayout_13);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        frame_8 = new QFrame(OverviewPage);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        verticalLayout_16 = new QVBoxLayout(frame_8);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_17 = new QLabel(frame_8);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_14->addWidget(label_17);

        labelTransactionsStatus = new QLabel(frame_8);
        labelTransactionsStatus->setObjectName(QString::fromUtf8("labelTransactionsStatus"));
        labelTransactionsStatus->setStyleSheet(QString::fromUtf8("QLabel { color: red; }"));
        labelTransactionsStatus->setText(QString::fromUtf8("(out of sync)"));
        labelTransactionsStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(labelTransactionsStatus);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_12);


        verticalLayout_16->addLayout(horizontalLayout_14);

        listTransactions = new QListView(frame_8);
        listTransactions->setObjectName(QString::fromUtf8("listTransactions"));
        listTransactions->setStyleSheet(QString::fromUtf8("QListView { background: transparent; }"));
        listTransactions->setFrameShape(QFrame::NoFrame);
        listTransactions->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listTransactions->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listTransactions->setSelectionMode(QAbstractItemView::NoSelection);

        verticalLayout_16->addWidget(listTransactions);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout_16->addItem(verticalSpacer_5);


        verticalLayout_15->addWidget(frame_8);


        horizontalLayout_12->addLayout(verticalLayout_15);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_12);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(OverviewPage);

        QMetaObject::connectSlotsByName(OverviewPage);
    } // setupUi

    void retranslateUi(QWidget *OverviewPage)
    {
        OverviewPage->setWindowTitle(QApplication::translate("OverviewPage", "Form", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("OverviewPage", "Wallet", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OverviewPage", "v1.1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelWalletStatus->setToolTip(QApplication::translate("OverviewPage", "The displayed information may be out of date. Your wallet automatically synchronizes with the Preiscoin network after a connection is established, but this process has not completed yet.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_15->setText(QApplication::translate("OverviewPage", "Balance:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelBalance->setToolTip(QApplication::translate("OverviewPage", "Your current balance", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_16->setText(QApplication::translate("OverviewPage", "Unconfirmed:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelUnconfirmed->setToolTip(QApplication::translate("OverviewPage", "Total of transactions that have yet to be confirmed, and do not yet count toward the current balance", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        labelImmatureText->setText(QApplication::translate("OverviewPage", "Immature:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelImmature->setToolTip(QApplication::translate("OverviewPage", "Mined balance that has not yet matured", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_17->setText(QApplication::translate("OverviewPage", "<b>Recent transactions</b>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelTransactionsStatus->setToolTip(QApplication::translate("OverviewPage", "The displayed information may be out of date. Your wallet automatically synchronizes with the Preiscoin network after a connection is established, but this process has not completed yet.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class OverviewPage: public Ui_OverviewPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OVERVIEWPAGE_H
