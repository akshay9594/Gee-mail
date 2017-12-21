//All imported libraries 
#include <stdio.h>
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <gcrypt.h>
#include <iomanip>
#include <vector>

using namespace std;

//All function's declarations 
static int userNameCount(void *data, int argc, char **argv, char **azColName);
static int insert_query(char* query);
static void registers();
static void logins();
static void second_menu();
static void menu();
static int mydata_callback(void *ptr, int argc, char *argv[], char *names[]);
string hashed(string value);
//all what I should get from the databases
struct MyData {
    string username,password,salt;
};

static int mydata_callback(void *ptr, int argc, char *argv[], char *names[])
{
    vector<MyData> *list = reinterpret_cast<vector<MyData> *>(ptr);
    MyData d;
    d.username = argv[0] ? argv[0] : "";
    d.password = argv[1] ? argv[1] : "";
    d.salt = argv[2] ? argv[2] : "";
    list->push_back(d);
    return 0;
}
//inserting into the database.
static int insert_query(char* query){

    sqlite3* db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("geemail.db", &db);
    if( rc ){
        fprintf(stderr, "Error: Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    };
    
    char* sql = query;
    rc = sqlite3_exec(db, sql, userNameCount, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Error: SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }else{
        fprintf(stdout, "the query inserted successfully\n");
        return 1;
    }
    sqlite3_close(db);
    
}
//converting from string to hexa
static string strToHex(string str){
    static const char* const lut="0123456789ABCDEF";
    size_t len =str.length();
    
    string output;
    output.reserve(2*len);
    for (size_t i=0; i<len ;++i){
        const unsigned char c = str[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    
    return output;
}

//callback after the sqlite3_exec 
//data is not used we can 
static int userNameCount(void *data, int argc, char **argv, char **azColName){
   int i;
    
    *(char*) data=0;
   
//   for(i = 0; i<argc; i++){
//       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//   }
   if(argv[0]>0){
       *(char*) data=1;
   }

   return 0;
}

static int search_in(char* query){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    char data[500];
    /* Open database */
   rc = sqlite3_open("geemail.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Error: Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } 
   /* Create SQL statement */
   char* sql = query;
   //sql = "SELECT * from COMPANY";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, userNameCount, (void*) &data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "Error:SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Search done successfully\n");
      
   }
   sqlite3_close(db);
   return (int)data[0];
}

static void menu(){
    string choice;
    while (1){


        cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"<<endl;
        cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout<<  "║   .d8888b.                                           d8b 888  ║" << endl;
        cout<<  "║  d88P  Y88b                                          Y8P 888  ║" << endl;
        cout<<  "║  888    888                                              888  ║" << endl;
        cout<<  "║  888         .d88b.   .d88b.  88888b.d88b.   8888b.  888 888  ║" << endl;
        cout<<  "║  888  88888 d8P  Y8b d8P  Y8b 888 \"888 \"88b      88b 888 888  ║" << endl;
        cout<<  "║  888    888 88888888 88888888 888  888  888 .d888888 888 888  ║"<< endl;
        cout<<  "║  Y88b  d88P Y8b.     Y8b.     888  888  888 888  888 888 888  ║"<< endl;
        cout<<  "║   \"Y8888P88  \"Y8888   \"Y8888  888  888  888 \"Y888888 888 888  ║"<<endl;
        cout << "║                                                               ║" << endl;
        cout << "║                        - MAIN MENU -                          ║" << endl;
        cout << "║───────────────────────────────────────────────────────────────║" << endl;
        cout << "║  1- Login to your account.                                    ║" << endl;
        cout << "║  2- Register.                                                 ║" << endl;
        cout << "║  3- Exit.                                                     ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║───────────────────────────────────────────────────────────────║" << endl;
        cout << "║   © copy right reserved to STAK 2017.                         ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;
        cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓" << endl;
        cout << " ┌──────────────────────────────────────────────────────────────┐"<< endl;
        cout << " |Please enter one of the options:                              | "<< endl;
        cout << " └──────────────────────────────────────────────────────────────┘"<< endl;
        cin >> choice;
        
        if (isdigit(choice[0]) && (choice=="1")){
            logins();
            break;
        }
        else if (isdigit(choice[0]) && choice== "2"){
            registers();
            break;
        }
        else if (isdigit(choice[0]) && choice== "3"){
            cout <<"._.o0o( Good bye! )o0o._."<<endl;
            exit(0);
            break;
        }
        
        else{
            cout << "Error: Enter a valid choice from th menu.\n\n" << endl;
        }
    }
}



static void registers(){
    string username="";
    string password="";
    string hash_password;
    string p_key="";
    string iquery;
    
     while (1){
    cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"<< endl;
    cout << "╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║          ._.o0o(  Welcome To Geemail )o0o._.           ║" << endl;
    cout << "║                     - Register -                       ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
    cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"<<endl;
    cout << " ┌──────────────────────────────────────────────────────┐"<< endl;
    cout << " |Please enter a user name:                             |" << endl;
    cout << " └──────────────────────────────────────────────────────┘"<< endl;
    cin >> username;
    cout << " ┌──────────────────────────────────────────────────────┐"<< endl;
    cout << " |Please enter a user password:                         |" << endl;
    cout << " └──────────────────────────────────────────────────────┘"<< endl;
    cin >> password;
    cout << " ┌──────────────────────────────────────────────────────┐"<< endl;
    cout << " |Please enter a user public key:                       |" << endl;
    cout << " └──────────────────────────────────────────────────────┘"<< endl;
    cin >> p_key;
    if (username==""||password==""||p_key==""){
        cout<<"Error: username, password and public key can't be empty.\n\n"<<endl;
    }
    if(username.length()<6){
        cout<<"Error: username can't be less than 6 characters.\n\n"<<endl;
    }
    if(password.length()<6){
        cout<<"Error: password can't be less than 6 characters.\n\n"<<endl;
    }
   
    //... all other constraints  to username password key places here
    else{

        cout<<"._.o0o(Thank you for signing up "+username+" !)o0o._."<<endl;
        break;
    }
    }
    string unameSquery="SELECT count(*) as count FROM users WHERE name='"+username+"';";
    char *sql1 = (char *)alloca(unameSquery.size() + 1);
    memcpy(sql1, unameSquery.c_str(), unameSquery.size() + 1);
    int i=search_in(sql1);
        if (i>0){
            cout<<"Error: The username is already in use. Please pick another username."<<endl;
        }
    else{
    hash_password = hashed(password);
    iquery="insert into USERS ('name','password','key')  values ('"+username+"','"+hash_password+"','"+p_key+"');";
    char *sql = (char *)alloca(iquery.size() + 1);
    memcpy(sql, iquery.c_str(), iquery.size() + 1);
    i=insert_query(sql);
    }
    
}
static void app_menu(string username){
    
string choice;
    while (1){
        cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"<<endl;
        cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout<<  "║   .d8888b.                                           d8b 888  ║" << endl;
        cout<<  "║  d88P  Y88b                                          Y8P 888  ║" << endl;
        cout<<  "║  888    888                                              888  ║" << endl;
        cout<<  "║  888         .d88b.   .d88b.  88888b.d88b.   8888b.  888 888  ║" << endl;
        cout<<  "║  888  88888 d8P  Y8b d8P  Y8b 888 \"888 \"88b      88b 888 888  ║" << endl;
        cout<<  "║  888    888 88888888 88888888 888  888  888 .d888888 888 888  ║"<< endl;
        cout<<  "║  Y88b  d88P Y8b.     Y8b.     888  888  888 888  888 888 888  ║"<< endl;
        cout<<  "║   \"Y8888P88  \"Y8888   \"Y8888  888  888  888 \"Y888888 888 888  ║"<<endl;
        cout << "║                                                               ║" << endl;
        cout << "║                         - APP MENU -                          ║" << endl;
        cout << "║───────────────────────────────────────────────────────────────║" << endl;
        cout << "║  1- Send a messsage.                                          ║" << endl;
        cout << "║  2- Read your inbox messages.                                 ║" << endl;
        cout << "║  3- Exit.                                                     ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║                                                               ║" << endl;
        cout << "║───────────────────────────────────────────────────────────────║" << endl;
        cout << "║   © copy right reserved to STAK 2017.                         ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;
        cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓" << endl;
        cout << " ┌──────────────────────────────────────────────────────────────┐"<< endl;
        cout << " |Please enter one of the options:                              | "<< endl;
        cout << " └──────────────────────────────────────────────────────────────┘"<< endl;
        cin >> choice;
        
        if (isdigit(choice[0]) && (choice=="1")){
            //sendmessage();
            break;
        }
        else if (isdigit(choice[0]) && choice== "2"){
            //show_inbox();
            break;
        }
        else if (isdigit(choice[0]) && choice== "3"){
            cout <<"._.o0o( Good bye! )o0o._."<<endl;
            exit(0);
            break;
        }
        
        else{
            cout << "Error: Enter a valid choice from th menu.\n\n" << endl;
        }
    }
    
    
}
static void logins(){
    string username;
    string password;    
    cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"<< endl;
    cout << "╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║          ._.o0o(  Welcome To Geemail )o0o._.           ║" << endl;
    cout << "║                      - Login -                         ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
    cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓"<<endl;
    cout << " ┌──────────────────────────────────────────────────────┐"<< endl;
    cout << " |Please enter a user name:                             |" << endl;
    cout << " └──────────────────────────────────────────────────────┘"<< endl;
    cin >> username;
    cout << " ┌──────────────────────────────────────────────────────┐"<< endl;
    cout << " |Please enter a user password:                         |" << endl;
    cout << " └──────────────────────────────────────────────────────┘"<< endl;
    cin >> password;
    
    
}




string hashed(string value){
    size_t txtLength = value.length();
    size_t index;
    const char * cvalue = value.c_str();
    char * hashBuffer = (char*)malloc(33);
    char * hex2str = (char*)malloc(64);
    char * textBuffer = (char*)malloc(txtLength+1);
    memset(hashBuffer, 0, 33);
    strncpy(textBuffer, cvalue, txtLength);
    gcry_md_hash_buffer(
        GCRY_MD_SHA256, // gcry_cipher_hd_t
        hashBuffer,    // void *
        textBuffer,    // const void *
        txtLength);   // size_t
        
    for(index = 0; index < 32; index++)
      snprintf(hex2str+index*2,sizeof(hex2str),"%02x", (unsigned char)hashBuffer[index]);
    return hex2str;
    free(hashBuffer);
    free(hex2str);
    free(textBuffer);
}

int main(){

    menu();
    return 0;
}
