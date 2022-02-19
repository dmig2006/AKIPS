#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "md_object.h"
#include "event_bus.h"
#include "Delegate.h"
#include "ava_sqlite.h"

#include <vector>
#include <string>
#include <time.h>
#include <QVector>
#include <QString>

/*  TUNGUSKA_ROCKET - название ракеты
 *  KASHTAN_ROCKET - название ракеты
 *  TUNGUSKA_TEST - номер последней проверки
 *  KASHTAN_TEST - номер последней проверки
*/
#define TUNGUSKA_ROCKET "9М311-1М"
#define KASHTAN_ROCKET "9М311-1Э"
#define TUNGUSKA_TEST "34"
#define KASHTAN_TEST "31"
#define FALSE_RUS "БРАК"
#define FALSE_ENG "BRAK"

/*
 * Следующие определения нужны для формирования БД на разных языках
*/
#define TESTNUM_RUS "'Проверка № "
#define TESTNUM_ENG "'Test № "
#define NODATA_RUS "'Нет данных'"
#define NODATA_ENG "'Not date'"
#define ROCKET_ENG "Rocket"
#define TUNGUSKA_ENG "R9M311_1M"
#define KASHTAN_ENG "R9M311_1E"
#define PARTY_RUS "'Номер партии'"
#define PARTY_ENG "'Number partia'"
#define SERIAL_RUS "'Серийный номер'"
#define SERIAL_ENG "'Serial number'"
#define TIME_RUS "'Дата_Время'"
#define TIME_ENG "'Date_Time'"
#define STATE_RUS "'Статус'"
#define STATE_ENG "'Status'"
#define TIMEALL_RUS "'Общее время проверки'"
#define TIMEALL_ENG "'Test time all'"
#define VALUE_RUS "'Данные проверки "
#define VALUE_ENG "'Test value "
#define TESTTIME_RUS "'Время проверки "
#define TESTTIME_ENG "'Test time "

using namespace std;
/**
 * @brief The DataM struct структура для хранения данных о проведенных проверках
 * DataM_Ch хранит пришедшие с порта байты
 * DataM_Str хранит уже готовые строки о результатах проверки, т.е. в каждой строке содержится
 * информация о проверках в формате №проверки - измеренное значение - контрольное значение
 * DataM_tm - хнанит время между проверками в мс.
 */
struct DataM{
    vector<char> DataM_Ch;
    vector<string> DataM_Str;
    vector<clock_t> DataM_tm;
};
/**
 * @brief The DataHead struct хранит данные о ракете
 * num - номер ракеты
 * serialnr - серийный номер
 * date - воемя и дату проверки
 */
struct DataHead{
    string num;
    string serialnr;
    string date;
    //string state;
};

class DataManager: public MDObject
{
public:
    DataManager(){};
    DataManager(unsigned short int id_mdobj, string name_mdobj);
    ~DataManager();
    /**
     * @brief AddDataM_Ch метод для заполнения поля DataM_Ch структуры DataM
     * @param Data получает вектор байтов из класса KPA_Com
     * @return
     *
     */
    char AddDataM_Ch(vector<char> Data);
    /**
     * @brief AddDataM_Str метод для заполнения поля DataM_Str структуры DataM
     * @param Data получает вектор строк из класса KPA_Rocket
     * @return
     */
    char AddDataM_Str(QVector<QString> Data);
    /**
     * @brief AddDataHead метод для получения серийного номера и номера партии ракеты
     * @param num - номер
     * @param serialnr - номер партии
     * @return
     */
    char AddDataHead(string num, string serialnr);
    /**
     * @brief DataM_To_Str_db метод для записи данных в БД по окончании проверки. Срабатывает при сохранении данных
     * проверки
     */
    void DataM_To_Str_db();
    /**
     * @brief GetTableName метод для получения названий таблиц из БД, необходим для проверки
     * наличия нужных таблиц а БД
     * @param TableName вектор строк с названиями таблиц
     */
    void GetTableName(vector<string> TableName);
    void GetTableRow(_row row);
    /**
     * @brief ClearData метод для очистки результаттов проверки срабатывает при нажатии
     * кнопки обновить и при разрыве соединения
     */
    void ClearData();
private:
    /**
     * @brief R_Type содержит тип ракеты
     * State содержит состояние годен/брак
     */
    string R_Type, State;
    /**
     * @brief t необходимо для вычисления времени между проверками
     */
    time_t t;
    /**
     * @brief aTm то же самое
     */
    struct tm *aTm;
    DataHead DataH;
    DataM Data;
    /**
     * @brief ms и опять вычисление времени между проверками
     */
    clock_t ms, mss;
    /**
     * @brief TableName вектор с названиями таблиц БД
     */
    vector<string> TableName;
    /**
     * @brief FindTable флаг отвечающий за то, найдена таблица в БД или нет
     */
    bool FindTable = false;
    /**
     * @brief Good флаг исправности ракеты
     */
    bool Good = true;

    _row row;
    //vector<string> *DataBaseString;
};

#endif // DATAMANAGER_H
