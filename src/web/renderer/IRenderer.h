#ifndef IRENDERER_H
#define IRENDERER_H

#include "Text.h"
#include "Link.h"
#include "string"

namespace sentinel {
    namespace web {
        namespace renderer {
            class Text;
            class Link;
            
            class IRenderer {
            public:
                virtual ~IRenderer() { } ;
                virtual bool render(Text& renderable) = 0;
                virtual bool render(Link& renderable) = 0;
                virtual bool start(std::string name) = 0;
                virtual bool end(std::string name) = 0;
                virtual bool newLine() = 0;
            };            
        }
    }
}

#endif /* IRENDERER_H */

