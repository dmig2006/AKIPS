#include "kpa_com.h"
#include "com_randomizer.h"
#include "ava_sql_helper.h"

#include "mainwindow.h"

using namespace std;
//
KPA_COM::KPA_COM(unsigned short id_mdobj, string name_mdobj):MDObject(id_mdobj,(char*)name_mdobj.data()),status(0),state(0),error(0)
{
#ifdef UPDATEBUTTON
    testComFlag = true;
#endif

    param.clear();
    param["StopBit"]=TwoStop;
    param["Parity"]=NoParity;
    param["DataBit"]=Data8;
    param["Baud"]=B9600;
    param["CRC_CFG"]=CRC8;
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(ReadCOM()));

    ADDEvent((char *) "OpenCOM", new Delegate(this,&KPA_COM::OpenCOM));
    ADDEvent((char *) "OpenCOMX", new Delegate(this,&KPA_COM::OpenCOMX));
    ADDEvent((char *) "ClosePort", new Delegate(this,&KPA_COM::ClosedPort));
    ADDEvent((char *) "WriteCOM", new Delegate(this,&KPA_COM::WriteCOM));
    ADDEvent((char *) "ListenCOM", new Delegate(this,&KPA_COM::ListenCOM));
    ADDEvent((char *) "WriteParam", new Delegate(this,&KPA_COM::WriteParam));
    ADDEvent((char *) "ReadParam", new Delegate(this,&KPA_COM::ReadParam));
    ADDEvent((char *) "StartThread", new Delegate(this,&KPA_COM::AddThread));
    ADDEvent((char *) "ClearFlags", new Delegate(this,&KPA_COM::Clear));
    ADDEvent((char *) "ChoosePort");
    ADDEvent((char *) "ChangesStatus");
    ADDEvent((char *) "ErrorCOM");
    ADDEvent((char *) "DataRead");
    ADDEvent((char *) "Param");
    ADDEvent((char *) "DataWrite");
    ADDEvent((char *) "Give_MDObject_Name", new Delegate(this,&KPA_COM::Give_MDObject_Name));
    ADDEvent((char *) "Port_close");

    Event_BUS::getInstance() -> AddMDObject(this);

}

void KPA_COM::OpenCOM()
{
    if((status==COM_PORT_CLOSED)) //если порт не открыт
    {
        int size=0;
        list_info=QSerialPortInfo::availablePorts();

        size=list_info.size();
        if(size>1)
        {
            ChoosePort(&list_info);
        }
        else
        {
            if(size==1)
            {
                OpenCOMX(0);
            }
            else
            {
                error=COM_PORT_ERROR_NO_COM_PORT;
                    ErrorCOM(error);
                status=0;
                state=0;
            }
        }
    }
}

void KPA_COM::OpenCOMX(int id)
{
    //Event_BUS::getInstance()->SendEvent((char *) "Port_open", 0, ReadID());
    //string str1;
    readnr = 0;
    readbyte = 0;
    readpacket = false;
    readbyteb = false;
#ifdef _READTEST
     ReadCOM();//test tolko
#endif

    if(status==COM_PORT_CLOSED)
    {
        error=COM_PORT_ERROR_NO;
            if(!serial.setBaudRate((QSerialPort::BaudRate)param.at("Baud")))
                error=COM_PORT_ERROR_SET_BAUD;
            else
                if(!serial.setDataBits((QSerialPort::DataBits)param.at("DataBit")))
                    error=COM_PORT_ERROR_SET_DATABIT;
                else
                    if(!serial.setParity((QSerialPort::Parity)param.at("Parity")))
                        error=COM_PORT_ERROR_SET_PARITY;
                    else
                    {
                        //Если параметры норм установлены
#ifdef LOG
                        str1="думаю открыть порт "+to_string(id)+"name is "+ list_info.at(id).portName().toStdString();
                        Log::GetInstance() -> WriteLogData((char *)str1.data());
#endif
                        serial.setBaudRate(QSerialPort::Baud9600);
                        serial.setDataBits(QSerialPort::Data8);
                        serial.setParity(QSerialPort::NoParity);

                        serial.setPort(list_info.at(id));
                        if(serial.error()==0)
                        {
                            if (serial.open(QIODevice::ReadWrite))
                            { //open norm

                                status=COM_PORT_CONNECTED;
                                state=COM_PORT_STATE_CONNECTED;
                                error=COM_PORT_ERROR_NO;
                                ChangesStatus(status);
                                ListenCOM(1);
                                //Event_BUS::getInstance()->SendEvent("New_Log",0,0, QString::fromStdString("open"));
                                Event_BUS::getInstance()->SendEvent((char *) "Port_open", 0, ReadID());
                                //str1="Open "+serial.portName().toStdString()+" !!";
                                //Log::GetInstance() -> WriteLogData((char *)str1.data());
                                AddThread();

                            }
                            else
                            {
                                status=0;
                                error = serial.error();
#ifdef LOG
                                string str1="Error COM "+serial.errorString().toStdString()+" !!";
                                Log::GetInstance() -> WriteLogError((char *)str1.data());
#endif
                                error=COM_PORT_ERROR_OPEN_COM;

                            }
                        }
                        else
                        {
                            status=0;
                            error=COM_PORT_ERROR_BAD_PATH_TO_COM;

                        }
                    }
            if(error!=COM_PORT_ERROR_NO)
                ErrorCOM(error);

    }
    else
    {
        //port yge otkrit
    }
}


