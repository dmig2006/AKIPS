/*! \file kpa_com.h
    \brief Работа с СОМ-портом
  Класс KPA_COM реализует объект спроектированный для работы с СОМ-портом
  с помощью событий.
  Входящие события:
  OpenCOM() открыть СОМ-порт (если СОМ портов несколько то вызовет связонное событие "ChoosePort"(vector<string>))
  OpenCOMX(char *path) открыть СОМ-порт по path
  ClosedPort()
  WriteCOM(char *data,int len)
  ReadCOM()
  ListenCOM(char type)
  WriteParam(char *param,int set_param)
  ReadParam(char *param)
  Исходящие события:
  DataRead(vector<char>) - Данные пришли
  Param(char status,int param)


*/

#ifndef KPA_COM_H
#define KPA_COM_H

#define kriticaltime 1000 /*9300*/
#define kriticalbyte /*5*/ 35 //При usb-com
//#define _BITYEDANNBLE
//#define _READTEST
#define _CRITICAL_READ
//#define ROCK_TEST

#define TESTCLASS

#include <vector>
#include <map>
#include <string>
#include <sys/types.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>
#include <qthread.h>
#include <thread>
#include <QTimer>

#include "eventmap.h"
#include "event_bus.h"
#include "Delegate.h"
#include "event.h"
#include "md_object.h"

#ifdef TESTCLASS
    #include "error.h"
#endif

using namespace std;

/**
 * @brief The Parity enum
 */
enum Parity
{
    NoParity, EvenParity, OddParity, SpaceParity, MarkParity, UnknownParity
};
/**
 * @brief The StopBit enum
 */
enum StopBit
{
    OneStop, OneAndHalfStop, TwoStop, UnknownStopBits
};
/**
 * @brief The DataBit enum
 */
enum DataBit
{
    Data5, Data6, Data7, Data8, UnknownDataBits
};
/**
 * @brief The Baud enum
 */
enum Baud
{
    B1200,B2400,B4800,B9600,B19200,B38400,B547600,B115200, UnknownBaud
};

enum CRC_CFG
{
    NONE,CRC8,CRC16,CR32
};

//! \class KPA_COM Работа с СОМ-портом
/*!
  Класс KPA_COM реализует объект спроектированный для работы с СОМ-портом
  с помощью событий.<br>
  Входящие события Event IN:<br>
  OpenCOM() открыть СОМ-порт (если СОМ портов несколько то вызовет связонное событие "ChoosePort"(vector<string>))<br>
  OpenCOMX(char *path) открыть СОМ-порт по path<br>
  ClosedPort()<br>
  WriteCOM(char *data,int len)<br>
  ReadCOM()<br>
  ListenCOM(char type)<br>
  WriteParam(char *param,int set_param)<br>
  ReadParam(char *param)<br>
  Исходящие события Event OUT:<br>
  ChoosePort(vector<string> vcom) Выбери СОМ-порт<br>
  ChangesStatus(char status) Статус изменен<br>
  ErrorCOM(char error) Ошибка <br>
  Param(string param,int data)Параметр<br>
  DataRead(vector<char> data) Данные пришли<br>
  DataWrite(int len) Данные записаны<br>

  \sa MDObject, EventMap
*/
class KPA_COM: public QObject, public MDObject //,EventMap
{
    Q_OBJECT
public:
    void AddThread();

    /**
     * @brief Конструктор
     */
    KPA_COM(){};
    KPA_COM(unsigned short int id_mdobj, string name_mdobj);
    /**
     * @brief Виртуальный Диструктор
     */
    virtual ~KPA_COM(){};

protected slots:
    /**
     * @brief Event IN. Прочитать данные с порта
     * вызовет событие DataRead(vector<char> data)
     */
    void ReadCOM();

protected:
//Event IN
    /**
     * @brief Event IN. Открыть порт
     * Если портов нескольво вызовет событие выбора СОМ-порта ChoosePort(vector<string> vcom)
     */
    void OpenCOM();
    /**
     * @brief Event IN. Открыть определенный СОМ-порт
     * @param path путь к СОМ порту
     */
    void OpenCOMX(int id);
    /**
     * @brief Event IN. Закрыть СОМ-порт
     */
    void ClosedPort();
    /**
     * @brief Event IN. Записать данные
     * @param data указатель на массив байт
     * @param len кол-во байт которых нужно передать
     */
    void WriteCOM(char *data,int len);

