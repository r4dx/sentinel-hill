#include "WebResponse.h"

WebResponse::WebResponse(std::string response) : 
    response(response) {

}

std::string WebResponse::getResponse() {
    return response;
}