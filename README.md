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


