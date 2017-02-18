#include "Body.h"

namespace sentinel {
    namespace web {
        namespace renderer {
            bool Body::render(IRenderer& renderer) {
                return renderer.render(*this);
            }
            
            Body::~Body() {
                if (onDestroyFunc)
                    onDestroyFunc();
            }
        }
    }
}