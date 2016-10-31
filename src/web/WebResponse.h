#ifndef WEBRESPONSE_H
#define WEBRESPONSE_H

#include <string>

class WebResponse {
private:
    std::string response;
    
public:
    static WebResponse const invalid;
    WebResponse(std::string response);
    
    std::string getResponse();
};

#endif