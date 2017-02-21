#include "File.h"

namespace sd {
    namespace file {

        bool valid(File* file) {
            return strlen(file->name()) != 0;
        }

        bool isFolder(std::string path) {
            File file = SD.open(path.c_str());
            bool result = file.isDirectory();
            file.close();
            return result;
        }
    }
}

