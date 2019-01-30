#include "searchfiles.h"

SearchFiles::SearchFiles() : type_(BY_NAME), count_(0), c_dir_(1) {}

SearchFiles::~SearchFiles() {}

#if defined(_WIN32)
void SearchFiles::Index(ofstream_t& fout, string_t path) {
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
void SearchFiles::Index(ofstream_t& fout, string_t path) {
    DIR *dir;
    struct dirent *dir_obj;
    struct stat file_info;
    FileInfo curr_file_info;
    string_t temp_path;
    path.push_back ('/');

    if ((dir = opendir(path.c_str ())) != NULL) {
        if (path.back ()!= '/') path.push_back ('/');
        while ((dir_obj = readdir(dir)) != NULL) {
            if (strcmp(".", dir_obj->d_name) == 0 || strcmp("..", dir_obj->d_name) == 0 || dir_obj->d_name[0] == '.') {
                continue;
            }
            temp_path = path;
            temp_path += dir_obj->d_name;
            stat(temp_path.c_str (), &file_info);
            if (!(dir_obj->d_type ^ DT_DIR)) {
                ++c_dir_;
                path += dir_obj->d_name;
                Index(fout, path);
                path.resize(path.size() - strlen(dir_obj->d_name));
            }
            //init fileinfo

            curr_file_info.name = dir_obj->d_name;
            curr_file_info.path = path + curr_file_info.name;
            curr_file_info.date = file_info.st_mtim.tv_sec;
            curr_file_info.extension =  !(!(dir_obj->d_type ^ DT_DIR) || dir_obj->d_name[0] == '.') ?
                                            (curr_file_info.name.substr(curr_file_info.name.find_last_of('.') + 1) == curr_file_info.name ?
                                                "Unknown": curr_file_info.name.substr(curr_file_info.name.find_last_of('.') + 1)):
                                        "DIR";
            curr_file_info.size = curr_file_info.extension == "DIR" ? 0 : file_info.st_size;
            temp_path.clear ();
            ++count_;
            WriteNodeMap(fout, curr_file_info);
        }
        closedir(dir);
    }
}
#endif

void SearchFiles::WriteNodeMap(ofstream_t& fout, FileInfo& node) const {
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

