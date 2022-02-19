#ifndef AVA_CXPOH_H
#define AVA_CXPOH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <QDateTime>

//#include "kpa_def.h"


#define RANDOM_PACKEG 10
#define MAX_SIZE_PACKEG 5000
#define NAME_FILE "cxpoh.dat"
#define BAD_CXPOH_PATH "log/"

/* в самом первой packeg в первых 4 байтах хранится
 *  информация сколько нормальных пакетов записано
 *
*/


/*  Упаковка данных в 16 байт
 *  0 - байт результата проверки если меньше 240 то сгенерирован случайно
 *
 *  1..3 - Серия изделия
 *  4..7 - Номер Изделия
 *  8 - Номер проверки (при годен случайные цисла)
 *  9..10 - Измеренное значение
 *  11 - День
 *  12 - месяц
 *  13 - год
 *  14 - час
 *  15 - минуты
 */


struct BitField
{
    unsigned char bit0:1;
    unsigned char bit1:1;
    unsigned char bit2:1;
    unsigned char bit3:1;
    unsigned char bit4:1;
    unsigned char bit5:1;
    unsigned char bit6:1;
    unsigned char bit7:1;
};

union BYTE //8bit
{
    struct BitField bit;
    unsigned char data;
};

struct TwoHalfByte
{
    unsigned char hb1:4;
    unsigned char hb2:4;
};
struct HalfByte
{
    unsigned char hb:4;

};

union UHByte
{
    struct TwoHalfByte hb;
    unsigned char uc;
};

struct Packeg
{
    unsigned char data[16];
    unsigned char hash[16];
};

struct NormData
{
    unsigned char data_com[2];
    unsigned char proverka;
    unsigned char status;
    unsigned char day;
    unsigned char mounth;
    unsigned char years;
    unsigned char hour;
    unsigned char min;
    unsigned char serial[3];
    unsigned char num_rocket[4];
};


struct Block4
{
    QDateTime data;
    QByteArray byte;
    QString serial;
    QString number;
};

class ava_cxpoH
{
public:


    ava_cxpoH();
    char CXPOH_Write(Block4 data);
    char CXPOH_Read(Packeg *out_ppac,int *out_size);
    char CXPOH_New();


private:
    unsigned char key[16]={  100, 211,  9, 55, 43,  89, 77, 165,  72, 111,  173, 145,  226, 99, 4, 15 };

    //MIX Section
    void Mix(unsigned char *data,unsigned char *out,unsigned char *key);
    void antiMix(unsigned char *data,unsigned char *out,unsigned char *key);
    void WriteHalfByteIn(unsigned char *otkyda,HalfByte *kyda);
    char init_key;
    HalfByte hkey[32];
    HalfByte hdata[32];

    //
    //HalfByte TabPodstava(HalfByte hb_data,HalfByte hb_key);


    //MD5 Section Begin
    void to_bytes(uint32_t val, uint8_t *bytes);
    uint32_t to_int32(const uint8_t *bytes);
    void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest);
    //MD5 Section END

    //FILE SECTION
    char fstatus;
    char ferr;
    Packeg pac[MAX_SIZE_PACKEG];
    //Packeg normpac[MAX_SIZE_PACKEG];
    FILE *fCXPOH;


    char ReadCXPOH();

    char fAntiMix();

    //Пихай сюда только после расшифровки данных
    char WriteDataToCXPOH(unsigned char *data);// записать новые данные в рандомную ячейку

    char fMIX(); //смешаем все

    char CreateCXPOH(char * name);

    char CopyBadCXPOH();




    //FILE SECTION END


};

#endif // AVA_CXPOH_H