void KPA_COM::ClosedPort()
{
    serial.close();
    data.clear();
    status=COM_PORT_CLOSED;
    state=COM_PORT_STATE_OFF;
    error=0;
    ChangesStatus(status);
    Event_BUS::getInstance() -> SendEvent((char *) "Port_close", 0, ReadID());
    readnr = 0;
    m_timer.stop();

}

void KPA_COM::WriteCOM(char *data, int len)
{

    //Event_BUS::getInstance() -> SendEvent((char *) "New_Log", 0, ReadID(), QString::number(len));

    int nlen=0;
    if((status==COM_PORT_CONNECTED)&((state==COM_PORT_STATE_CONNECTED)|(state==COM_PORT_STATE_LISTEN)))
    {
        state=COM_PORT_STATE_WRITE_DATA;
        nlen=serial.write(data,len);
        //Event_BUS::getInstance() -> SendEvent("New_Log", 0, ReadID(), /*QString::number(nlen)*/QString("chrum"));
        if(nlen==-1)
        {
            error=COM_PORT_ERROR_WRITE_DATA;
            status=COM_PORT_ERROR;
            state=COM_PORT_STATE_OFF;
            ErrorCOM(error);
            ChangesStatus(status);
        }
        else
        { //Данные отправлены нoрм
            state=COM_PORT_STATE_CONNECTED;
            DataWrite(len);
            //Event_BUS::getInstance() -> SendEvent("New_Log", 0, ReadID(), QString("all good"));
        }

    }

}

