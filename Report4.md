# Report 4

## Weekly Meeting Notes 
Servers are now able to leave the chat session without affecting chat functionality.  We added a command called “leave” that sends a message to the leader containing a “remove server” request.  This is part of the NuRaft API.

One goal for the past week was to set up a central server to facilitate the creation and joining of chat lobbies automatically, as
the current base Raft application required the leader to manually add members via their ip addresses. Test code separate from
the NuRaft codebase, involving dummy clients and servers, was developed for the purposes of learning the asio library that NuRaft relies on for network communications. Once the correct functionality was observed, this was translated as custom classes in our chat
application. Unfortunately, progress was heavily impeded by the difficulty of including these files into the preexisting build
system. This was overcome after countless headaches from trying to understand CMake, but we were able to successfully incorporate
our code into their build system. Now, our application exhibits the ability to communicate with this central server and send
specific messages, such as a join request. The next goal is to have the central server keep track of the **leaders** of certain
chat rooms and have it forward the ip address of new members to those leaders for them to add to their quorum.

Further goals for next week include cleaning up the terminal interface, storing persistent chat history, and adding functionality to the central server to facilitate new members joining a chat session.

Nuraft now supports storing persistent chat history by either typing a command(‘hist’) or outputting a text file. When everyone leaves the chat room, there is a record of past history that can be downloaded and reloaded again in another chatroom session. The reload function is still in test phase and will be the main focus of next week. Also the nuraft now is able to customize the user id so that we can use it instead of the ip address to keep track of every participant. 


[Trello Board](https://trello.com/b/hbhwfHb7/ecs251-final-project)