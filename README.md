# IPC message queues
The server program provides two IPC message queues: input and output. A client program sends a single query with its process PID as 
the message type and then receives the response from the other queue (both queues common for the server and all clients). Numbers (keys)
of both server queues are known to the clients. The server can receive messages of any type (mtype = 0), and responses to clients can go to a 
common queue because they are distinguished by the type being the number of the client's process.

The server performs the function of a Polish-English dictionary; receives a string containing a Polish word and sends back the 
corresponding English word or the message "I dont know that word".

## remarks
* run programs in separate terminals
* run server program first
