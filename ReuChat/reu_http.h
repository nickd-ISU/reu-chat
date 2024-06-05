#pragma once

#include <string>

// GET returns a string representation of a list of ALL chat messages in the database
std::string GET(std::string url) {
    std::string cmd = "curl -s -w \\n%{http_code} " + url;
    FILE* p = _popen(cmd.c_str(), "r");
    char buffer[2];
    std::string body;
    if (!p) {
        return "Error running curl command";
    }
    while (fgets(buffer, sizeof(buffer), p)) {
        body += buffer;
    }
    std::string status = body.substr(body.find_last_of('\n') + 1);
    if (status == "200") {
        return body.substr(0, body.find_last_of('\n'));
    }
    else if (status == "404") {
        std::cout << "404 Not Found: Make sure the URL is correct" << std::endl;
    }
    else if (status == "500") {
        std::cout << "500 Internal Server Error: The server is not responding" << std::endl;
    }
    else if (status == "000") {
        std::cout << "000 Error: Make sure the URL is correct" << std::endl;
    }
    else {
        std::cout << "Error: " << status << std::endl;
    }
}

// POST sends a message to be stored in the database. If successful, it returns the string "200"
std::string POST(std::string url, std::string message) {
    std::string cmd = "curl -s POST -d \"chat=" + message + "\" " + url;
    FILE* p = _popen(cmd.c_str(), "r");
    char buffer[2];
    std::string body;
    if (!p) {
        return "Error running curl command";
    }
    while (fgets(buffer, sizeof(buffer), p)) {
        body += buffer;
    }
    if (body == "200") {
        return "200";
    }
    else {
        std::cout << "Error inserting message: Make sure the URL is correct" << std::endl;
    }
    return body;
}
