# Report 4

## Weekly Meeting Notes 
Servers are now able to leave the chat session without affecting chat functionality.  We added a command called “leave” that sends a message to the leader containing a “remove server” request.  This is part of the NuRaft API.

Further goals for next week include cleaning up the terminal interface, storing persistent chat history, and adding a central server to facilitate new members joining a chat session.

Nuraft now supports storing persistent chat history by either typing a command(‘hist’) or outputting a text file. When everyone leaves the chat room, there is a record of past history that can be downloaded and reloaded again in another chatroom session. The reload function is still in test phase and will be the main focus of next week. Also the nuraft now is able to customize the user id so that we can use it instead of the ip address to keep track of every participant. 


[Trello Board](https://trello.com/b/hbhwfHb7/ecs251-final-project)