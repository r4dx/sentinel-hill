#ifndef LINK_H
#define LINK_H

#include "IRenderer.h"
#include "IRenderable.h"
#include <string>
#include <memory>

namespace sentinel {
    namespace web {
        namespace renderer {
            class Link : public IRenderable {
            public:
                Link(std::shared_ptr<std::string> label, 
                        std::shared_ptr<std::string> ref);
                bool render(IRenderer& renderer) override;
                
                const std::string& getLabel() const {
                    return *label;
                }
                
                const std::string& getRef() const {
                    return *ref;
                }
                
            private:
                std::shared_ptr<std::string> label;
                std::shared_ptr<std::string> ref;
            };            
        }
    }
}

#endif /* LINK_H */

