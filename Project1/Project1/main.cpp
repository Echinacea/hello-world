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
    DLLVSERION = MAKEWORD(2,1);//Winsocket-DLL ����
    //�� WSAStartup �}�l Winsocket-DLL
    r = WSAStartup(DLLVSERION, &wsaData);
 
    //�ŧi socket ��}��T(���P���q�T,�����P����}��T,�ҥH�|�����P����Ƶ��c�s��o�Ǧ�}��T)
    SOCKADDR_IN addr;
    int addrlen = sizeof(addr);
 
    //�إ� socket
    SOCKET sListen; //listening for an incoming connection
    SOCKET sConnect; //operating if a connection was found
 
    //AF_INET�G��ܫإߪ� socket �ݩ� internet family
    //SOCK_STREAM�G��ܫإߪ� socket �O connection-oriented socket 
    sConnect = socket(AF_INET, SOCK_STREAM, NULL);
 
    //�]�w��}��T�����
    addr.sin_addr.s_addr = inet_addr("140.125.33.210");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
 
    //�]�w Listen
    sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);//SOMAXCONN: listening without any limit
 
    //���ݳs�u
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
//�}���ɮ�
if(! (fp = fopen(filePath, mode))){
//File Open Error
return -1;
}
//���ʫ��Ш��ɮת�����
if(fseek(fp, 0, SEEK_END)) {
//File seek error.
return -1;
}
//���o�ɮפj�p ���byte
fileLength = ftell(fp);
//���ʫ��Ц^�ɮװ_�l
rewind(fp);

return fileLength;
}
