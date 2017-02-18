#ifndef TEXT_H
#define TEXT_H

#include "IRenderer.h"
#include "IRenderable.h"
#include <string>

namespace sentinel {
    namespace web {
        namespace renderer {
            class Text : public IRenderable {
            public:
                ~Text() { } ;
                Text(const std::string label);
                bool render(IRenderer& renderer) override;
                
                const std::string& getLabel() const {
                    return label;
                }
                
            private:
                const std::string label;
                
            };            
        }
    }
}

#endif /* TEXT_H */

