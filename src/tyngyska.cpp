#include "tyngyska.h"

QString Tyngyska::TakeStatus(unsigned char status)
{
    QString str;

    if(status==Tyngyska_OK)
    {
        str=tr(TESTOK_RUS);
        this->status=status;
    }
    else
    {
        if(status==Tyngyska_ERROE)
        {
            str=tr(TESTFAIL_RUS);
            this->status=status;
        }
        else
        {
            str="";
            this->status=0;
            err=1;
        }
    }

    return str;

}

QString Tyngyska::TakeProverka(unsigned char pr)
{
    QString str;

    prov=pr;

    if(pr==5)
        if (KPA_Rocket::flag)
            data_unit="mOm";
        else
            data_unit = "мОм";
    else
    if((pr==8)|(pr==9)|(pr==34))
        if (KPA_Rocket::flag)
            data_unit = "mA";
        else
           data_unit="мА";
    else
    if((pr==22)|(pr==29))
        if (KPA_Rocket::flag)
            data_unit = "ms";
        else
            data_unit="мс";
    else
        if (KPA_Rocket::flag)
            data_unit = "mV";
        else
            data_unit="мВ";

    str=QString::number(pr);

    return str;
}

QString Tyngyska::TakeData(int32_t data)
{
    QString str;

    if(data & 0x800000)
    {
        if((prov==6)|(prov==7)|((prov>=10)&(prov<=21))|((prov>=23)&(prov<=28))|((prov>=30)&(prov<=33)))
        {
            data=  (data ^ 0x00800000) * -1;
        }
    }
    this->data=data;
    if(prov==5)
    {
        if(data>3000) str="> 3000 "+data_unit;
        else
        str=QString::number((int32_t)data)+" "+data_unit;
        return str;

    }
    else if(prov == 22 || prov == 29){
        if(data > 99999)
            str = "> 100 " + data_unit;
        else
            str = QString::number((int32_t) data) + " " + data_unit;
    }
    else if(prov <= 34 && prov > 5 && (prov != 22 || prov != 29))
        str = QString::number((int32_t) data) + " " + data_unit;
    else{
        if (KPA_Rocket::flag)
                    str = NOTCHECK_ENG;
                else
                    str = NOTCHECK_RUS;
        err=1;
    }
    return str;
}

QString Tyngyska::TakeDati()
{
    QString str;
    if(prov==5)
    {
        str="< 2500 " + data_unit;
    }
    else
    if((prov==6)|(prov==31)|(prov==32))
    {
        str="< -12300 " + data_unit;
    }
    else
    if(prov==7)
    {
        str="> 12300 " + data_unit;
    }
    else
    if(prov==8)
    {
        if(data<1500) str="> 900 " + data_unit;
        if(data>=1500) str="< 2100 " + data_unit;
    }
    else
    if(prov==9)
    {
        if(data<1500) str="> 800 " + data_unit;
        if(data>=1500) str="< 2250 " + data_unit;
    }
    else
    if((prov==10)|(prov==11)|(prov==20)|(prov==27))
    {
        if(data<0) str="> -400 " + data_unit;
        if(data>=0) str="< 400 " + data_unit;
    }
    else
    if((prov==12)|(prov==14))
    {
        if(data<-1500) str="> -2200 " + data_unit;
        if(data>=-1500) str="< -900 " + data_unit;
    }
    else
    if((prov==13)|(prov==15))
    {
        if(data<1500) str="> 900 " + data_unit;
        if(data>=1500) str="< 2200 " + data_unit;
    }
    else
    if((prov==16)|(prov==23))
    {
        if(data<7000) str="> 5600 " + data_unit;
        if(data>=7000) str="< 8800 " + data_unit;
    }
    else
    if(((prov>=17)&(prov<=19))|(prov==21)|(prov==28)|((prov>=24)&(prov<=26)))
    {
        if(data<-7000) str="> -8800 " + data_unit;
        if(data>=-7000) str="< -5600 " + data_unit;
    }
    else
    if((prov==22)|(prov==29))
    {
        str="< 100 " + data_unit;
    }
    else
    if((prov==30)|(prov==33))
    {
        if(data<-5000) str="> -10000 " + data_unit;
        if(data>=-5000) str="< -2000 " + data_unit;
    }
    else
    if(prov==34)
    {
        if(data<4500) str="> 3200 " + data_unit;
        if(data>=4500) str="< 5200 " + data_unit;
    }
    else
    {
        if (KPA_Rocket::flag)
                    str = NOTCHECK_ENG;
                else
                    str = NOTCHECK_RUS;
        err=1;
    }


     return str;
}

QString Tyngyska::TakeType()
{
    return Tyngyska_TYPE;
}

void Tyngyska::ClearRocket()
{
    prov=0; dati.clear();data=0;data_unit.clear();status=0;err=0;

}

unsigned char Tyngyska::TakeProv(){
    return prov;
}
