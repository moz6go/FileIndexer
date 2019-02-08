#ifndef XMLREADER_H
#define XMLREADER_H

#include "general.h"

class IndexReader: public QObject {
    Q_OBJECT
    string_t xml_doc_;
    string_t GetElement(const string_t& open_tag, const string_t& close_tag, const size_t& open_tag_size, const size_t& pos);
public:
    void ReadIndexToString();
    void SearchInIndex(SearchType key, string_t value);
signals:
    void Message(QString mes);
    void MessageCount(unsigned res_coun);
    void SendInfoToView(FileInfo f_info);
};

#endif // XMLREADER_H
