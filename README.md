# RPC(Three Tier System)

Team Members: Tyler Hartje and Raj Powar

Contributions
Raj Powar: Design Documentation, main client(places_client.c), modifying the MAKE file and places server
Tyler Hartje: Design Documentation, main clinet(places_client.c), modifying the MAKE file and airports server

Data Structures and Algorithms
Airport Server: Underlying data structure is KD-tree to find the closest five airports
Places Server: Underlying data structure is Prefix Tree(Trie)

Third Party Library
Places Server: makes use of <stdbool.h> library to incorperate boolean type use in C
Airport Server: makes use of of an external kd-tree library for implementation (https://github.com/jtsiomb/kdtree)

Strengths:
1. Our system design is a sturdy one, where we make use of applicabe data structures and alogrithims that can improve the efficiency of the searches. This will also be applicable when the data is scaled.

2. The system a replicates a proper 3-tier rpc system

3. We are able to handle errors based on search as well as any RPC generated errors

Weakness
1. We had issues with the intial set up of the midtier sytem, where the places server is expected to make use of aiports client. We had to combine the the Makefile from the airports into the Makefile of places, where we used one Makefile going forward. Even after combining the Makefile we were seeing issues wiht the places.o not recognizaing the methods declared in the airports. Inorder to overcome this we had tocopy over the xdr methods from the airports into the places xdr file and also methods from airports_svc into places_svc.

2. Our program expects the user to enter in the search in the following format 
   eg: ./places_client localhost seattlecity wa

   It will lead to an error if user searched for "seattle city wa", this is one of drawbacks to the apllication as we are not able to deal with more than two arguments

This will also applied to places that expect a town or anyother  appended to the place

3. Also when we are populating the tree we converting the letters to lower case

4. The output of the places client can be cleaned up and we missed on State infromation for the ouput airports

Instructions
Run places server
./places_server&
Run airports server
./airports_server&
Run the client
./places_client localhost seattlecity wa
