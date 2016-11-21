#ifndef IWEBHANDLER_H
#define IWEBHANDLER_H

class IWebHandler {
public:
    virtual ~IWebHandler() {};
    virtual std::string getPath() const = 0;
    virtual WebResponse get(WebRequest& request) = 0;
    virtual WebResponse post(WebRequest& request) = 0;
    //virtual WebResponse head(WebRequest& request) = 0;
    //virtual WebResponse put(WebRequest& request) = 0;
    //virtual WebResponse do_delete(WebRequest& request) = 0;
    //virtual WebResponse options(WebRequest& request) = 0;
};
#endif