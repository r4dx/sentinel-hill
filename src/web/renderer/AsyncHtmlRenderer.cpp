#include "AsyncHtmlRenderer.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            AsyncHtmlRenderer::AsyncHtmlRenderer(IWebSender* sender) 
                : sender(sender) { 
                sender->sendContent("<html>");
            }

            AsyncHtmlRenderer::~AsyncHtmlRenderer() {
                // never throws exceptions thus acceptable
                sender->sendContent("</html>");
            }

            
            bool AsyncHtmlRenderer::render(Text& renderable) {
                sender->sendContent("<span>" + renderable.getLabel() + "</span>");
                return true;
            }
            
            bool AsyncHtmlRenderer::render(Link& renderable) {
                sender->sendContent("<a href='" + renderable.getRef() + "'>" + 
                    renderable.getLabel() + "</a>");
                return true;
            }
            
            bool AsyncHtmlRenderer::newLine() {
                sender->sendContent("<br />");
                return true;
            }
            
            bool AsyncHtmlRenderer::start(std::string name) {
                sender->sendContent("<" + name + ">");
                return true;
            }
            bool AsyncHtmlRenderer::end(std::string name) {
                sender->sendContent("</" + name + ">");
                return true;                
            }
        }
    }
}