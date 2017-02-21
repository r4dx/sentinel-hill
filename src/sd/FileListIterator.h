#ifndef FILELISTITERATOR_H
#define FILELISTITERATOR_H

#include <string>
#include <memory>
#include <SD.h>

namespace sentinel {
    namespace sd {
        namespace file {
            struct FileEntry {
                std::shared_ptr<std::string> fileName;
                bool isDirectory;
            };

            class FileListIterator {
            public:
                explicit FileListIterator(File& folder);
                FileListIterator& operator++ ();
                FileListIterator operator++ (int);
                bool operator== (const FileListIterator& rhs) const;
                bool operator!= (const FileListIterator& rhs) const;
                FileEntry& operator* () const;
                FileEntry* operator-> () const;

                const FileListIterator& end() const;

            private:            
                FileListIterator();
                void next();
                bool equals(const FileListIterator& rhs) const;

                bool isEnd;
                File* folder;
                const FileListIterator* end_iterator;
                
                std::shared_ptr<FileEntry> current;

            };
        }
    }
}
#endif /* FILELISTITERATOR_H */

