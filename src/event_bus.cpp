#include "event_bus.h"

Event_BUS * Event_BUS::p_instance=0;

char Event_BUS::FindEventInMDObj(char *eve, MDObject *md)
{
    vector<const char*> vs=md->TakeListEvent();
    string str=eve;
    int size=vs.size();
    int i=0;

    while(i<size)
    {
        if(str.compare(vs.at(i))==0)
            return 1;
        i++;
    }
    return 0;
}

char Event_BUS::AddMDObject(MDObject *obj)
{
    if(obj!=NULL)
    {
        int size=mdobj.size();
        int i=0;
        while(i<size)
        {
            if(obj->ReadID()==mdobj[i]->ReadID())
            {
                return 0;
            }
            i++;
        }

           mdobj.push_back(obj);
           return 1;

    }
    else
    {
        //error NULL pointer
        return -1;
    }
}

char Event_BUS::RemoveMDObject(MDObject *obj)
{
    if(obj!=NULL)
    {
        int size=mdobj.size();
        int i=0;
        while(i<size)
        {
            if(obj->ReadID()==mdobj[i]->ReadID())
            {
                mdobj.erase(mdobj.begin()+i);
                return 1;
            }
            i++;
        }

        return 0;

    }
    else
    {
        //error NULL pointer
        return -1;
    }
}

int Event_BUS::ListMDObject(vector<_sMDObject> *out)
{
    if(out!=NULL)
    {
        int size=mdobj.size();
        int i=0;
         _sMDObject s;
         out->clear();
        while(i<size)
        {
            s.name=mdobj[i]->ReadNAME();
            s.uid=mdobj[i]->ReadID();
            out->push_back(s);
            i++;
        }
        return i;
    }
    return -1;
}

int Event_BUS::SendEvent(char *eve, unsigned short uid_target,unsigned short int uid_sender)
{
    int size=mdobj.size();
    int i=0;
    int n=0;
    if(uid_target==0)//работаем только по имени
    {


        while(i<size)
        {
         // n=n+mdobj[i]->RunEvent(eve,0);
          n=n+mdobj[i]->RunEvent(eve,uid_sender);
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

              //n=mdobj[i]->RunEvent(eve,0);
               n=mdobj[i]->RunEvent(eve,uid_sender);
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
