#ifndef SERCHFILES_H
#define SERCHFILES_H

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>

#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

enum SearchType {
    BY_NAME = 1,
    BY_EXTANSION,
    BY_DATE,
    BY_SIZE
};

class SearchFiles {
    struct FileInfo{
        char name[PATH_MAX];
        char path[PATH_MAX];
        char extension[PATH_MAX];
        unsigned size;
        time_t date;
        bool is_dir;
    };
    char path_[PATH_MAX];												//root path
    SearchType type_;														//type of sort
    unsigned count_;													//count of sorted objects
    unsigned c_dir_;													//count of dir and subdirs
    void SetFileType(dirent* dir_obj, FileInfo& curr_file_info);
    void WriteNodeMap(std::ofstream& fout, FileInfo& node) const;
public:
    SearchFiles(char* path);
    ~SearchFiles();
    unsigned GetObjectCount() const;
    unsigned GetDirCount() const;
    void GetFilesListMapWrite(std::ofstream& fout, char* path);
};

#endif // SERCHFILES_H
