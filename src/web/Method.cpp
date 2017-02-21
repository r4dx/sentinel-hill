#include "Method.h"
#include <assert.h>

namespace sentinel {
    namespace web {
        HTTPMethod methodToHTTPMethod(Method method) {
            switch (method) {
                case Method::GET:
                    return HTTPMethod::HTTP_GET;
                case Method::POST:
                    return HTTPMethod::HTTP_POST;
                case Method::DELETE:
                    return HTTPMethod::HTTP_DELETE;
                default:
                    assert(0 && "Undefined Method");
            }
        }

        Method httpMethodToMethod(HTTPMethod method) {    
            switch (method) {
                case HTTPMethod::HTTP_GET:
                    return Method::GET;
                case HTTPMethod::HTTP_POST:
                    return Method::POST;
                case HTTPMethod::HTTP_DELETE:
                    return Method::DELETE;
                default:
                    assert(0 && "Undefined HTTPMethod");
            }
        }
    }
}