#ifndef BODY_H
#define BODY_H

#include "IRenderer.h"
#include <list>

namespace sentinel {
    namespace web {
        namespace renderer {
            class Body : public IRenderable {
            public:
                ~Body() { } ;
                bool render(IRenderer& renderer) override;
                
                void add(IRenderable& element) {
                    children.push_back(&element);
                }
                
                std::list<IRenderable*>::const_iterator begin() {
                    return children.begin();
                }

                std::list<IRenderable*>::const_iterator end() {
                    return children.end();
                }
                
            private:
                std::list<IRenderable*> children;
            };            
        }
    }
}

#endif /* BODY_H */

