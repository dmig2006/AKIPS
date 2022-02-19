#include "kashtan.h"
//bool KPA_Rocket::flag;
QString Kashtan::TakeStatus(unsigned char status)   //метод для получения статуса ракеты
{
    QString str;

    if(status==Kashtan_OK)  //если мктод получил байт 0xfd
    {
        str=tr(TESTOK_RUS); //строка str равна "годен"
        this->status=status;    //переменная status равна полученному байту
    }
    else    //иначе
    {
        if(status==Kashtan_ERROE)   //если байт на вхрде равен 0xfc
        {
            str=tr(TESTFAIL_RUS);   //str равна "браку"
            this->status=status;    //переменная status равна полученному байту
        }
        else    //иначе
        {
            str=""; //str пустая строка (битвй байт)
            this->status=0;
            err=1;  //произошла ошибка
        }
    }

    return str;

}

QString Kashtan::TakeProverka(unsigned char pr) //метод для определения единиц измерения того что измеряем
{
    QString str;

    prov=pr;
    if(pr==5)   //если 5 проверка то еденицы измерения МОм и так дальше по аналогии, см. протокол проверок
        if (KPA_Rocket::flag)
            data_unit = "mOm";
        else
            data_unit = "мОм";
    else
    if((pr==8)|(pr==9)|(pr==30))
        if (KPA_Rocket::flag)
            data_unit = "mA";
        else
           data_unit="мА";

    else
    if((pr==18)|(pr==21))
        if (KPA_Rocket::flag)
            data_unit = "ms";
        else
            data_unit="мс";
    else
    if(pr==31)
        if (KPA_Rocket::flag)
            data_unit = "imp";
        else
            data_unit="Имп";
    else
        if (KPA_Rocket::flag)
            data_unit = "mV";
        else
            data_unit="мВ";

    str=QString::number(pr);

    return str;
}

QString Kashtan::TakeData(int32_t data) //метод для коррекции измеренных значений
{
    QString str;

    if(data & 0x800000) //так как измеряемое значение приходит в виде последовательности из 3 байт при этом старший бит старшего ьайта измерения может быть знаковым проверяем это
    {

        if((prov==6)|(prov==7)|(prov==19)|(prov==20)|((prov>=10)&(prov<=17))|((prov>=22)&(prov<=29)))   //если проверка равна 6. 7, 19, 20, 10-17 или 22-29 то корректируем знаковый бит так как измерения зранятся в 4 байтной переменной
        {
            data = (data ^ 0x00800000) * -1;
        }
    }
    this->data=data;
    if(prov==5) //все по аналогиис предыдущим методом (см протокол проверок)
    {
        if((int32_t)data>3000) str="> 3000 "+data_unit;
        else
        str=QString::number((int32_t)data)+" "+data_unit;
        return str;

    }else if(prov == 18 || prov == 21){
        if(data > 99999)
            str = "> 100 " + data_unit;
        else
            str = QString::number((int32_t) data) + " " + data_unit;
    }else if(prov < 32 && prov > 5 && (prov != 18 || prov != 21))
        str = QString::number((int32_t) data) + " " + data_unit;
    else    //если номер проверки некорректен (произошла ошибка)
    {
        if (KPA_Rocket::flag)
                    str = NOTCHECK_ENG;
                else
                    str = NOTCHECK_RUS;
        err=1;
    }
    return str;
}

QString Kashtan::TakeDati() //метод для определения пороговых величин измеряемых значений (см протокол проверок)
{
    QString str;
    if(prov==5)
    {
        str="< 2500 " + data_unit;
    }
    else
    if(prov==6)
    {
        str="< -9000 " + data_unit;
    }
    else
    if(prov==7)
    {
        str="> 11700 " + data_unit;
    }
    else
    if(prov==8)
    {
        if(data<1300) str="> 900 " + data_unit;
        if(data>=1300) str="< 1700 " + data_unit;
    }
    else
    if(prov==9)
    {
        if(data<1600) str="> 950 " + data_unit;
        if(data>=1600) str="< 2250 " + data_unit;
    }
    else
    if((prov==10)|(prov==11))
    {
        if(data<0) str="> -400 " + data_unit;
        if(data>=0) str="< 400 " + data_unit;
    }
    else
    if((prov==12)|(prov==14))
    {
        if(data<-1600) str="> -2350 " + data_unit;
        if(data>=-1600) str="< -840 " + data_unit;
    }
    else
    if((prov==13)|(prov==15))
    {
        if(data<1600) str="> 840 " + data_unit;
        if(data>=1600) str="< 2350 " + data_unit;
    }
    else
    if((prov==16)|(prov==19)|(prov==26)|(prov==29))
    {
        if(data<7000) str="> 5300 " + data_unit;
        if(data>=7000) str="< 9200 " + data_unit;
    }
    else
    if((prov==17)|(prov==20)|(prov==27)|(prov==28))
    {
        if(data<-7000) str="> -9200 " + data_unit;
        if(data>=-7000) str="< -5300 " + data_unit;
    }
    else
    if((prov==22)|(prov==25))
    {
        if(data<-5000) str="> -10500 " + data_unit;
        if(data>=-5000) str="< -2000 " + data_unit;
    }
    else
    if((prov==18)|(prov==21))
    {
        str="< 100 " + data_unit;
    }
    else
    if((prov==23)|(prov==24))
    {
         str="< -11700 " + data_unit;
    }
    else
    if(prov==30)
    {
        if(data<5000) str="> 3150 " + data_unit;
        if(data>=5000) str="< 6050 " + data_unit;
    }
    else
    if(prov==31)
    {
         str="10 " + data_unit;
    }
    else    //если номер проверки некорректен
    {   if (KPA_Rocket::flag)
            str = NOTCHECK_ENG;
        else
            str = NOTCHECK_RUS;
        err=1;
    }

     return str;
}

QString Kashtan::TakeType()
{
    return Kashtan_TYPE;
}

void Kashtan::ClearRocket() //метод сброса
{
    prov=0; dati.clear();data=0;data_unit.clear();status=0;err=0;

}

unsigned char Kashtan::TakeProv(){
    return prov;
}
