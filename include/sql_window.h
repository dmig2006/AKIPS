#ifndef SQL_WINDOW_H
#define SQL_WINDOW_H

#define _TRANSLATE
#define ERRROR_SQLITE

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QTimer>

#include "event_bus.h"
#include "md_object.h"
#include "ava_sqlite.h"
#include "string"

#ifdef ERRROR_SQLITE
    #include "error.h"
#else
#define SQL_WINDOW_ERROR_OPENDB 1
#define SQL_WINDOW_ERROR_OPENTABLE 2
#define SQL_WINDOW_ERROR_TIMEOUT_DATA 3
#endif
using namespace std;

namespace Ui {
class sql_window;
}

class sql_window : public QMainWindow, public MDObject
{
    Q_OBJECT

public:
    explicit sql_window(QWidget *parent = 0);
    ~sql_window();
    AVA_SQLite *mysql;
    void ReadDB_Over(vector<string> data);
    void ReadTable_Over(_row table);
    void ReadTitleTable_Over(_AVA_DB_File db);

    void OpenDB();
    void SQLite_ERROR(int error);
#ifdef _TRANSLATE
    void retranslateUi();
#endif
private slots:
   // void on_action_changed();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_openBD_triggered();

    void on_comboBox_activated(const QString &arg1);
     void timeout();
     void on_exitTable_triggered();

private:


    Ui::sql_window *ui;
    vector<string> name_table;
    //QTimer timer_my;
    char status;
    char state;

    string path;
    string read_table;
};

#endif // SQL_WINDOW_H
