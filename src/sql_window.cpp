#include "sql_window.h"
#include "ui_sql_window.h"

sql_window::sql_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sql_window),MDObject(112,"SQL_Windows")
{
    mysql = new AVA_SQLite(113,"AVA_SQL_Window");

    ui -> setupUi(this);
    char ch;
    status = 0;
    state = 0;
    name_table.clear();
    ch = ADDEvent("AVA_SQLite_ERROR", new Delegate(this, &sql_window::SQLite_ERROR),113);
    ch = ADDEvent("ReadDB_Over", new Delegate(this, &sql_window::ReadDB_Over),113);
    ch = ADDEvent("ReadTable_Over", new Delegate(this, &sql_window::ReadTable_Over),113);
    ch = ADDEvent("ReadTableTitle_Over", new Delegate(this, &sql_window::ReadTitleTable_Over),113);
    ch = ADDEvent("OpenSQLiteDB");
    ch = ADDEvent("OpenSQLiteTable");
    ch = ADDEvent("ClosedSQLiteDB");
    ch = ADDEvent("SQL_Window_ERROR");

    Event_BUS::getInstance() -> AddMDObject(this);
    ui -> label -> setText("....");
    ui -> label_2 -> setText("....");

    string str;
    char c[2]; c[0]=0;c[1]=0;
    SQLite_Helper::ACharToHex(10,c);
    str=SQLite_Helper::UnsignedCharToHex(10);
    SQLite_Helper::ACharToHex(5,c);
    str=SQLite_Helper::UnsignedCharToHex(5);
    SQLite_Helper::ACharToHex(16,c);
    str=SQLite_Helper::UnsignedCharToHex(16);
    SQLite_Helper::ACharToHex(30,c);
    str=SQLite_Helper::UnsignedCharToHex(30);
    SQLite_Helper::ACharToHex(-1,c);
    str=SQLite_Helper::UnsignedCharToHex(-1);
    SQLite_Helper::ACharToHex(-100,c);
    str=SQLite_Helper::UnsignedCharToHex(-100);
    SQLite_Helper::ACharToHex(-12,c);

#ifdef _TRANSLATE
    retranslateUi();
#endif
}

sql_window::~sql_window()
{
    delete ui;
    delete mysql;
}

void sql_window::ReadDB_Over(vector<string> data)
{
    int i = 0;
    if(state == 1)
    {
#ifdef _TRANSLATE
        ui -> label -> setText(tr("Обрабатываю информацию о базе данных"));
#else
        ui -> label -> setText("Обрабатываю информацию о базе данных");
#endif
        while(i < data.size())
        {
            ui -> comboBox -> addItem(data.at(i).data());
            i++;
        }
        state = 2;
#ifdef _TRANSLATE
        ui -> label -> setText(tr("База данных открыта"));
#else
        ui -> label -> setText("База данных открыта");
#endif
    }

}

void sql_window::ReadTable_Over(_row table)
{
    if(state == 4)
    {
#ifdef _TRANSLATE
        ui -> label -> setText(tr("Формирую таблицу"));
#else
         ui -> label -> setText("Формирую таблицу");
#endif
        int i=0;
        int i1=0;

        ui -> tableWidget -> setRowCount(table.row.size()+1); // указываем количество строк
        ui -> tableWidget -> setColumnCount(table.title_colums.size()); // указываем количество столбцов
        while(i < table.title_colums.size())
        {
            ui -> tableWidget -> setItem(0,i,new QTableWidgetItem(table.title_colums.at(i).data()));
            i++;
        }
        i = 0;
        i1 = 0;
        while(i < (table.row.size()))
        {
            i1 = 0;
            while(i1 < table.title_colums.size())
            {
                ui -> tableWidget -> setItem(i+1,i1,new QTableWidgetItem(table.row.at(i).at(i1).data()));
                i1++;
            }
            i++;
        }
         state = 2;
#ifdef _TRANSLATE
         ui -> label-> setText(tr("База данных открыта"));
#else
         ui -> label -> setText("База данных открыта");
#endif
    }
}

void sql_window::ReadTitleTable_Over(_AVA_DB_File db)
{
    int i = db.num_table;
    if(state == 3)
    {
        state = 4;
#ifdef _TRANSLATE
        ui -> label -> setText(tr("Прочитал заголовки таблицы"));
#else
        ui -> label -> setText("Прочитал заголовки таблицы");
#endif
        Event_BUS::getInstance() -> SendEvent("ReadSQLite_Table",113,ReadID());


    }
}

