/**
  класс Delegate необходим для того, чтобы связать всю логику работы программы воедино
  при помощи делегата и связанных с ним классов, таких как event, event map и event_bus
  становиться возможно вызывать методы классов из любого места программы, в данном классе
  с вероятностью близкой к 1 ничего менять не надо, так как он не влияет на логику работы программы,
  являясь по сути служебным классом
  Для простоты понимания того, что тут происходит, можно считать, что экземпляр данного класса - это
  указатель на какой-то метод какого-то класса, или сам метод
  данный класс содержит методы run() для выполнения делегата, т.е. по сути для запуска выполнения метода,
  на который указывает конкретный экземпляр данного класса.
*/
#ifndef DELEGATE_H
#define DELEGATE_H

//#define LOG

#include <iostream>
#include <typeinfo>
#include "log.h"
using namespace std;


class Delegate
{
private:

	struct X {};
	typedef void (X::*Func)();

	X *_ptr;
	Func _func;
    char status;
    string arg1;
    string arg2;

public:

	Delegate()
        : _ptr(0), _func(0),status(0)
	{
#ifdef LOG
        cout << "Create emty delegate" << endl;
#endif
	}
    virtual ~Delegate()
    {
#ifdef LOG
       cout << "delete delegate" << endl;
#endif
    }

    template <class Owner, class ret>
        Delegate(Owner *owner, ret (Owner::*func)())
        : _ptr(0), _func(0),status(0)
	{
		_func = reinterpret_cast<Func>(func);
		_ptr = reinterpret_cast<X *>(owner);
        status=1;
#ifdef LOG
        cout << "Create delegate with 0 param" << endl;
#endif
	}

    template <class Owner, class Arg, class ret>
        Delegate(Owner *owner, ret (Owner::*func)(Arg))
        : _ptr(0), _func(0),status(0)
	{
		_func = reinterpret_cast<Func>(func);
		_ptr = reinterpret_cast<X *>(owner);
        status=2;
        arg1=typeid(Arg).name();
#ifdef LOG
        cout << "Create delegate with 1 param" << endl;
#endif
	}

    template <class Owner, class Arg1, class Arg2, class ret>
        Delegate(Owner *owner, ret (Owner::*func)(Arg1, Arg2))
        : _ptr(0), _func(0),status(0)
	{
		_func = reinterpret_cast<Func>(func);
		_ptr = reinterpret_cast<X *>(owner);
        status=3;
        arg1=typeid(Arg1).name();
        arg2=typeid(Arg2).name();
#ifdef LOG
        cout << "Create delegate with 2 param" << endl;
#endif
	}

	bool operator ! ()
	{
		return (!_ptr || !_func);
	}

	bool operator == (const Delegate &delegate)
	{
		return (_ptr == delegate._ptr && _func == delegate._func);
	}

	bool operator != (const Delegate &delegate)
	{
		return !(*this == delegate);
	}

    char operator () ();

    template <class Owner>
    char CheckClass(Owner *owner);
    template <class Owner>
    char CheckFunc(void (Owner::*func)());
    template <class Owner, class Arg>
    char CheckFunc(void (Owner::*func)(Arg));
    template <class Owner, class Arg1, class Arg2>
    char CheckFunc(void (Owner::*func)(Arg1, Arg2));

	template <class Arg>
        char operator() (Arg arg);

	template <class Arg1, class Arg2>
        char operator() (Arg1 arg1, Arg2 arg2);

};


inline char Delegate::operator () ()
{
    if(status==1)
    {
    if (_ptr && _func){
		(_ptr->*_func)();
        return 1;
    }
    return 0;
    }
    return 0;
}

template <class Arg>
char Delegate::operator () (Arg arg)
{
    string str=typeid(Arg).name();
#ifdef LOG
    //Log::GetInstance()->WriteLogSys((char*)(str+arg1).data());
#endif
    if((status==2)&(str==arg1))
    {
	typedef void (X::*Mfn)(Arg);
    Mfn func = reinterpret_cast<Mfn>(_func);

    if (_ptr && func){
        (_ptr->*func)(arg);
        return 1;
    }
    return 0;
    }
    return 0;
}

template <class Arg1, class Arg2>
char Delegate::operator () (Arg1 arg1, Arg2 arg2)
{
    if(status==3)
    {
    typedef void (X::*Mfn)(Arg1, Arg2);
    Mfn func = reinterpret_cast<Mfn>(_func);

    if (_ptr && func){
        (_ptr->*func)(arg1, arg2);
        return 1;
    }
    return 0;
    }
    return 0;
}

template <class Owner>
char Delegate::CheckClass(Owner *owner)
{
    if(reinterpret_cast<X *>(owner)==_ptr) return 1;
    else return 0;
}
template <class Owner>
char Delegate::CheckFunc(void (Owner::*func)())
{
    if(func==_func) return 1;
    else return 0;
}

template <class Owner, class Arg>
char Delegate::CheckFunc(void (Owner::*func)(Arg))
{
    if(func==_func) return 1;
    else return 0;
}

template <class Owner, class Arg1, class Arg2>
char Delegate::CheckFunc(void (Owner::*func)(Arg1, Arg2))
{
    if(reinterpret_cast<Func>(func)==_func) return 1;
    else return 0;
}

#endif
