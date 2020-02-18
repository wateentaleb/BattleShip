// Josh Bainbridge -- 250869629
#include "thread.h"
#include "socket.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace Sync;

// This thread handles the connection to the server
class ClientThread : public Thread
{
private:
	// Reference to our connected socket
	Socket& socket;

	// Data to send to server
	bool& done;
	ByteArray data;
	std::string data_str;
public:
	ClientThread(Socket& socket, bool& done)
	: socket(socket), done(done)
	{}

	~ClientThread()
	{}

	virtual long ThreadMain()
	{
		try{
			int result = socket.Open();
		} 
		catch (...){
			std::cout << "Could not connect" <<std::endl;
			done = true;
 		}
				// Get the data

		if (done == true){
			return 0; 
		}
		else
		{
			//std::cout << "Please input your data (done to exit): ";
			//std::cout.flush();
			//std::getline(std::cin, data_str);
			done = false; 
			bool wait = true; 
								
			while(data_str != "done" && !done){
		
			// Write to the server
				socket.Read(data); 
				if (data.ToString() == "2" ){
					std::cout <<"Server says I am --> " << data.ToString()<< std::endl;
					socket.Read(data); 
					std::cout <<"Incoming Message --> " << data.ToString()<< std::endl;
					wait = false;
				}
				else if (data.ToString() == "wait")
					wait = true; 				

				else {
					std::cout <<"Server says I am --> " << data.ToString()<< std::endl;
					std::cout << "Please input another data (done to exit): ";
					std::cout.flush();
					std::getline(std::cin, data_str);
					socket.Write(ByteArray(data_str));
					wait = false;
				}
				if(wait == false)break;
			
			//if (socket.Read(data) <= 0 || socket.Write(data) <= 0 ){
			//	done = true;
			//	std::cout <<"Ops we lost the server!" <<std::endl;  
			//}
			//else{
			// Get the response
			//socket.Read(data);
			//...
			//return 1; 
			//}
			
			// Get the data
			
			//if (data_str != " " )
				
		

		}
	}
		done = true; 
		return 0;
	}
};

int main(void)
{
	// Welcome the user 
	bool done = false; 
	std::cout << "SE3313 Lab 4 Client" << std::endl;

	// Create our socket
	Socket socket("127.0.0.1", 3000);
	
	ClientThread clientThread(socket, done); 
	while (!done){
		sleep(1);
	}
	try 
	{
		socket.Close();
	}
	catch (...)
	{

	}
	
	return 0;
}
