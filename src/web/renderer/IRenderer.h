#ifndef IRENDERER_H
#define IRENDERER_H

#include "Text.h"
#include "Link.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            class Text;
            class Link;
            class Body;
            
            class IRenderer {
            public:
                virtual ~IRenderer() { } ;
                virtual bool render(Text& renderable) = 0;
                virtual bool render(Link& renderable) = 0;
                virtual bool render(Body& renderable) = 0;
            };            
        }
    }
}

#endif /* IRENDERER_H */

