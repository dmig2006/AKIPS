#include "helper_converter.h"

void Helper_Converter::Take_argv(char *in_str, vector<string> *args,char razdelitel)
{
    int num_argv=0;

    int i=0;
    int pos=-1;
    if((in_str!=0)&(args!=0))
    {
        int size=strlen(in_str);
    if(!args->empty()) args->clear();

    while(i<(size+1))
    {


        if((in_str[i]!=razdelitel)&(in_str[i]!=0))
        {
            if(pos==-1) args->resize(1+num_argv);
            pos=i;

            args->at(num_argv).push_back(in_str[i]);
            //str1.push_back(str[i]);
            //args[num_argv].push_back(str[i]);


        }
        else
        {
            if(pos>=0)
            {
               // args.push_back(str1);

                num_argv++;
                pos=-1;
            }
        }
        if(in_str[i]==0) break;
        i++;
    }
    }

}

void Helper_Converter::Take_argv(char *in_str, vector<int> *args, char razdelitel)
{
    int num_argv=0;

    int i=0;
    int pos=-1;
    string str;
    if((in_str!=0)&(args!=0))
    {
        int size=strlen(in_str);
    if(!args->empty()) args->clear();

    while(i<(size+1))
    {


        if((in_str[i]!=razdelitel)&(in_str[i]!=0))
        {
            //if(pos==-1) args->resize(1+num_argv);
            pos=i;

            str.push_back(in_str[i]);


        }
        else
        {
            if(pos>=0)
            {
               // args.push_back(str1);
                if(str[0]>47&&str[0]<58)//Проверка на цифру
                {
                num_argv=atoi(str.c_str());
                args->push_back(num_argv);
                }
                str.clear();

                pos=-1;
            }
        }
        if(in_str[i]==0) break;
        i++;
    }
    }
}

void Helper_Converter::Packeg_argv(vector<string> *args, string *out_str, char razdelitel)
{

    if((out_str!=0)&(args!=0))
    {
        if(!out_str->empty()) out_str->clear();

        int size=args->size();
        int i=0;

        while(i<size)
        {
            out_str->append(args->at(i));
            if(i!=(size-1)) out_str->push_back(razdelitel);
            i++;
        }
    }
}

void Helper_Converter::Packeg_argv(vector<int> *args, string *out_str, char razdelitel)
{

    if((out_str!=0)&(args!=0))
    {
        if(!out_str->empty()) out_str->clear();

        int size=args->size();
        int i=0;

        while(i<size)
        {
            out_str->append(std::to_string(args->at(i)));
            out_str->push_back(razdelitel);
            i++;
        }
    }
}
