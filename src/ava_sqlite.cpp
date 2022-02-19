#include "ava_sqlite.h"



AVA_SQLite::AVA_SQLite(unsigned short id_mdobj, string name_mdobj):MDObject(id_mdobj,(char*)name_mdobj.data()),status(0),state(0),error(0)
{
    char c=0;
    my_db.num_table=0;
    my_db.table_in_file.clear();
    c=ADDEvent("OpenSQLite_DB", new Delegate(this,&AVA_SQLite::OpenSQLiteDB));
    c=ADDEvent("CloseSQLite_DB", new Delegate(this,&AVA_SQLite::ClosedSQL));
    c=ADDEvent("CreateSQLiteDB", new Delegate(this,&AVA_SQLite::CreateSQLiteDB));
    c=ADDEvent("CreateSQLiteTable", new Delegate(this,&AVA_SQLite::CreateTable));
    c=ADDEvent("OpenSQLiteTable", new Delegate(this,&AVA_SQLite::OpenTable));
    c=ADDEvent("AddROWSQLiteTable", new Delegate(this,&AVA_SQLite::AddROW));
    c=ADDEvent("ReadSQLite_Table", new Delegate(this,&AVA_SQLite::ReadSQLite_Table));
    c=ADDEvent("Replace_Row", new Delegate(this,&AVA_SQLite::Replace_Row));

    c=ADDEvent("ReadDB_Over");
    c=ADDEvent("ReadTable_Over");
    c=ADDEvent("ReadTableTitle_Over");
    c=ADDEvent("AVA_SQLite_ERROR");

    Event_BUS::getInstance()->AddMDObject(this);
    flag_nocallback=0;
}

AVA_SQLite::~AVA_SQLite()
{
    ClosedSQL();
#ifdef LOG
    cout << "Delete AVA_SQLite" << endl;
#endif
}

void AVA_SQLite::ClosedSQL()
{
    if((status==AVA_SQLLITE_DB_OPEN||status==AVA_SQLLITE_TABLE_OPEN)||status==AVA_SQLLITE_DB_ERROR)
    {
        status=AVA_SQLLITE_DB_NONE;
        state=0;
        error=0;
        sqlite3_close(my_sqll);
        my_db.num_table=0;
        my_db.table_in_file.clear();
    }
}

const char *AVA_SQLite::TakeErrorSQL()
{

    return sqlite3_errmsg(my_sqll);
}

void AVA_SQLite::CreateSQLiteDB(const char *path)
{
     string str;
     ifstream fin(path); //read file

     if (!fin.is_open()) // если файл не открыт
     {
         fin.close();
         //Такого файла нет или несмогли открыть
         ofstream fout(path, ios_base::out | ios_base::trunc);
         if (!fout.is_open()) // если файл небыл открыт
             {
              str="AVA_SQLite::CreateSQLiteDB('"+string(path)+"') Файл не может быть открыт или создан\n";
#ifdef LOG
              Log::GetInstance()->WriteLogError((char*)str.data());
#endif
              Event_BUS::getInstance()->SendEvent("AVA_SQLite_ERROR",0,ReadID(),Error_CreateDB);

             }
         else
         {
             //файл создан норм
             str="AVA_SQLite::CreateSQLiteDB('"+string(path)+"') Файл успешно создан\n";
#ifdef LOG
             Log::GetInstance()->WriteLogData((char*)str.data());
#endif
         }
         fout.close();

     }
     else
     {
         fin.close();
         str="AVA_SQLite::CreateSQLiteDB('"+string(path)+"') Файл уже существует\n";
#ifdef LOG
         Log::GetInstance()->WriteLogData((char*)str.data());
#endif
     }
}



char AVA_SQLite::CreateTable(vector<string> *new_table)
{
    vector<string> data_table=*new_table;
    char c=0;
    string str;
    _AVA_Table tab;

    if(status==AVA_SQLLITE_DB_OPEN&&state==AVA_SQLITE_STATE_NONE)
    {
        //name_table=new_table->at(0).data();
        SQLite_Helper::ADDSQLCommand("CREATE TABLE",new_table->at(0).data(),&str);
        data_table[0]="ID INTEGER PRIMARY KEY AUTOINCREMENT";

        SQLite_Helper::ADDSQLValues(0,&data_table,&str);
        str=str+";";
        c=SendSQLRequest_NoneCallback(str);
        if(c==1)
        {
            my_db.table_in_file.insert(pair<string,_AVA_Table>(new_table->at(0).data(),tab));
        }
        return c;
        //Log::GetInstance()->WriteLogData((char*)str.data());


    }

    return 0;
}

