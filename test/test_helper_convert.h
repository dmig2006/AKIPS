#include "helper_converter.h"
#include <iostream>

#include <QString>

using namespace std;

class TEST_helper_converter
{
public:


    //Указатель не должен быть нулевой
    int NULL_Pointer()
    {
         char *pc=0;
         char c='A';
         string *str=0;
         vector<string> *vs=0;
         vector<int> *vi=0;
         cout << "Helper_Converter::Take_argv all null "<< endl;
         Helper_Converter::Take_argv(pc,vs,' ');
         Helper_Converter::Take_argv(pc,vi,' ');
         cout << "Helper_Converter::Packeg_argv all null "<< endl;
         Helper_Converter::Packeg_argv(vi,str,' ');
         Helper_Converter::Packeg_argv(vs,str,' ');
         pc=&c;
         str=new string("100");
         cout << "Helper_Converter::Take_argv vi/vs null "<< endl;
         Helper_Converter::Take_argv(pc,vs,' ');
         Helper_Converter::Take_argv(pc,vi,' ');
         cout << "Helper_Converter::Packeg_argv vi/vs null "<< endl;
         Helper_Converter::Packeg_argv(vi,str,' ');
         Helper_Converter::Packeg_argv(vs,str,' ');
         pc=0;
         vs=new vector<string>;
         vi=new vector<int>;
         str=0;
         cout << "Helper_Converter::Take_argv pc/str null "<< endl;
         Helper_Converter::Take_argv(pc,vs,' ');
         Helper_Converter::Take_argv(pc,vi,' ');
         cout << "Helper_Converter::Packeg_argv pc/str null "<< endl;
         Helper_Converter::Packeg_argv(vi,str,' ');
         Helper_Converter::Packeg_argv(vs,str,' ');
         return 1;

    }
    //упаковка в инт должна игнорировать/пропускать не цыфровые значения
    int Test_Packeg_argv_INT()
    {
        string pc="100 ava 200 300 ...";
        string pc1="eer 400 ~gdf 500 1 <<\n 4";
        vector<int> vi;
        vector<string> vs;
        Helper_Converter::Packeg_argv(&vi,&pc,' ');
        Helper_Converter::Packeg_argv(&vs,&pc1,' ');
        vi.push_back(10);
        vi.push_back(11);
        vi.push_back(12);
        vi.push_back(13);
        vs.push_back("Test");
        vs.push_back("ctoto");
        vs.push_back("poka!");
        Helper_Converter::Packeg_argv(&vi,&pc,' ');
        Helper_Converter::Packeg_argv(&vs,&pc1,' ');


        return 1;
    }
    int Test_Take_argv_INT()
    {
        char *ps=0;

        string pc="100 ava 200 300 ...";
        string pc1="eer 400 ~gdf 500 1 <<\n 4";
        vector<int> vi;
        vector<string> vs;
        Helper_Converter::Take_argv(ps,&vi,' ');
        Helper_Converter::Take_argv(ps,&vs,' ');

        Helper_Converter::Take_argv((char*)pc.data(),&vi,' ');
        Helper_Converter::Take_argv((char*)pc1.data(),&vs,' ');


        return 1;
    }

    std::string TestHexString(std::string pStr)
    {
        QString str1;
        std::string pStrRead;
        int number = 0;
        str1 = QString::fromStdString(pStr);
        number = str1.toInt();
        str1.clear();
        str1 = QString::number(number,16);
        pStrRead = str1.toStdString();
        return pStrRead;

    }

};

