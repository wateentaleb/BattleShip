# BattleShip

## Objective 
The project ties together the elements you have been using in the labs to create a multi-user, multi-transaction server. This project implements threads, thread synchronization (semaphores and so on), and parallel processing. 

## Project Constraints 

The multi-transaction, multi-user server MUST conform to the following:
+ The server MUST run in the UNIX/LINUX environment. The project is hosted on Amazons AWS server. Keep in mind, that if you are working behind a router (maybe at home you are using a router) or firewall, you may need to forward or open ports.
+ The server MUST run in a different physical environment (machine) than the clients. Running the server on VM and a client on machine hosting this VM does not comply with this requirement.
+ Each transaction MUST have AT LEAST two participating clients.
+ There should in principle be NO LIMIT to the number of simultaneous possible
transactions.
+ Termination MUST be graceful. That means transactions clean up after themselves
in a graceful way. It also means that terminating the server terminates all associated transactions in a graceful way. “Graceful” means without core dumps, unhandled exceptions, the need to kill the process and so on. A client can be unceremoniously booted out of a transaction, as long as no crashes occur.

The project is flexible with respect to the following:
+ The client can run in whatever environment (or set of environments) you like. Possibilities include Android and Java clients. 

## Demonstration 

![battleship](https://user-images.githubusercontent.com/16707828/74701538-09a65100-51d5-11ea-9c69-6633410abe09.gif)


## Battleship Game Design (Client) 
The battleship game utilizes two separate host clients, Client 1 and Client 2.  These clients are connected to a server which acts as a median to allow communication between both clients.  The server creates a thread that include client pairs, moreover; it represents the game instance, which includes both Client 1 and Client 2.  The server relays information between the clients (synchronization of objects). The data being sent from client to client through server medium is sent in a string with the following format (“bool win, bool hit, int move x, int move y, int shipID,boolean hasGone()”). The server sends the string to the client as is. Furthermore, once the object successfully travels from the sending client through the server to the receiving client, the string is parsed using “,” as the delimited.   The game itself runs on both clients with the battleship GUI being displayed on both ends. 

When the clients establish connections to the server, Client 1 sends a move to the server, which the server then relays to Client 2.  Client 2 will receive Client 1’s move and determine whether it is a hit or a miss.  The GUI of Client 2 is then updated with that result and sends it back to the server.  The server sends this response to Client 1 which prompts the GUI of Client 1 to be updated with this new information.  For the next turn, this sequence is repeated but in reverse order, with Client 2 sending a move to be received by Client 1.  To ensure no data is overwritten and the sequence of relaying data between clients handled by the server stays consistent, the client knows when to wait and when to go based on semaphore like values. Clients are always at a particular state, either making and sending a move, waiting for feedback on that dame move, or waiting for the opponent's move.  

## Server and Termination Design

The server in this application ensures that the connections are being held in a thread.  The threads are stored in a dynamic list that is located in the server.  Each element in this list is a pointer which references each game instance.  As soon as the conditions for a game instance termination are met, the server searches the list for the pointer of said game instance and deletes it.  There are two general situations that will trigger application termination: game over or a disconnect.

### `Game Over`

Every time each client determines whether the received move was a hit or a miss, it checks to see if the game is over.  The conditions of a game over are all ships of either client being destroyed.  If a game over is detected, the application will terminate.  This termination process is outlined above.

### `Disconnection`

There are two disconnect scenarios to account for that will result in program termination:
1)	A client disconnects
2)	Server disconnects

These scenarios are handled within the code to ensure graceful termination.  

**Client Disconnects**
If a client disconnects, the server must first close its connection with the client.  After this is done, the server will shut-down.  

**Server Disconnects**
If the server disconnects, the clients must simply first close their ports, and shutdown.
