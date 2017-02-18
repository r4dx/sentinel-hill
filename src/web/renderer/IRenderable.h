#ifndef IRENDERABLE_H
#define IRENDERABLE_H

#include "IRenderer.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            class IRenderer;
            
            class IRenderable {
            public:
                virtual ~IRenderable() { } ;
                virtual bool render(IRenderer& renderer) = 0;
            };            
        }
    }
}

#endif /* IRENDERABLE_H */