void KPA_COM::ReadCOM()
{
#ifdef UPDATEBUTTON
    if (testComFlag)
    {
#endif

    #ifdef _READTEST
        Event_BUS::getInstance() -> SendEvent((char *) "ClearData", 110, ReadID());
        data.resize(5);
        for(char i = 5; i < 32; i++){
            data = randomizer3(i);
            DataRead(data);
            if(data.at(0) == (char)0xfc)
                break;
        }
    #endif
        if((status==COM_PORT_CONNECTED)|(state==COM_PORT_STATE_WAIT_DATA)|(state==COM_PORT_STATE_LISTEN)&(error==COM_PORT_ERROR_NO))
        {
            char c;
            char state_old = state;
            int i = 0;
            i = serial.read(&c, 1);
            if(i == -1 || i == 0)
            { //если i = -1 то произошла ошибка чтения, если i = 0 то на COM порте нет данных
                if(serial.error() == 0)
                { //нет ошибки
                    state = state_old;
                    if(readpacket) //если уже прочитали первый пакет увеличиваем readnr
                        readnr ++;
                    if(readbyteb)  //если был прочитан байт увеличиваем readbyte
                        readbyte ++;
                    if(readnr == kriticaltime)
                    { //если первый пакет уже считан и в течение kriticaltime/1000 с не пришел новый пакет
                        data.clear(); //очищаем буффер
                        readbyteb = false; //больше не отслеживаем приём отдельных байтов
                        readnr = 0; //больше пакетов не ожидается
                        readpacket = false;
                        ClosedPort(); //отключаем COM порт
                        ErrorCOM(COM_PORT_ERROR_DISCONECTED); //сообщение об ошибке
                    }
                    if(readbyte == kriticalbyte)
                    { //если в течение kriticalbyte мс не пришел следующий байт
                        data.clear(); //очищаем буфер
                        readbyteb = false; //больше не ожидаем приема байтов
                        readbyte = 0; //обнуляем
                    }
                }
                else
                { //Ошибка чтения байта
                    state=COM_PORT_STATE_OFF;
                    status=COM_PORT_ERROR;
                    error=COM_PORT_ERROR_READ_DATA;
                    ErrorCOM(error);
                    ChangesStatus(status);
                    ClosedPort();
                }
            }
            else
            { //если байт пришел
                if(readbyteb && data.size() >= (int) 2)
                { //если мы ждем прихода байта
                    data.push_back(c);
                    readbyte = 0; //обнуляем и ждем еще kriticalbyte мс следующий байт
                }
                if(data.size() == 1 && c == (char) cyrrentpacknr)
                { //если ожидается второй байт пакета
                    data.push_back(c);
                    loosepacket = false;
                    readbyte = 0; //обнуляем и ждем еще kriticalbyte мс следующий байт
                }
                else if(data.size() == 1 && c != (char) cyrrentpacknr)
                { //если пакет пропущен или пришел неверный номер проверки
                    data.push_back(c);
                    readbyte = 0; //обнуляем и ждем еще kriticalbyte мс следующий байт


                    if((c == (char) cyrrentpacknr) or (c == (char)testBuffer))
                    { //это означает что случилось чудо (см. описание переменной cyrrentpacknrbuff)
                        //loosepacket = false;
                        //cyrrentpacknr --;
                        loosepacket = false;
                        cyrrentpacknr = testBuffer;
                    }
                    else
                    {
                        if (data.size() == 2)
                            data.clear();

                        loosepacket = true;
                        testComFlag = true;
                        readpacket = true; // ждем 10 секунд, если пакет не пришел то ошибка
                        cyrrentpacknrbuff = cyrrentpacknr;
                        //cyrrentpacknr ++;
                    }
                }

                if((c <= (char) 0xfd && c >= (char) 0xfa) && !data.size())
                {
                    //если прочитанный байт соответствует формату первого байта пакета
                    data.push_back(c);  //записываем байт в буффер
                    readbyte = 0; //обнуляем и ждем еще kriticalbyte мс следующий байт
                    readbyteb = true; //теперь мы ждем что не позднее kriticalbyte мс прийдет следубщий байт пакета
                }

                if (data.size() == 6)
                { //

                    if (cyrrentpacknr < 35)
                        readpacket = true;

                    if(param.at("CRC_CFG")==CRC8)
                    { //Если необходим расчет CRC
                        if(Take_CRC8(data.data(),(data.size() - 1)) == ((unsigned char) data.at(data.size() - 1)))
                        { //CRC посчитан норм
                            data.pop_back();  //удаляем crc байт
                            cyrrentpacknr ++;

                            testBuffer++;

                            readbyteb = false; //больше байтов не ожидается
                            readbyte = 0; //обнуляем счетчик байтов
                            readnr = 0; //обнуляем счетчик пакетов
                            if((data.at(1) == (char) 0x22 && data.at(0) == (char) 0xfb) ||
                                    (data.at(0) == (char) 0xfd && data.at(1) == (char) 0x1f) ||
                                         data.at(0) == (char) 0xfa || data.at(0) == (char) 0xfc)
                            { //пришел последний пакет или брак
                                readpacket = false; //пакетов больше не ожидается
                                readnr = 0; //сброс счетчика
                                readbyteb = false;
#ifdef UPDATEBUTTON
                                testComFlag = false;
#endif
                                readbyte = 0;
                                if(brokendata || loosepacket)
                                {  //если приходили битые данные или был потерян пакет
                                    Event_BUS::getInstance() -> SendEvent((char *) "ClearData", 110, ReadID()); //стираем данные в datamanager
                                    ErrorCOM(COM_PORT_ERROR_WRITE_DATA);
                                }
                            }
                            DataRead(data);
                            data.clear();
                        }
                        else
                        { //ошибка CRC
                            brokendata = true;
                            data.clear(); //очищаем принятые данные
                            cyrrentpacknr ++;
                            readbyteb = false; //больше байтов не ожидается
                            readbyte = 0; //обнуляем счетчик байтов
                            readnr = 0; //обнуляем счетчик пакетов
                        }
                    }
                }
           }
        }
#ifdef UPDATEBUTTON
    }
    else
    {
        data.clear();
        serial.clear();
    }
#endif
}

void KPA_COM::Clear()
{
    brokendata = false;
    cyrrentpacknr = 5;
    testBuffer = 5;

#ifdef UPDATEBUTTON
    testComFlag = true;
#endif

    //cyrrentpacknrbuff = cyrrentpacknr;
    readbyteb = false;
    loosepacket = false;
    readpacket = false;
    readbyte = 0;
    readnr = 0;
}

