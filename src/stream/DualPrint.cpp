#include "DualPrint.h"
#include <cassert>

namespace sentinel {
    namespace stream {
        DualPrint::DualPrint(Print& print1, Print& print2) : 
            prints({ { print1, false }, { print2, false } }) {
        }
        size_t DualPrint::write(uint8_t byte) {           
            size_t result = -1;
            
            for (int i = 0; i < ELEMENTS; i++) {
                if (!prints[i].isStopped)
                    result = prints[i].print.write(byte);
            }
            return result;
        }
        
        size_t DualPrint::write(const uint8_t *buffer, size_t size) {
            size_t result = -1;
            for (int i = 0; i < ELEMENTS; i++) {
                if (!prints[i].isStopped)
                    result = prints[i].print.write(buffer, size);
            }            
            return result;
        }
        
        void DualPrint::suspend(PrintNum printNum) {
            prints[printNum].isStopped = true;
        }
        
        void DualPrint::resume(PrintNum printNum) {
            prints[printNum].isStopped = false;
        }
        
        bool DualPrint::substitute(PrintNum printNum, const Print& print) {
            if (!prints[printNum].isStopped)
                return false;
            
            prints[printNum].print = print;
            return true;
        }
    }
}