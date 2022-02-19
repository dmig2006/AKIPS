#include "datamanager.h"
#include "mainwindow.h"

using namespace std;

DataManager::DataManager(unsigned short id_mdobj, string name_mdobj) :MDObject(id_mdobj,(char*)name_mdobj.data())
{
    mss = 0;    //Общее время проверки равно 0
    t = time(NULL); //инициализация таймера
    aTm = localtime(&t);    //инициализация таймера
    ADDEvent((char *) "DataRead", new Delegate(this,&DataManager::AddDataM_Ch));    //добавляем новые события, см комментарии в файле md_object
    ADDEvent((char *) "TestOk", new Delegate(this, &DataManager::AddDataM_Str));
    ADDEvent((char *) "ReadDB_Over", new Delegate(this, &DataManager::GetTableName));
    ADDEvent((char *) "ClearData", new Delegate(this, &DataManager::ClearData));
    ADDEvent((char *) "SaveData", new Delegate(this, &DataManager::DataM_To_Str_db));
    ADDEvent((char *) "ReadTable_Over", new Delegate(this, &DataManager::GetTableRow));

    Event_BUS::getInstance() -> AddMDObject(this);  //добавляем все события в event_bus (см соответствующие комментарии)
}

DataManager::~DataManager(){
    cout << "Delete DataManager" << endl;
}

char DataManager::AddDataM_Ch(vector<char> Data)    //метод устарел см комменты в заголовочном файле
{
    if(Good)
    {
        for(unsigned i = 0; i < Data.size(); i++)
        {
            this -> Data.DataM_Ch.push_back(Data.at(i));
        }
    }
    return 1;
}

char DataManager::AddDataM_Str(QVector<QString> Data)
{
    if(Good)    //в семом начале флаг good кстановлен в истину, считаем что ракета исправна
    {
        if (!R_Type.size()) //если мы еще не знаем типа ракеты
            R_Type = (Data.at(0).toStdString());   //получили тип ракеты
        State = Data.at(1).toStdString();   //текущее состояние брак/годен

#ifdef _TRANSLATE
        if (KPA_Rocket::flag)   //формируем строки в формате № проверки измеренное значение допустимое значение
            this ->  Data.DataM_Str.push_back(TESTNUM_ENG + Data.at(2).toStdString() + " " + Data.at(3).toStdString() + Data.at(4).toStdString() + "'");
        else
            this ->  Data.DataM_Str.push_back(TESTNUM_RUS + Data.at(2).toStdString() + " " + Data.at(3).toStdString() + Data.at(4).toStdString() + "'");
#else
        this ->  Data.DataM_Str.push_back(TESTNUM_RUS + Data.at(2).toStdString() + " " + Data.at(3).toStdString() + Data.at(4).toStdString() + "'");
#endif

        if(Data.at(2) == "5")   //если текущая проверка 5 то сохраняем время когда она пришла для отсчета времени между проверками
            ms = clock();
        else
        {
            this -> Data.DataM_tm.push_back(clock() - ms); //иначе время текущей проверки равно текущее время - время прошлой проверки
            mss += clock() - ms;    //прибавляем время текущей проверки к общему времени проверок
            ms = clock();   //сохраняем текущее время для вычисления времени след проверки
        }
    }
    if((Data.at(2) == TUNGUSKA_TEST && (R_Type == TUNGUSKA_ROCKET)) ||  //если прошла 34 проверка и тип ракеты определен как тунгуска
        (Data.at(2) == KASHTAN_TEST && (R_Type == KASHTAN_ROCKET)) ||   //или если прошла 31 проверка и тип ракеты определен как каштан
         State == FALSE_ENG || State == FALSE_RUS)  //или пришел брак
    {
        Good = false;   //сбрасываем флаг в ложь
        QByteArray data; //формируем массив из байтов где содержатся данные последней проверки, необходимо для вывода на
        data.push_back(this -> Data.DataM_Ch.at(this -> Data.DataM_Ch.size() - 5)); //экран надписей типа годен/брак
        data.push_back(this -> Data.DataM_Ch.at(this -> Data.DataM_Ch.size() - 4)); //и результатов проверки (измеренное значение и всё такое)
        data.push_back(this -> Data.DataM_Ch.at(this -> Data.DataM_Ch.size() - 2));
        data.push_back(this -> Data.DataM_Ch.at(this -> Data.DataM_Ch.size() - 1));
        Event_BUS::getInstance() -> SendEvent((char *) "Data_Come", 0, ReadID(), &data);    //вызываем событие Data_Come (см соответствующие комментарии)
        //Event_BUS::getInstance() -> SendEvent((char *) "New_Log", 0, ReadID(), QString::number(Good));
    }
    return 1;
}

