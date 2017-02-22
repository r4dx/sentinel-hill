#include "Link.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            Link::Link(std::shared_ptr<std::string> label, 
                    std::shared_ptr<std::string> ref) 
                : label(label), ref(ref) { }
                
            bool Link::render(IRenderer& renderer) {
                return renderer.render(*this);
            }
        }
    }
}