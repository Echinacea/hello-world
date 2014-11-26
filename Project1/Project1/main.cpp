#pragma comment(lib, "Ws2_32.lib")
#include <iostream.>
#include <WinSock2.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;
long doGetFileSize(const char* filePath, const char* mode);
//https://www.byvoid.com/blog/fast-readfilea
//http://openhome.cc/Gossip/CppGossip/BinaryFileIO.html
//http://xyz.cinc.biz/2014/02/c-socket-server-client.html
//http://www2.lssh.tp.edu.tw/~hlf/class-1/lang-c/c++file.htm
int main(void)
{
	
	
	//=======================read file========================
	static char data_name[20]="test.png";
	
	cout<<"file reading . . ."<<endl;
	long int size=0;
	size=doGetFileSize(data_name,"r");//get size
	cout<<"file size="<<size<<"byte"<<endl; 
	char *ptr = (char*)malloc(sizeof(char)*size);
	cout<<"locate finish"<<endl;
	fstream file;
	file.open(data_name,ios::in|ios::binary);
	file.read(ptr, size);
	file.close();
	file.open(data_name,ios::out|ios::binary);
	file.write(ptr, size);
	file.close();
	cout<<"read fininsh!"<<endl;
	//=======================================================
	
	int r;
    WSAData wsaData;
    WORD DLLVSERION;
    DLLVSERION = MAKEWORD(2,1);//Winsocket-DLL 版本
    //用 WSAStartup 開始 Winsocket-DLL
    r = WSAStartup(DLLVSERION, &wsaData);
 
    //宣告 socket 位址資訊(不同的通訊,有不同的位址資訊,所以會有不同的資料結構存放這些位址資訊)
    SOCKADDR_IN addr;
    int addrlen = sizeof(addr);
 
    //建立 socket
    SOCKET sListen; //listening for an incoming connection
    SOCKET sConnect; //operating if a connection was found
 
    //AF_INET：表示建立的 socket 屬於 internet family
    //SOCK_STREAM：表示建立的 socket 是 connection-oriented socket 
    sConnect = socket(AF_INET, SOCK_STREAM, NULL);
 
    //設定位址資訊的資料
    addr.sin_addr.s_addr = inet_addr("140.125.33.210");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
 
    //設定 Listen
    sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);//SOMAXCONN: listening without any limit
 
    //等待連線
    SOCKADDR_IN clinetAddr;
    
        cout << "waiting..." << endl;
		
	while(1)
	{
			if(sConnect =accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen))
			{
				
				
				printf("server: got connection from %s\n", inet_ntoa(addr.sin_addr));
				while(1)
				{
					Sleep(1000);
					
					static int data;
				
					//send(sConnect, ptr, size, 0);
				
					data++;
					data_name[0]=data;
					if(send(sConnect, ptr,size, 0)==-1)
					{
						cout<<"connect close"<<endl;	
						break;
					}else
					{
						cout<<"success_send_output"<<sizeof(data_name)<<endl;
					}
				}
			}
			
	} 

system("pause");

return 0;

}
long doGetFileSize(const char* filePath, const char* mode){
long fileLength = 0;
FILE *fp;
//開啟檔案
if(! (fp = fopen(filePath, mode))){
//File Open Error
return -1;
}
//移動指標到檔案的結尾
if(fseek(fp, 0, SEEK_END)) {
//File seek error.
return -1;
}
//取得檔案大小 單位byte
fileLength = ftell(fp);
//移動指標回檔案起始
rewind(fp);

return fileLength;
}
