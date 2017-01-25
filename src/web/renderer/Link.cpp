#include "Link.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            Link::Link(const std::string& label, const std::string& ref) 
                : label(label), ref(ref) { }
                
            bool Link::render(IRenderer& renderer) {
                return renderer.render(*this);
            }
        }
    }
}