╔═╗╔╦╗╔═╗╦╔═  ╔═╗╔═╗╔═╗╔╦╗╔═╗╦╦  
╚═╗ ║ ╠═╣╠╩╗  ║ ╦║╣ ║╣ ║║║╠═╣║║  
╚═╝ ╩ ╩ ╩╩ ╩  ╚═╝╚═╝╚═╝╩ ╩╩ ╩╩╩═╝
HOW TO RUN (STAK GEEMAIL APP) TEAM #11:
 
1-Install all these libraries :
sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils

sudo apt-get install sqlite3

wget https://www.cryptopp.com/cryptopp563.zip
unzip -aoq cryptopp563.zip -d cryptopp
cd cryptopp
make

2-The main file of our code is called “gee mail.cpp”
To run it do:
g++ geemail.cpp -Wno-write-strings -lgcrypt --std=c++11 -lsqlite3

You need to have our database “gee mail.db” on the same directory.