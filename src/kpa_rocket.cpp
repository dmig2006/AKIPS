#include "kpa_rocket.h"

KPA_Rocket::KPA_Rocket(unsigned short id_mdobj, string name_mdobj) : MDObject(id_mdobj,(char*)name_mdobj.data())
{
     rocket = NULL; //изначально неизвестно какая ракета будет проверяться
     report.resize(5);  //результат измерений вснгда состоит из 5 полей
     ADDEvent((char *) "DataRead", new Delegate(this, &KPA_Rocket::KPA_Test), 100); //регистрируем события (см описание класса md_object и связанных с ним классов)
     ADDEvent((char *) "TestOK");
     ADDEvent((char *) "TestERR");
     ADDEvent((char *) "Del_Rocket", new Delegate(this, &KPA_Rocket::KPA_RocketClear), 0);

#ifdef DISABLEDEDIT
      ADDEvent((char *) "disabled_edit");
#endif

     Event_BUS::getInstance() -> AddMDObject(this); //добавляем события в event_bus
}

KPA_Rocket::~KPA_Rocket()
{
#ifdef LOG
    cout << "Delete KPA_Rocket" << endl;
#endif
}

void KPA_Rocket::KPA_Test(vector<char> data)
{
    int size=data.size();   //определяем сколько байт получили на вход (должно быть 5 байт без crc, так как проверка crc проходит в классе kpa_com)
    bool set = false; //флаг определяющий окончание проверки (брак или последняя проверка)
    if(size == 5){  //если получили 5 байт
        if(((unsigned char) data.at(0) == (unsigned char) Tyngyska_OK || (unsigned char) data.at(0) == (unsigned char) Tyngyska_ERROE) && !rocket)  //если первый байт соответствует тунгуске
            rocket = new Tyngyska();    //то переменная rocket хранит в себе экземпляр класса тунгуска
        else if(!rocket)
            rocket = new Kashtan(); //иначе каштан
        report[0] = rocket -> TakeType();   //выполняем все проверки определенные в классах каштан и тунгуска (проверки выполняются в соответствие с тем, экземпляр какого коасса хранит rocket)
        report[1] = rocket -> TakeStatus(data.at(0));
        report[2] = rocket -> TakeProverka(data.at(1));
        struct FourByte mtb;    //создаем четврехбайтные структуры и заносим в них измеренные данные
        FourByteINT umtb;
        mtb.c4 = 0x00;
        mtb.c3 = data.at(2);
        mtb.c2 = data.at(3);
        mtb.c1 = data.at(4);
        umtb.tbyte = mtb;
        report[3] = rocket -> TakeData(umtb.i); //продолжаем проверки
        report[4] = rocket -> TakeDati();
        if(report[1] == TESTFAIL_RUS || report[1] == TESTFAIL_ENG ||
                (report[0] == Kashtan_TYPE && rocket -> TakeProv() == Kashtan_MAXPROV) ||
                (report[0] == Tyngyska_TYPE && rocket -> TakeProv() == Tyngyska_MAXPROV))   //если прошла последняя проверка
        {
            set = true; //устанавливаем флаг
#ifdef DISABLEDEDIT
            Event_BUS::getInstance() -> SendEvent((char *) "disabled_edit", 0, ReadID());
#endif
        }
#ifdef _TRANSLATE

        if (flag)
        {
            if (report[1] == TESTFAIL_RUS)
                report[1] = TESTFAIL_ENG;
            else if (report[1] == TESTOK_RUS)
                report[1] = TESTOK_ENG;
        }

#endif
    }   //если пришло не 5 байт
    else
    {
        Event_BUS::getInstance() -> SendEvent((char *) "TestERR", 0, ReadID(), KPA_ROCKET_ERROR_SIZE_PACKEG);   //произошла ошибка
    }

    if(rocket -> TakeERR() == 0)    //емли ошибок не было
    {
        Event_BUS::getInstance() -> SendEvent((char *) "TestOk", 110, ReadID(), report);    //послать данные проверок в datamanager
        if(set)
        {
            Event_BUS::getInstance() -> SendEvent((char *) "TestOk", 104, ReadID(), report);   //если это была последняя проверка то послать данные в графическую оболочку

        }
    }
    else
    {
        Event_BUS::getInstance() -> SendEvent((char *) "TestERR", 0, ReadID(),ERROR_ROCKET/*rocket -> TakeERR()*/ );   //если произошла ошибка
    }

}
void KPA_Rocket::Update()
{
    rocket -> ClearRocket();    //обнулить
}

void KPA_Rocket::KPA_RocketClear(){
    if(rocket){
        delete rocket;
        rocket = NULL;
    }
}
