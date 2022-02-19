/**
  класс eventmap необходим длятого, чтобы связать всю логтку работы программы воедино
  при помощи eventmap и связанных с ним классов, таких как delegate, event и event_bus
  становиться возможно вызывать методы классов из любого места программы, в данном классе
  с вероятностью близкой к 1 ничего менять не надо, так как он не влияет на логику работы программы,
  являясь по сути служебным классом
  Для лучшего понимания того, что тут происходит можно ознакомиться с описанием классов Delegate и event и прочитать
  комментарии к полям класса и его методам ниже
*/
#ifndef EVENTMAP_H
#define EVENTMAP_H

#include <string>
#include <map>
#include <vector>
#include "event.h"
#include <iostream>

using namespace std;

class EventMap
{
private:
    /**
     * @brief map_event карта которая хранит в себе данные в виде последовательности ключ/значение (название эвента/эвент)
     */
    map<string, Event*> map_event;
public:
    EventMap();
    vector<const char*> TakeListEvent();
    //char RunEvent(char *event_name);
    //template<class T> char RunEvent(char *event_name, T t);
    //template<class T, class W> char RunEvent(char *event_name, T t, W w);
    /**
     * @brief RunEvent метод для запуска эвентов работает по тем же пинципам что и методы в классе event
     * в котором можно почитать комментарии к методам для лучшего понимания
     * @param event_name имя эвента
     * @param id идентификационный номер класса, подробнее о нем можно узнать из описания класса
     * md_object
     * @return
     */
    char RunEvent(char *event_name,unsigned short id);
    template<class T> char RunEvent(char *event_name, T t,unsigned short id);
    template<class T, class W> char RunEvent(char *event_name, T t, W w,unsigned short id);
    virtual ~EventMap();
protected:
    /**
     * @brief ADDEvent перегруженные методы для добавления эвентов в карту
     * @param event_name
     * @return
     */
    char ADDEvent(char *event_name);
    char ADDEvent(char *event_name, Delegate *listener);
    char ADDEvent(char *event_name,unsigned short id);
    char ADDEvent(char *event_name, Delegate *listener,unsigned short id);
    char RemoveEvent(char *event_name);
    char ADDListener(char *event_name, Delegate *listener);
    char RemoveListener(char *event_name, Delegate *listener);
    Event *TakeEvent(char *event_name);

};

template<class T>
char EventMap::RunEvent(char *event_name, T t,unsigned short id)
{
    map<string, Event*>::iterator it;
    it = map_event.find(event_name);
    if(it != map_event.end()&&(map_event.at(it -> first)->TakeWaitID()==id||map_event.at(it -> first)->TakeWaitID()==0))
    {
        map_event.at(it -> first)->Run(t);
        return 1;
    }
    else
        return 0;
}

template<class T, class W>
char  EventMap::RunEvent(char *event_name, T t, W w,unsigned short id)
{
    map<string, Event*>::iterator it;
    it = map_event.find(event_name);
    if(it != map_event.end()&&(map_event.at(it -> first)->TakeWaitID()==id||map_event.at(it -> first)->TakeWaitID()==0))
    {
        map_event.at(it -> first)->Run(t, w);
        return 1;
    }
    else
        return 0;
}


#endif // EVENTMAP_H
