/**
  Устаревший код. Изначально писался для проверки работы COM порта в отсутствие
  оборудования.
*/


#ifndef COM_RANDOMIZER_H
#define COM_RANDOMIZER_H

//#include <conio.h>
//#include <stdio.h>
#include <time.h>
//#include <stdlib.h>
#include <vector>
//#include <windows.h>


using namespace std;

/**
 * @brief randomizer3 функция генерирующая случайный пакет данных
 * @param nr_prov номер проверки
 * @return
 */

vector<char> randomizer3(char nr_prov){
    vector<char> vchar; //вектор для хранения сгенерированных данных проверок
    srand(time(NULL));
    char c = 50 + rand() % 100;   //с - случайное число от 50 до 149
    time_t curr_time = clock();   //curr_time - текущее время
    while(curr_time + c > clock());    //пока сумма предыдущих переменных больше текущего времени ничего не делаем
    vchar.resize(5);    //устанавливаем размер вектора равным 5
    if(!(rand() % 4))   //если остаток от целочисленного деления случайного числа на 4 больше 0 то генерируется
        vchar[0] = 0xfc;    //байт 0хfc и значение присваивается первому байту пакета
    else
        vchar[0] = 0xfd;    //иначе 0xfd, таким рбразом генерируется пакет с ошибкой с вероятностью 1/4
    if(!(rand() % 4))
        vchar[2] = 0x81;    //по аналогии с первым байтом третий байт с вероятностью 3/4 генерируется со знаком
    else
        vchar[2] = 0x00;
    vchar[1] = nr_prov; //второй байт пакета равен номеру проверки
    vchar[3] = rand() % 256;    //4 и 5 байты генерируются во всех возможных диапозонах значений
    vchar[4] = rand() % 256;
    return vchar;   //возаращаем пакет из 5 байт без CRC
}

#endif // COM_RANDOMIZER_H
