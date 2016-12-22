#ifndef DUALPRINT_H
#define DUALPRINT_H

#include <Print.h>

namespace sentinel {
    namespace stream {
        
        enum PrintNum {
            First,
            Second
        };
        
        class DualPrint : public Print {
        public:
            DualPrint(Print& print1, Print& print2);

            size_t write(uint8_t) override;
            size_t write(const uint8_t *buffer, size_t size) override;

            void suspend(PrintNum printNum);
            void resume(PrintNum printNum);
            bool substitute(PrintNum printNum, const Print& print);

        private:
            const static int ELEMENTS = PrintNum::Second + 1;
            
            struct StoppablePrint {
                Print& print;
                bool isStopped;
            };
            
            DualPrint::StoppablePrint prints[ELEMENTS];
        };
    }
}
#endif /* DUALPRINT_H */

