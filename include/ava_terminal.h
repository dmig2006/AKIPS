#ifndef AVA_TERMINAL_H
#define AVA_TERMINAL_H

//#define LOG

#include <iostream>
#include "vector"
#include "string"
#include "string.h"
#include "helper_converter.h"
#include "event_bus.h"
#include "log.h"

using namespace std;

class AVA_Terminal
{
public:
    AVA_Terminal();
    virtual ~AVA_Terminal();


    virtual void RUN_AVA_Terminal();
     virtual void RUN_AVA_Terminal(char *data);


private:

    char RunEvent();
    void WriteIN(char *str);
    vector<char> *str_term;
    vector<string> *args;
    vector<int> *int_data;
    char status;



protected:


};






#endif // AVA_TERMINAL_H
