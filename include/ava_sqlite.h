#ifndef AVA_SQLITE_H
#define AVA_SQLITE_H

#include "string"
#include "vector"
#include "map"
#include "sqlite3.h"

#include <fstream>
#include <stdexcept>

#include "ava_sql_helper.h"
#include "helper_converter.h"
#include "log.h"
#include "md_object.h"
#include "event_bus.h"

//#define LOG

#define AVA_SQLLITE_DB_NONE 0
#define AVA_SQLLITE_DB_OPEN 1
#define AVA_SQLLITE_TABLE_OPEN 2
#define AVA_SQLLITE_DB_ERROR -1

#define AVA_SQLITE_ERROR_OPEN_FILE 1
#define AVA_SQLITE_ERROR_NO_CALLBACK 2

#define AVA_SQLITE_STATE_NONE 0
#define AVA_SQLITE_STATE_WAIT_CALLBACK_READ_TITLE_TABLE 1
#define AVA_SQLITE_STATE_WAIT_CALLBACK_READ_DB 2
#define AVA_SQLITE_STATE_WAIT_CALLBACK_READ_NUMBER_ROW_IN_TABLE 3
#define AVA_SQLITE_STATE_SEND_COMMAND_ADD_ROW 4
#define AVA_SQLITE_STATE_WAIT_CALLBACK_READ_TABLE 5




using namespace std;

enum AVA_SQLite_Error
{
    NoneError, Error_CreateDB, Error_Request, Error_nocallback
};

struct _row
{
    vector<string> title_colums;
    vector<vector<string>> row;
};

struct _AVA_Table
{
    string name;
    vector<string> title_column;
    _row answer;
    ///кол-во строк
    int row;
    ///кол-во столбец
    int column;
};

struct _AVA_DB_File
{
    map<string,_AVA_Table> table_in_file;
   // char status;
    int num_table;
};


class AVA_SQLite : public MDObject
{
public:
    AVA_SQLite(){};
    AVA_SQLite(unsigned short int id_mdobj, string name_mdobj);
    virtual ~AVA_SQLite();

    /**
     * @brief OpenSQLiteDB Открываем базу данных
     * @param path путь к базе данных
     * @return 1 если все хорошо 0 если уже открыта база какая то
     * -1 если ошибка при открытии
     */
    char OpenSQLiteDB(const char *path);
    /**
     * @brief ClosedSQL Закрываем базу данных
     */
    void ClosedSQL();
    /**
     * @brief TakeErrorSQL получить ошибку из sqlite3_error
     * @return текст ошибки
     */
    const char * TakeErrorSQL();

    /**
     * @brief CreateSQLiteDB Создать файл ДБ
     * @param path путь к файлу
     */
    void CreateSQLiteDB(const char *path);
    /**
     * @brief CreateTable Создать таблицу (всегда автоматически добавляется ID primary key)
     * @param new_table [0] имя таблицы [...] названия элемента
     * @return 1 ОК 0 неичего не сделано(нет условий для выполнения) -1ошибка
     */
    char CreateTable(vector<string> *new_table);

    /**
     * @brief OpenTable Открыть таблицу (получаем заголовки столбцов и кол-во строк)
     * @param table_name имя таблицы
     * @return
     */
    char OpenTable(const char *table_name);

    /**
     * @brief AddROW добовляет строку в открытую таблице
     * @param data элементы которые добавляются (без ID)
     * @return 1 если все Ок -1 ошибка 0 невыполнены условия
     */
    char AddROW(vector<string> *data);


    /**
     * @brief ReadSQLite_Table
     * прочитать текущую таблицу
     */
    void ReadSQLite_Table();

    void Replace_Row(vector<string> *data,string *row_id);
    //char ReadTable(_row *out);









private:
    //QFile pFile;
    /**
     * @brief ReadTable Прочитать все таблицу
     * @param out сюда будет записаны данные таблицы
     * @return 1 если все гуд
     */
    char ReadTable(_row *out);

    static int sqll_callback(void *data, int num_colums, char **data_row, char **name_colums);

    static int OpenDB_callback(void *data, int num_colums, char **data_row, char **name_colums);
    static int OpenTable_callback(void *data, int num_colums, char **data_row, char **name_colums);
    static int Select_callback(void *data, int num_colums, char **data_row, char **name_colums);

    char SendSQLRequest(string request);
    char SendSQLRequest_NoneCallback(string request);

    //static int num_request_sql;
    //_AVA_Table now_table;
    sqlite3 *my_sqll;

    string path_file;
    string name_table;
    _AVA_DB_File my_db;

    char status;
    char state;
    char flag_nocallback;

    /**
     * @brief error Ошибки
     */
    int error;

    string request;
    _row answer;


};

#endif // AVA_SQLITE_H
