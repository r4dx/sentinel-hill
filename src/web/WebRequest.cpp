#include "WebRequest.h"

std::string WebRequest::getPath() {
    return "Test";
}

Method WebRequest::getMethod() {
    return GET;
}

std::string WebRequest::getRequest() {
    return request;
}

WebRequest::WebRequest(std::string request) : 
    request(request) {

}