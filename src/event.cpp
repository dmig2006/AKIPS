#include "event.h"

Event::Event(char *name)
{
    this -> name =string(name);
    wait_id=0;
#ifdef LOG
    cout << "Create Event with name " << this -> name << endl;
#endif
}

Event::Event(char *name, unsigned short id)
{
    this -> name =string(name);
    wait_id=id;
#ifdef LOG
    cout << "Create Event with name " << this -> name << endl;
#endif
}

char Event::ADDDelegate(Delegate *listener){
    this -> listener.push_back(listener);
    return 1;
}

char Event::RemoveDelegate(Delegate *listener){
    char c=0;
    int i = 0;

    int size=this->listener.size();
    while(i<size)
    {
        if (this -> listener[i] == listener)
        {

            delete(this -> listener[i]);
            this -> listener.erase(this -> listener.begin()+i);


            c++;
            size--;
        }else i++;
    }
    return c;
}

char* Event::TakeName()
{
    return (char*)name.data();
}

char Event::SetName(char *name){
    this -> name = name;
    return 1;
}

char Event::Run(){
    char c;
    for (unsigned int i = 0; i < this -> listener.size(); i++){
        c += listener[i]->operator ()();

    }
#ifdef LOG
    cout << "Event run with " << (int)c << " delegates";
#endif
    if(c > 0)
        return 1;
    else
        return 0;
}

Event::~Event(){
    for(int i = listener.size() - 1; i >= 0; i--){
        delete(listener[i]);
        listener.erase(listener.begin() + i);
    }
#ifdef LOG
    cout << "Event erase: " << name << endl;
#endif
}