char DataManager::AddDataHead(string num, string serialnr)
{
    DataH.num = num;    //сохраняем серию номер ракеты и текушие дату/время
    DataH.serialnr = serialnr;
    aTm = localtime(&t);
    DataH.date = to_string(aTm->tm_year+1900) + ":" + to_string(aTm->tm_mon+1) + ":" + to_string(aTm->tm_mday) + " " + to_string(aTm->tm_hour) + ":" + to_string(aTm->tm_min) + ":" + to_string(aTm->tm_sec);
    return 1;
}

//-------------------------------------------------
//Метод DataM_To_Str_db() переписан 20.01.17
//-------------------------------------------------
/*
void DataManager::DataM_To_Str_db()
{
    vector<string> vstr;
    vstr.push_back("'" + DataH.num + "'");
    vstr.push_back("'" + DataH.serialnr + "'");
    vstr.push_back("'" + DataH.date + "'");
    vstr.push_back("'" + State + "'");
    vstr.push_back("'" + to_string(mss) + "'");  //Получаем данные в формате НОМЕР РАКЕТЫ/СЕРИЙНЫЙ НОМЕР/ДАТА ВРЕМЯ/РЕЗУЛЬТАТ ПРОВЕРКИ/ОБЩЕЕ ВРЕМЯ ПРОВЕРКИ
    unsigned i = 0;
    while(1)
    {
        if(i == 0 && Data.DataM_Str.size() > 0)
            vstr.push_back(Data.DataM_Str.at(i));
        else if(Data.DataM_Str.size() > i)
        {
            vstr.push_back(Data.DataM_Str.at(i));
            vstr.push_back(to_string(Data.DataM_tm.at(i - 1)));
        }
        else if(Data.DataM_Str.size() <= i && ((i < 27 && R_Type == KASHTAN_ROCKET) || (i < 30 && R_Type == TUNGUSKA_ROCKET)))
        {
#ifdef _TRANSLATE
            if(KPA_Rocket::flag)
            {
                vstr.push_back(NODATA_ENG);
                vstr.push_back("'-'");
            }
            else
            {
                vstr.push_back(NODATA_RUS);
                vstr.push_back("'-'");
            }
#else
            vstr.push_back(NODATA_RUS);
            vstr.push_back("'-'");
#endif
        }
        else
            break;
        i++;
    }
    Event_BUS::getInstance() -> SendEvent((char *) "CreateSQLiteDB", 111, ReadID(), "KPA_DataBase.db");
    Event_BUS::getInstance() -> SendEvent((char *) "OpenSQLite_DB", 111, ReadID(), "KPA_DataBase.db");
    FindTable = false;
    for(char i = 0; i < TableName.size(); i++)
        if(ROCKET_ENG == TableName.at(i))
            FindTable = true;
    if(!FindTable)
    {   vector<string> vstrr;
#ifdef _TRANSLATE
        if (KPA_Rocket::flag)
        {
            vstrr.push_back(ROCKET_ENG);
            vstrr.push_back(PARTY_ENG);
            vstrr.push_back(SERIAL_ENG);
            vstrr.push_back(TIME_ENG);
            vstrr.push_back(STATE_ENG);
        }
        else
        {
            vstrr.push_back(ROCKET_ENG);
            vstrr.push_back(PARTY_RUS);
            vstrr.push_back(SERIAL_RUS);
            vstrr.push_back(TIME_RUS);
            vstrr.push_back(STATE_RUS);
        }
#else
        vstrr.push_back(ROCKET_ENG);
        vstrr.push_back(PARTY_RUS);
        vstrr.push_back(SERIAL_RUS);
        vstrr.push_back(TIME_RUS);
        vstrr.push_back(STATE_RUS);
#endif
        Event_BUS::getInstance() -> SendEvent((char *) "CreateSQLiteTable", 111, ReadID(), &vstrr);
        FindTable = false;
    }
    FindTable = false;
    if(R_Type == TUNGUSKA_ROCKET)
    {
        for(char i = 0; i < TableName.size(); i++)
            if(TUNGUSKA_ENG == TableName.at(i))
                FindTable = true;
        if(!FindTable)
        {
            vector<string> vstrr;
#ifdef _TRANSLATE
            if (KPA_Rocket::flag)
            {
                vstrr.push_back(TUNGUSKA_ENG);
                vstrr.push_back(PARTY_ENG);
                vstrr.push_back(SERIAL_ENG);
                vstrr.push_back(TIME_ENG);
                vstrr.push_back(STATE_ENG);
                vstrr.push_back(TIMEALL_ENG);
                vstrr.push_back(string(VALUE_ENG) + string("5'"));
            }
            else
            {
                vstrr.push_back(TUNGUSKA_ENG);
                vstrr.push_back(PARTY_RUS);
                vstrr.push_back(SERIAL_RUS);
                vstrr.push_back(TIME_RUS);
                vstrr.push_back(STATE_RUS);
                vstrr.push_back(TIMEALL_RUS);
                vstrr.push_back(string(VALUE_RUS) + string("5'"));
            }
#else
            vstrr.push_back(TUNGUSKA_ENG);
            vstrr.push_back(PARTY_RUS);
            vstrr.push_back(SERIAL_RUS);
            vstrr.push_back(TIME_RUS);
            vstrr.push_back(STATE_RUS);
            vstrr.push_back(TIMEALL_RUS);
            vstrr.push_back(string(VALUE_RUS) + string("5'"));
#endif
            for(char i = 6; i < 35; i++)
            {
#ifdef _TRANSLATE
                if (KPA_Rocket::flag)
                {
                    vstrr.push_back(VALUE_ENG + to_string(i) + "'");
                    vstrr.push_back(TESTTIME_ENG + to_string(i) + " ms'");
                }
                else
                {
                    vstrr.push_back(VALUE_RUS + to_string(i) + "'");
                    vstrr.push_back(TESTTIME_RUS + to_string(i) + " мс'");
                }
#else
                vstrr.push_back(VALUE_RUS + to_string(i) + "'");
                vstrr.push_back(TESTNUM_RUS + to_string(i) + " мс'");
#endif
            }
            Event_BUS::getInstance() -> SendEvent((char *) "CreateSQLiteTable", 111, ReadID(), &vstrr);
        }
        FindTable = false;
    }
    FindTable = false;
        if(R_Type == KASHTAN_ROCKET)
        {
            for(char i = 0; i < TableName.size(); i++)
                if("R9M311_1E" == TableName.at(i))
                    FindTable = true;
            if(!FindTable)
            {
                vector<string> vstrr;
#ifdef _TRANSLATE
                if (KPA_Rocket::flag)
                {
                    vstrr.push_back(KASHTAN_ENG);
                    vstrr.push_back(PARTY_ENG);
                    vstrr.push_back(SERIAL_ENG);
                    vstrr.push_back(TIME_ENG);
                    vstrr.push_back(STATE_ENG);
                    vstrr.push_back(TIMEALL_ENG);
                    vstrr.push_back(string(VALUE_ENG) + string("5'"));
                }
                else
                {
                    vstrr.push_back(KASHTAN_ENG);
                    vstrr.push_back(PARTY_RUS);
                    vstrr.push_back(SERIAL_RUS);
                    vstrr.push_back(TIME_RUS);
                    vstrr.push_back(STATE_RUS);
                    vstrr.push_back(TIMEALL_RUS);
                    vstrr.push_back(string(VALUE_RUS) + string("5'"));
                }
#else
                vstrr.push_back(KASHTAN_ENG);
                vstrr.push_back(PARTY_RUS);
                vstrr.push_back(SERIAL_RUS);
                vstrr.push_back(TIME_RUS);
                vstrr.push_back(STATE_RUS);
                vstrr.push_back(TIMEALL_RUS);
                vstrr.push_back(string(VALUE_RUS) + string("5'"));
#endif
                for(char i = 6; i < 32; i++)
                {
#ifdef _TRANSLATE
                if (KPA_Rocket::flag)
                {
                    vstrr.push_back(VALUE_ENG + to_string(i) + "'");
                    vstrr.push_back(TESTTIME_ENG + to_string(i) + " ms'");
                }
                else
                {
                    vstrr.push_back(VALUE_RUS + to_string(i) + "'");
                    vstrr.push_back(TESTTIME_RUS + to_string(i) + " мс'");
                }
#else
                vstrr.push_back(VALUE_RUS + to_string(i) + "'");
                vstrr.push_back(TESTNUM_RUS + to_string(i) + " мс'");
#endif
                }
                Event_BUS::getInstance() -> SendEvent((char *) "CreateSQLiteTable", 111, ReadID(), &vstrr);
            }
        FindTable = false;
        }



    if(R_Type == KASHTAN_ROCKET)
        Event_BUS::getInstance() -> SendEvent((char *) "OpenSQLiteTable", 111, ReadID(), KASHTAN_ENG);
    else if(R_Type == TUNGUSKA_ROCKET)
        Event_BUS::getInstance() -> SendEvent((char *) "OpenSQLiteTable", 111, ReadID(), TUNGUSKA_ENG);
    Event_BUS::getInstance() -> SendEvent((char *) "AddROWSQLiteTable", 111, ReadID(), &vstr);

    vstr.resize(4);
    this -> row.title_colums.clear();
    this -> row.row.clear();
    Event_BUS::getInstance() -> SendEvent((char *) "OpenSQLiteTable", 111, ReadID(), "Rocket");
    Event_BUS::getInstance() -> SendEvent((char *) "ReadSQLite_Table", 111, ReadID());
    if(row.row.size() > 0)
    {   //если таблица обновилась
        int i=0;
        string rn1;
        string rn2;

        while(i<row.row.size())
        {
            rn1=row.row.at(i).at(1);
            rn2=row.row.at(i).at(2);

            if((vstr.at(0).compare(rn1.data())==0)&(vstr.at(1).compare(rn2.data())==0))
            {
                string rid=row.row.at(i).at(0);
                Event_BUS::getInstance() -> SendEvent((char *) "Replace_Row", 111, ReadID(), &vstr, &rid);
                break;
            }
            i++;
        }
    }
    else
    {
        //что то пошло не так
    }

    Event_BUS::getInstance() -> SendEvent((char *) "AddROWSQLiteTable", 111, ReadID(), &vstr);
    Event_BUS::getInstance() -> SendEvent((char *) "CloseSQLite_DB", 111, ReadID());
}
*/
//-------------------------------------------------
//Метод DataM_To_Str_db() переписан 20.01.17 конец
//-------------------------------------------------