void sql_window::OpenDB(){}

void sql_window::SQLite_ERROR(int error)
{
    string str;
    if(state == 1)
    {
        str="sql_window::SQLite_ERROR("+to_string(error)+") state 1 OpenDB\n";
#ifdef LOG
        Log::GetInstance() -> WriteLogError((char *)str.data());
#endif
        Event_BUS::getInstance() -> SendEvent("SQL_Window_ERROR",0,ReadID(),SQL_WINDOW_ERROR_OPENDB);
        state = 0;
        ui -> label -> setText("....");
    }
    if(state = 3)
    {
        str="sql_window::SQLite_ERROR("+to_string(error)+") state 3 OpenTable\n";
        Log::GetInstance() -> WriteLogError((char *)str.data());
        Event_BUS::getInstance() -> SendEvent("SQL_Window_ERROR",0,ReadID(),SQL_WINDOW_ERROR_OPENTABLE);
        state = 2;
#ifdef _TRANSLATE
         ui -> label-> setText(tr("База данных открыта"));
#else
         ui -> label -> setText("База данных открыта");
#endif
    }
    if(state=4)
    {
        str = "sql_window::SQLite_ERROR("+to_string(error)+") state 4 ReadTable\n";
        Log::GetInstance() -> WriteLogError((char *)str.data());
        Event_BUS::getInstance() -> SendEvent("SQL_Window_ERROR",0,ReadID(),SQL_WINDOW_ERROR_OPENTABLE);
        state = 2;
#ifdef _TRANSLATE
         ui -> label-> setText(tr("База данных открыта"));
#else
         ui -> label -> setText("База данных открыта");
#endif
    }

}
#ifdef _TRANSLATE
void sql_window::retranslateUi()
{
    ui -> retranslateUi(this);
}
#endif
void sql_window::on_comboBox_currentIndexChanged(const QString &arg1)
{
    string str = arg1.toStdString();
    if(state == 2)
    {
        ui -> tableWidget -> clear();
        state = 3;
        read_table = str;
        Event_BUS::getInstance() -> SendEvent("OpenSQLiteTable",113,ReadID(),str.data());
#ifdef _TRANSLATE
        ui -> label -> setText(tr("Открываю Таблицу"));
#else
        ui -> label -> setText("Открываю Таблицу");
#endif
    }
}

void sql_window::on_openBD_triggered()
{
    Event_BUS::getInstance() -> SendEvent("CloseSQLite_DB",113,ReadID());
    state = 0;
    ui -> comboBox -> clear();
    ui -> tableWidget -> clear();
   QString path = QFileDialog::getOpenFileName(this, "Open DB", QDir::currentPath(), "*");
   if(path.size()!=0)
   {
       this -> path = path.toStdString();
       state = 1;
       Event_BUS::getInstance() -> SendEvent("OpenSQLite_DB",113,ReadID(),this -> path.data());
#ifdef _TRANSLATE
       ui -> label -> setText(tr("Открываю Базу данных"));
#else
       ui -> label -> setText("Открываю Базу данных");
#endif
       ui -> label_2 -> setText(path);
   }
}

void sql_window::on_comboBox_activated(const QString &arg1)
{
    string str = arg1.toStdString();
    if(state == 2)
    {
        state = 3;
        read_table = str;
        Event_BUS::getInstance() -> SendEvent("OpenSQLiteTable",113,ReadID(),str.data());
#ifdef _TRANSLATE
        ui -> label -> setText(tr("Открываю Таблицу"));
#else
        ui -> label -> setText("Открываю Таблицу");
#endif
       // Event_BUS::getInstance()->SendEvent("ReadSQLite_Table",113,ReadID());
    }
    ui -> centralwidget -> setFocus();
}

void sql_window::timeout()
{
    if(state > 2)
    {
        state = 2;
#ifdef _TRANSLATE
        ui -> label -> setText(tr("База данных открыта"));
#else
        ui -> label -> setText("База данных открыта");
#endif

    }else
    {state = 0;
        ui -> label -> setText("...");
    }
    Event_BUS::getInstance() -> SendEvent("SQL_Window_ERROR",0,ReadID(),SQL_WINDOW_ERROR_TIMEOUT_DATA);

}

void sql_window::on_exitTable_triggered()
{
    this -> close();
}
