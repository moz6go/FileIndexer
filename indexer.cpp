#include "indexer.h"

Indexer::Indexer() : count_(0), c_dir_(1), search_res_count_(0), type_(ALL)  {
#if defined(_WIN32)
    GetWinDrives();
#endif
}

Indexer::~Indexer() {}

#if defined(_WIN32)
void Indexer::GetWinDrives() {
    DWORD dr = GetLogicalDrives();
    for (int x = 0; x <= 'Z'-'A'; x++) {
        int n = ((dr >> x) & 1);
        if (n) {
            string_t curr_drive;
            curr_drive.push_back(static_cast<wchar_t>('A' + x));
            curr_drive += L":\\";
            drives_.push_back(curr_drive);
        }
    }
}
#endif

void Indexer::WriteIndex(){
    type_ = ALL;
    fout_.open(INDEX_FILE);
    if (fout_.is_open()) {
        fout_ << HEADER_TAG << REM_TAG << FS_OPEN_TAG;
    }
#if defined(_WIN32)
    for (auto& drive : drives_){
        RecursiveSearchFiles(drive); //D:\\Chlam
    }
#else
    RecursiveSearchFiles (""); // /home/myroslav/Документи/Repos
#endif
    fout_ << FS_CLOSE_TAG;
    fout_.close ();
}

void Indexer::ReadIndex() {
    ifstream_t fin("index.xml");
    if (fin.is_open()) {
        xml_doc_.clear();
        xml_doc_ = string_t(std::istreambuf_iterator<char_t>(fin), std::istreambuf_iterator<char_t>());
        if(xml_doc_.size()) {
            emit Message(INDEX_SUCCESS);
        }
        else {
            emit Message(INDEX_IS_EMPTY);
        }
        fin.close();
    }
    else {
        emit Message(INDEX_IS_EMPTY);
    }
}

