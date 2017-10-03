/*
 */

#include <bitset>
#include <stdexcept>
#include <string>

#include "base64.h"

using namespace std;


namespace base64
{
        
    const string TABLE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    const char PADDING = '=';
    
    
    int get_index(char character);
    
    
    string encode(char a, char b, char c)
    {        
        string result;
        
        int b00111111 = bitset<8>(string("00111111")).to_ulong();
        
        int i1 = a >> 2;
        int i2 = ((a << 4) + (b >> 4)) & b00111111;
        int i3 = ((b << 2) + (c >> 6)) & b00111111;
        int i4 = c & b00111111;
        
        result += TABLE[i1];
        result += TABLE[i2];
        result += (b == 0) ? PADDING : TABLE[i3];
        result += (c == 0) ? PADDING : TABLE[i4];
        return result;
        
    }
    
    string encode(const string& text)
    {
        string result;
        int text_length = text.length();
        
        for (int i = 0; i < text_length; i += 3)
        {
            char a = text[i];
            char b = (i + 1 < text_length) ? text[i + 1] : 0;
            char c = (i + 2 < text_length) ? text[i + 2] : 0;
            result += encode(a, b, c);
        }
        return result;
    }
    
    int get_index(char character)
    {
        int i = TABLE.find(character);
        
        if (i == string::npos)
            throw invalid_argument(string("Character '") + character + "' cannot be decoded"); 
        
        return i;
    }
    
    string decode(char a, char b, char c, char d)
    {
        string result;
        
        int b11111111 = bitset<8>(string("11111111")).to_ulong();
        
        int i1 = get_index(a);
        int i2 = get_index(b);
        int i3 = (c == PADDING) ? 0 : get_index(c);
        int i4 = (d == PADDING) ? 0 : get_index(d);
        
        result += (((i1 << 2) + (i2 >> 4)) & b11111111);
        
        if (c != PADDING)
        {
            result += (((i2 << 4) + (i3 >> 2)) & b11111111);
        
            if (d != PADDING)
                result += (((i3 << 6) + i4) & b11111111);
        }
        return result;
    }
    
    string decode(const string& text)
    {
        int length = text.length();
        
        if (length % 4 != 0)
            throw invalid_argument("Text length must be divisible by four");
        
        string result;
        
        for (int i = 0; i < text.length(); i += 4)
            result += decode(text[i], text[i + 1], text[i + 2], text[i + 3]);
        
        return result;
    }
    
}