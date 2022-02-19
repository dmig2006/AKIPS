#include "mixik.h"

mixik * mixik::mix = 0;

mixik::mixik()
{
}

mixik *mixik::GetInstance(){
    if(!mix)
        mix = new mixik();
    return mix;
}

QString mixik::DoMixik(vector<string> vector){
    srand(time(NULL));
    out -> clear(); //очищаем выходную строку
    char bufff;
    char size;
    char c = rand() % KEY_LENGHT; //рандомное число указывающее на стартовый байт ключа
    CharToHex(&c, buff);    //преобразуем байт в формат 0хХХ
    out -> push_back(buff[0]);  //дописываем в конец выходной строки полученные дпнные
    out -> push_back(buff[1]);
    for(char i = 0; i < vector.size(); i++){    //для всех элементов во входном векторе
        size = vector.at(i).size(); //получаем размер очередного элемента
        if(c == KEY_LENGHT) //если с равно длине ключа сбрасываем его в 0. Т.е. в процессе шифрования если мы доходим до конца ключа переходим на его начало
            c = 0;
        ROL(&size, key[c] % 0x08);  //шифруем размер первого элемента вектора
        size += key[c]; //тоже шифровка
        CharToHex(&size, buff); //преобразуем зашифрованный байт в формат hex
        out -> push_back(buff[0]);  //записываем полученные данные в конец выходной строки
        out -> push_back(buff[1]);
        c++;    //инкремент с
        for(char j = 0; j < vector.at(i).size(); j++){  //аналогично шифруем и записываем сами данные в элементе вектора
            if(c == KEY_LENGHT)
                c = 0;
            bufff = QString(vector.at(i).at(j)).toStdWString().at(0);
            ROL(&bufff, key[c] % 0x08);
            bufff += key[c];
            CharToHex(&bufff, buff);
            out -> push_back(buff[0]);
            out -> push_back(buff[1]);
            c++;
        }
    }
    return QString::fromUtf8(out -> c_str());
}

vector<string> mixik::DoDeMixik(char *c, int lenght){
    vector<string> out; //вектор выходных данных
    string qstr;
    char size = 0, k, b1;
    buff[0] = *c;   //записываем в буффер первые 2 байта зашифрованной строки
    buff[1] = *(c + 1);
    HexToChar(buff, &k);    //преобразуем эти байты из формата hex в байт, который показывает с какого байта ключа начиналась шифровка
    for(int t = 2; t < lenght; t += 2){ //пока не дойдем до конца зашифрованной строки
        if(!size){  //если текущий размер элемента равен 0
            if(k == KEY_LENGHT) //если текущий байт ключа равен размеру ключа то сбрасываем его
                k = 0;
            buff[0] = *(c + t); //получаем очередные 2 байта в формате hex
            buff[1] = *(c + t +1);
            HexToChar(buff, &size); //получаем размер текущего элемента для расшифровки
            size -= key[k]; //делаем всё так же как и в шифровании но в обратном порядке
            ROR(&size, key[k] % 0x08);
            k ++;
            continue;
        }
        if(size){   //если размер не равен 0 расшифроввываем непосредственно сам элемент аналогично с расшифровкой размера
            if(k == KEY_LENGHT)
                k = 0;
            buff[0] = *(c + t);
            buff[1] = *(c + t +1);
            HexToChar(buff, &b1);
            b1 -= key[k];
            ROR(&b1, key[k] % 0x08);
            qstr.push_back(b1);
            k ++;
            size --;
            if(!size){  //если дошли до конца расшифровки элемента то записываем его в выходной вектор
                out.push_back(qstr);
                qstr.clear();
            }
        }
    }
    return out;
}

void mixik::ROL(char *in, char step){
    if(step >= 0x08)    //если шаг больше или равен 8 то ничего не делаем
        return;
    char mask = 0x00, out = *in;
    char low, high;
    for(char i = 0; i < 0x08 - step; i++)   //получаем маску для сдвига
        mask |= 0x01 << i;
    low = (out & mask) << step; //получаем половинки байта после вращения
    high = (unsigned char)(out & ~mask) >> (0x08 - step);
    out = low | high;   //склеиваем их
    *in = out;
    return;
}

void mixik::ROR(char *in, char step){ //все делается аналогично левому вращению
    if(step >= 0x08)
        return;
    char mask = 0x00, out = *in;
    char low, high;
    for(char i = 0; i < 0x08 - step; i++)
        mask|= (unsigned char)0x80 >> i;
    low = (unsigned char)(out & mask) >> step;
    high = (out & ~mask) << (0x08 - step);
    out = low | high;
    *in = out;
    return;
}

void mixik::CharToHex(char *in, char *out){
    char low, high;
    low = *in & 0x0f;   //получаем половинки байта
    high = (*in >> 4) & 0x0f;
    *out = high;
    *(out + 1) = low;
    for(char i = 0; i < 2; i++){    //преобразуем половинки в формат hex
        if(*(out + i) >=0x00 && *(out + i) <= 0x09)
            *(out + i) += '0';
        if(*(out + i) >= 0x0a && *(out + i) <= 0x0f)
            *(out + i) += ('A' - 0x0a);
    }
}

void mixik::HexToChar(char *in, char *out){ //аналогично CharToHex
    for(char i = 0; i < 2; i++){
        if(*(in + i) >= 'A' && *(in + i) <= 'F'){
            *(in + i) -= ('A' - 0x0a);
        }
        if(*(in + i) >= '0' && *(in + i) <= '9')
            *(in + i) -= '0';
    }
    *out = (*(in) << 4) | *(in + 1);
}

