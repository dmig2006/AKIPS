/**
  класс event необходим длятого, чтобы связать всю логтку работы программы воедино
  при помощи event и связанных с ним классов, таких как delegate, event map и event_bus
  становиться возможно вызывать методы классов из любого места программы, в данном классе
  с вероятностью близкой к 1 ничего менять не надо, так как он не влияет на логику работы программы,
  являясь по сути служебным классом
  Для лучшего понимания того, что тут происходит можно ознакомиться с описанием класса Delegate и прочитать
  комментарии к полям класса и его методам ниже
*/
#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <string>
#include "Delegate.h"
#include <iostream>

using namespace std;


class Event{
private:
    /**
     * @brief listener в данном векторе храгятся делегаты данного класса
     */
    vector<Delegate*> listener;
    /**
     * @brief name поле с именем класса, задается при его создании
     */
    string name;
    char status;
    unsigned short int wait_id;
public:
    //Event(){};
    Event(char *name);
    Event(char *name,unsigned short int id);
    void SetWaitID(unsigned short int id){wait_id=id;}
    unsigned short int TakeWaitID(){return wait_id;}
    /**
     * @brief ADDDelegate метод для добавления нового делегата
     * @param listener
     * @return
     */
    char ADDDelegate(Delegate *listener);
    char RemoveDelegate(Delegate *listener);
    template <class Owner>
    char RemoveDelegate(Owner *owner);
    template <class Owner>
    char RemoveDelegate(void (Owner::*func)());
    template <class Owner, class Arg>
    char RemoveDelegate(void (Owner::*func)(Arg));
    template <class Owner, class Arg1, class Arg2>
    char RemoveDelegate(void (Owner::*func)(Arg1, Arg2));

    char *TakeName();
    char SetName(char *name);
    /**
     * @brief Run метод для запуска делегата без параметров. Как это работает:
     * //метод проходиться по всему вектору с делегатами и запускает только те делегаты, которые указывают
     * //на методы без рараметров
     * @return
     */
    char Run();
    /**
     * аналогично работает запуск делегатов с 1 параметром. ---->!!!!!Важно!!!!!<----: если в векторе с делегатами
     * хранится, для примера, один делегат который указывает на метод foo(string) то для запуска этого делегата
     * в данный метод необходимо подать string, если метод получит параметр другого типа делегат не
     * будет запущен
     */
    template<class T> char Run(T t);
    /**
     * аналогично вышесказанному только с 2 параметрами
     */
    template<class T, class W> char Run(T t, W w);

    virtual ~Event();
};

template<class T> char Event::Run(T t)
{
    char c = 0;
    for (int i = 0; i < this -> listener.size(); i++){
            c += listener[i]->operator()(t);
        }
#ifdef LOG
        cout << "Event run with " << (int)c << " delegates";
#endif
        if(c > 0)
            return 1;
        else
            return 0;
}

template<class T, class W> char Event::Run(T t, W w)
{
    char c = 0;
    for (int i = 0; i < this -> listener.size(); i++){
            c += listener[i]->operator()(t, w);

        }
#ifdef LOG
    cout << "Event run with " << (int)c << " delegates";
#endif
    if(c > 0)
        return 1;
    else
        return 0;
}

template <class Owner>
char Event::RemoveDelegate(Owner *owner)
{
    char c=0;
    int i = 0;
    int size=listener.size();
    while(i<size)
    {


        if(listener[i]->CheckClass(owner))
        {
            delete(this -> listener[i]);
            this -> listener.erase(this -> listener.begin()+i);
            c++;
            size--;
        }
        else i++;

    }
        return c;
}
template <class Owner>
char Event::RemoveDelegate(void (Owner::*func)())
{
    char c=0;
    int i = 0;
    int size=listener.size();
    while(i<size)
    {
        if(listener[i]->CheckFunc(func))
        {
            delete(this -> listener[i]);
            this -> listener.erase(this -> listener.begin()+i);
            c++;
            size--;
        }
        else i++;

    }
        return c;
}
template <class Owner, class Arg>
char Event::RemoveDelegate(void (Owner::*func)(Arg))
{
    char c=0;
    int i = 0;
    int size=listener.size();
    while(i<size)
    {


        if(listener[i]->CheckFunc(func))
        {
            delete(this -> listener[i]);
            this -> listener.erase(this -> listener.begin()+i);
            c++;
            size--;
        }
        else i++;

    }
        return c;
}
template <class Owner, class Arg1, class Arg2>
char Event::RemoveDelegate(void (Owner::*func)(Arg1, Arg2))
{

    char c=0;
    int i = 0;
    int size=listener.size();
    while(i<size)
    {


        if(listener[i]->CheckFunc(func))
        {
            delete(this -> listener[i]);
            this -> listener.erase(this -> listener.begin()+i);
            c++;
            size--;
        }
        else i++;

    }
        return c;
}

#endif // EVENT_H
