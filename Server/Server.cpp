// Josh Bainbridge -- 250869629
#include "thread.h"
#include "socketserver.h"
#include <stdlib.h>
#include <time.h>
#include <list>
#include <vector>
#include <algorithm>
#include <string>

using namespace Sync;

int usercount;

// This thread handles each client connection
class SocketThread : public Thread
{
private:
    // Reference to our connected socket
    Socket& socket1;
    Socket& socket2;
    // The data we are receiving
    ByteArray data;
public:
    SocketThread(Socket& socket1, Socket& socket2)
    : socket1(socket1), socket2(socket2)
    {}

    ~SocketThread()
    {}

    Socket& GetSocket1()
    {
        return socket1;
    }
    Socket& GetSocket2()
    {
        return socket2;
    }

    virtual long ThreadMain()
    {
        int you = 0; 
        std::string data_str; 
        char check; 
         printf("start talking\n");
                socket1.Write(ByteArray("1"));
                socket2.Write(ByteArray("2"));
        while(1)
        {
            try
            {
                // Wait for data
                socket1.Read(data);                
                // Perform operations on the data
                data_str = data.ToString();
                printf("Socket 1 says");
                std::cout <<data_str <<std::endl;
                // Send it back
                socket2.Write(data);
            }
            catch (...)
            {
                // ???
                std::cout << "Exception occured";
            }
        }
		
	// ???

        return 0;
    }
};

// This thread handles the server operations
class ServerThread : public Thread
{
private:
    SocketServer& server;
    bool terminate = false;
    int count = 0;
    std::vector<SocketThread*> v;
public:
    ServerThread(SocketServer& server)
    : server(server)
    {}

    ~ServerThread()
    {
        for (auto thread : v)
        {
            try 
            {
            Socket& toClose = thread -> GetSocket1();
            toClose.Close(); 
            Socket& toClose2 = thread -> GetSocket2();
            toClose2.Close();
            }
            catch(...)
            {

            }
        }
            
    }
    
    virtual long ThreadMain()
    {
        //while(true){
        int users = 0;   
        Socket* temp;
        while(users < 3){
            try 
            { 
                // Wait for a client socket connection
                Socket* newConnection= new Socket(server.Accept());
                if (users == 0){
                    printf("Please wait for another connection\n");
                    temp = newConnection;
                    Socket& tempSocket = *temp;
                    std::string wait = "Please wait";
                    tempSocket.Write((ByteArray)wait);
                    users++;
                }
                else {
                    Socket& user1 = *temp;
                    Socket& user2 = *newConnection;
                    printf("They are connected\n");
                    SocketThread* socketThread = new SocketThread(user1,user2);
                    v.push_back(socketThread); 
                }                    
                // Pass a reference to this pointer into a new socket thread
                
                
            }
            catch (TerminationException terminationExcp)
            {
               return terminationExcp;
            }
            catch (std::string error)
            {
                return 1;
            }   
        }
        ThreadMain();

    }
};


int main(void)
{
    std::cout << "!!!I am a server." << std::endl;
	std::cout << "Press enter to terminate the server...";
    std::cout.flush();
	
    // Create our server
    SocketServer server(3000);    

    // Need a thread to perform server operations
    ServerThread serverThread(server);
	
    // This will wait for input to shutdown the server
    FlexWait cinWaiter(1, stdin);
    cinWaiter.Wait();
    std::cin.get();

    // Shut down and clean up the server
    server.Shutdown();

}
