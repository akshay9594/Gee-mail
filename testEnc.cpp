#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <gcrypt.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "crypto++/salsa.h"
#include "crypto++/osrng.h"
#include <iomanip> 
#include <sstream>

using namespace std;
using namespace CryptoPP;

string encriptEmail (string body, string passphrase, string& iv);
string decryptEmail (string body, string passphrase, string iv);
string strtohex(string str);
string hextostr(string hex);


string strtohex(string str){

        
    static const char* const lut = "0123456789ABCDEF";
    size_t len = str.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = str[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
        
     
    
}
string hextostr(string hex){
    
string str;
   
CryptoPP::HexDecoder decoder;

decoder.Put( (byte*)hex.data(), hex.size() );
decoder.MessageEnd();

word64 size = decoder.MaxRetrievable();
if(size && size <= SIZE_MAX)
{
    str.resize(size);		
    decoder.Get((byte*)str.data(), str.size());
}
    return str;
}

string encriptEmail (string body, string passphrase, string& iv){
    
  ifstream f;
  string temp;
  f.open("/dev/urandom");
  getline(f,temp);
  AutoSeededRandomPool prng;
  gcry_error_t     gcryError;
    gcry_cipher_hd_t gcryCipherHd;
    size_t           index;
    char * salsaKey = hash2(passphrase); // 32 bytes
    cout <<"salsaKey len: "<<strlen(salsaKey)<<endl<<salsaKey<<endl;
    //string ivBytes = "AAAAAAAA"; // 8 bytes
    //iv = ivBytes
    
    char *ivBytes = (char*) malloc(9);
    bool tag = false;
    while(!tag){
    if(temp.length()>8){
    strncpy(ivBytes,temp.substr(0,8).c_str(),8);
    ivBytes[8]='\0';
    cout <<"ivBytes len: "<<strlen(ivBytes)<<endl<<ivBytes<<endl;
    temp = temp.substr(0,8) ;
    cout <<"temp: "<<temp.length()<<endl<<temp<<endl;
    iv = strtohex(temp);
    cout <<"iv: "<<iv.length()<<endl<<iv<<endl;
        tag =true;
    }
    else{
        getline(f,temp);
    }}
    f.close();
    gcryError = gcry_cipher_open(
        &gcryCipherHd, // gcry_cipher_hd_t *
        GCRY_CIPHER_SALSA20,   // int
        GCRY_CIPHER_MODE_STREAM,   // int
        0);            // unsigned int
   
    printf("gcry_cipher_open worked\n");
    
    gcryError = gcry_cipher_setkey(gcryCipherHd, salsaKey, 32);
 
    printf("gcry_cipher_setkey worked\n");
    
    gcryError = gcry_cipher_setiv(gcryCipherHd, ivBytes, 8);
  
    printf("gcry_cipher_setiv worked\n");
    
    size_t txtLength = body.length();
    char * encBuffer = (char*)malloc(txtLength+1);
    char * textBuffer = (char*)malloc(txtLength+1);

    strncpy(textBuffer,body.c_str(),body.length());
    textBuffer[body.length()]='\0';
    txtLength = strlen(textBuffer);
    cout<<"Text buffer len: "<<strlen(textBuffer)<<endl<<textBuffer<<endl;

    gcryError = gcry_cipher_encrypt(
        gcryCipherHd, // gcry_cipher_hd_t
        encBuffer,    // void *
        txtLength,    // size_t
        textBuffer,    // const void *
        txtLength);   // size_t
    encBuffer[txtLength]='\0';
    cout<<"Enc buffer len: "<<strlen(encBuffer)<<endl<<encBuffer<<endl;
    string ciphertextStr(encBuffer);
    string cipherhex = strtohex(ciphertextStr);
    free(encBuffer);
    free(textBuffer);
    free(salsaKey);
    free(ivBytes);
    cout<<"cipherhex len: "<<cipherhex.length()<<endl<<cipherhex<<endl;
    return cipherhex;

    
}

string decryptEmail (string body, string passphrase, string iv){
    
  
  
    gcry_error_t     gcryError;
    gcry_cipher_hd_t gcryCipherHd;
    size_t           index;
    char * salsaKey = passphrase; // 32 bytes
    //string ivBytes = "AAAAAAAA"; // 8 bytes
    
    string ivstring = hextostr(iv);
    cout<<"iv: "<<iv.length()<<endl<<iv;
    char *ivBytes = (char*)malloc(9);
    strncpy(ivBytes,ivstring.c_str(),ivstring.length());
    ivBytes[8]='\0';
    cout <<"ivBytes len: "<<strlen(ivBytes)<<endl<<ivBytes<<endl;
    //byte *ivBytes = (byte*)iv.c_str();
	

    gcryError = gcry_cipher_open(
        &gcryCipherHd, // gcry_cipher_hd_t *
        GCRY_CIPHER_SALSA20,   // int
        GCRY_CIPHER_MODE_STREAM,   // int
        0);            // unsigned int
 
    printf("gcry_cipher_open worked\n");
    
    gcryError = gcry_cipher_setkey(gcryCipherHd, salsaKey, 32);
 
    printf("gcry_cipher_setkey worked\n");
    
    gcryError = gcry_cipher_setiv(gcryCipherHd, ivBytes, 8);
  
    printf("gcry_cipher_setiv worked\n");
    
    cout <<"body length is: "<<body.length()<<endl<<body<<endl;
    string cipherstr = hextostr(body);
    cout <<"cipherstr length is: "<<cipherstr.length()<<endl<<cipherstr<<endl;
    size_t txtLength = cipherstr.length();
    char * encBuffer = (char*)malloc(txtLength+10);
    char * textBuffer = (char*)malloc(txtLength+10);
    
    strncpy(encBuffer,cipherstr.c_str(),cipherstr.length());
    encBuffer[cipherstr.length()]='\0';
    txtLength=strlen(encBuffer);
    cout <<"encBuffer length is: "<<txtLength<<endl<<encBuffer<<endl;
    gcryError = gcry_cipher_encrypt(
        gcryCipherHd, // gcry_cipher_hd_t
        textBuffer,    // void *
        txtLength,    // size_t
        encBuffer,    // const void *
        txtLength);   // size_t
    textBuffer[cipherstr.length()]='\0';
    cout <<"textBuffer length is: "<<textBuffer<<" "<< strlen(textBuffer)<<endl;
    string plaintextStr(textBuffer);
    cout <<"plaintextStr length is: "<<plaintextStr.length()<<endl<<plaintextStr<<endl;
    free(encBuffer);
    free(textBuffer);
    free(salsaKey);
    free(ivBytes);
    return plaintextStr;

    
}

int main (int argc, char *argv[]) {

string text="My name is Saleh!!!";
string iv="123456";
string passphrase="E73D77DF36F331DE8981B57BCEBE5AA07AD38AAA2D2D18A4909E3B05E418DB31";
cout << encriptEmail(text,passphrase,iv)<<endl;

return 0;
}