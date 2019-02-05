#ifndef GENERAL
#define GENERAL

#include <string>
#include <cstring>
#include <fstream>

#if defined(_WIN32)
    typedef std::wstring string_t;
    typedef std::wofstream ofstream_t;
    typedef unsigned long f_size_t;
#else
    typedef std::string string_t;
    typedef std::ofstream ofstream_t;
    typedef long f_size_t;
#endif

#define INDEX_FILE "index.xml"

enum SearchType {
    BY_NAME = 1,
    BY_EXTANSION,
    BY_DATE,
    BY_SIZE
};

enum Process {
    DEFAULT = 1,
    START,
    STOP,
    PAUSE,
    SEARCH
};

struct FileInfo {
    string_t name;
    string_t path;
    string_t extension;
    f_size_t size;
    time_t date;
};

#endif

