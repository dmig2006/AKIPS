#include "ava_cxpoh.h"




char ava_cxpoH::ReadCXPOH()
{
    int i=0;
    int i1=0;

    unsigned char c=0;


    if(fstatus==0)
    {
        fCXPOH=fopen(NAME_FILE,"r");
        if(fCXPOH==NULL)
        {
            ferr=1;
            fstatus=-1;
            return -1;
        }
        else
        {
        while(i<MAX_SIZE_PACKEG)
        {
            i1=0;
            while (i1<16)
            {   //Читаем секцию DATA
                c=getc(fCXPOH);
                if(c!=EOF)
                {
                    pac[i].data[i1]=c;
                    i1++;
                }else
                {
                    fclose(fCXPOH);
                    ferr=2;
                    fstatus=-1;
                    return -2; //Непредвиденный конец файла
                }
            }
            i1=0;
            while (i1<16)
            {   //Читаем секцию HASH
                c=getc(fCXPOH);
                if(c!=EOF)
                {
                    pac[i].hash[i1]=c;
                    i1++;
                }else
                {
                    fclose(fCXPOH);
                    ferr=2;
                    fstatus=-1;
                    return -2; //Непредвиденный конец файла
                }
            }
         i++;
        }
        fstatus=1;
        fclose(fCXPOH);
    }
    }
    return 1;
}

char ava_cxpoH::fAntiMix()
{
    Packeg testpac,tp;
    int i=0;
    int i1=0;
    int i2=0;
    while(i<MAX_SIZE_PACKEG)
    {
        antiMix(pac[i].data,testpac.data,key);
        i1=0;
        while(i1<16)
        {
            pac[i].data[i1]=testpac.data[i1];
            i1++;
        }
        antiMix(pac[i].hash,testpac.hash,key);

        i1=0;
        while(i1<16)
        {
            pac[i].hash[i1]=testpac.hash[i1];
            i1++;
        }
        md5(pac[i].data,16,tp.hash);
        i2=0;
        while(i2<16)
        {
            if(tp.hash[i2]!=pac[i].hash[i2]) return -1; //Битый ХЭШ
            i2++;
        }


        i++;
    }


return 1;
}


char ava_cxpoH::WriteDataToCXPOH(unsigned char *data)
{
    int num_pak=0;
    char flag_pack_write=0;
    //int proveren[MAX_SIZE_PACKEG]={0};
    int i=1;
    int i1=0;
    int i2=0;
    uint32_t num_norm_pac=0;
    BYTE c;

    fstatus=0;
    fCXPOH=fopen(NAME_FILE,"r+");
    if(fCXPOH==NULL)
    {
        ferr=1;
        fstatus=-1;
        return -1;
    }

    //Читаем первые 4 байта где хранятся данные о кол-во записей
    num_norm_pac=to_int32(pac[0].data)+1;
    i=(int)(num_norm_pac);
    if(i>=MAX_SIZE_PACKEG) i=0;
    //Save data
    i1=0;
    while(i1<16)
    {
        pac[i].data[i1]=data[i1];
        i1++;
    }
    md5(pac[i].data,16,pac[i].hash);
    //save 0 pac
    to_bytes(num_norm_pac,pac[0].data);
    i1=4;
    while(i1<16)
    {
        pac[0].data[i1]=rand() % 255;
        i1++;
    }
    md5(pac[0].data,16,pac[0].hash);
    //

    //save random packeg
    i++;
    while(i<MAX_SIZE_PACKEG)
    {
        //num_pak=rand() % MAX_SIZE_PACKEG;

      //делаем рандомный пакет
            c.data=rand() % 240;//<240 сгенерирован случайно
            pac[i].data[0]=c.data;
            i1=1;
            while(i1<16)
            {
                pac[i].data[i1]=rand() % 255;
                i1++;
            }
        md5(pac[i].data,16,pac[i].hash);
        i++;
    }
    fMIX();
    //
    //Write file
    i=0; i1=0;
    while(i<MAX_SIZE_PACKEG)
    {
        i1=0;
        while (i1<16)
        {
           putc(pac[i].data[i1], fCXPOH);
           i1++;
        }
        i2=0;
        while (i2<16)
        {
           putc(pac[i].hash[i2], fCXPOH);
           i2++;
        }

    i++;
    }


    if(fCXPOH!=NULL) fclose(fCXPOH);


    return 1;



}

char ava_cxpoH::fMIX()
{
    int i=0;
    int i1=0;
    Packeg testpac;

    while(i<MAX_SIZE_PACKEG)
    {
        Mix(pac[i].data,testpac.data,key);
        i1=0;
        while(i1<16)
        {
            pac[i].data[i1]=testpac.data[i1];
            i1++;
        }
        Mix(pac[i].hash,testpac.hash,key);
        i1=0;
        while(i1<16)
        {
            pac[i].hash[i1]=testpac.hash[i1];
            i1++;
        }
        i++;

    }
    return 1;
}

char ava_cxpoH::CreateCXPOH(char *name)
{
    int i=1;
    int i1=0;
    int i2=0;
    unsigned char c=0;

    fCXPOH=fopen(name,"w");
    if(fCXPOH==NULL)
    {
        ferr=1;
        fstatus=-1;
        return -1;
    }

    to_bytes(0,pac[0].data);
    i1=4;
    while(i1<16)
    {
        pac[0].data[i1]=rand() % 255;
        i1++;
    }
    md5(pac[0].data,16,pac[0].hash);

    i=1;
    while(i<MAX_SIZE_PACKEG)
    {
        //num_pak=rand() % MAX_SIZE_PACKEG;

      //делаем рандомный пакет
            c=rand() % 62; //7 and 6 bit dont use
            pac[i].data[0]=c;
            i1=1;
            while(i1<16)
            {
                pac[i].data[i1]=rand() % 255;
                i1++;
            }
        md5(pac[i].data,16,pac[i].hash);
        i++;
    }

    fMIX();
    //Write file
    i=0; i1=0;
    while(i<MAX_SIZE_PACKEG)
    {
        i1=0;
        while (i1<16)
        {
           putc(pac[i].data[i1], fCXPOH);
           i1++;
        }
        i2=0;
        while (i2<16)
        {
           putc(pac[i].hash[i2], fCXPOH);
           i2++;
        }

    i++;
    }


    if(fCXPOH!=NULL) fclose(fCXPOH);
    return 1;
}

char ava_cxpoH::CopyBadCXPOH()
{
    FILE *bad;
    FILE *newfile;
    char path[100];
    long i=0;
    char day,month,hour,min,sec,cr,c,c1;
    QDateTime dt;
    dt=QDateTime::currentDateTime();
    
            day=(char)dt.date().day();
            month=(char)dt.date().month();

            hour=(char)dt.time().hour();
            min=(char)dt.time().minute();
            sec=(char)dt.time().second();
            cr=(char)rand() % 9;


    i=sprintf(path,"%s%d%d%d%d%d%d",BAD_CXPOH_PATH,day,month,hour,min,sec,cr);
    if(i<100) path[i]=0;
        else path[99]=0;
    
    bad=fopen(NAME_FILE,"r");
    newfile=fopen(path,"w");
    if((bad==NULL)|(newfile==NULL))
    {
        //ошибка открытия файлов
        return -1;
    }

    while(!feof(bad))
    {
        c=getc(bad);
        putc(c, newfile);
    }


    return 1;
}

