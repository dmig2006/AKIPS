#include "ava_terminal.h"

AVA_Terminal::AVA_Terminal():status(0),args(0),str_term(0),int_data(0)
{
    args=new vector<string>;
    str_term=new vector<char>;
    int_data=new vector<int>;
}

AVA_Terminal::~AVA_Terminal()
{
    delete(args);
    delete(str_term);
    delete(int_data);
}

void AVA_Terminal::RUN_AVA_Terminal()
{
    string str;
    char c[256];
    while(1)
    {
#ifdef LOG
      std::cout << "Ожидаю ваших указаний О Великий!!: "<<endl;
      std::getline (std::cin,str); // считать строку из стандартного потока ввода
#endif
    }
}

void AVA_Terminal::RUN_AVA_Terminal(char * data)
{
    WriteIN(data);
}

void AVA_Terminal::WriteIN(char *str)
{
    int num_argv=0;
    int size=strlen(str);

    if(size>0)
    {
    args->clear();
    int_data->clear();
    str_term->clear();
    str_term->resize(size);

    Helper_Converter::Take_argv(str,args,' ');
    Helper_Converter::Take_argv(str,int_data,' ');
if(args->size()>0) RunEvent();
    }

}

char AVA_Terminal::RunEvent()
{
    int num_arg=args->size();
    int num_int=int_data->size();
    int num_delegate;

    if(num_arg==1)
    {
         num_delegate=Event_BUS::getInstance()->SendEvent((char*)args->at(0).data(),0,0);
#ifdef LOG
         Log::GetInstance()->WriteEvent((char*)args->at(0).data(),num_delegate);
#endif
    }
    else
    if(num_arg==2)
    {
         if(num_int>0)
         {
             num_delegate=Event_BUS::getInstance()->SendEvent((char*)args->at(0).data(),0,0,int_data->at(0));
#ifdef LOG
             Log::GetInstance()->WriteEvent((char*)args->at(0).data(),num_delegate);
#endif
         }
         else
         {
            num_delegate=Event_BUS::getInstance()->SendEvent((char*)args->at(0).data(),0,0,(char*)args->at(1).data());
#ifdef LOG
            Log::GetInstance()->WriteEvent((char*)args->at(0).data(),num_delegate);
#endif
         }
    }
    else
    if(num_arg==3)
    {
        if(args->at(1)[0]>47&&args->at(1)[0]<58)//Проверка на цифру аргумента
        {
         if(num_int==1)
         {
            num_delegate=Event_BUS::getInstance()->SendEvent((char*)args->at(0).data(),0,0,int_data->at(0),(char*)args->at(2).data());
#ifdef LOG
            Log::GetInstance()->WriteEvent((char*)args->at(0).data(),num_delegate);
#endif
         }
         else
         if(num_int==2)
         {
            num_delegate=Event_BUS::getInstance()->SendEvent((char*)args->at(0).data(),0,0,int_data->at(0),int_data->at(1));
#ifdef LOG
            Log::GetInstance()->WriteEvent((char*)args->at(0).data(),num_delegate);
#endif
         }
        }
        else //первый аргумент не цифра
        {
            if(num_int==1)
            {
                num_delegate=Event_BUS::getInstance()->SendEvent((char*)args->at(0).data(),0,0,(char*)args->at(1).data(),int_data->at(0));
#ifdef LOG
                Log::GetInstance()->WriteEvent((char*)args->at(0).data(),num_delegate);
#endif
            }
            else
            {
                num_delegate=Event_BUS::getInstance()->SendEvent((char*)args->at(0).data(),0,0,(char*)args->at(1).data(),(char*)args->at(2).data());
#ifdef LOG
                Log::GetInstance()->WriteEvent((char*)args->at(0).data(),num_delegate);
#endif
            }

        }
    }
    else
    {
        // не корректное кол-во аргументов
    }



}


