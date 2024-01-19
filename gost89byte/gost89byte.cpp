#include <iostream>
#include <stdint.h>
#include <bitset>
#include <cstddef>
#include <string>
#include <windows.h>
using namespace std;
typedef bitset<32> byte32;
typedef bitset<4> byte4;
unsigned long Tab_Z[8][16] =
{
 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
 0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,
 0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,
 0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,
 0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,
 0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,
 0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,
 0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x0,0x1,0x2,0x3,0x4,0x5,0x6,
};
unsigned long encode(unsigned long val, unsigned long key)
{
    unsigned long temp = val ^ key;
    int div = 0;
    unsigned long new_val = 0;
    for (size_t i = 0; i < 8; i++)
    {
        unsigned long temp1 = (temp >> 28-i*4) & 15;
        new_val ^= temp1 << 28 - i * 4;
    }
    new_val = (new_val << 11) | (new_val >> 21);
    return new_val;
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string word = "hellomynameiswho";
    string key = "thisisaveryhardkeybecauseyoucant";
    int i2 = 0;
    unsigned long left,right,key_u,right_temp = 0;
    //int div = 24;
    cout << "hellomyn"<<endl;
    for (size_t i = 0; i < 4; i++)
    {
        unsigned long temp = word[i] << 24 - i * 8;
        unsigned long temp1 = word[i+4] << 24 - i * 8;
        unsigned long key1 = key[i] << 24 - i * 8;
        left ^= temp;
        right ^= temp1;
        key_u ^= key1;

    }
    for (size_t i = 0; i < 32; i++)
    {
        if (i % 8 == 0) { cout << "________" << endl; }
        for (size_t j = 0; j < 4; j++)
        {   
            int x = i > 23 ? j + ((31-i) % 8) * 4 : j + 4 * ((i % 8) + 1) - 4;
            cout << x << " ";
        }
        
        cout << endl;
    }
    for (size_t i = 0; i < 32; i++)
    {

        for (size_t j = 0; j < 4; j++)
        {
            unsigned long key1 = 0;
            key1 = i > 23 ? key[j + ((31 - i) % 8) * 4] << 24 - j * 8 : key[j + 4 * ((i % 8) + 1) - 4] << 24 - j * 8;
            key_u ^= key1;
        }
        right_temp = right;
        left ^= encode(right, key_u);
        right = left;
        left = right_temp;
    }
    //cout << right << " " << left << endl;
    for (size_t i = 0; i < 4; i++)
    {
        unsigned long t = (right >> 24 - i * 4)&255;
        cout << (char)t;
    }
    for (size_t i = 0; i < 4; i++)
    {
        unsigned long t = (left >> 24 - i * 4) & 255;
        cout << (char)t;
    }
}

