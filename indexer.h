#ifndef SERCHFILES_H
#define SERCHFILES_H

#include <string>
#include <cstring>
#include <fstream>

#include "statechecker.h"

#if defined(_WIN32)
    #include <Windows.h>
    #include <wchar.h>
    typedef std::wstring string_t;
    typedef std::wofstream ofstream_t;
    typedef unsigned long f_size_t;
#else
    #include <dirent.h>
    #include <sys/stat.h>
    typedef std::string string_t;
    typedef std::ofstream ofstream_t;
    typedef long f_size_t;
#endif

#define INDEX_FILE "index.xml"

class Indexer : public StateChecker {
    Q_OBJECT
public:
    struct FileInfo {
        string_t name;
        string_t path;
        string_t extension;
        f_size_t size;
        time_t date;
    };
    Indexer();
    ~Indexer();
    void Index();
    unsigned GetObjectCount() const;
    unsigned GetDirCount() const;
    void SetCount(unsigned c_dir, unsigned c_obj);
private:
    SearchType type_;
    unsigned count_;
    unsigned c_dir_;
    ofstream_t fout;
    void WriteXml(FileInfo& node, ofstream_t& fout) const;
    void RecursiveSearchFiles(string_t path);
};

#endif // SERCHFILES_H
