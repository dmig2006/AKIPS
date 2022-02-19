#ifndef HELPER_CONVERTER_H
#define HELPER_CONVERTER_H

#include "vector"
#include "string"
#include <cstring>


using namespace std;

class Helper_Converter
{
public:
    /**
     * @brief Take_argv разбивает входную строку на аргументы
     * @param in_str входная строка
     * @param args указатель на массив аргументов типа string
     * @param razdelitel символ разделения аргументов
     */
    static void Take_argv(char *in_str, vector<string> *args, char razdelitel);
    static void Take_argv(char *in_str,vector<int> *args, char razdelitel);

    /**
     * @brief Packeg_argv упоковывает массив аргументов в одну строку
     * @param args указатель на массив аргументов
     * @param out_str строка куда записываются аргументы через разделитель
     * @param razdelitel символ разделителя
     */
    static void Packeg_argv(vector<string> *args, string *out_str, char razdelitel);
    static void Packeg_argv(vector<int> *args,string *out_str, char razdelitel);
};




#endif // HELPER_CONVERTER_H