void DataManager::DataM_To_Str_db()
{
    if(Data.DataM_Str.size()){  //Если поле DataM_str в структуре Data имеет не нулевой размер
        vector<string> vstr;    //Вектор строк в котором содержаться номер и серия ракеты, дата/время проверки, результат проверки
        vstr.push_back("'" + DataH.num + "'");     //и все данные по всем проверкам такие как время проверки, номер проверки, измеренный результат и общее время всех проверок
        vstr.push_back("'" + DataH.serialnr + "'");
        vstr.push_back("'" + DataH.date + "'");
        vstr.push_back("'" + State + "'");
        vstr.push_back("'" + to_string(mss) + "'");  //Получаем данные в формате НОМЕР РАКЕТЫ/СЕРИЙНЫЙ НОМЕР/ДАТА ВРЕМЯ/РЕЗУЛЬТАТ ПРОВЕРКИ/ОБЩЕЕ ВРЕМЯ ПРОВЕРКИ
        unsigned iterator = 5;  //Текущая проверка 5
        unsigned DataSize = Data.DataM_Str.size() + 5; //Временная переменная для хранения колличества проверок, считаем что у нас есть все проверки начиная с 1
        unsigned MaxData;   //Максимально возможное колличество проверок, зависит от типа ракеты
        if(R_Type == Tyngyska_TYPE || R_Type == Tyngyska_TYPE_E)
            MaxData = Tyngyska_MAXPROV;
        else if(R_Type == Kashtan_TYPE || R_Type == Kashtan_TYPE_E)
            MaxData = Kashtan_MAXPROV;
        while(iterator <= MaxData){ //Когда текущий номер проверки меньше общего колличества проверок
            if(iterator < DataSize){    //Если текущий номер проверки меньше колличества полученных проверок
                if(iterator == 5)      //Если текущий номер проверки равен 5
                    vstr.push_back(Data.DataM_Str.at(iterator - 5)); //в выходной вектор записываем только данные проверки
                else{
                    vstr.push_back(Data.DataM_Str.at(iterator - 5));    //иначе данные проверки и время между проверками
                    vstr.push_back(to_string(Data.DataM_tm.at(iterator - 6)));
                }
            }
            if(iterator >= DataSize){   //Если текущий номер проверки больше номера последней проверки, но меньше максимально возможного колличества проверок
                if(KPA_Rocket::flag)    //значит данные по этим проверкам не пришли
                {
                    vstr.push_back(NODATA_ENG);
                    vstr.push_back("'-'");
                }
                else
                {
                    vstr.push_back(NODATA_RUS);
                    vstr.push_back("'-'");
                }
            }
            iterator ++;    //номер проверки = номер проверки + 1
        }
        char *DBname;   //указатель символов на название файла БД
        if(KPA_Rocket::flag)
            DBname = "KPA_DataBase_eng.db"; //зависит от текущих настроек языка в программе
        else
            DBname = "KPA_DataBase_rus.db";
        Event_BUS::getInstance() -> SendEvent((char *) "CreateSQLiteDB", 111, ReadID(), (const char *)DBname);  //Посылаем события на созданин и открытие БД
        Event_BUS::getInstance() -> SendEvent((char *) "OpenSQLite_DB", 111, ReadID(), (const char *)DBname);   //Если БД уже создана то она только откроется иначе будет создана и откроется
        FindTable = false;  //Флаг указывающий на то найдена или нет таблица в БД
        for(char i = 0; i < TableName.size(); i++)
            if(ROCKET_ENG == TableName.at(i))   //проверяем создана ли таблица с общими сведениями, если нет то создаем ее
                FindTable = true;
        if(!FindTable){
            vector<string> vstrr;
            if (KPA_Rocket::flag)
            {
                vstrr.push_back(ROCKET_ENG);
                vstrr.push_back(PARTY_ENG);
                vstrr.push_back(SERIAL_ENG);
                vstrr.push_back(TIME_ENG);
                vstrr.push_back(STATE_ENG);
            }
            else
            {
                vstrr.push_back(ROCKET_ENG);
                vstrr.push_back(PARTY_RUS);
                vstrr.push_back(SERIAL_RUS);
                vstrr.push_back(TIME_RUS);
                vstrr.push_back(STATE_RUS);
            }
            Event_BUS::getInstance() -> SendEvent((char *) "CreateSQLiteTable", 111, ReadID(), &vstrr);
        }
        FindTable = false;
        if(R_Type == TUNGUSKA_ROCKET) //Если тип ракеты определен как тунгуска
        {
            for(char i = 0; i < TableName.size(); i++)
                if(TUNGUSKA_ENG == TableName.at(i)) //проверяем создана ли таблица с подробными сведениями по ракете тунгуска, если нет то создаем ее
                    FindTable = true;
            if(!FindTable)
            {
                vector<string> vstrr;
                if (KPA_Rocket::flag)
                {
                    vstrr.push_back(TUNGUSKA_ENG);
                    vstrr.push_back(PARTY_ENG);
                    vstrr.push_back(SERIAL_ENG);
                    vstrr.push_back(TIME_ENG);
                    vstrr.push_back(STATE_ENG);
                    vstrr.push_back(TIMEALL_ENG);
                    vstrr.push_back(string(VALUE_ENG) + string("5'"));
                }
                else
                {
                    vstrr.push_back(TUNGUSKA_ENG);
                    vstrr.push_back(PARTY_RUS);
                    vstrr.push_back(SERIAL_RUS);
                    vstrr.push_back(TIME_RUS);
                    vstrr.push_back(STATE_RUS);
                    vstrr.push_back(TIMEALL_RUS);
                    vstrr.push_back(string(VALUE_RUS) + string("5'"));
                }
                for(char i = 6; i < 35; i++)
                {
                    if (KPA_Rocket::flag)
                    {
                        vstrr.push_back(VALUE_ENG + to_string(i) + "'");
                        vstrr.push_back(TESTTIME_ENG + to_string(i) + " ms'");
                    }
                    else
                    {
                        vstrr.push_back(VALUE_RUS + to_string(i) + "'");
                        vstrr.push_back(TESTTIME_RUS + to_string(i) + " мс'");
                    }
                }
                Event_BUS::getInstance() -> SendEvent((char *) "CreateSQLiteTable", 111, ReadID(), &vstrr);
            }
            FindTable = false;
        }
        if(R_Type == KASHTAN_ROCKET)    //Если тип ракеты определен как каштан
        {
            for(char i = 0; i < TableName.size(); i++)
                if(KASHTAN_ENG == TableName.at(i))  //проверяем создана ли таблица с подробными сведениями по ракете каштан, если нет то создаем ее
                    FindTable = true;
            if(!FindTable)
            {
                vector<string> vstrr;
                if (KPA_Rocket::flag)
                {
                    vstrr.push_back(KASHTAN_ENG);
                    vstrr.push_back(PARTY_ENG);
                    vstrr.push_back(SERIAL_ENG);
                    vstrr.push_back(TIME_ENG);
                    vstrr.push_back(STATE_ENG);
                    vstrr.push_back(TIMEALL_ENG);
                    vstrr.push_back(string(VALUE_ENG) + string("5'"));
                }
                else
                {
                    vstrr.push_back(KASHTAN_ENG);
                    vstrr.push_back(PARTY_RUS);
                    vstrr.push_back(SERIAL_RUS);
                    vstrr.push_back(TIME_RUS);
                    vstrr.push_back(STATE_RUS);
                    vstrr.push_back(TIMEALL_RUS);
                    vstrr.push_back(string(VALUE_RUS) + string("5'"));
                }
                for(char i = 6; i < 32; i++)
                {
                    if (KPA_Rocket::flag)
                    {
                        vstrr.push_back(VALUE_ENG + to_string(i) + "'");
                        vstrr.push_back(TESTTIME_ENG + to_string(i) + " ms'");
                    }
                    else
                    {
                        vstrr.push_back(VALUE_RUS + to_string(i) + "'");
                        vstrr.push_back(TESTTIME_RUS + to_string(i) + " мс'");
                    }
                }
                Event_BUS::getInstance() -> SendEvent((char *) "CreateSQLiteTable", 111, ReadID(), &vstrr);
            }
        FindTable = false;
        }
        if(R_Type == KASHTAN_ROCKET)
            Event_BUS::getInstance() -> SendEvent((char *) "OpenSQLiteTable", 111, ReadID(), KASHTAN_ENG); //Если тип ракеты определен как каштан заносим данные в соответствующую таблицу БД
        else if(R_Type == TUNGUSKA_ROCKET)
            Event_BUS::getInstance() -> SendEvent((char *) "OpenSQLiteTable", 111, ReadID(), TUNGUSKA_ENG); //Если тип ракеты определен как тунгуска заносим данные в соответствующую таблицу БД
        Event_BUS::getInstance() -> SendEvent((char *) "AddROWSQLiteTable", 111, ReadID(), &vstr);
        vstr.resize(4);
        this -> row.title_colums.clear();
        this -> row.row.clear();
        Event_BUS::getInstance() -> SendEvent((char *) "OpenSQLiteTable", 111, ReadID(), "Rocket");
        Event_BUS::getInstance() -> SendEvent((char *) "ReadSQLite_Table", 111, ReadID());
        if(row.row.size() > 0)  //Если размер общей таблицы больше 0
        {
            int i=0;
            string rn1;
            string rn2;

            while(i<row.row.size()) //когда индекс меньше колличества записей в таблице
            {
                rn1=row.row.at(i).at(1);    //берем номер партии в i-той строке
                rn2=row.row.at(i).at(2);    //берем серийный номер в i-той строке

                if((vstr.at(0).compare(rn1.data())==0)&(vstr.at(1).compare(rn2.data())==0)) //если номер партии и серийный номер проверенной ракеты совпадают с ранее измеренной ракетой
                {
                    string rid=row.row.at(i).at(0);
                    Event_BUS::getInstance() -> SendEvent((char *) "Replace_Row", 111, ReadID(), &vstr, &rid);  //то заменяем эту запись на только что проверенную ракету
                    break;
                }
                i++;
            }
        }
        else
        {
            //что то пошло не так
        }

        Event_BUS::getInstance() -> SendEvent((char *) "AddROWSQLiteTable", 111, ReadID(), &vstr);  //заносим данные в таблицу
        Event_BUS::getInstance() -> SendEvent((char *) "CloseSQLite_DB", 111, ReadID());    //закрываем БД
    }
}

void DataManager::GetTableName(vector<string> TableName)    //получаем вектор с названиями таблиц и сохраняем их в переменную tablename
{
    char i = 0;
    while(i < TableName.size())
        this -> TableName.push_back(TableName.at(i++));
}

void DataManager::ClearData()   //метод который очищает и обнуляет все данные относящиеся к проверкам в данном классн
{
    Data.DataM_Ch.clear();
    Data.DataM_Str.clear();
    Data.DataM_tm.clear();
    R_Type.clear();
    Good = true;
    mss = 0;
    Event_BUS::getInstance() -> SendEvent((char *) "Del_Rocket", 0, ReadID());
}

void DataManager::GetTableRow(_row row) //метод для получения данных из таблицы, структура row содержит в себе все заголовки столбцов таблицы и данные из всех строк
{

    this -> row=row;
}

