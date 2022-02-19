/**
  класс event_bus является вершиной системы событийно ориентированного механизма
  работ программы, и является синглтоном, то есть в любой точке программы возможен
  вызов метода getInstance(), который возвращает указатель на единственный
  экземпляр данного класса в программе, при этом так как данный класс является
  вершиной механизма событийно ориентированной схемы работы, внутри него содержиться
  вся информация обо всех эвентах и делегатах всех классов которые подключены
  к данному классу. Можно провести такую аналогию: event_bus - это некий сервер, к которому
  могут удаленно подключаться компьютеры для обмена информацией между собой. Для того, чтобы
  компьютер имел доступ к серверу, на него должно быть установленно соответствубщее программное обеспечение.
  В данном случае таким ПО выступает класс md_object. Как только компьютер подключаетмся к серверу
  он должен сообщить кто он такой (в данном случае сообщить своё имя и идентификационный номер см. описание
  класса md_object). Так же после подключения компьютер должен сообщить какие сообщения он хотел бы получать
  от других компьютеров (т.е создать eventmap и передать его на event_bus). Так же после подключения компьютер может
  отправлять сообщения на сервер, и сервер уже ищет подписан ли кто-то на сообщения с таким названием и параметрами,
  и если да, то отправлять из получателю.
*/

#ifndef EVENT_BUS_H
#define EVENT_BUS_H

//#define LOG

#include "md_object.h"
#include "vector"
#include "string"
#include "log.h"

using namespace std;

struct _sMDObject
{
    string name;
    unsigned short int uid;

};

struct _sUID
{
    unsigned char type;
    unsigned char id;
};

class Event_BUS
{
  private:
    static Event_BUS * p_instance;
    // Конструкторы и оператор присваивания недоступны клиентам
    Event_BUS() {};
    Event_BUS( const Event_BUS& );
    Event_BUS& operator=( Event_BUS& );
    vector<MDObject*> mdobj;
    char FindEventInMDObj(char *eve,MDObject* md);

  public:
    /**
     * @brief getInstance метод для получения указателя на единственный экземпляр event_bus
     * @return
     */
    static Event_BUS * getInstance()
    {
        if(!p_instance)
            p_instance = new Event_BUS();
        return p_instance;
    }

    char AddMDObject(MDObject * obj);
    char RemoveMDObject(MDObject * obj);
    int ListMDObject(vector<_sMDObject> *out);
    /**
     * @brief SendEvent перегруженные методы для отправления эвентов
     * @param eve название эвента
     * @param uid_target идентификационный номер получателя
     * @param uid_sender идентификационный номер отправителя
     * @return
     */
    int SendEvent(char * eve,unsigned short int uid_target,unsigned short int uid_sender);
    template<class T> int SendEvent(char * eve,unsigned short int uid_target,unsigned short int uid_sender,T t);
    template<class T, class W> int SendEvent(char * eve,unsigned short int uid_target,unsigned short int uid_sender,T t, W w);

};
template<class T>
int Event_BUS::SendEvent(char *eve, unsigned short uid_target,unsigned short int uid_sender,T t)
{
    int size=mdobj.size();
    int i=0;
    int n=0;
    if(uid_target==0)//работаем только по имени
    {
        int n=0;

        while(i<size)
        {
         // n=n+mdobj[i]->RunEvent(eve,t,0);
          n=n+mdobj[i]->RunEvent(eve,t,uid_sender);
          i++;
        }
#ifdef LOG
        Log::GetInstance()->WriteEvent(eve,n);
#endif
        return n;
    }
    else
    {
        i=0;
        while(i<size)
        {
          if(mdobj[i]->ReadID()==uid_target)
          {
             // n=(int)mdobj[i]->RunEvent(eve,t,0);
              n=n+mdobj[i]->RunEvent(eve,t,uid_sender);
#ifdef LOG
              Log::GetInstance()->WriteEvent(eve,n);
#endif
              return n;

          }
          i++;
        }
        return -1;//no this uid
    }
}

template<class T, class W>
int Event_BUS::SendEvent(char *eve, unsigned short uid_target,unsigned short int uid_sender,T t,W w)
{
    int size=mdobj.size();
    int i=0;
    int n=0;
    if(uid_target==0)//работаем только по имени
    {
        int n=0;

        while(i<size)
        {
         // n=n+mdobj[i]->RunEvent(eve,t,w,0);
          n=n+mdobj[i]->RunEvent(eve,t,w,uid_sender);
          i++;
        }
        Log::GetInstance()->WriteEvent(eve,i);
        return n;
    }
    else
    {
        i=0;
        while(i<size)
        {
          if(mdobj[i]->ReadID()==uid_target)
          {
            //  n=(int)mdobj[i]->RunEvent(eve,t,w,0);
              n=n+mdobj[i]->RunEvent(eve,t,w,uid_sender);
              Log::GetInstance()->WriteEvent(eve,n);
              return n;

          }
          i++;
        }
        return -1;//no this uid
    }
}





#endif // EVENT_BUS_H
