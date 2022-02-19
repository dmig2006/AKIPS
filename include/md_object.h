/**
  класс md_object должен наследоваться всеми классами коммуникация междк
  которыми должна обеспечиваться при помощи делегатов. В данном классе определены такие поля как имя и иден
  тификационный номер. идентификационный номер нужен для того, чтобы при вызове делегатов
  была возможность определить к какому классу идёт обращение. Т.е. если у нас есть 2 класса foo и bar и каждфй
  из этих классов реализует эвент run с делегатом f(int, string) то если в системе вызвать выполнение эвента с параметрами
  "run", int, string то должны выполниться оба эвента, что может быть не совсем желательно, одгако если класс foo
  имеет идентификационный номер 1 а bar номер 2, то при вызове эвента с параметрами "run", int, strung, id = 2 будет
  выполнен эвент класса bar
*/
#ifndef MD_OBJECT_H
#define MD_OBJECT_H

#include "eventmap.h"

class iMDObject
{
public:
    virtual unsigned short int ReadID()=0;
    virtual char RunEvent(char *eve)=0;

};

class MDObject :public EventMap
{
public:
    MDObject(){};
    MDObject(unsigned short int uid,char *name);
    virtual ~MDObject(){};
    string ReadNAME(){return name_mdobj;};
    unsigned short int ReadID(){return id_mdobj;};
    void SetID(unsigned short int id_mdobj){this -> id_mdobj = id_mdobj;};
    void SetName(string name_mdobj){this -> name_mdobj = name_mdobj;};

private:
    unsigned short int id_mdobj;
    string name_mdobj;
};

#endif // MD_OBJECT_H
