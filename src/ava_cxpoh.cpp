#include "ava_cxpoh.h"




ava_cxpoH::ava_cxpoH()
{

}

char ava_cxpoH::CXPOH_Write(Block4 data)
{
     char c=0;
     char c1,c2;
    unsigned char serial[8];
    unsigned char ucd[16];
    unsigned char ucy[4];
   int i=0;

    ucd[0]=data.byte[0]; //Результат проверки


    while(i<8)
    {
        serial[i]=(unsigned char)data.serial.data()[i].unicode();
        i++;
    }
    unsigned char id[3];
    sscanf((char *)serial,"%d-%d-%d",&ucd[1],&ucd[2],&ucd[3]);//серия изделия

    //номер изделия
    ucd[4]=data.number[0].unicode();
    ucd[5]=data.number[1].unicode();
    ucd[6]=data.number[2].unicode();
    ucd[7]=data.number[3].unicode();

    if((ucd[0]!=0xFB)|(ucd[0]!=0xFD))
    {
        ucd[8]=data.byte[1]; //Номер проверки при неисправной ракете

        ucd[9]=data.byte[2];
        ucd[10]=data.byte[3]; //результат измерения

    }
    else
    {
        ucd[8]=rand() % 255;
        ucd[9]=rand() % 255;
        ucd[10]=rand() % 255;

    }

    ucd[11]=(unsigned char)data.data.date().day();
    ucd[12]=(unsigned char)data.data.date().month();

    i=data.data.date().year();
    if(i<=2000) i=i-1900;
    else i=i-2000;

    ucd[13]=(unsigned char)i;
    ucd[14]=(unsigned char)data.data.time().hour();
    ucd[15]=(unsigned char)data.data.time().minute();


    c=ReadCXPOH();
    c1=fAntiMix();
    if((c!=1)|(c1!=1))
    {
        CopyBadCXPOH();
        CXPOH_New();
        c=ReadCXPOH();
        c1=fAntiMix();
    }

    c2=WriteDataToCXPOH(ucd);

    return 1;
}

char ava_cxpoH::CXPOH_Read(Packeg *out_ppac, int *out_size)
{
    unsigned char c=0;

      c=ReadCXPOH();
return 1;
}

char ava_cxpoH::CXPOH_New()
{
    unsigned char c=0;
    c=CreateCXPOH(NAME_FILE);
    return 1;
}

void ava_cxpoH::Mix(unsigned char *data, unsigned char *out, unsigned char *key)
{
    UHByte uhb;
    UHByte uhb1;
    HalfByte hb;
    HalfByte hb1;
    unsigned char save;

    int i=0;
    int i1=0;

    WriteHalfByteIn(key,hkey);
    WriteHalfByteIn(data,hdata);

while(i1<16)
{
hb=hdata[i1];
 save=hkey[31-i1].hb;
hb1=hdata[save];
hdata[i1]=hb1;
hdata[hkey[31-i1].hb]=hb;

i1++;
}
while(i1<32)
{
    hb=hdata[i1];
    save=hkey[i].hb;
    hb1=hdata[save];
    hdata[i1]=hb1;
    hdata[hkey[i].hb]=hb;
    i1++;
    i++;
}
i=0;i1=0;
while(i<32)
{
    uhb.hb.hb1=hdata[i].hb;
    i++;
    uhb.hb.hb2=hdata[i].hb;
    out[i1]=uhb.uc;
    i++;
    i1++;
}


}

void ava_cxpoH::antiMix(unsigned char *data, unsigned char *out, unsigned char *key)
{
    UHByte uhb;
    UHByte uhb1;
    HalfByte hb;
    HalfByte hb1;
    unsigned char save;

    int i=15;
    int i1=31;

    WriteHalfByteIn(key,hkey);
    WriteHalfByteIn(data,hdata);


while(i1>15)
{
    hb=hdata[i1];
    hb1=hdata[hkey[i].hb];
    hdata[i1]=hb1;
    hdata[hkey[i].hb]=hb;
    i1--;
    i--;
}
i=15;
while(i1>=0)
{
hb=hdata[i1];
hb1=hdata[hkey[31-i].hb];
hdata[i1]=hb1;
hdata[hkey[31-i].hb]=hb;
i--;
i1--;
}
i=0;i1=0;
while(i<32)
{
    uhb.hb.hb1=hdata[i].hb;
    i++;
    uhb.hb.hb2=hdata[i].hb;
    out[i1]=uhb.uc;
    i++;
    i1++;
}

}

void ava_cxpoH::WriteHalfByteIn(unsigned char *otkyda, HalfByte *kyda)
{
   UHByte uhb;
   int i=0;
   int i1=0;

   while(i<16)
   {
       uhb.uc=otkyda[i];
       kyda[i1].hb=uhb.hb.hb1;
       kyda[i1+1].hb=uhb.hb.hb2;
       i1=i1+2;
       i++;
   }


}



