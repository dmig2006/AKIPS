/********************************************************************************
** Form generated from reading UI file 'sql_window.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQL_WINDOW_H
#define UI_SQL_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sql_window
{
public:
    QAction *openBD;
    QAction *exitTable;
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QMenu *menuSQLite_DB_Seer;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *sql_window)
    {
        if (sql_window->objectName().isEmpty())
            sql_window->setObjectName(QStringLiteral("sql_window"));
        sql_window->resize(1181, 600);
        openBD = new QAction(sql_window);
        openBD->setObjectName(QStringLiteral("openBD"));
        exitTable = new QAction(sql_window);
        exitTable->setObjectName(QStringLiteral("exitTable"));
        centralwidget = new QWidget(sql_window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 60, 1161, 501));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(890, 20, 281, 33));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 521, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 731, 21));
        sql_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(sql_window);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1181, 19));
        menuSQLite_DB_Seer = new QMenu(menubar);
        menuSQLite_DB_Seer->setObjectName(QStringLiteral("menuSQLite_DB_Seer"));
        sql_window->setMenuBar(menubar);
        statusbar = new QStatusBar(sql_window);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        sql_window->setStatusBar(statusbar);

        menubar->addAction(menuSQLite_DB_Seer->menuAction());
        menuSQLite_DB_Seer->addAction(openBD);
        menuSQLite_DB_Seer->addAction(exitTable);

        retranslateUi(sql_window);

        QMetaObject::connectSlotsByName(sql_window);
    } // setupUi

    void retranslateUi(QMainWindow *sql_window)
    {
        sql_window->setWindowTitle(QApplication::translate("sql_window", "\320\236\320\272\320\275\320\276 \320\221\320\224", Q_NULLPTR));
        openBD->setText(QApplication::translate("sql_window", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\261\320\260\320\267\321\203 \320\264\320\260\320\275\320\275\321\213\321\205", Q_NULLPTR));
        exitTable->setText(QApplication::translate("sql_window", "\320\222\321\213\320\271\321\202\320\270", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QString());
        menuSQLite_DB_Seer->setTitle(QApplication::translate("sql_window", "\320\234\320\265\320\275\321\216", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sql_window: public Ui_sql_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQL_WINDOW_H
