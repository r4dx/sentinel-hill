#ifndef HTMLRENDERER_H
#define HTMLRENDERER_H

#include "IRenderer.h"
#include "IRenderable.h"
#include "Text.h"
#include "Link.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            class HtmlRenderer: public IRenderer {
            public:
                ~HtmlRenderer() { } ;
                bool render(Text renderable) override;
                bool render(Link renderable) override;
            };            
        }
    }
}

#endif /* HTMLRENDERER_H */

