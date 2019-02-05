#ifndef XMLREADER_H
#define XMLREADER_H

#include <string>
#include <fstream>
#include <iterator>

#include "general.h"

class IndexReader {
    string_t xml_doc;
    string_t tag_name;
    string_t el_val;
public:
    string_t GetStr();
    void ReadIndexToString();
    void Parse();
};

#endif // XMLREADER_H
