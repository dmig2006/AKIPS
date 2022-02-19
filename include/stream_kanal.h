#ifndef STREAM_KANAL_H
#define STREAM_KANAL_H

#include <string>
#include <iostream>

using namespace std;

class Stream_Kanal
{
private:
    char status;
    char cfg;
    string path;
public:
    Stream_Kanal();
    void SetCFG(char *path, char cfg);
    void WriteIN(char *data);
    char ReadStatus();
    void Clear();
};

#endif // STREAM_KANAL_H
