#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char * encryptDecrypt(char *input, char *key1) {
	int i=0;
	int len1 = strlen(input);
	int len2 = strlen(key1);
	char * result = malloc(len1);
	char * key = malloc(len2);
	for(i = 0; i< len2; i++){
	    if(key1[i]>='a' && key1[i]<='z'){
            key[i]=key1[i]-32;
        } else key[i] = key1[i];
	}
	for (i=0;i<len1;i++){
	    //printf("%c",key[i % len2]);
	    //printf("%c",input[i]);
	    result[i] = input[i] ^ key[i % len2];
	    //printf("%c",result[i]);
	}
	return result;
	free(result);
	free(key);
}

int main (int argc, char *argv[]) {
	char * message = "hello My name is S@l#h ? I @m T!es^ting *& the coDE' )( ±";
	char * key1 = "wewe";
	char * encrpyt = encryptDecrypt(message,key1);
	char * decrpyt = encryptDecrypt(encrpyt,key1);
	printf("%s\n",encrpyt);
	printf("%s\n",decrpyt);
	
}