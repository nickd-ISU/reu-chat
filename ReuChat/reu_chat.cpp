#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "reu_http.h"

using namespace std;

#include <iostream>
#include <vector>
#include <sstream>
#include "reu_http.h"

std::vector<std::string> splitString(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

int main()
{
	// url is the address of the chat server
	std::string url = "http://nicks-mac.vrac.iastate.edu:5001/api/v1/chats";

	std::string input;
	while (true) {
		std::cout << "Enter 'get' to view chat messages or 'post' to send a message: ";
		std::cin >> input;
		if (input == "get") {
			std::string messages = GET(url);
			std::vector<std::string> messageList = splitString(messages, ',');
			int i = 0;
			std::cout << "\nChat messages:" << std::endl;
			while (i < 10 && i < messageList.size()) {
				std::cout << i << ": " << messageList[messageList.size() - i - 1] << std::endl;
				i++;
			}
			std::cout << std::endl;
		}
		else if (input == "post") {
			std::string message;
			std::cout << "Enter your message: ";
			std::cin.ignore();
			std::getline(std::cin, message);
			if (POST(url, message) == "200") {
				std::cout << "Message sent successfully" << std::endl;
			}
			else {
				std::cout << "Error sending message" << std::endl;
			}
		}
		else {
			std::cout << "Invalid input" << std::endl;
		}
	}
}