char AVA_SQLite::OpenTable(const char *table_name)
{
    string str;
    char c=0;
    _AVA_Table tab;
    if(state==AVA_SQLITE_STATE_NONE&&(status==AVA_SQLLITE_DB_OPEN||status==AVA_SQLLITE_TABLE_OPEN))
    {
        try
        {
            tab=my_db.table_in_file.at(table_name);
        }
        catch (const std::out_of_range& oor)
        {
            str="AVA_SQLite::OpenTable('"+string(table_name)+"') Таблица отсутствует\n";
#ifdef LOG
            Log::GetInstance()->WriteLogError((char*)str.data());
#endif
            return -1;

        }

        SQLite_Helper::ADDSQLCommand("SELECT * FROM ",table_name,&str);
        SQLite_Helper::ADDSQLCommand("LIMIT","1",&str);
        str=str+";";
        //Обнуляем тек. таблицу
        name_table=table_name;
        state=AVA_SQLITE_STATE_WAIT_CALLBACK_READ_TITLE_TABLE;
        c=SendSQLRequest(str);
        if(c==1)
        {
            str.clear();
            SQLite_Helper::ADDSQLCommand("SELECT count(*) FROM ",table_name,&str);
            str=str+";";
            state=AVA_SQLITE_STATE_WAIT_CALLBACK_READ_NUMBER_ROW_IN_TABLE;
            c=SendSQLRequest(str);
            if(c==1)
            {
                status=AVA_SQLLITE_TABLE_OPEN;
                Event_BUS::getInstance()->SendEvent("ReadTableTitle_Over",0,ReadID(),my_db);
            }

        }
        else
        {
            Event_BUS::getInstance()->SendEvent("AVA_SQLite_ERROR",0,ReadID(),error);
        }


    }
    state=AVA_SQLITE_STATE_NONE;
    return c;
}

char AVA_SQLite::AddROW(vector<string> *data)
{
    string str;
    vector<string> vs=*data;
    vs.insert(vs.begin(),"NULL");
    char c=0;
    if(state==AVA_SQLITE_STATE_NONE&&status==AVA_SQLLITE_TABLE_OPEN)
    {

        SQLite_Helper::ADDSQLCommand("INSERT INTO",(char*)name_table.data(),&str);
        SQLite_Helper::ADDSQLValues("VALUES",&vs,&str);
        str=str+";";
        state=AVA_SQLITE_STATE_SEND_COMMAND_ADD_ROW;
        c=SendSQLRequest_NoneCallback(str);
        if(c==1)
        {
            my_db.table_in_file.at(name_table).row++;
        }
    }
    state=AVA_SQLITE_STATE_NONE;
    return c;
}

char AVA_SQLite::ReadTable(_row *out)
{
    string str;
    char c=0;
    if(state==AVA_SQLITE_STATE_NONE&&status==AVA_SQLLITE_TABLE_OPEN)
    {

        SQLite_Helper::ADDSQLCommand("SELECT * FROM",(char*)name_table.data(),&str);
        str=str+";";
        state=AVA_SQLITE_STATE_WAIT_CALLBACK_READ_TABLE;

        c=SendSQLRequest(str);
        if(c==1)
        {
            *out=answer;
        }
    }
    state=AVA_SQLITE_STATE_NONE;
    return c;
}

void AVA_SQLite::ReadSQLite_Table()
{
    _row myrow;
    if(ReadTable(&myrow))
        Event_BUS::getInstance()->SendEvent("ReadTable_Over",0,ReadID(),myrow);
    else
    {
        string str="AVA_SQLite::ReadSQLite_Table() - ошибка получения данных\n";
#ifdef LOG
        Log::GetInstance()->WriteLogError((char*)str.data());
#endif
    }
    answer.row.clear();
    answer.title_colums.clear();

}

void AVA_SQLite::Replace_Row(vector<string> *data,string *row_id)
{
    string str;
    vector<string> vs=*data;
    vs.insert(vs.begin(),*row_id);
    char c=0;
    if(state==AVA_SQLITE_STATE_NONE&&status==AVA_SQLLITE_TABLE_OPEN)
    {

        SQLite_Helper::ADDSQLCommand("REPLACE INTO",(char*)name_table.data(),&str);
        SQLite_Helper::ADDSQLValues("VALUES",&vs,&str);
        str=str+";";
        state=AVA_SQLITE_STATE_SEND_COMMAND_ADD_ROW;
        c=SendSQLRequest_NoneCallback(str);
        if(c==1)
        {
           // my_db.table_in_file.at(name_table).row++;
        }
    }
    state=AVA_SQLITE_STATE_NONE;

}

