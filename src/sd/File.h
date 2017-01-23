#ifndef FILE_H
#define FILE_H
#include <SD.h>
#include <string.h>
#include "FileListIterator.h"

namespace sd {
    namespace file {
        bool valid(File* file);
        bool isFolder(std::string path);
        FileListIterator list(std::string folder);
    }
}

#endif /* FILE_H */