    /**
     * @brief Event IN. Перейти в режим прослушки СОМ-порта
     * @param type 0-отключить прослушку 1-включить прослушку
     */
    void ListenCOM(char type);
    /**
     * @brief Event IN. Записать параметр
     * @param param имя параметра
     * @param set_param новое значение
     * Вызовет событие Param(string param,int data) с новым установленным значением
     */
    void WriteParam(char *param,int set_param);
    /**
     * @brief Event IN. Прочитать значение параметра
     * @param param имя параметра
     * Вызовет событие Param(string param,int data) с текущим значением данного параметра
     */
    void ReadParam(char *param);
    /**
     * @brief Дайте имя и ид MDObject
     */
    void Give_MDObject_Name();


 //Event OUT
    /**
     * @brief Event OUT. Выберите порт плз
     * @param vcom список доступных портов
     * После выбора вызовите плз OpenCOMX(string path)
     */
    void ChoosePort(QList<QSerialPortInfo> *listqs);

    /**
     * @brief Event OUT. Статус был изменен
     * @param status новый статус
     */
    void ChangesStatus(char status);

    /**
     * @brief Event OUT. Произошла ошибка
     * @param error номер ошбики
     */
    void ErrorCOM(char error);
    /**
     * @brief Event OUT. Получите значение параметра
     * @param param имя параметра
     * @param data значение параметра
     */
    void Param(string param,int data);
    /**
     * @brief Event OUT. Данные пришли
     * @param data
     */
    void DataRead(vector<char> data);
    /**
     * @brief DataWrite Данные записаны
     * @param len кол-во записанных данных
     */
    void DataWrite(int len);
    /**
     * @brief Вомзите Имя мое и ИД
     */
    void Take_MDObject_Name();



private:
    //! 0-откл 1-подк 2- режим прослушки 3-жду данных 4-Пишу в порт -1 ошибка
    char status;

    //! 0-жду подкл 1-подключаюсь 2-слушаю 3-передаю 4-читаю -1 заблокирован
    char state;
    /// Ошибки
    char error;
    ///Здесь хранится конфигурация порта
    map<string,int16_t> param;
    ///информация о портах
    QList<QSerialPortInfo> list_info;
    ///класс сом-порта
    QSerialPort serial;
    ///текущая полученные данные
    vector<char> data;
    ///таймер по переполнению которого (каждую мс) происходит чтение байта данных
    QTimer m_timer;
    ///флаг проверки чтения пакетов, = true после получения первого пакета, = false после получения брака или последней прорверки
    bool readpacket = false;
    ///флаг проверки чтения байтов, = true после получения первого байта, = false после окончания чтения пакета или при переполнении
    ///таймера чтения байтов (в течение 5 мс не пришел следующий байт)
    bool readbyteb = false;
    ///флаг ошибки чтения пакета, = true если в каком-то из пакетов произошла ошибка CRC, иначе = false
    bool brokendata = false;
    ///если флаг readpacket == true, при каждой операции считывания байта увеличивается на 1.
    ///при достижении значения readnr == kriticaltime COM порт отключается, выводится ошибка, тк следующий пакет не пришел
    ///по окончании приема пакета сбрасывается на 0
    int readnr = 0;
    ///если флаг readbyte == true, при каждой операции считывания байта увеличивается на 1.
    ///при достижении значения readbyte == kriticalbyte все данные записанные в data стираются
    ///при приеме каждого байта сбрасывается в 0
    int readbyte = 0;
    ///переменнай cyrrentpacknr отвечает за номер проверки которая ожидается в данный момент
    ///необходима для проверки все ли пакеты пришли не затерялся ли 1
    int cyrrentpacknr = 5;
    ///это заплатка на случай!!!!! если между пакетами прийдёт мусорный байт
    ///равный от 0хfa до 0xfd, и если!!!! в течение 5 мс после него посмеет прийти
    ///ещё один мусорный байт который задаст номер пакета но при этом полный пакет так и не
    ///будет сформирован
    int cyrrentpacknrbuff = cyrrentpacknr;
    ///флаг для определения пропажи пакетов
    bool loosepacket = false;
    /**
    * @brief CRC8 Расчет CRC8
    * @param data строка данных
    * @param len кол-во символов
    * @return значение CRC8
    */
   unsigned char Take_CRC8(char *data,int16_t len);
   ///очистка буффера при включении COM порта
   void ClearBuff();
   ///очистка всяких флажочков
   void Clear();

   int testBuffer = 5;

#ifdef UPDATEBUTTON
   bool testComFlag = false;
#endif

};


#endif // KPA_COM_H
