#include "stdio.h"
#include <gcrypt.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>



using namespace std;
string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}


string hex_to_string(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}
/*
int main()
{
  string s = "2d61372f7df1b1a5b9bdc626bf4130e4211ce38cb361fa0ee9b9606b4e79b079";
  string value = string_to_hex(s);
  cout<< "hex is:"<<value<< endl;
  string hex_converted =  hex_to_string(value);
  cout<< "the hash is:"<<hex_converted<< endl;
}
*/

static string HexOfPass(string password,int salt){
    unsigned char result[32];
    int i,r;
    size_t index;
    char * hashBuffer = (char*)malloc(33);
    size_t txtLength;
    memset(hashBuffer, 0, 33);
    string password =password;
    string append;
    string hash;
    //get the salt
     //int salt =283453656;//random_var();
     string StringSalt=to_string(abs(salt));
     //password+salt
     append=password+StringSalt;
     txtLength = append.length()+1;
     printf("%zu\n",txtLength);
     
    char * textBuffer = (char*)malloc(33);
    cout << append<<endl;
    strncpy(textBuffer,append.c_str(),txtLength);
    
    //hashing
    for(r=0;r<3;r++)
    {
     gcry_md_hash_buffer(
        GCRY_MD_SHA256, // gcry_cipher_hd_t
        hashBuffer,    // void *
        textBuffer,    // const void *
        txtLength);   // size_t

    printf("hashBuffer = ");
    for (index = 0; index<32; index++)
    {   //printf((unsigned char)hashBuffer[index]);
        
        printf("%02X",(unsigned char)hashBuffer[index]);
        if(r==2)
        hash+=("%02X",(unsigned char)hashBuffer[index]);
        //hash[index]=("%02X",(unsigned char)hashBuffer[index]);
    }
    strncpy(textBuffer,hashBuffer,strlen(hashBuffer));
    printf("\n");
   // printf("%s",hash);
    }
    cout<<hash<<endl;
    string hex=string_to_hex(hash);
    cout<<hex<<endl;
    free(hashBuffer);
    free(textBuffer);
   
     return hex;
}
/*
int main () {
    unsigned char result[32];
    int i,r;
    size_t index;
    char * hashBuffer = (char*)malloc(33);
    size_t txtLength;
    memset(hashBuffer, 0, 33);
    string password ="string";
    string append;
    string hash;
    //get the salt
     int salt =283453656;//random_var();
     string StringSalt=to_string(abs(salt));
     //password+salt
     append=password+StringSalt;
     txtLength = append.length()+1;
     printf("%zu\n",txtLength);
     
    char * textBuffer = (char*)malloc(33);
    cout << append<<endl;
    strncpy(textBuffer,append.c_str(),txtLength);
    
    //hashing
    for(r=0;r<3;r++)
    {
     gcry_md_hash_buffer(
        GCRY_MD_SHA256, // gcry_cipher_hd_t
        hashBuffer,    // void *
        textBuffer,    // const void *
        txtLength);   // size_t

    printf("hashBuffer = ");
    for (index = 0; index<32; index++)
    {   //printf((unsigned char)hashBuffer[index]);
        
        printf("%02X",(unsigned char)hashBuffer[index]);
        if(r==2)
        hash+=("%02X",(unsigned char)hashBuffer[index]);
        //hash[index]=("%02X",(unsigned char)hashBuffer[index]);
    }
    strncpy(textBuffer,hashBuffer,strlen(hashBuffer));
    printf("\n");
   // printf("%s",hash);
    }
    cout<<hash<<endl;
    string hex=string_to_hex(hash);
    cout<<hex<<endl;
    free(hashBuffer);
    free(textBuffer);
   
     return 0;
}*/