#ifndef LINK_H
#define LINK_H

#include "IRenderer.h"
#include "IRenderable.h"
#include <string>

namespace sentinel {
    namespace web {
        namespace renderer {
            class Link : public IRenderable {
            public:
                ~Link() { } ;
                Link(const std::string label, const std::string ref);
                bool render(IRenderer& renderer) override;
                
                const std::string& getLabel() const {
                    return label;
                }
                
                const std::string& getRef() const {
                    return ref;
                }
                
            private:
                const std::string label;
                const std::string ref;
            };            
        }
    }
}

#endif /* LINK_H */

