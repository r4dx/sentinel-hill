#ifndef ASYNCHTMLRENDERER_H
#define ASYNCHTMLRENDERER_H

#include "IRenderer.h"
#include "IRenderable.h"
#include "Link.h"
#include "web/IWebServer.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            class AsyncHtmlRenderer: public IRenderer {
            public:                              
                AsyncHtmlRenderer(IWebSender& sender);
                ~AsyncHtmlRenderer();
                bool render(Link& renderable) override;
                bool start(std::string name) override;
                bool end(std::string name) override;
                bool newLine() override;
            private:
                IWebSender& sender;
            };
        }
    }
}

#endif /* ASYNCHTMLRENDERER_H */

