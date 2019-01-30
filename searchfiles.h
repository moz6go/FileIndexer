#ifndef SERCHFILES_H
#define SERCHFILES_H

#include <string>
#include <fstream>
#include <cstring>

#if defined(_WIN32)
    #include <Windows.h>
    #include <wchar.h>
    typedef std::wstring string_t
    typedef std::wofstream ofstream_t;
#else
    #include <dirent.h>
    #include <sys/stat.h>
    typedef std::string string_t;
    typedef std::ofstream ofstream_t;
#endif


enum SearchType {
    BY_NAME = 1,
    BY_EXTANSION,
    BY_DATE,
    BY_SIZE
};

class SearchFiles {
    struct FileInfo {
        string_t name;
        string_t path;
        string_t extension;
        unsigned size;
        time_t date;
        bool is_dir;
    };
    SearchType type_;
    unsigned count_;
    unsigned c_dir_;
    void WriteNodeMap(ofstream_t& fout, FileInfo& node) const;
public:
    SearchFiles();
    ~SearchFiles();
    void Index(ofstream_t& fout, string_t path);
    unsigned GetObjectCount() const;
    unsigned GetDirCount() const;
};

#endif // SERCHFILES_H