//--------------------------------------------------------------------
//закоменированно 20.01.17 пробуем переписать метод чтения COM порта
//--------------------------------------------------------------------
/*        char c;
        int i=0;
        char state_old=state;
        i=serial.read(&c,1);
        if(i==-1||i==0)
        {
            if(serial.error()==0)
            {//Нет данных
               state=state_old;
#ifdef _CRITICAL_READ
               if(readpacket)
                    readnr ++;
               if(readbyteb)
                   readbyte ++;
               if(readbyte == kriticalbyte){
                   data.clear();
                   readbyteb = false;
               }
               if(readnr == kriticaltime){
                   ClosedPort();
                   ErrorCOM(COM_PORT_ERROR_DISCONECTED);
               }
#endif
#ifdef _BITYEDANNBLE
  data.resize(6);
  data[0]=0xFc;
  data[1]=0x19;
  data[2]=0x80;//00
  data[3]=0x10;//80
  data[4]=0x00;//80
  data[5]=0xBE;//E6
#endif
               if(data.size()>5)
               {
                   readbyteb = false;

                   if(param.at("CRC_CFG")==CRC8)
                   {
                       unsigned char c2=Take_CRC8(data.data(),(data.size()-1));
#ifdef LOG
                       string str1="Data " +SQLite_Helper::UnsignedCharToHex(data.at(0))+" "+SQLite_Helper::UnsignedCharToHex(data.at(1))+" "+SQLite_Helper::UnsignedCharToHex(data.at(2))+" "+SQLite_Helper::UnsignedCharToHex(data.at(3))+" "+SQLite_Helper::UnsignedCharToHex(data.at(4))+" "+SQLite_Helper::UnsignedCharToHex(data.at(5))+"-"+SQLite_Helper::UnsignedCharToHex((char)c2);
                       Log::GetInstance() -> WriteLogData((char *)str1.data());
#endif
#ifdef ROCK_TEST
                       data.pop_back();
                       DataRead(data);
                       data.clear();
#endif
#ifndef ROCK_TEST
                       if(Take_CRC8(data.data(),(data.size()-1))== ((unsigned char)data.at(data.size()-1)))
                        {
                            //CRC8 Ok
                            data.pop_back();
                            readnr = 0;
                            string str="Take Data " + to_string((int)data.at(0))+" "+ to_string((int)data.at(1))+" "+ to_string((int)data.at(2))+" "+ to_string((int)data.at(3))+" "+ to_string((int)data.at(4))+" ";
#ifdef LOG
                            Log::GetInstance() -> WriteLogData((char *)str.data());
#endif
                            DataRead(data);
                            if((data.at(1) == (char) 0x22 && data.at(0) == (char) 0xfb) ||
                                    (data.at(0) == (char) 0xfd && data.at(1) == (char) 0x1f) ||
                                         data.at(0) == (char) 0xfa || data.at(0) == (char) 0xfc){
                                if(brokendata)
                                    ErrorCOM(COM_PORT_ERROR_CRC8);
                                brokendata = false;
                                readpacket = false;
                                readnr = 0;
                            }
                            data.clear();
                        }
                        else
                        {*/
//-------------------------------------------------------------------------------------------
//Закоментировано 19.01.17 тк ошибка CRC больше не нужна
//-------------------------------------------------------------------------------------------
                             /*m_timer.stop();
#ifdef LOG
                             Log::GetInstance() -> WriteLogData("com_PORT_ERROR_CRC8");
#endif
                             ErrorCOM(COM_PORT_ERROR_CRC8);*/
//-------------------------------------------------------------------------------------------
//Закоментировано 19.01.17 тк ошибка CRC больше не нужна
//-------------------------------------------------------------------------------------------
/*                           brokendata = true;
                           if((data.at(1) == (char) 0x22 && data.at(0) == (char) 0xfb) ||
                                   (data.at(0) == (char) 0xfd && data.at(1) == (char) 0x1f) ||
                                        data.at(0) == (char) 0xfa || data.at(0) == (char) 0xfc){
                               data.pop_back();
                               DataRead(data);
                               if(brokendata)
                                   ErrorCOM(COM_PORT_ERROR_CRC8);
                               brokendata = false;
                               readpacket = false;
                               readnr = 0;
                           }
                           data.clear();
                           readnr = 0;
                           MainWindow::appendLog("Битый пакет");
                       }
#endif

                   }
               }
            }
            else
            {
                //Ошибка чтения

                m_timer.stop();
#ifdef LOG
                string str1="com_PORT_ERROR_READ_DATA "+serial.errorString().toStdString()+" !!";
                Log::GetInstance() -> WriteLogData((char *)str1.data());
#endif
                state=COM_PORT_STATE_OFF;
                status=COM_PORT_ERROR;
                error=COM_PORT_ERROR_READ_DATA;
                ErrorCOM(error);
                ChangesStatus(status);
            }
        }  else
        {
            if((!data.size() && (c >= 0xfa || c <=0xfd)) || readbyteb){
                data.push_back(c);
                readpacket = true;
                readbyteb = true;
                readbyte = 0;
            }
        readnr = 0;
        c=0;
        }

        if(state==COM_PORT_STATE_WAIT_DATA)
            state=COM_PORT_STATE_CONNECTED;
    }
}*/
//--------------------------------------------------------------------
//закоменированно 20.01.17 пробуем переписать метод чтения COM порта конец
//--------------------------------------------------------------------
void KPA_COM::ListenCOM(char type)
{
    if(type==1)
    if((status==COM_PORT_CONNECTED)&(state!=COM_PORT_STATE_LISTEN)&(state!=COM_PORT_STATE_WRITE_DATA)&(state!=COM_PORT_STATE_READ_DATA))
    {
        state=COM_PORT_STATE_LISTEN;


    }
    if((type==0)&(state==COM_PORT_STATE_LISTEN))
        if(status==COM_PORT_CONNECTED) state=COM_PORT_STATE_CONNECTED;
            else state=COM_PORT_STATE_OFF;
}

