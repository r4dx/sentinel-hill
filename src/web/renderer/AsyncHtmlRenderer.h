#ifndef ASYNCHTMLRENDERER_H
#define ASYNCHTMLRENDERER_H

#include "IRenderer.h"
#include "IRenderable.h"
#include "Text.h"
#include "Link.h"
#include "web/IWebServer.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            class AsyncHtmlRenderer: public IRenderer {
            public:               
                
                // Would be much simpler to just add start("body") and end()
                // and to remove body at all for simplicity reasons
                
                AsyncHtmlRenderer(IWebSender* sender);
                ~AsyncHtmlRenderer();
                bool render(Text& renderable) override;
                bool render(Link& renderable) override;
                bool render(Body& renderable) override;
                
            private:
                IWebSender* sender;
            };
        }
    }
}

#endif /* ASYNCHTMLRENDERER_H */