char AVA_SQLite::OpenSQLiteDB(const char *path)
{
    int i=0;
    string str;
    char c=0;

    if(path==0) return -1;
    if(status==AVA_SQLLITE_DB_NONE&&error==0&&state==AVA_SQLITE_STATE_NONE)
    {
    i=sqlite3_open(path,&my_sqll);
    if(i==SQLITE_OK)
    {
            //Open norm
       status=AVA_SQLLITE_DB_OPEN;
       state=0;
       path_file=path;
       str="AVA_SQLite::OpenSQLiteDB(";
       str=str+path+") Open!\n";
#ifdef LOG
          Log::GetInstance()->WriteLogData((char*)str.data());
#endif

          //SQLite_Helper::ADDSQLCommand("SELECT name FROM sqlite_master WHERE type='table'",0,&str);
          str="SELECT name FROM sqlite_master WHERE type='table';";
          state=AVA_SQLITE_STATE_WAIT_CALLBACK_READ_DB;
          c=SendSQLRequest(str);
          if(c==1)
          {
              vector<string> vs;
              map<string,_AVA_Table>::iterator it=my_db.table_in_file.begin();
              int size=my_db.table_in_file.size();
              i=0;
              while(i<size)
              {
                  vs.push_back((it++)->first);
                  i++;
              }
            Event_BUS::getInstance()->SendEvent("ReadDB_Over",0,ReadID(),vs);
            return 1;
          }
          else return c;

    }
    else
    {
        status=AVA_SQLLITE_DB_ERROR;
        state=0;
        error=AVA_SQLITE_ERROR_OPEN_FILE;
        str="AVA_SQLite::OpenSQLiteDB(";
        str=str+path+") Error "+to_string(error)+"!\n";
#ifdef LOG
        Log::GetInstance()->WriteLogError((char*)str.data());
#endif
        return -1;
    }

    }

    return 0;

}

char AVA_SQLite::SendSQLRequest(string request)
{
    int i=0;
    string str;
    char *zErrMsg;

    if(status==AVA_SQLLITE_DB_OPEN||status==AVA_SQLLITE_TABLE_OPEN)
    {
    this->request=request;

        str="AVA_SQLite::SendSQLRequest(";
        str=str+" "+request+") Запрос отправлен\n";
#ifdef LOG
    Log::GetInstance()->WriteLogData((char*)str.data());
#endif
    flag_nocallback=1;
    i = sqlite3_exec(my_sqll, request.data(), sqll_callback, this, &zErrMsg);

    state=AVA_SQLITE_STATE_NONE;

    if( i != SQLITE_OK && flag_nocallback==1 )
    {

        str="AVA_SQLite::SendSQLRequest(";
       if(flag_nocallback==1)
       {
           str=str+" "+request+" NO_CALLBACK"+zErrMsg+" \n";
           Event_BUS::getInstance()->SendEvent("AVA_SQLite_ERROR",0,ReadID(),Error_nocallback);
       }
       else
       {
           str=str+" "+request+" "+zErrMsg+" \n";
           Event_BUS::getInstance()->SendEvent("AVA_SQLite_ERROR",0,ReadID(),Error_Request);
       }
       if(i != SQLITE_OK) sqlite3_free(zErrMsg);
#ifdef LOG
        Log::GetInstance()->WriteLogError((char*)str.data());
#endif

       return -1;
    }else
    {
        /*
        str="AVA_SQLite::SendSQLRequest(";
        str=str+" "+request+") Запрос отправлен успешно\n";

       Log::GetInstance()->WriteLogData((char*)str.data());
       */
       return 1;
    }
    }
    return 0;
}

char AVA_SQLite::SendSQLRequest_NoneCallback(string request)
{
    int i=0;
    string str;
    char *zErrMsg;

    if(status==AVA_SQLLITE_DB_OPEN||status==AVA_SQLLITE_TABLE_OPEN)
    {
    this->request=request;

        str="AVA_SQLite::SendSQLRequest_NoneCallback(";
        str=str+" "+request+") Запрос отправлен\n";
    Log::GetInstance()->WriteLogData((char*)str.data());

    i = sqlite3_exec(my_sqll, request.data(), 0, this, &zErrMsg);
    if( i != SQLITE_OK )
    {
        str="AVA_SQLite::SendSQLRequest_NoneCallback(";
        str=str+" "+request+" "+zErrMsg+")\n";
#ifdef LOG
       Log::GetInstance()->WriteLogError((char*)str.data());
#endif
       sqlite3_free(zErrMsg);
       Event_BUS::getInstance()->SendEvent("AVA_SQLite_ERROR",0,ReadID(),Error_Request);
       return -1;
    }else
    {
/*
        str="AVA_SQLite::SendSQLRequest_NoneCallback(";
        str=str+" "+request+") Запрос отправлен успешно\n";

       Log::GetInstance()->WriteLogData((char*)str.data());
       */
       return 1;
    }
    }
    return 0;
}

