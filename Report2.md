# Report 2

## Weekly Meeting Notes 
Over the weekend, we met with the primary goal of selecting a Raft library to use for our project.  We tried several libraries, but many were dated and had issues with installation including outdated dependencies.

We finally settled on Nuraft, a relatively recent Raft implementation in C++.  

Nuraft includes two example programs that work for us locally on Mac and Linux.  While supported by a full Raft implementation under the hood, these example programs work by running as separate processes that communicate with each other over localhost. 

The first example program allows the user to type a message in the terminal of the "leader" process, which is received and printed by the follower processes.  The second example program is a distributed calculator that allows the user to enter arithmetic commands in the terminal of the leader.  The results are stored and printed by all processes.

## Future Goals

The example programs show some basic Raft functionality.  However, we intend to update them in several ways.  First, we will decide on what we want our application to do.  Our current plan is to implement a chat application.  Then we will determine a way to deploy the app. 


[Trello Board](https://trello.com/b/hbhwfHb7/ecs251-final-project)
