# Report 2

## Weekly Meeting Notes 
Over the weekend, we met with the primary goal of selecting a Raft library to use for our project.  We tried several libraries, but many were dated and had issues with installation including outdated dependencies.

We finally settled on Nuraft, a relatively recent Raft implementation in C++.  

Nuraft includes two example programs that work for us locally on Mac and Linux.  While supported by a full Raft implementation under the hood, these example programs work by running as separate processes that communicate with each other over localhost. 

The first example program allows the user to type a message in the terminal of the "leader" process, which is received and printed by the follower processes.  The second example program is a distributed calculator that allows the user to enter arithmetic commands in the terminal of the leader.  The results are stored and printed by all processes.

Subsequently, we created a docker image that containerizes the Nuraft library and dependencies.  We successfully deployed the docker image to a Google cloud compute instance.

## Future Goals

The example programs show some basic Raft functionality.  However, we intend to update them in several ways.  

We posted our goals to the project Trello board.  In the short term, we want to 1) finalize our cloud deployment strategy, 2) implement communication between compute instances, 3) modify the existing "echo" sample application to function as a terminal based chat application.

In the longer term, we are considering possible directions for this project.  One idea is to implement a web application that uses Nuraft.  This would include a more user-friendly, web based chat interface.


[Trello Board](https://trello.com/b/hbhwfHb7/ecs251-final-project)
