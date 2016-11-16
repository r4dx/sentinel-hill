#include "File.h"

bool sd::file::valid(File* file) {
    return strlen(file->name()) != 0;
}    