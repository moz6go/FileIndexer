#include "searchfiles.h"

#if defined(_WIN32)
void SearchFiles::Index(std::wofstream& fout, std::wstring path) {
    WIN32_FIND_DATAW file_data;
    FileInfo curr_file_info;
    path += L"\\*.*";
    HANDLE file = FindFirstFile(path.c_str(), &file_data);
    path.resize(path.size() - 3);
    if (file != INVALID_HANDLE_VALUE) {
        do {
            //skip "." and ".."
            if (wcslen(file_data.cFileName) == 1 && wcschr(file_data.cFileName, '.') != nullptr) {
                if (FindNextFile(file, &file_data) == 0) {
                    break;
                }
            }
            if (wcslen(file_data.cFileName) == 2 && wcsstr(file_data.cFileName, L"..") != nullptr) {
                if (FindNextFile(file, &file_data) == 0) {
                    break;
                }
            }

            if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                ++c_dir_;
                path += file_data.cFileName;
                Index(fout, path);
                path.resize(path.size() - wcslen(file_data.cFileName) - 1);
            }
            //init fileinfo
            curr_file_info.name = file_data.cFileName;
            curr_file_info.path = path + curr_file_info.name;
            curr_file_info.date = file_data.ftLastWriteTime.dwLowDateTime;
            curr_file_info.extension =  !(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ?
                                            (curr_file_info.name.substr(curr_file_info.name.find_last_of('.') + 1) == curr_file_info.name ?
                                                L"Unknown": curr_file_info.name.substr(curr_file_info.name.find_last_of('.') + 1)):
                                        L"DIR";
            curr_file_info.size = file_data.nFileSizeLow;

            ++count_;
            WriteNodeMap(fout, curr_file_info);
        } while (FindNextFile(file, &file_data) != 0);
        FindClose(file);
    }
}

#else
void SearchFiles::Index(std::ofstream& fout, char* path) {
    DIR *dir;
    struct dirent *dir_obj;
    struct stat file_info;
    FileInfo curr_file_info;
    char temp_path[PATH_MAX];
    strcat(path, "/");

    if ((dir = opendir(path)) != NULL) {
        if (path[strlen(path) - 1] != '/') strcat(path, "/");
        while ((dir_obj = readdir(dir)) != NULL) {
            if (strcmp(".", dir_obj->d_name) == 0 || strcmp("..", dir_obj->d_name) == 0 || dir_obj->d_name[0] == '.') {
                continue;
            }
            strcpy(temp_path, path);
            strcat(temp_path, dir_obj->d_name);
            if (!(dir_obj->d_type ^ DT_DIR)) {
                ++c_dir_;
                strcat(path, dir_obj->d_name);
                Index(fout, path);
                path[strlen(path) - strlen(dir_obj->d_name) - 1] = '\0';;
            }
            //init fileinfo
            strcpy(curr_file_info.name, dir_obj->d_name);
            strcat(strcpy(curr_file_info.path, path), curr_file_info.name);
            curr_file_info.date = file_info.st_mtim.tv_sec;
            SetFileExtension(dir_obj, curr_file_info);
            curr_file_info.size = !strcmp(curr_file_info.extension, "DIR") ? 0 : file_info.st_size;

            temp_path[0] = '\0';
            ++count_;
            WriteNodeMap(fout, curr_file_info);
        }
        closedir(dir);
    }
}
#endif


#if defined(_WIN32)
void SearchFiles::SetFileExtension(const WIN32_FIND_DATAW& file_data, FileInfo& curr_file_info) {
    if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        curr_file_info.extension = L"DIR";
        curr_file_info.is_dir = true;
    }
    else {
        size_t j = 0;
        size_t i = wcslen(file_data.cFileName) - 1;
        while (file_data.cFileName[i] != '.' && i) {
            curr_file_info.extension[j] = file_data.cFileName[i];
            ++j;
            --i;
        }
        if(!i) {
            curr_file_info.extension = L"Unknown";
        }
        else {
            curr_file_info.extension[j] = '\0';

            if (curr_file_info.extension.size()) {
                i = curr_file_info.extension.size() - 1;
                j = 0;
                while (i > j) {
                    wchar_t tmp = curr_file_info.extension[i];
                    curr_file_info.extension[i] = curr_file_info.extension[j];
                    curr_file_info.extension[j] = tmp;
                    --i;
                    ++j;
                }
            }
        }
        curr_file_info.is_dir = false;
    }
}

#else
void SearchFiles::SetFileExtension(dirent* dir_obj, FileInfo& curr_file_info) {
    if (!(dir_obj->d_type ^ DT_DIR) || dir_obj->d_name[0] == '.') {
        strcpy(curr_file_info.extension, "DIR");
        curr_file_info.is_dir = true;
    }
    else {
        size_t j = 0;
        size_t i = strlen(dir_obj->d_name) - 1;
        while (dir_obj->d_name[i] != '.' && i) {
            curr_file_info.extension[j] = dir_obj->d_name[i];
            ++j;
            --i;
        }
        if(!i) {
            strcpy(curr_file_info.extension, "Unknown");
        }
        else {
            curr_file_info.extension[j] = '\0';
            if (strlen(curr_file_info.extension)) {
                i = strlen(curr_file_info.extension) - 1;
                j = 0;
                while (i > j) {
                    char tmp = curr_file_info.extension[i];
                    curr_file_info.extension[i] = curr_file_info.extension[j];
                    curr_file_info.extension[j] = tmp;
                    --i;
                    ++j;
                }
            }
        }
        curr_file_info.is_dir = false;
    }
}
#endif

SearchFiles::SearchFiles() : type_(BY_NAME), count_(0), c_dir_(1) {}

SearchFiles::~SearchFiles() {}

void SearchFiles::WriteNodeMap(std::wofstream& fout, FileInfo& node) const {
    if (fout.is_open()) {
#if defined(_WIN32)
        fout << "Object Name: \t" << node.name <<
            "\nObject Path: \t" << node.path <<
            "\nObject Date: \t" << node.date <<
            "\nObject Extension: \t" << node.extension <<
            "\nObject Size: \t" << node.size << "\n\n";

#else
        char str_date[20];
        strftime(str_date, 20, "%Y-%m-%d %H:%M:%S", localtime(&node.date));
        fout << "Object Name: \t" << node.name <<
            "\nObject Path: \t" << node.path <<
            "\nObject Date: \t" << str_date <<
            "\nObject Extension: \t" << node.extension <<
            "\nObject Size: \t" << node.size << "\n\n";
#endif
    }
}

unsigned SearchFiles::GetObjectCount() const {
    return count_;
}

unsigned SearchFiles::GetDirCount() const {
    return c_dir_;
}

