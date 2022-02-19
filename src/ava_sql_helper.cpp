#include "ava_sql_helper.h"
#include <QString>

void SQLite_Helper::ADDSQLCommand(const char *command, const char *value, std::string *out)
{

    if(out->size()>0)
    {
        *out=*out+" "+command+" "+value;

    }
    else
        *out=*out+command+" "+value;

}

void SQLite_Helper::ADDSQLValues(const char *command, vector<string> *data, string *out)
{
    if(data!=0&&out!=0)
    {
    if(out->size()>0)
    {
        if(command!=0) *out=*out+" "+command+" (";
        else *out=*out+" (";

    }
    else
        if(command!=0) *out=*out+command+" (";
        else *out=*out+" (";

    string str;
    Helper_Converter::Packeg_argv(data,&str,',');
    *out=*out+str+")";
    }

}


void SQLite_Helper::ACharToHex(char in, char *out)
{
    unsigned char l=0;
    unsigned char h=0;

    l=in<<4;
    l=l>>4;
    h=(unsigned char)in>>4;

    if(h>9)
    {
         *out=h+65;
    }
    else
    {
        *out=h+48;
    }
    if(l>9)
    {
             *(out+1)=h+65;
    }
    else
    {
        *(out+1)=l+48;
    }
}
string SQLite_Helper::UnsignedCharToHex(char c)
{
    char ccc[2];
    string str;
    ccc[0] = (c & 0xf0) >> 4;
    ccc[1] = (c & 0x0f);
    if(ccc[0] >9 && ccc[0] < 16)
        ccc[0] += 55;
    else
        ccc[0] += 48;
    if(ccc[1] >9 && ccc[1] < 16)
        ccc[1] += 55;
    else
        ccc[1] += 48;
    str += ccc[0];
    str += ccc[1];
    return str;

}

std::string TestHexString(std::string pStr)
{
    QString str1;
    std::string pStrRead;
    int number = 0;
    str1 = QString::fromStdString(pStr);
    number = str1.toInt();
    str1.clear();
    str1 = QString::number(number,16);
    pStrRead = str1.toStdString();
    return pStrRead;

}
