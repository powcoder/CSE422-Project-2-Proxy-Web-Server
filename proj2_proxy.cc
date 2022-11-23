https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Modified from CSE422 FS09
// Modified from CSE422 FS12

#include <csignal>
#include <sstream>
#include "proj2_proxy.h"

using namespace std;

// Globals...
Proxy_Worker *worker = NULL;
TCP_Socket *listen_sock = NULL;
TCP_Socket *client_sock = NULL;

/**
 * Delete's non-NULL globals and exits.
 *
 * @param sig The received signal.
 */
void sigint_handler(int sig) {
    // TODO
}

/**
 * The main server loop that handles requests by 
 * spawing child processes
 *
 * @param argc The number of cmd args
 * @param argv The array of cmd args
 * @return 0 on clean exit, and 1 on error
 */
int main(int argc, char *argv[]) {
    unsigned short int port = 0;
    int req_id = 0;

    pid_t pid;

    // We need a clean way to exit
    signal(SIGINT, sigint_handler);

    parse_args(argc, argv);

    // SETUP THE LISTENING TCP SOCKET
    // (BIND, LISTEN ... etc)
    // GET THE PORT NUMBER ASSIGNED BY THE OS
    // HAVE A LOOK AT TCP_Socket CLASS
    // You will also gain some insight of these classes by going through the
    // client program.

    cout << "Proxy running at " << port << "..." << endl;

    // start the infinite server loop
    while(true) {
        // accept incoming connections
        
        // For each incoming connection, you want to new a client_sock
        // and do the accept. (Check out TCP_Sock Class)

        // create new process

        // if pid < 0, the creation of process is failed.
        if(pid < 0)
        {
            cerr << "Unable to fork new child process." << endl;
            exit(1);
        }
        // if pid == 0, this is the child process
        else if(pid == 0)
        {
            // call child worker code

            // try to close the client_sock            
            
            break; // Exit this main loop and terminate this child process
        }
        // if pid > 0, this is the parent process
        // Parent process continues the loop to accept new incoming 
        // connections.

        // The child process has done handleing this connection
        // Terminate the child process
    }

    if(pid == 0)
    {
        cout << "Child process terminated." << endl;
    }
    // The parent process
    else
    {
        // close the listening sock
        cout << "Parent process termianted." << endl;
    }

    return 0;
}