void KPA_COM::WriteParam(char *param, int set_param)
{
    map<string,int16_t>::iterator it;

    it = this->param.find(param);
    if(it != this->param.end()){
        this->param.at(it->first)=set_param;
        //return 1; */
    }
}

void KPA_COM::ReadParam(char *param)
{
    map<string,int16_t>::iterator it;

    it = this->param.find(param);
    if(it != this->param.end())
    {
        //передать событие
    }
}

void KPA_COM::Give_MDObject_Name()
{
    Take_MDObject_Name();
}

void KPA_COM::ChoosePort(QList<QSerialPortInfo> *listqs)
{
    Event_BUS::getInstance()-> SendEvent((char *) "ChoosePort", 0, ReadID(), listqs);
}

void KPA_COM::ChangesStatus(char status)
{
    Event_BUS::getInstance()-> SendEvent((char *) "ChangesStatus", 0, ReadID(), status);
}

void KPA_COM::ErrorCOM(char error)
{
    Event_BUS::getInstance()-> SendEvent((char *) "Port_Error", 104, ReadID(), (int)error);
}

void KPA_COM::Param(string param, int data)
{
    Event_BUS::getInstance()-> SendEvent((char *) "Param", 0, ReadID(), param, data);
}

void KPA_COM::DataRead(vector<char> data)
{
    Event_BUS::getInstance()-> SendEvent((char *) "DataRead", 110, ReadID(), data);
    Event_BUS::getInstance()-> SendEvent((char *) "DataRead", 101, ReadID(), data);
}

void KPA_COM::DataWrite(int len)
{
    Event_BUS::getInstance()-> SendEvent((char *) "DataWrite", 0, ReadID(), len);
}

void KPA_COM::Take_MDObject_Name()
{
    Event_BUS::getInstance()-> SendEvent((char *) "Take_MDObject_Name", 0, ReadID(), ReadNAME().data(), ReadID());
}

unsigned char KPA_COM::Take_CRC8(char *data,int16_t len)
{
    /*
      Name  : CRC-8
      Poly  : 0x31    x^8 + x^5 + x^4 + 1
      Init  : 0xFF
      Revert: false
      XorOut: 0x00
      Check : 0xF7 ("123456789")
      MaxLen: 15 байт(127 бит) - обнаружение
        одинарных, двойных, тройных и всех нечетных ошибок
    */

        unsigned char crc = 0x00;//0xFF;
        unsigned int i,i1;
        unsigned char c=0;
        unsigned char poly=71; // Poly  : 0x31    x^8 + x^5 + x^4 + 1


        //int len=data->size()-1;
        i1=0;
        while (len--)
        {
              c= data[i1];
              crc ^= c;
              i1++;
            for (i = 0; i < 8; i++)
            {
             if(crc & 0x80) //128 or 8bit
                 crc=(crc) ^ poly; // crc=(crc << 1) ^ poly;

                 crc= crc << 1;
            }
                //crc = crc & 0x80 ? (crc << 1) ^ poly : crc << 1;
        }

        return crc;

}

void KPA_COM::AddThread()
{
#ifdef UPDATEBUTTON
//      if (testComFlag)
//      {
          ClearBuff();
          m_timer.setSingleShot(false);
          m_timer.start(1);
//      }
#else
    ClearBuff();
    m_timer.setSingleShot(false);
    m_timer.start(1);

#endif
}

void KPA_COM::ClearBuff()
{
    char c;
    while(serial.read(&c,1))
        ;
    data.clear();
}
