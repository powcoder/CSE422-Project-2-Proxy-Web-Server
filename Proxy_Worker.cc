https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Modified from CSE422 FS09
// Modified from CSE422 FS12
// Modified again for CSE422 FS20

#include "Proxy_Worker.h"
#include <sstream>

using namespace std;

/**
 * Constructor.
 *
 * @param cs The socket that is already connected to the requesting client
 */
Proxy_Worker::Proxy_Worker(TCP_Socket *cs) {
    client_sock = cs;
    port = 80; // For a full blown proxy, the server information should be 
               // obtained from each request. However, we simply assume it 
               // to be 80 for our labs.
    server_url = NULL;
               // Must be obtain from each request.
}

/**
 * Deletes all non-null pointers and closes all sockets.
 */
Proxy_Worker::~Proxy_Worker() {
    if(server_url != NULL) {
        delete server_url;
    }

    if(client_request != NULL) {
        delete client_request;
    }

    if(server_response != NULL) {
        delete server_response;
    }
    server_sock.Close();
    client_sock->Close();
}

/******* Private Methods ******/

/**
 * Receives the request from a client and parse it.
 *
 * @return A boolean indicating if getting the request was succesful or not
 */
bool Proxy_Worker::get_request() {
    string url_str;
    try {
        // TODO Get the request from the client (HTTP_Request::receive)

        // TODO Check if the request is received correctly

        // These lines store and remove the client identifier from the header
        // This is used to tag output for the test cases
        client_request->get_header_value("ClientID", client_id);
        client_request->remove_header_field("ClientID");

        // TODO Obtain the server_url from the request (HTTP_Request::get_host 
        //      and HTTP_Request::get_path). url = host + path

        // TODO parse the url using URL::parse

    }
    // Return an internal server error code (this should never happen, 
    // hopefully)
    //
    catch(string msg) {
        print_with_pref(msg, cerr);
        proxy_response(500);
        return false;
    }
    // Catch an error that should be returned to the client as a response
    // This should not happen
    catch (unsigned code) {
        proxy_response(code);
        return false;
    }

    return true;
}

/**
 * Check if the request just received is valid
 *
 * @return If the request is valid or not.
 */
bool Proxy_Worker::check_request() {
    // TODO:`
    // 1. Make sure we're pointing to a server URL
    //    Respond a 404 Not Found if the server is invalid
    //    (That is server_url == NULL)
    // 2. Filter out any "host" with the keyword "facebook"
    //    Note that we are filtering out "host" with "facebook".
    //    "path" with facebook is allowed.
    //    Respond a 403 forbidden for host with facebook.
}

/**
 * Forwards a client request to the server and get the response
 *      1. Forward the request to the server
 *      2. Receive the response header and modify the server field
 *      3. Receive the response body. Handle both chunk/default encoding.
 *
 * @return A boolean indicating if forwarding the request was succesful or not
 */
bool Proxy_Worker::forward_request_get_response() {
    // TODO client.cc can be very helpful for you.

    // TODO pass the client request to the server
    
    // TODO First, connect to the server
    
    // TODO send the request to the server
    
    // TODO receive the response header from the server
    
    // TODO check the response header, is it default encoding or chunked
    
    // TODO receive response body

    return true;
}

/**
 * Modify the Server field and return the response from the server to the client
 *          
 * @return A boolean indicating if returning the request was succesful or not
 *      (always true for now)
 */
bool Proxy_Worker::return_response() {
    // TODO Also modify the server field. Change it to whatever you want.
    //      As long as it contains 'CSE422', it is good.

    // just outputting the response, it is interesting to have a look.
    string buffer;
    print_with_pref("Returning response to client ...", cout);
    print_with_pref("==========================================================", cout);

    buffer.clear();
    server_response->print(buffer);
    print_with_pref(buffer.substr(0, buffer.length() - 4), cout);

    print_with_pref("==========================================================", cout);
    
    // TODO Some code to return the response to the client.

    return true;
}

/**
 * Create a response "locally" and return it to a client
 * For error situations like 403, 404, and 500 .. etc
 *
 * @param error The error code
 * @return A boolean indicating if returning the request was succesful
 *      or not (always true for now)
 */
bool Proxy_Worker::proxy_response(int status_code) {
    string buffer;
    HTTP_Response proxy_res(status_code);
    stringstream ss;
    int content_length = int(proxy_res.get_content_length());
    ss << content_length;

    proxy_res.set_header_field("Content-Length", ss.str());

    ss.str("");
    ss.clear();

    ss << "Returning " << status_code << " to client ...";
    print_with_pref(ss.str(), cout);
    print_with_pref("==========================================================", cout);

    buffer.clear();
    proxy_res.print(buffer);

    print_with_pref(buffer.substr(0, buffer.length() - 4), cout);
    print_with_pref("==========================================================", cout);

    proxy_res.send(*client_sock);
    return true;
}

/**
 * Prints the data to the ostream with each line prefixed with the client ID tag.
 * Adds a newline character at the end.
 *
 * @param data The string to print.
 * @param out The out stream to print to.
 */
void Proxy_Worker::print_with_pref(string data, ostream &out) {
    if (client_id.length() == 0) {
        client_id = "?";
    }

    istringstream iss(data);
    string line;
    while (getline(iss, line))
        out << "[" << client_id << "] " << line << endl;
}

/**
 * Extract the chunk size from a string
 *
 * @param the string
 * @return  the chunk size in int
 *          Note that the chunk size in hex is removed from the string.
 */
// You probably will need this function in 
// Proxy_Worker::forward_request_get_response()
// You can find a similar function in client.h
// You can either remove the hex chunk size or leave it in the data string.
// Both is fine. Maybe you dont want to implement this and you are able 
// to extract the chunk size in the function. It is fine.
// If you dont want this, dont forget to remove the function prototype in 
// Proxy_Worker.h.
int Proxy_Worker::get_chunk_size(string &data) {
    // TODO
}

/******* Public Methods *******/

void Proxy_Worker::handle_request() {
    string buffer;

    // Get HTTP request from the client, check if the request is valid by 
    // parsing it. (parsing is done using HTTP_Request::receive)
    // From the parsed request, obtain the server address (in code, 
    // server_url).
    print_with_pref("New connection established.", cout);
    print_with_pref("New proxy child process started.", cout);
    print_with_pref("Getting request from client...", cout);

    if(!get_request())  {
        // did not get the request, something is wrong, stop this process
        return;
    }  

    // Just outputting the requrst.
    print_with_pref("Received request:", cout);
    print_with_pref("==========================================================", cout);

    client_request->print(buffer);
    print_with_pref(buffer.substr(0, buffer.length() - 4), cout);

    print_with_pref("==========================================================", cout);

    print_with_pref("Checking request...", cout);
    if(!check_request()) {
        // request is invalid, something is wrong, stop this process
        return;
    }
    print_with_pref("Done. The request is valid.", cout);

    // Forward the request to the server.
    // Receive the response header and modify the server header field
    // Receive the response body. Handle the default and chunked transfor 
    // encoding.
    print_with_pref("Forwarding request to server...", cout);
    if(!forward_request_get_response()) {
        return;
    }
  
    //return the response to the client
    return_response();
    print_with_pref("Connection served. Proxy child process terminating.", cout);

    return;
}
