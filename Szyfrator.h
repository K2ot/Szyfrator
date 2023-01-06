#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>

enum klucz
{
    gadery_poluki = 1,
    malinowe_buty =2 ,
    mors = 3,
    cezar = 4
};

std::string inPlik()
{
    std::cout << "*** Otwieranie ***" << std::endl;
    std::string slowo;
    std::fstream plik;
    plik.open("szyfr.txt", plik.in);
    while (!(plik.is_open()))
    {
        std::cout << "Plik nie owarty!" << std::endl;
        std::cout << "Podaj nazwe pliku: ";
        std::string nazwaPlik{ "" };
        std::cin >> nazwaPlik;
        if (nazwaPlik.find(".txt") == std::string::npos)
        {
            nazwaPlik.append(".txt");
        }
        plik.open(nazwaPlik, plik.in);
    }

    while (!getline(plik, slowo, '\n').eof())
    {
        plik >> slowo;
    }
    std::cout << slowo << std::endl;
    plik.close();
    return slowo;
}

void outPlik(std::string& slowo)
{   
    std::string nazwaPlik;
    std::fstream plik;

    plik.open("szyfr.txt", std::ifstream::out | std::ifstream::app);
    while (!(plik.is_open()))
    {
        std::cout << "Plik nie owarty!" << std::endl;
        std::cout << "Podaj nazwe pliku: ";
        std::cin >> nazwaPlik;
        if (nazwaPlik.find(".txt") == std::string::npos)
        {
            nazwaPlik.append(".txt");
        }
        plik.open(nazwaPlik, std::ifstream::out | std::ifstream::app);
    }

   // std::cout << "slowo!  " <<slowo<< std::endl;
    plik << slowo;
    plik.close();

    
}


class cSzyfr
{
public:
    //virtual ~cSzyfr() = default;
    //std::string slowo_{""};
    virtual std::string szyfrowanie(std::string& slowo ) = 0;
   // virtual std::string szyfrowanie(std::string& slowo, int& przesuw) = 0;
private:

};

class cGadery : public cSzyfr
{
public:
    std::string szyfrowanie(std::string& slowo) override
    {
        for (int i = 0; i < slowo.size(); i++)
        {
            auto k = mapa_.find(slowo[i]);
            if (k != mapa_.end())
            {
                slowo[i] = k->second;
            }
        }
        return slowo;
    }
private:
std::map<char, char> mapa_{
                        {'g','a'}, {'a','g'},  {'d','e'},  {'e','d'},  {'r','y'},  {'y','r'},
                        {'p','o'}, {'o','p'},  {'l','u'},  {'u','l'},  {'k','i'},  {'i','k'},
                        {'G','A'}, {'A','G'},  {'D','E'},  {'E','D'},  {'R','Y'},  {'Y','R'},
                        {'P','O'}, {'O','P'},  {'L','U'},  {'U','L'},  {'K','I'},  {'I','K'}
};
};

class cMalinowe : public cSzyfr
{
public:
    std::string szyfrowanie(std::string& slowo) override
        {
            for (int i = 0; i < slowo.size(); i++)
            {
                auto k = mapa_.find(slowo[i]);
                if (k != mapa_.end())
                {
                    slowo[i] = k->second;
                }
            }
            return slowo;
        }
private:
    std::map<char, char> mapa_{
                            {'m','a'}, {'a','m'},  {'l','i'},  {'i','l'},  {'n','o'},  {'o','n'},
                            {'w','e'}, {'e','w'},  {'b','u'},  {'u','b'},  {'t','y'},  {'y','t'},
                            {'M','A'}, {'A','M'},  {'L','I'},  {'I','L'},  {'N','O'},  {'O','N'},
                            {'W','E'}, {'E','W'},  {'B','U'},  {'U','B'},  {'T','Y'},  {'Y','T'}
    };

    
};

class cMorse : public cSzyfr
{
private:
std::map<char, std::string> mapa_{
    {' ',"/"},
    {'a', "*-/"},{'b',"-***/"},{'c',"-*-*/"},{'d',"-**/"},{'e',"*/"},
    {'f',"**-*/"},{'g',"--*/"},{'i',"**/"},{'j',"*---/"},{'k',"-*-/"},
    {'l',"*-**/"},{'m',"--/"},{'n',"-*/"},{'o',"---/"},{'p',"*--*/"},
    {'q',"--*-/"},{'r',"*-*/"},{'s',"***/"},{'t',"-/"},{'u',"**-/"},
    {'w',"*--/"},{'x', "-**-/"},{'y',"-*--/"}, {'z', "--**/"},
    {'A', "*-/"},{'B',"-***/"},{'C',"-*-*/"},{'D',"-**/"},{'E',"*/"},
    {'F',"**-*/"},{'G',"--*/"},{'I',"**/"},{'J',"*---/"},{'K',"-*-/"},
    {'L',"*-**/"},{'M',"--/"},{'N',"-*/"},{'O',"---/"},{'P',"*--*/"},
    {'Q',"--*-/"},{'R',"*-*/"},{'S',"***/"},{'T',"-/"},{'U',"**-/"},
    {'W',"*--/"},{'X', "-**-/"},{'Y',"-*--/"}, {'Z', "--**/"}
};
public:

std::string szyfrowanie (std::string& slowo) override
{
    std::string slowo2{};
    for (int i = 0; i < slowo.size(); i++)
    {
        auto k = mapa_.find(slowo[i]);
        if (k != mapa_.end())
        {
            slowo2 += k->second;
        }
    }
    slowo2 += {"/"};
    return slowo2;
}
};


class cCezar : public cSzyfr
{
   
public:
 
std::string szyfrowanie(std::string& slowo) override
{
    int przesuw{ 0 };
    std::cout << "O ile przesunac znaki +/- 26:";
    std::cin >> przesuw;

    for (auto i = 0; i < size(slowo); i++)
    {
        if ((slowo[i] >= 97 && slowo[i] <= 122))
        {
            slowo[i] -= 32;
        }
    }

    if (!(przesuw >= -26 && przesuw <= 26))
    {
        
        std::cout << "dupa przesuw >= -26 && przesuw <= 26 \n ";
        return slowo;
    }

    if(przesuw >=0)
    {
        std::cout << std::endl;
        for (auto i = 0; i < size(slowo); i++)
        {    
            if ( slowo[i] + przesuw <= 'Z')
            {
                slowo[i] += przesuw;
            }
            else
            {
                slowo[i] += przesuw -26 ;
            }
        }
    }
    else
    {
        for (auto i = 0; i < size(slowo); i++)
        {
            if ( slowo[i] + przesuw >= 'A')
            {
                slowo[i] += przesuw;
            }
            else
            {
                slowo[i] += przesuw + 26;
            }
        }
    }
  
    return slowo;
}

};


