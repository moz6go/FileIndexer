#include "indexreader.h"

void IndexReader::ReadIndexToString() {
    std::ifstream fin("index.xml");
    if (fin.is_open()){
        xml_doc_ = string_t(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
        if(xml_doc_.size()) {
            emit Message("Index was read successful");
        }
        else {
            emit Message("Index is empty");
        }
        fin.close();
    }
    else {
        emit Message("Index is empty");
    }
}

void IndexReader::SearchInIndex(SearchType key, string_t value) {
    string_t open_tag, close_tag;
    unsigned res_count(0);
    size_t open_tag_size = NAME_OPEN_TAG_SIZE;
    FileInfo f_info;

    switch (key) {
    case BY_NAME:
        open_tag = NAME_OPEN_TAG;
        close_tag = NAME_CLOSE_TAG;
        open_tag_size = NAME_OPEN_TAG_SIZE;
        break;
    case BY_EXTANSION:
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
    }

    if(xml_doc_.size()) {
        size_t pos = 0;
        do {
            if ((xml_doc_.find(open_tag, pos) + open_tag_size) > pos) {
                //if (GetElement(open_tag, close_tag, open_tag_size, pos) == value) {
                if (xml_doc_.substr(xml_doc_.find(open_tag, pos) + open_tag_size,
                                  xml_doc_.find(close_tag, pos) - (xml_doc_.find(open_tag, pos) + open_tag_size)) == value) {

                    //store FileInfo and send signal to view
                    f_info.path = xml_doc_.substr(xml_doc_.find(OBJECT_OPEN_TAG, pos) + OBJECT_OPEN_TAG_SIZE,
                                                 xml_doc_.find(OBJECT_CLOSE_TAG_ATTR, pos) - (xml_doc_.find(OBJECT_OPEN_TAG, pos) + OBJECT_OPEN_TAG_SIZE));

                    f_info.name = xml_doc_.substr(xml_doc_.find(NAME_OPEN_TAG, pos) +  NAME_OPEN_TAG_SIZE,
                                                 xml_doc_.find(NAME_CLOSE_TAG, pos) - (xml_doc_.find(NAME_OPEN_TAG, pos) + NAME_OPEN_TAG_SIZE));

                    f_info.extension = xml_doc_.substr(xml_doc_.find(EXT_OPEN_TAG, pos) + EXT_OPEN_TAG_SIZE,
                                                 xml_doc_.find(EXT_CLOSE_TAG, pos) - (xml_doc_.find(EXT_OPEN_TAG, pos) + EXT_OPEN_TAG_SIZE));

                    f_info.size = std::stoul(xml_doc_.substr(xml_doc_.find(SIZE_OPEN_TAG, pos) + SIZE_OPEN_TAG_SIZE,
                                                 xml_doc_.find(SIZE_CLOSE_TAG, pos) - (xml_doc_.find(SIZE_OPEN_TAG, pos) + SIZE_OPEN_TAG_SIZE)));


                    f_info.date = xml_doc_.substr(xml_doc_.find(DATE_OPEN_TAG, pos) + DATE_OPEN_TAG_SIZE,
                                                 xml_doc_.find(DATE_CLOSE_TAG, pos) - (xml_doc_.find(DATE_OPEN_TAG, pos) + DATE_OPEN_TAG_SIZE));

                    //Very slow impl....try #define???-------------------------------------------------------------

                    /*f_info.path = GetElement (OBJECT_OPEN_TAG, OBJECT_CLOSE_TAG_ATTR, OBJECT_OPEN_TAG_SIZE, pos);
                    f_info.name = GetElement (NAME_OPEN_TAG, NAME_CLOSE_TAG, NAME_OPEN_TAG_SIZE, pos);
                    f_info.extension = GetElement (EXT_OPEN_TAG, EXT_CLOSE_TAG, EXT_OPEN_TAG_SIZE, pos);
                    f_info.size = std::stol(GetElement (SIZE_OPEN_TAG, SIZE_CLOSE_TAG, SIZE_OPEN_TAG_SIZE, pos));
                    f_info.date = std::stol(GetElement (DATE_OPEN_TAG, SIZE_CLOSE_TAG, DATE_OPEN_TAG_SIZE, pos));*/
                    //----------------------------------------------------------------------------------------
                    ++res_count;
                    emit SendInfoToView(f_info);
                }
                pos = xml_doc_.find(OBJECT_CLOSE_TAG, pos) + 1;
            }
            else {
                pos = xml_doc_.size();
            }
        } while (pos < xml_doc_.size());

    }

    if(!res_count) {
        // search in filesystem
    }
    emit MessageCount(res_count);
}

inline string_t IndexReader::GetElement(const string_t& open_tag, const string_t& close_tag, const size_t& open_tag_size, const size_t& pos){
    return xml_doc_.substr(xml_doc_.find(open_tag, pos) + open_tag_size,
                          xml_doc_.find(close_tag, pos) - (xml_doc_.find(open_tag, pos) + open_tag_size));
}
