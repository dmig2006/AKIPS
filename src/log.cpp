/**
  данный класс был создан для вывода сообщений в консоль для отладки всей программы, сейчас уже не используется
  */
#include "log.h"
#include "mainwindow.h"

Log *Log::p_Instance = 0;

Log::Log():t(0),aTm(0)
{
    t=time(NULL);
#ifdef LOG
    cout << "Create log" << endl;
#endif
}

Log *Log::GetInstance(){
    if(!p_Instance)
        p_Instance = new Log();
    return p_Instance;
}

void Log::WriteLogData(char *data){
    aTm = localtime(&t);
#ifdef LOG
    cout << aTm->tm_year+1900 << ":" << aTm->tm_mon+1 << ":" << aTm->tm_mday << " " << aTm->tm_hour << ":" << aTm->tm_min << ":" << aTm->tm_sec << " Data: ";
    log_data.WriteIN(data);
    MainWindow::appendLog(data);
#endif
}

void Log::WriteLogSys(char *data){
    aTm = localtime(&t);
#ifdef LOG
    cout << aTm->tm_year+1900 << ":" << aTm->tm_mon+1 << ":" << aTm->tm_mday << " " << aTm->tm_hour << ":" << aTm->tm_min << ":" << aTm->tm_sec << " System: ";
    log_sys.WriteIN(data);
    MainWindow::appendLog(data);
#endif
}

void Log::WriteLogError(char *data){
    aTm = localtime(&t);
#ifdef LOG
    cout << aTm->tm_year+1900 << ":" << aTm->tm_mon+1 << ":" << aTm->tm_mday << " " << aTm->tm_hour << ":" << aTm->tm_min << ":" << aTm->tm_sec << " Error: ";
    log_error.WriteIN(data);
    MainWindow::appendLog(data);
#endif

}

void Log::SetCFGLogData(char *path, char cfg){
    log_data.SetCFG(path, cfg);
}

void Log::SetCFGLogSys(char *path, char cfg){
    log_sys.SetCFG(path, cfg);
}

void Log::SetCFGLogError(char *path, char cfg){
    log_error.SetCFG(path, cfg);
}

void Log::SetCFGLogEvent(char *path, char cfg){
    log_event.SetCFG(path, cfg);
}

void Log::WriteEvent(char *name_event, int delegate_run){
     aTm = localtime(&t);
#ifdef LOG
    cout << aTm->tm_year+1900 << ":" << aTm->tm_mon+1 << ":" << aTm->tm_mday << " " << aTm->tm_hour << ":" << aTm->tm_min << ":" << aTm->tm_sec << " Event " << name_event << " run with " << delegate_run << " delegate(s)" << endl;
    MainWindow::appendLog(name_event);
#endif
}

