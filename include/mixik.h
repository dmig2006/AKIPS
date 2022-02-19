#ifndef MIXIK_H
/**
  класс для шифрования дешифрования данных, работает слкдующим образом:
  есть ключ шифрования и данные которые надо зашифровать, в самом начале
  генерируется рандомное число которое указывает на какой-то байт ключа
  затем происходит шифрование первого байта данных с использованием полученного
  байта ключа, затем шифрование следующего байта данных с использованием следующего байта
  ключа и так далее.
  */

#define MIXIK_H

#include <QVector>
#include <QString>
#include <QChar>
#include <string>
#include <vector>
#include <string>
#include <ctime>

#define KEY_LENGHT 42

using namespace std;

class mixik
{
public:
    //метод для получения указателя на единственный экземпляр класса
    static mixik *GetInstance();
    //метод для шифрования вектора строк
    QString DoMixik(vector<string> vector);
    //метод дешифровки
    vector<string> DoDeMixik(char *c, int lenght);
private:
    mixik();
    static mixik *mix;
    string *out = new string();
    char buff[2] = {0};
    //левое вращение байта, если на вход подается байт 0х100 01100 и шаг равный 3 то на выходе будет байт 0х01100 100
    void ROL(char *in, char step);
    //аналогично правое вращение
    void ROR(char *in, char step);
    void CharToHex(char *in, char *out);
    void HexToChar(char *in, char *out);
    const char key[KEY_LENGHT] = {'A',  'O', '\"', 'K',  'O',
                                  'N',  'C', 'E',  'R',  'N',
                                  '\"', 'K', 'A',  'L',  'A',
                                  'S',  'H', 'N',  'I',  'K',
                                  'O',  'V', '\"', 'D',  'I',
                                  'V',  'I', 'S',  'I',  'O',
                                  'N',  'S', 'P',  'E',  'C',
                                  'T',  'E', 'H',  'N',  'I',
                                  'K', 'A'};  //Ключ шифрования, может быть любым
};

#endif // MIXIK_H
