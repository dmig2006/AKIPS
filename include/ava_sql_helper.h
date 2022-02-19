#ifndef AVA_SQL_HELPER_H
#define AVA_SQL_HELPER_H

#include "sqlite3.h"
#include "string"
#include "vector"

#include "helper_converter.h"

#include <string>

using namespace std;


 class SQLite_Helper
 {
 private:

 public:
    static void ADDSQLCommand(const char *command,const char *value,string *out);
    static void ADDSQLValues(const char *command,vector<string> *data,string *out);

    static void ACharToHex(char in,char *out);


    static string UnsignedCharToHex(char c);


 };


#endif // AVA_SQL_HELPER_H
