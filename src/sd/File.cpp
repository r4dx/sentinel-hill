#include "File.h"

bool sd::file::valid(File* file) {
    return strlen(file->name()) != 0;
    //return file->available();
}

bool sd::file::isFolder(std::string path) {
    File file = SD.open(path.c_str());
    bool result = file.isDirectory();
    file.close();
    return result;
}

