#ifndef SERCHFILES_H
#define SERCHFILES_H

#include "statechecker.h"
#include "xmlreader.h"

#if defined(_WIN32)
    #include <Windows.h>
    #include <wchar.h>
#else
    #include <dirent.h>
    #include <sys/stat.h>
#endif

class Indexer : public StateChecker {
    Q_OBJECT
    SearchType type_;
    unsigned count_;
    unsigned c_dir_;
    ofstream_t fout;
    void WriteIndex(FileInfo& node, ofstream_t& fout) const;
    void RecursiveSearchFiles(string_t path);
public:
    Indexer();
    ~Indexer();
    void Index();
    unsigned GetObjectCount() const;
    unsigned GetDirCount() const;
    void SetCount(unsigned c_dir, unsigned c_obj);
};

#endif // SERCHFILES_H
