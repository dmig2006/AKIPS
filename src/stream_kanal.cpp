#include "stream_kanal.h"

Stream_Kanal::Stream_Kanal()
{
#ifdef LOG
    cout << "Create Stream_Kanal" << endl;
#endif
}

void Stream_Kanal::SetCFG(char *path, char cfg){
    this -> path = path;
    this -> cfg = cfg;
#ifdef LOG
    cout << "Path: " << this -> path << ", cfg: " << this -> cfg << endl;
#endif
}

void Stream_Kanal::WriteIN(char *data)
{
#ifdef LOG
    cout << data << endl;
#endif
}

char Stream_Kanal::ReadStatus(){
    return status;
}

void Stream_Kanal::Clear(){
    system("clear");
}
