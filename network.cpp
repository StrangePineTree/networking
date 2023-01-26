#include <iostream>
#include<SFML/Network.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
     cout << "Client[c] or server[s]? " <<  endl;
     string consoleInput;
     getline( cin, consoleInput);
     if (consoleInput == "c")
     {
         cout << "Input server address: " << endl;
         getline(cin, consoleInput);

         // ----- The client -----
         // Create a socket and connect it to port 55001
         sf::TcpSocket socket;
         socket.connect(consoleInput, 55001);

         // Send a message to the connected host
         string message = "client is watching";
         socket.send(message.c_str(), message.size() + 1);

         int posx = 0;
         int posy = 0;

         while(true){
             // Receive an answer from the server
             char buffer[1024];
             size_t received = 0;
             socket.receive(buffer, sizeof(buffer), received);
             posx = socket.receive(buffer, sizeof(buffer), received);
             posy = socket.receive(buffer, sizeof(buffer), received);
             cout << "The server said: " << buffer << endl;
             cout << posx << endl;
             cout << posy << endl;
         }
    }
    else if (consoleInput == "s")
    {
         int choice;
         string posx;
         string posy;
        // ----- The server -----
        // Create a listener to wait for incoming connections on port 55001
        sf::TcpListener listener;
        listener.listen(55001);

        //Show ip address
         cout << sf::IpAddress::getLocalAddress() <<  endl;
         cout << sf::IpAddress::getPublicAddress() <<  endl;

        // Wait for a connection
        sf::TcpSocket socket;
        listener.accept(socket);
         cout << "New client connected: " << socket.getRemoteAddress() <<  endl;

        // Receive a message from the client
        char buffer[1024];
         size_t received = 0;
        socket.receive(buffer, sizeof(buffer), received);
         cout << "The client said: " << buffer <<  endl;


        string message = "Welcome, client";
        while (true) {
            socket.send(message.c_str(), message.size() + 1);
            socket.send(posx.c_str(), posx.size() + 1);
            socket.send(posy.c_str(), posy.size() + 1);
            cout << "type 1 to send message type 2 to edit location" << endl;
            cin >> choice;
            if (choice == 1) {
                cout << "send your message" << endl;
                cin >> message;
            }
            else{
                cout << "type 1 to edit x and 2 to edit y" << endl;
                cin >> choice;
                if (choice == 1) {
                    cout << "send the new x pos" << endl;
                    cin >> posx;
                }
                else {
                    cout << "send the new y pos" << endl;
                    cin >> posy;
                }
                }
        }
    }

    return 0;
}