void Indexer::Search(SearchType type, string_t key)  {
    key_ = key;
    type_ = type;
    search_res_count_ = 0;
    string_t open_tag, close_tag;

    size_t open_tag_size = NAME_OPEN_TAG_SIZE;
    FileInfo f_info;

    switch (type) {
    case BY_NAME:
        open_tag = NAME_OPEN_TAG;
        close_tag = NAME_CLOSE_TAG;
        open_tag_size = NAME_OPEN_TAG_SIZE;
        break;
    case BY_EXTENSION:
        open_tag = EXT_OPEN_TAG;
        close_tag = EXT_CLOSE_TAG;
        open_tag_size = EXT_OPEN_TAG_SIZE;
        break;
    case BY_DATE:
        open_tag = DATE_OPEN_TAG;
        close_tag = DATE_CLOSE_TAG;
        open_tag_size = DATE_OPEN_TAG_SIZE;
        break;
    case BY_SIZE:
        open_tag = SIZE_OPEN_TAG;
        close_tag = SIZE_CLOSE_TAG;
        open_tag_size = SIZE_OPEN_TAG_SIZE;
        break;
    case ALL:;
    }

    if(xml_doc_.size()) {
        size_t pos = 0;
        do {
            if ((xml_doc_.find(open_tag, pos) + open_tag_size) > pos) {
                if (xml_doc_.substr(xml_doc_.find(open_tag, pos) + open_tag_size,
                                  xml_doc_.find(close_tag, pos) - (xml_doc_.find(open_tag, pos) + open_tag_size)) == key) {

                    //store FileInfo and send signal to view
                    f_info.path = xml_doc_.substr(xml_doc_.find(OBJECT_OPEN_TAG, pos) + OBJECT_OPEN_TAG_SIZE,
                                                 xml_doc_.find(OBJECT_CLOSE_TAG_ATTR, pos) - (xml_doc_.find(OBJECT_OPEN_TAG, pos) + OBJECT_OPEN_TAG_SIZE));

                    f_info.name = xml_doc_.substr(xml_doc_.find(NAME_OPEN_TAG, pos) +  NAME_OPEN_TAG_SIZE,
                                                 xml_doc_.find(NAME_CLOSE_TAG, pos) - (xml_doc_.find(NAME_OPEN_TAG, pos) + NAME_OPEN_TAG_SIZE));

                    f_info.extension = xml_doc_.substr(xml_doc_.find(EXT_OPEN_TAG, pos) + EXT_OPEN_TAG_SIZE,
                                                 xml_doc_.find(EXT_CLOSE_TAG, pos) - (xml_doc_.find(EXT_OPEN_TAG, pos) + EXT_OPEN_TAG_SIZE));

                    f_info.size = xml_doc_.substr(xml_doc_.find(SIZE_OPEN_TAG, pos) + SIZE_OPEN_TAG_SIZE,
                                                 xml_doc_.find(SIZE_CLOSE_TAG, pos) - (xml_doc_.find(SIZE_OPEN_TAG, pos) + SIZE_OPEN_TAG_SIZE));


                    f_info.date = xml_doc_.substr(xml_doc_.find(DATE_OPEN_TAG, pos) + DATE_OPEN_TAG_SIZE,
                                                 xml_doc_.find(DATE_CLOSE_TAG, pos) - (xml_doc_.find(DATE_OPEN_TAG, pos) + DATE_OPEN_TAG_SIZE));

                    if (isObjExist(f_info)){
                        ++search_res_count_;
                        emit SendInfoToView(f_info);
                    }
                }
                pos = xml_doc_.find(OBJECT_CLOSE_TAG, pos) + 1;
            }
            else {
                pos = xml_doc_.size();
            }
            if(state_ == STOP){
                emit MessageSearchCount(search_res_count_);
                return;
            }
        } while (pos < xml_doc_.size());

    }
    if(!search_res_count_) {
        emit Message(SEARCH_IN_FS);
#if defined(_WIN32)
        for (auto& drive : drives_) {
            RecursiveSearchFiles(drive);
        }
#else
        RecursiveSearchFiles ("");
#endif
    }
    emit MessageSearchCount(search_res_count_);
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
// private methods-------------------------------------------------------------------------------------------
void Indexer::RecursiveSearchFiles(string_t path) {
    char_t str_date[20];
    FileInfo curr_file_info;
#if defined(_WIN32)
    if(!(count_ % 100)){
        emit CurrDir(QString::fromStdWString (path).remove(3,1), count_);
    }

    WIN32_FIND_DATAW file_data;
    SYSTEMTIME sys_time;
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
            FileTimeToSystemTime(&file_data.ftLastWriteTime, &sys_time);
            GetDateFormatW(GetThreadLocale(), DATE_SHORTDATE,  &sys_time, nullptr, str_date, 20) ;

            curr_file_info.name = file_data.cFileName;
            curr_file_info.path = path + curr_file_info.name;
            curr_file_info.date = str_date;
            curr_file_info.extension =  !(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ?
                                            (curr_file_info.name.substr(curr_file_info.name.find_last_of('.') + 1) == curr_file_info.name ?
                                                L"Unknown": curr_file_info.name.substr(curr_file_info.name.find_last_of('.') + 1)):
                                        DIR_EXT;
            curr_file_info.size = std::to_wstring(file_data.nFileSizeLow);
#else
    if(!(count_ % 100)){
        emit CurrDir(QString::fromStdString (path), count_);
    }

    DIR *dir;
    struct dirent *dir_obj;
    struct stat file_info;
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
            strftime(str_date, 20, "%d.%m.%Y", localtime(&file_info.st_mtim.tv_sec));
            curr_file_info.date = str_date;
            curr_file_info.extension =  !(!(dir_obj->d_type ^ DT_DIR) || dir_obj->d_name[0] == '.') ?
                        (curr_file_info.name.substr(curr_file_info.name.find_last_of('.') + 1) == curr_file_info.name ?
                             "Unknown": curr_file_info.name.substr(curr_file_info.name.find_last_of('.') + 1)):
                        "DIR";
            curr_file_info.size = curr_file_info.extension == "DIR" ? "0" : std::to_string(file_info.st_size);
            temp_path.clear ();
#endif
            switch(type_) {
            case ALL:
                WriteIndexNode(curr_file_info, fout_);
                ++count_;
                break;
            case BY_NAME:
                if (key_ == curr_file_info.name){
                    emit SendInfoToView(curr_file_info);
                    ++search_res_count_;
                }
                break;
            case BY_EXTENSION:
                if (key_ == curr_file_info.extension){
                    emit SendInfoToView(curr_file_info);
                    ++search_res_count_;
                }
                break;

            case BY_SIZE:
                if (key_ == curr_file_info.size){
                    emit SendInfoToView(curr_file_info);
                    ++search_res_count_;
                }
                break;
            case BY_DATE:
                if (key_ == curr_file_info.date){
                    emit SendInfoToView(curr_file_info);
                    ++search_res_count_;
                }
                break;
            }

            if(CheckState() == STOP) return;
            CheckPause();

#if defined(_WIN32)
        } while (FindNextFile(file, &file_data) != 0);
        FindClose(file);

#else
        }
        closedir(dir);
#endif
    }
}

void Indexer::WriteIndexNode(FileInfo& node, ofstream_t& fout) const {
    if (fout.is_open()) {
        fout << OBJECT_OPEN_TAG << node.path << OBJECT_CLOSE_TAG_ATTR <<
                NAME_OPEN_TAG << node.name << NAME_CLOSE_TAG <<
                EXT_OPEN_TAG << node.extension << EXT_CLOSE_TAG <<
                SIZE_OPEN_TAG << node.size << SIZE_CLOSE_TAG <<
                DATE_OPEN_TAG << node.date << DATE_CLOSE_TAG <<
                OBJECT_CLOSE_TAG;
    }
}


bool Indexer::isObjExist(FileInfo& f_info) {
    if(f_info.extension != DIR_EXT){
        ifstream_t infile(f_info.path);
        return infile.good();
    }
    else {
#if defined(_WIN32)
        DWORD f_attr = GetFileAttributesW(f_info.path.c_str());
        return (f_attr != INVALID_FILE_ATTRIBUTES && (f_attr & FILE_ATTRIBUTE_DIRECTORY));
#else
        struct stat info;
        return stat(f_info.path.c_str(), &info) != 0 ? false : true;
#endif
    }
}
