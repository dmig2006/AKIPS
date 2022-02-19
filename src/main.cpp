#include "mainwindow.h"

#include <QApplication>

#include "ava_terminal.h"
#include "event.h"
#include "Delegate.h"
#include "eventmap.h"
#include "test/test_helper_convert.h"
#include "log.h"
#include "ava_sql_helper.h"

#include "ava_sqlite.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

bool KPA_Rocket::flag;

int main(int argc, char *argv[])
{
    char *oldenv = getenv("PATH"), *newenv;
    newenv = (char *)malloc(strlen(oldenv) + 41);
    strcpy(newenv, "PATH=");
    strcat(newenv, oldenv);
    strcat(newenv, ";C:\\Project\\kpa_new_test\\bin\\dll");
    if(!putenv(newenv))
        qDebug() << getenv("PATH");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
