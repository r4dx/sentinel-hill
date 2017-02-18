#ifndef BODY_H
#define BODY_H

#include "IRenderer.h"
#include <list>
#include <functional>

namespace sentinel {
    namespace web {
        namespace renderer {
            class Body : public IRenderable {
            public:
                
                typedef std::function<void(IRenderable&)> TOnAddFunction;
                typedef std::function<void(void)> TOnDestroyFunction;
                
                ~Body();
                bool render(IRenderer& renderer) override;
                
                void add(IRenderable& element) {
                    children.push_back(&element);
                    if (onAddFunc)
                        onAddFunc(element);
                }
                
                void onAdd(TOnAddFunction func) {
                    onAddFunc = func;
                }
                
                void onDestroy(TOnDestroyFunction func) {
                    onDestroyFunc = func;
                }
                
                std::list<IRenderable*>::const_iterator begin() {
                    return children.begin();
                }

                std::list<IRenderable*>::const_iterator end() {
                    return children.end();
                }
                
            private:
                TOnAddFunction onAddFunc;
                TOnDestroyFunction onDestroyFunc;
                
                std::list<IRenderable*> children;
            };            
        }
    }
}

#endif /* BODY_H */

