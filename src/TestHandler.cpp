#include "TestHandler.h"

std::string TestHandler::getPath() const {
    return "Test";
}

WebResponse TestHandler::post(WebRequest& request) {
    return WebResponse("<html><h1>POST</h1></html>");
}

WebResponse TestHandler::get(WebRequest& request) {
    return WebResponse("<html><h1>GET</h1></html>");
}
