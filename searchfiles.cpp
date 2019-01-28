#include "searchfiles.h"

void SearchFiles::GetFilesListMapWrite(std::ofstream& fout, char* path){
    DIR *dir;
    struct dirent *dir_obj;
    struct stat file_info;
    FileInfo curr_file_info;
    char temp_path[PATH_MAX];
    strcat(path, "/");
    if ((dir = opendir (path)) != NULL) {
        if (path[strlen(path)-1] != '/') strcat(path, "/");
        while ((dir_obj = readdir (dir)) != NULL) {
            if(strcmp( ".", dir_obj->d_name ) == 0 || strcmp( "..", dir_obj->d_name ) == 0 || dir_obj->d_name[0] == '.') {
                continue;
            }
            strcpy(temp_path, path);
            strcat(temp_path, dir_obj->d_name);
            //stat(temp_path, &file_info);
            if (!(dir_obj->d_type ^ DT_DIR)) {    // or S_ISDIR( file_info.st_mode )
                ++c_dir_;
                strcat(path, dir_obj->d_name);
                GetFilesListMapWrite (fout, path);
                path[strlen(path) - strlen(dir_obj->d_name) - 1] = '\0';;
            }
            //init fileinfo
            strcpy(curr_file_info.name, dir_obj->d_name);
            strcat(strcpy(curr_file_info.path, path),curr_file_info.name);
            curr_file_info.date = file_info.st_mtim.tv_sec;
            SetFileType(dir_obj, curr_file_info);
            curr_file_info.size = !strcmp(curr_file_info.extension, "DIR") ? 0 : file_info.st_size;

            temp_path[0] = '\0';
            ++count_;
            WriteNodeMap(fout, curr_file_info);
        }
        closedir (dir);
    }
}

void SearchFiles::SetFileType(dirent* dir_obj, FileInfo& curr_file_info)
{

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
        curr_file_info.extension[j] = '\0';

        if (strlen(curr_file_info.extension)) {
            i = strlen(curr_file_info.extension) - 1;
            j = 0;
            while(i > j){
                char tmp = curr_file_info.extension[i];
                curr_file_info.extension[i] = curr_file_info.extension[j];
                curr_file_info.extension[j] = tmp;
                --i;
                ++j;
            }
        }
        curr_file_info.is_dir = false;
    }
}

SearchFiles::SearchFiles(char* path): type_(BY_NAME), count_(0), c_dir_(1) {
    strcpy(path_, path);
}

SearchFiles::~SearchFiles()
{
}

void SearchFiles::WriteNodeMap(std::ofstream& fout, FileInfo& node) const {
    if(fout.is_open ()){
        char str_date[20];
        strftime(str_date, 20, "%Y-%m-%d %H:%M:%S", localtime(&node.date));

        fout << "Object Name: \t" << node.name <<
                "\nObject Path: \t" << node.path <<
                "\nObject Date: \t" << str_date <<
                "\nObject Extension: \t" << node.extension <<
                "\nObject Size: \t" << node.size << "\n\n";
    }
}

unsigned SearchFiles::GetObjectCount() const {
    return count_;
}

unsigned SearchFiles::GetDirCount() const{
    return c_dir_;
}

