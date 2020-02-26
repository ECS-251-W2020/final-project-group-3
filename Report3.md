# Report 3

## Weekly Meeting Notes 
Over the past week, we made progress with our project.  We are now considering what future goals are interesting and also realistic to pursue in the time that remains for this quarter.

First, we enabled communication between our Google cloud instances.  Although seemingly simple, we were prevented from acheiving this until we realized we needed to open ports on our instances for communication.

The sample program we are working with is provided by Nuraft and is called "echo server".  In it's initial formulation, when it runs it takes two parameters: a number representing the Nuraft member number, and a second string which comprises the instance IP address and port number.  Communication is provided by the Nuraft library and faithfully emulates the Raft protocol.  

The program has some shortcomings.  It is terminal based and is not particularly user friendly.  Initially, only the leader had the capability to print messages, and then replicate those messages across the cluster.

Nuraft was published recently (2019) by two programmers that work at Ebay.  We understand that Ebay users Nuraft internally for some purpose (we are not sure what it is used for).

One upside of Nuraft is we found that one of the code authors is willing to communicate with us over public Github posts.  It seems they want to encourage people to use Nuraft.

We were puzzled regarding how to enable message posts by Raft followers (i.e. instances other than the leader).  Initially, echo server did not provide this functionality.  However, after posting a question on Github, one of the authors (Jung-Sang Ahn) advised us to change a single variable, called "auto-forwarding", from false to true.  After doing this, message posts from followers are enabled.

We now have a very basic chat app implementation that is consistent with Raft.  For example, servers can crash (i.e. terminate Google cloud instance), but so long as a majority of the cluster remains the app will function. When a member rejoins, it is updated and prints out the current state (i.e. message log).  

## Current Shortcomings

Echo Server is intended only as a simple demonstration program.  While functional as a Raft based chat application, it does have some shortcomings.

One problem is that currently when instances leave, the cluster size is not reduced.  For example, if we start with 10 members, and then 5 leave, the cluster size does not update.  Thus, since we now lack a quorum (majority), the app will stop working.  While theoretically, this allows servers to crash and rejoin, it presents obvious usability problems for a chat application.

Other shortcomings include the UI, which is currently terminal based.  Even without migrating from the terminal, the current output could be improved.  

We like the idea of a peer to peer chat app that does not require a database.  We discovered there is a similar app already on the app store, called Firechat.  It is not clear how Firechat stores messages, since it functions without wifi or cellular data.  However, we do not believe it is using Raft.  So the idea for our project may have some improvements in the area of fault tolerance over a product like Firechat.


## Future Goals

As far as more grandiose goals, we would like some input regarding what is acheivable this quarter.  We like the idea of a peer to peer mobile app using Raft, but this may be too difficult.  For one thing, no one on our team has any experience with mobile programming.  In addition, it is not clear how the phones using something like Firechat would communicate.  Do the use wifi with an antannae for extended range?  Or the phones radiofrequency transmitter that ordinarily communicates with the nearest tower?  We're not sure.  Other ideas include putting the echo server functionality inside a web browser, which is actually the idea behind the paper, Peer-to-Peer Browser Middleware for Communication and Consensus in an Unreliable Infrastructure (2015).  Once it's in a browser, the idea is to use WebRTC to communicate directly between mobile devices.  Although we tried to compile raft.js, which is the library behind this paper, we found it had many outdated dependencies.  We were not able to compile or run it. 


[Trello Board](https://trello.com/b/hbhwfHb7/ecs251-final-project)