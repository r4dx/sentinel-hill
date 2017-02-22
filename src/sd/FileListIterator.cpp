#include "FileListIterator.h"
#include "File.h"
#include "logger/ConsoleFileLoggerWrapper.h"
#include <assert.h>

namespace sentinel {
    namespace sd {
        namespace file {

            FileListIterator::FileListIterator(File& folder) 
                : folder(&folder), current(nullptr), isEnd(false), 
                    end_iterator(std::shared_ptr<FileListIterator>(
                        new FileListIterator())) { 

                folder.rewindDirectory();
                next(); 
            }

            FileListIterator::FileListIterator() : folder(nullptr), 
                    current(nullptr), isEnd(true), end_iterator(nullptr) { }

            FileListIterator& FileListIterator::operator++ () {
                next();
                return *this;
            }

            void FileListIterator::next() {
                if (isEnd)
                    return;

                File entry = folder->openNextFile();
                bool isValid = valid(entry);
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

            FileEntry& FileListIterator::operator* () const {
                assert(current != nullptr && "Invalid iterator dereference");
                return *current;
            }

            FileEntry* FileListIterator::operator-> () const {
                assert(current != nullptr && "Invalid iterator dereference");
                return current.get();
            }

            FileListIterator FileListIterator::operator++ (int) {
                FileListIterator tmp(*this);
                next();
                return tmp;
            }
            bool FileListIterator::operator== (
                const FileListIterator& rhs) const {
                return equals(rhs);
            }

            bool FileListIterator::operator!= (
                const FileListIterator& rhs) const {
                return !equals(rhs);
            }

            bool FileListIterator::equals(
                const FileListIterator& rhs) const {
                return current == rhs.current && isEnd == rhs.isEnd;
            }

             const FileListIterator& FileListIterator::end() const {
                return end_iterator == nullptr ? *this : *end_iterator;
            }
        }
    }
}