#ifndef SERCHFILES_H
#define SERCHFILES_H

#include <string>
#include <fstream>
#include <cstring>

#if defined(_WIN32)
    #include <windows.h>
    #define MAX_LEN MAX_PATH
#else
    #include <dirent.h>
    #include <sys/stat.h>
    #define MAX_LEN PATH_MAX
#endif


enum SearchType {
    BY_NAME = 1,
    BY_EXTANSION,
    BY_DATE,
    BY_SIZE
};

class SearchFiles {
    struct FileInfo {
        char name[MAX_LEN];
        char path[MAX_LEN];
        char extension[MAX_LEN];
        unsigned size;
        time_t date;
        bool is_dir;
    };
    SearchType type_;
    unsigned count_;
    unsigned c_dir_;

#if defined(_WIN32)
    void SetFileExtension(const WIN32_FIND_DATAA& file_data, FileInfo& curr_file_data);
#else
    void SetFileExtension(dirent* dir_obj, FileInfo& curr_file_info);
#endif

    void WriteNodeMap(std::ofstream& fout, FileInfo& node) const;
public:
    SearchFiles();
    ~SearchFiles();
    unsigned GetObjectCount() const;
    unsigned GetDirCount() const;

#if defined(_WIN32)
    void Index(std::ofstream& fout, LPTSTR path);
#else
    void Index(std::ofstream& fout, char* path);
#endif

};

#endif // SERCHFILES_H
