/**
  здесь определяются 2 класса отвечающие за обработку данных по тунгуске и каштану а так же общий класс ракет см комментарии ниже
  */

#ifndef KPA_ROCKET_H
#define KPA_ROCKET_H

#define DISABLEDEDIT
#define _TRANSLATE
//#define LOG

#define TESTOK_RUS "ИСПРАВНО"
#define TESTOK_ENG "GOOD"
#define TESTFAIL_RUS "БРАК"
#define TESTFAIL_ENG "BRAK"
#define NOTCHECK_RUS "Нет такой проверки!!"
#define NOTCHECK_ENG "not this test!!"

#include <sys/types.h>

#include <QCoreApplication>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>
#include <QVector>
#include <vector>

#include "eventmap.h"
#include "event_bus.h"
#include "Delegate.h"
#include "event.h"
#include "md_object.h"

#include "error.h"
#include "mixik.h"

using namespace std;

#define Tyngyska_OK 0xFB
#define Tyngyska_ERROE 0xFA
#define Tyngyska_TYPE "9М311-1М"
#define Tyngyska_TYPE_E "9M311-1M"
#define Tyngyska_MAXPROV 34

#define Kashtan_OK 0xFD
#define Kashtan_ERROE 0xFC
#define Kashtan_TYPE "9М311-1Э"
#define Kashtan_TYPE_E "9M311-1E"
#define Kashtan_MAXPROV 31

#define KPA_ROCKET_ERROR_SIZE_PACKEG 100

class iRocket   //интерфейс ракет, и каштан и тунгуска должны его реалтзоввывать согласно протоколу проверок, см комментари  к соответствующему коду
{
public:
    virtual QString TakeStatus(unsigned char status)=0;
    virtual QString TakeProverka(unsigned char pr)=0;
    virtual QString TakeData(int32_t data)=0;
    virtual QString TakeDati()=0;
    virtual QString TakeType()=0;
    virtual void ClearRocket()=0;
    virtual char TakeERR()=0;
    virtual unsigned char TakeProv() = 0;

private:

};

class Tyngyska: public iRocket, public QObject  //класс тунгуски
{
    public:
       QString TakeStatus(unsigned char status);    //метод возвращающий статус ракеты
       QString TakeProverka(unsigned char pr);  //метод возвращающий еденицы измерения
       QString TakeData(int32_t data);  //метод корректировки измеренных величин
       QString TakeDati();  //метод возвращающий пороговые величины
       QString TakeType();  //метод для определения типа ракеты
       unsigned char TakeProv();
       char TakeERR(){return err;}
       void ClearRocket();  //метод очистки и обнуления

private:
       unsigned char status;
       unsigned char prov;
       QString dati;
       int16_t data;
       //QString type;
       char err;
       QString data_unit;


};

class Kashtan: public iRocket, public QObject   //аналогично тунгуске
{
    public:
       QString TakeStatus(unsigned char status);
       QString TakeProverka(unsigned char pr);
       QString TakeData(int32_t data);
       QString TakeDati();
       QString TakeType();
       unsigned char TakeProv();
       void ClearRocket();
       char TakeERR(){return err;}
private:
       unsigned char status;
       unsigned char prov;
       QString dati;
       int16_t data;
       //QString type;
       char err;
       QString data_unit;
};

struct FourByte //4 байтовая структура
{
    char c1;
    char c2;
    char c3;
    char c4;
};

union FourByteINT   //ещё одна четырез байтовая структура, в отличие от предыдущей может быть представлена как int , в то же время имея побайтный доступ
{
    struct FourByte tbyte;
    int32_t i;
};

class KPA_Rocket: public MDObject   //общий класс ракет
{
    //Q_OBJECT
public:
    KPA_Rocket(){};
    KPA_Rocket(unsigned short int id_mdobj, string name_mdobj);
    void KPA_RocketClear(); //метод очистки
    ~KPA_Rocket();

#ifdef _TRANSLATE
    void translate(bool pFlag);
    bool flagTranslate;
    static bool flag;
#endif

    //void Data_Analysis(QByteArray *data);

//public slots:
    void KPA_Test(vector<char> data);   //метод тестирования
    void Update();  //метод обновления

//signals:
  //  void Rocket_Test(QVector<QString>*data);
  //  void Rocket_Error(int);
private:
    //тип ракеты, статус, проверка, измеренно,допустимо
    QVector<QString> report;    //вектор с результатом проверки
    iRocket *rocket;    //переменная для хранения ракеты, можкт хранить как каштан так и тунгуску


};

#endif // KPA_ROCKET_H
