#include "Text.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            Text::Text(const std::string label) 
                : label(label) { }
                
            bool Text::render(IRenderer& renderer) {
                return renderer.render(*this);
            }
        }
    }
}