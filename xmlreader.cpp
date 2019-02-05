#include "xmlreader.h"

void IndexReader::Parse() {
    string_t tag_name;
    string_t el_val;
    for (unsigned i = 0; i < xml_doc.size(); ++i) {
        if(xml_doc[i] == '<') {
            ++i;
            while(xml_doc[i] != '>')
                tag_name.push_back(xml_doc[i++]);

            if(tag_name == "name"){

            }
            if(tag_name == "extension"){

            }
        }
    }
}

void IndexReader::ReadIndexToString(){
    std::ifstream ifs("index.xml");
    std::string string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    xml_doc = std::move(string);
}

string_t IndexReader::GetStr(){
    return xml_doc;
}
