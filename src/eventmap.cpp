#include "eventmap.h"

EventMap::EventMap()
{

}

char EventMap::ADDEvent(char *event_name){
    Event *ev = new Event(event_name);
    map_event.insert(pair<string, Event*>(event_name, ev));
    return 1;
}

char EventMap::ADDEvent(char *event_name, Delegate *listener){
    Event *ev = new Event(event_name);
    ev -> ADDDelegate(listener);
    map_event.insert(pair<string, Event*>(event_name, ev));
    return 1;
}

char EventMap::ADDEvent(char *event_name, unsigned short id)
{
    Event *ev = new Event(event_name,id);
    map_event.insert(pair<string, Event*>(event_name, ev));
    return 1;
}

char EventMap::ADDEvent(char *event_name, Delegate *listener, unsigned short id)
{
    Event *ev = new Event(event_name,id);
    ev -> ADDDelegate(listener);
    map_event.insert(pair<string, Event*>(event_name, ev));
    return 1;
}

char EventMap::RemoveEvent(char *event_name){
    map<string, Event*>::iterator it;
    it = map_event.find(event_name);
    if(it != map_event.end()){
        delete map_event.at(it -> first);
        map_event.erase(it);
        return 1;
    }
    else
        return 0;
}

char EventMap::ADDListener(char *event_name, Delegate *listener){
    map<string, Event*>::iterator it;
    it = map_event.find(event_name);
    if(it != map_event.end()){
        map_event.at(it->first)->ADDDelegate(listener);
        return 1;
    }
    else if(listener != NULL){
        ADDEvent(event_name, listener);
        return 2;
    }
    else
        return 0;
}

char EventMap::RemoveListener(char *event_name, Delegate *listener){
    map<string, Event*>::iterator it;
    it = map_event.find(event_name);
    if(it != map_event.end())
    {
        if(map_event.at(it->first)->RemoveDelegate(listener))
            return 1;
        return 0;
    }
    else
        return 0;
}

Event* EventMap::TakeEvent(char *event_name)
{
    map<string, Event*>::iterator it;
    it = map_event.find(event_name);
    if(it != map_event.end())
        return map_event.at(it -> first);
    else
        return 0;
}

vector<const char *> EventMap::TakeListEvent(){
    vector<const char*> vec;
    if(!map_event.empty()){
        for(map<string, Event*>::iterator it = map_event.begin(); it != map_event.end(); ++it)
            vec.push_back(map_event.at(it -> first)->TakeName());
        return vec;
    }
    else{
        vec.push_back("The list is empty");
        return vec;
    }
}

char EventMap::RunEvent(char *event_name, unsigned short id)
{
    map<string, Event*>::iterator it;
    it = map_event.find(event_name);
    if(it != map_event.end()&&(map_event.at(it -> first)->TakeWaitID()==id||map_event.at(it -> first)->TakeWaitID()==0))
    {

        map_event.at(it -> first)->Run();
        return 1;
    }
    else
        return 0;
}

EventMap::~EventMap(){
    for(map<string, Event*>::iterator it = map_event.end()--; it == map_event.begin(); --it)
    {
        delete &map_event.at(it -> first);

        map_event.erase(it);
    }
#ifdef LOG
    cout << "Erase EventMap" << endl;
#endif
}
