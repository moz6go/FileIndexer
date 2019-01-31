#ifndef SERCHFILES_H
#define SERCHFILES_H

#include <string>
#include <cstring>
#include <fstream>
#include "myenums.h"
#include "statechecker.h"

#if defined(_WIN32)
    #include <Windows.h>
    #include <wchar.h>
    typedef std::wstring string_t;
    typedef std::wofstream ofstream_t;
#else
    #include <dirent.h>
    #include <sys/stat.h>
    typedef std::string string_t;
    typedef std::ofstream ofstream_t;
#endif

class SearchFiles : public StateChecker {
    struct FileInfo {
        string_t name;
        string_t path;
        string_t extension;
        unsigned size;
        time_t date;
        bool is_dir;
    };
    bool stop_;
    SearchType type_;
    unsigned count_;
    unsigned c_dir_;
    void WriteNode(ofstream_t& fout, FileInfo& node) const;
public:
    SearchFiles();
    ~SearchFiles();
    void Index(ofstream_t& fout, string_t path);
    unsigned GetObjectCount() const;
    unsigned GetDirCount() const;
    void SetCount(unsigned c_dir, unsigned c_obj);
    void Stop(bool stop);
};

#endif // SERCHFILES_H
