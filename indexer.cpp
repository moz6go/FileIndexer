#include "indexer.h"

Indexer::Indexer() : type_(BY_NAME), count_(0), c_dir_(1)  {
}

Indexer::~Indexer() {}

void Indexer::Index(){
    fout.open(INDEX_FILE);
    if (fout.is_open()) {
        fout << "<?xml version = " << '"' << "1.0" << '"' << "?>\n" <<
                "<!-- Filesystem index -->\n" <<
                "<filesystem>\n";
    }
#if defined(_WIN32)
    DWORD dr = GetLogicalDrives();
    for (int x = 0; x <= 'Z'-'A'; x++)
    {
        int n = ((dr >> x) & 1);
        if (n)
        {
            string_t disc;
            disc.push_back(static_cast<wchar_t>('A' + x));
            disc += L":\\";
            RecursiveSearchFiles(disc);
        }
    }
#else
    RecursiveSearchFiles ("");
#endif
    fout << "</filesystem>";
    fout.close ();
}

#if defined(_WIN32)
void Indexer::RecursiveSearchFiles(string_t path) {
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
                RecursiveSearchFiles(path);
                path.resize(path.size() - wcslen(file_data.cFileName));
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
            WriteXml(curr_file_info, fout);

            if(state_ == STOP) return;
            if(state_ == PAUSE) while (state_ == PAUSE) QThread::msleep (100); //need to rework...

        } while (FindNextFile(file, &file_data) != 0);
        FindClose(file);
    }
}
#else
void Indexer::RecursiveSearchFiles(string_t path) {
    DIR *dir;
    struct dirent *dir_obj;
    struct stat file_info;
    FileInfo curr_file_info;
    string_t temp_path;
    path.push_back ('/');

    if ((dir = opendir(path.c_str ())) != nullptr) {
        if (path.back ()!= '/') path.push_back ('/');
        while ((dir_obj = readdir(dir)) != nullptr) {
            if (strcmp(".", dir_obj->d_name) == 0 || strcmp("..", dir_obj->d_name) == 0 || dir_obj->d_name[0] == '.') {
                continue;
            }
            temp_path = path;
            temp_path += dir_obj->d_name;
            stat(temp_path.c_str (), &file_info);
            if (!(dir_obj->d_type ^ DT_DIR)) {
                ++c_dir_;
                path += dir_obj->d_name;
                RecursiveSearchFiles(path);
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
            WriteXml(curr_file_info, fout);

            if(state_ == STOP) return;
            if(state_ == PAUSE) while (state_ == PAUSE) QThread::msleep (100); //need to rework...
        }
        closedir(dir);
    }
}
#endif

void Indexer::WriteXml(FileInfo& node, ofstream_t& fout) const {

    if (fout.is_open()) {
        fout << "  <object>\n" <<
                "    <name>" << node.name << "</name>\n" <<
                "    <extension>" << node.extension << "</extension>\n" <<
                "    <size>" << node.size << "</size>\n" <<
                "    <date>" << node.date << "</date>\n" <<
                "    <path>" << node.path << "</path>\n" <<
                "  </object>\n";
    }
}

unsigned Indexer::GetObjectCount() const {
    return count_;
}

unsigned Indexer::GetDirCount() const {
    return c_dir_;
}

void Indexer::SetCount(unsigned c_dir, unsigned c_obj) {
    c_dir_ = c_dir;
    count_ = c_obj;
}
