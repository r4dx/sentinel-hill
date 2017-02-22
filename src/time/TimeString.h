#ifndef TIMESTRING_H
#define TIMESTRING_H

#include <string>
#include <ctime>

namespace sentinel {
    namespace time {
        class ITimeProvider {
        public:
            virtual std::string now() const = 0;
            virtual ~ITimeProvider() { };
        };

        class MillisTimeProvider : public ITimeProvider {
        public:
            std::string now() const override;

        private:
            std::time_t getUnixTime() const;
        };
    }
}
#endif /* TIMESTRING_H */

