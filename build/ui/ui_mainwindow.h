/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QListWidget *logWidget;
    QPushButton *pushButton_t;
    QPushButton *pushButton_z;
    QPushButton *pushButton_g;
    QPushButton *pushButton_b;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1024, 768));
        MainWindow->setMaximumSize(QSize(1024, 768));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        logWidget = new QListWidget(centralWidget);
        logWidget->setObjectName(QStringLiteral("logWidget"));
        logWidget->setGeometry(QRect(746, 30, 256, 192));
        pushButton_t = new QPushButton(centralWidget);
        pushButton_t->setObjectName(QStringLiteral("pushButton_t"));
        pushButton_t->setGeometry(QRect(750, 720, 121, 23));
        pushButton_z = new QPushButton(centralWidget);
        pushButton_z->setObjectName(QStringLiteral("pushButton_z"));
        pushButton_z->setGeometry(QRect(880, 690, 121, 23));
        pushButton_g = new QPushButton(centralWidget);
        pushButton_g->setObjectName(QStringLiteral("pushButton_g"));
        pushButton_g->setGeometry(QRect(880, 720, 121, 23));
        pushButton_b = new QPushButton(centralWidget);
        pushButton_b->setObjectName(QStringLiteral("pushButton_b"));
        pushButton_b->setGeometry(QRect(750, 690, 121, 23));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\272\320\260 \320\270\320\267\320\264\320\265\320\273\320\270\321\217 9\320\234311-1\320\234", Q_NULLPTR));
        pushButton_t->setText(QApplication::translate("MainWindow", "send_t", Q_NULLPTR));
        pushButton_z->setText(QApplication::translate("MainWindow", "send_z", Q_NULLPTR));
        pushButton_g->setText(QApplication::translate("MainWindow", "send_g", Q_NULLPTR));
        pushButton_b->setText(QApplication::translate("MainWindow", "send_b", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