int AVA_SQLite::sqll_callback(void *data, int num_colums, char **data_row, char **name_colums)
{

    AVA_SQLite *pAVA_SQL=(AVA_SQLite*)data;
    int i=0;
    pAVA_SQL->flag_nocallback=0;
    if(pAVA_SQL->state==AVA_SQLITE_STATE_WAIT_CALLBACK_READ_DB)
    {
        OpenDB_callback(data,num_colums,data_row,name_colums);

        return 0;

    }
    if(pAVA_SQL->state==AVA_SQLITE_STATE_WAIT_CALLBACK_READ_TITLE_TABLE)
    {
        OpenTable_callback(data,num_colums,data_row,name_colums);
        return 0;
    }
    if(pAVA_SQL->state==AVA_SQLITE_STATE_WAIT_CALLBACK_READ_NUMBER_ROW_IN_TABLE)
    {

       OpenTable_callback(data,num_colums,data_row,name_colums);
       return 0;
    }
    if(pAVA_SQL->state==AVA_SQLITE_STATE_WAIT_CALLBACK_READ_TABLE)
    {

       Select_callback(data,num_colums,data_row,name_colums);
       return 0;
    }

    return 0;
}
int AVA_SQLite::OpenDB_callback(void *data, int num_colums, char **data_row, char **name_colums)
{

    AVA_SQLite *pAVA_SQL=(AVA_SQLite*)data;
    int i=0;
    if(pAVA_SQL->state==AVA_SQLITE_STATE_WAIT_CALLBACK_READ_DB)
    {
        _AVA_Table tab;

        //Заполняем название таблиц
        for(i=0; i<num_colums; i++)
        {
              //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
              tab.name=data_row[i];
              tab.row=0;
              tab.column=0;
              pAVA_SQL->my_db.table_in_file.insert(pair<string,_AVA_Table>(data_row[i],tab));
              pAVA_SQL->my_db.num_table++;
        }

           return 0;

    }
    return 0;
}

int AVA_SQLite::OpenTable_callback(void *data, int num_colums, char **data_row, char **name_colums)
{

    AVA_SQLite *pAVA_SQL=(AVA_SQLite*)data;
    int i=0;
    if(pAVA_SQL->state==AVA_SQLITE_STATE_WAIT_CALLBACK_READ_TITLE_TABLE)
    {

        //Заполняем таблицу
        for(i=0; i<num_colums; i++)
        {

              pAVA_SQL->my_db.table_in_file.at(pAVA_SQL->name_table).title_column.push_back(name_colums[i]);
              pAVA_SQL->my_db.table_in_file.at(pAVA_SQL->name_table).column++;

        }

           return 0;
    }
    if(pAVA_SQL->state==AVA_SQLITE_STATE_WAIT_CALLBACK_READ_NUMBER_ROW_IN_TABLE)
    {

        //Заполняем таблицу
        for(i=0; i<num_colums; i++)
        {
              pAVA_SQL->my_db.table_in_file.at(pAVA_SQL->name_table).row=atoi(data_row[i]);
        }

           return 0;
    }

    return 0;
}

int AVA_SQLite::Select_callback(void *data, int num_colums, char **data_row, char **name_colums)
{

    AVA_SQLite *pAVA_SQL=(AVA_SQLite*)data;
    vector<string> vs;
    int size=0;
    int i=0;
    if(pAVA_SQL->state==AVA_SQLITE_STATE_WAIT_CALLBACK_READ_TABLE)
    {
        pAVA_SQL->answer.row.push_back(vs);
        size=pAVA_SQL->answer.row.size();
        //Заполняем таблицу
        for(i=0; i<num_colums; i++)
        {
              if(pAVA_SQL->answer.title_colums.size()<(i+1))
                  pAVA_SQL->answer.title_colums.push_back(name_colums[i]);
              pAVA_SQL->answer.row.at(size-1).push_back(data_row[i]);

        }

           return 0;
    }
}
