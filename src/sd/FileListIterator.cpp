#include "FileListIterator.h"
#include "File.h"
#include <assert.h>

sd::file::FileListIterator::FileListIterator(File& folder) 
    : folder(&folder), current(nullptr), isEnd(false) 
{ 
    folder.rewindDirectory();
    next(); 
}

sd::file::FileListIterator::FileListIterator() : folder(nullptr), 
        current(nullptr), isEnd(true) {
    
}

sd::file::FileListIterator& sd::file::FileListIterator::operator++ () {
    next();
    return *this;
}

void sd::file::FileListIterator::next() {
    if (isEnd)
        return;
    
    File entry = folder->openNextFile();
    bool isValid = sd::file::valid(&entry);
    bool isDir = entry.isDirectory();
    char* name = entry.name();
    entry.close();

    if (!isValid) {
        isEnd = true;
        current = std::shared_ptr<FileEntry>(nullptr);
        return;
    }
    
    if (current == nullptr)
        current = std::shared_ptr<FileEntry>(new FileEntry());
    
    current->fileName = std::shared_ptr<std::string>(new std::string(name));
    current->isDirectory = isDir;    
}

sd::file::FileEntry& sd::file::FileListIterator::operator* () const {
    assert(current != nullptr && "Invalid iterator dereference");
    return *current;
}

sd::file::FileEntry* sd::file::FileListIterator::operator-> () const {
    assert(current != nullptr && "Invalid iterator dereference");
    return current.get();
}

sd::file::FileListIterator sd::file::FileListIterator::operator++ (int) {
    FileListIterator tmp(*this);
    next();
    return tmp;
}
bool sd::file::FileListIterator::operator== (
    const sd::file::FileListIterator& rhs) const {
    return equals(rhs);
}

bool sd::file::FileListIterator::operator!= (
    const sd::file::FileListIterator& rhs) const {
    return !equals(rhs);
}

bool sd::file::FileListIterator::equals(
    const sd::file::FileListIterator& rhs) const {
    return current == rhs.current && isEnd == rhs.isEnd;
}

 const sd::file::FileListIterator& sd::file::FileListIterator::end() {
    static sd::file::FileListIterator end_itr;
    return end_itr;
}