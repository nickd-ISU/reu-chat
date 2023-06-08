#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

std::string GET(std::string url) {
    std::string cmd = "curl -s " + url;
    FILE* p = _popen(cmd.c_str(), "r");
    char buffer[2];
    std::string body;
    if (!p) {
        return "Error";
    }
    while (fgets(buffer, sizeof(buffer), p)) {
        body += buffer;
    }
    return body;
}

std::string POST(std::string url, std::string message) {
    std::string cmd = "curl -s POST -d \"chat=" + message + "\" " + url;
    FILE* p = _popen(cmd.c_str(), "r");
    char buffer[2];
    std::string body;
    if (!p) {
        return "Error";
    }
    while (fgets(buffer, sizeof(buffer), p)) {
        body += buffer;
    }
    return body;
}

vector<string> getNewMessages() {
    string response = GET("10.24.221.117:5001/api/v1/chats");

    // parse messages into vector of strings
    stringstream ss(response);
    string item;
    vector<std::string> messages;

    while (getline(ss, item, ',')) {
        messages.push_back(item);
    }

    if (messages.size() < 8) {
        return messages;
    }
    else {
        vector<string> mostRecent(messages.end() - 8, messages.end());
        return mostRecent;
    }
}

string postNewMessage(string newMessage) {
    std::string response = POST("10.24.221.117:5001/api/v1/chats", newMessage);
    return response;
}

int main()
{
	try {
        cout << "Welcome to REU Chat, where you can share your thoughts with fellow interns over the network in C++!" << endl << endl;

        while (true) {
            string userCommand;

            // Ask user which action they want to take
            cout << "----------------------------------" << endl;
            cout << "What would you like to do?" << endl;
            cout << "r: Read new messages" << endl;
            cout << "w: Write a message" << endl;
            cout << "q: Quit the program" << endl;
            cout << "----------------------------------" << endl;
            getline(cin, userCommand);

            if (userCommand.compare("r") == 0) {
                // Get recent messages as a vector of strings, then print them out
                vector<string> messages = getNewMessages();
                cout << "------- recent messages -------" << endl;
                for (int i = 0; i < messages.size(); i++) {
                    cout << messages[i] << endl;
                }
                cout << endl;
            }
            else if (userCommand.compare("w") == 0) {
                // Take the users new message, and post it to the database
                string newMessage;
                cout << "Enter message to post?" << endl;
                getline(cin, newMessage);
                
                // Make sure they typed something
                if (newMessage.length() > 0) {
                    string response = postNewMessage(newMessage);
                    cout << "message sent!" << endl;
                }
                else {
                    cout << "-- Error: Do not leave message field blank --" << endl;
                }
            }
            else if (userCommand.compare("q") == 0) {
                break;
            }
            else {
                cout << "Invalid input - Please enter r, w or q" << endl;
            }
        }
        
	}
	catch (const exception& e) {
		cerr << "Request failed, error: " << e.what() << endl;
	}

	return 0;
}
