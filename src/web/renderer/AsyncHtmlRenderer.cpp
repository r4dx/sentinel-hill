#include "AsyncHtmlRenderer.h"
#include "Body.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            AsyncHtmlRenderer::AsyncHtmlRenderer(IWebSender* sender) 
                : sender(sender) { 
                sender->send(200, nullptr, "");
                sender->sendContent("<html>");
            }

            AsyncHtmlRenderer::~AsyncHtmlRenderer() {
                // never throws exceptions thus acceptable
                sender->sendContent("</html>");
            }

            
            bool AsyncHtmlRenderer::render(Text& renderable) {
                
            }
            
            bool AsyncHtmlRenderer::render(Link& renderable) {
                
            }
            
            bool AsyncHtmlRenderer::render(Body& renderable) {
                sender->sendContent("<body>");
                
                renderable.onDestroy([this]() {
                    this->sender->sendContent("</body>");
                });

                renderable.onAdd([this](IRenderable& renderable) {
                    renderable.render(*this);
                });
            }
        }
    }
}