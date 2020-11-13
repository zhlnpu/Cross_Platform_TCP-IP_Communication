#include<stdio.h>
#include<string.h>	//strlen
#include<stdlib.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

#include<pthread.h> //for threading , link with lpthread
#include<map> //for threading , link with lpthread

using namespace std;

enum CLIENT_NAME
{
    COMMAND_CONNECTION = 0,


    CN_PC_1 = 101,
    CN_PC_2 = 102,
    CN_PC_3 = 103,
    CN_PC_4 = 104,
    CN_PC_5 = 105,


    CN_UNITY_1 = 201,
    CN_UNITY_2 = 202,
    CN_UNITY_3 = 203,
    CN_UNITY_4 = 204,
    CN_UNITY_5 = 205,


    CN_ANDROID_1 = 301,
    CN_ANDROID_2 = 302,
    CN_ANDROID_3 = 303,
    CN_ANDROID_4 = 304,
    CN_ANDROID_5 = 305,


    CN_HOLOLENS_1 = 401,
    CN_HOLOLENS_2 = 402,
    CN_HOLOLENS_3 = 403,
    CN_HOLOLENS_4 = 404,
    CN_HOLOLENS_5 = 405,


};


typedef struct tagClientInfo
{
//	CLIENT_TYPE		Type;
    int				IP;
} ClientInfo;

// manage clients and distribute messages and objects
class ServerManager {
public:
    int ServerSocket;
    map<int, ClientInfo> m_Socket2Client;

private:
    //   ModelingManager				m_Manager;

public:

    void RmvClient(int client) {
        m_Socket2Client.erase(client);

    }

    void AddClient(int client, int ip) {

        ClientInfo cInfo;
        cInfo.IP = ip;
//	cInfo.Type = (CLIENT_TYPE)type;

        m_Socket2Client[client] = cInfo;
    }


// 	// Process inputs -------------------------------------------------------
// 	void ProcessInput(InputBase* pInput, const SOCKET& from);
//
// 	// Process outputs ------------------------------------------------------
// 	void ProcessModeling(Modeling* pModeling, const SOCKET& from);

    //void test(char input[]);
    ServerManager(void) {
    }

    ~ServerManager(void) {
    }
};

ServerManager		serverManager;


struct ClientThreadParam
{
    int			ipAddr;
    int		ClientSocket;
};
#define DEFAULT_BUFLEN	128


void *ClientThread(void *ctPrtam)
{
    //Get the socket descriptor
    ClientThreadParam* ctParam = (ClientThreadParam*)ctPrtam;

    // 1. Receiving and Sending Data on the Server
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult;

    do {                                                                                        // 5.1 Receive until the peer shuts down the connection
        iResult = recv(ctParam->ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {

            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &ctParam->ipAddr, ip_str, INET_ADDRSTRLEN);

            CLIENT_NAME _CommandType;

            memcpy(&_CommandType, &recvbuf[0], sizeof(int));
            //Command command(recvbuf);
            //0. connection new client
            if (_CommandType == CLIENT_NAME::COMMAND_CONNECTION) {
                serverManager.AddClient(ctParam->ClientSocket, ctParam->ipAddr);
                printf("Client number is %d.\n", serverManager.m_Socket2Client.size());
                printf("Client %s is connected!\n\n", ip_str);
            } else {
                //	cout << "Received data from client: " + to_string(_CommandType) << endl;

                for (map<int, ClientInfo>::iterator it = serverManager.m_Socket2Client.begin();
                     it != serverManager.m_Socket2Client.end(); it++) {
                    if ((*it).first == ctParam->ClientSocket)                // source should not be updated
                        continue;
                    send((*it).first, recvbuf, DEFAULT_BUFLEN, 0);
                }
            }

        }
    } while (iResult > 0);

// 2. Disconnecting the Server
    serverManager.RmvClient(ctParam->ClientSocket);
    printf("Client number is %d.\n", serverManager.m_Socket2Client.size());

    iResult = shutdown(ctParam->ClientSocket, SHUT_RDWR);										// 2.1 shutdown the connection since we're done
    if (iResult == 0) {
        close(ctParam->ClientSocket);													// 2.2 cleanup
        delete ctParam;
        return 0;
    }
    else {
        printf("Failed to shutdown client with error: %d\n");
        close(ctParam->ClientSocket);
        delete ctParam;
        return 0;
    }
}





void *ServerThread(void *socket_desc) {
    int addr_len = sizeof(struct sockaddr_in);



    // 1. Accepting a Connection -----------------------------------------------------------------------------
    while (true) {
        sockaddr client_addr;
        int new_socket;


        //wait, wait, wait..........until a client connected
        while ((new_socket = accept(serverManager.ServerSocket, &client_addr, (socklen_t *) &addr_len))) {
            struct sockaddr_in *pV4Addr = (struct sockaddr_in *) &client_addr;
            int ipAddr = pV4Addr->sin_addr.s_addr;

            ClientThreadParam *ctParam = new ClientThreadParam;
            ctParam->ipAddr = ipAddr;
            ctParam->ClientSocket = new_socket;

            pthread_t sniffer_thread;

            puts("new client detected");

            if( pthread_create( &sniffer_thread , NULL ,  ClientThread , (void*) ctParam) < 0)
            {
                perror("could not create client thread");
                //return 1;
            }
        }

        if (new_socket < 0) {
            perror("accept failed");
              return 0;
        }

    }

    return 0;
}


int main(int argc , char *argv[]) {
    int new_socket, c, *new_sock;
    struct sockaddr_in server, client;
    char *message;


    serverManager.ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverManager.ServerSocket == -1) {
        printf("Could not create socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(27015);

    //Bind
    if (bind(serverManager.ServerSocket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(serverManager.ServerSocket, SOMAXCONN);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");


    pthread_t server_thread;


    if (pthread_create(&server_thread, NULL, ServerThread, 0) < 0) {


        perror("could not create thread");
        return 1;
    }

    while (true) {
        char input[6];
        scanf("%s", input);

        if (strcmp(input, "clear") == 0) {
            system("cls");
        }


        if (strcmp(input, "exit") == 0) {
            if (serverManager.m_Socket2Client.size() == 0) {
                break;
            } else {
                printf("Client is running!\n\n");
            }
        }



        // type any key to test this code --------------------------------------
        //serverManager.test(input);
    }

    serverManager.m_Socket2Client.clear();

    close(serverManager.ServerSocket);                            // 4.2 No longer need server socket

    return 0;


}
