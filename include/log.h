#ifndef LOG_H
#define LOG_H

#include "stream_kanal.h"
#include <time.h>

class Log
{
public:
    static Log *GetInstance();
    void WriteLogData(char *data);
    void WriteLogSys(char *data);
    void WriteLogError(char *data);
    void WriteEvent(char *name_event, int delegate_run);
    void SetCFGLogData(char *path, char cfg);
    void SetCFGLogSys(char *path, char cfg);
    void SetCFGLogError(char *path, char cfg);
    void SetCFGLogEvent(char *path, char cfg);
protected:
    Log();
private:
    Stream_Kanal log_data;
    Stream_Kanal log_sys;
    Stream_Kanal log_error;
    Stream_Kanal log_event;
    static Log *p_Instance;
    time_t t;
    struct tm *aTm;
};

#endif // LOG_H
