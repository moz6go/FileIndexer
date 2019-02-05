#include "xmlreader.h"

/*void IndexReader::Parse() {
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

unsigned IndexReader::GetSize(){
    return xml_doc.size ();
}*/

/*bool XmlReader::characters(const QString& strText) {
        m_strText = strText;
        return true;
    }

    bool XmlReader::endElement(const QString&, const QString&, const QString& str) {
        if (str != "object" && str != "filesystem"){
            if (str == "name") f_info.name = m_strText.toStdString(); return true;
            if (str == "extension") f_info.extension = m_strText.toStdString(); return true;
            if (str == "size") f_info.size = m_strText.toLong (); return true;
            if (str == "date") f_info.date = m_strText.toLong (); return true;
            if (str == "path") f_info.path = m_strText.toStdString(); return true;
        }
        return true;
    }

    bool XmlReader::fatalError(const QXmlParseException& exception) {
        qDebug() << "Line:"      << exception.lineNumber()
                 << ", Column:"  << exception.columnNumber()
                 << ", Message:" << exception.message();
        return false;
    }*/

//#include <iostream>
//#include <string>
//#include <fstream>
//#include <vector>
//#include <ctime>

//#if defined(_WIN32)
//    typedef std::wstring string_t;
//    typedef std::wofstream ofstream_t;
//    typedef unsigned long f_size_t;
//#else
//    typedef std::string string_t;
//    typedef std::ofstream ofstream_t;
//    typedef long f_size_t;
//#endif

//using namespace std;

//struct FileInfo {
//    string_t name;
//    string_t path;
//    string_t extension;
//    f_size_t size;
//    time_t date;
//};

//const string_t NAME_OPEN = L"<name>";
//const string_t NAME_CLOSE = L"</name>";

//const size_t NAME_OPEN_SIZE = 6;

//void Parse(string_t& xml_doc) {
//    string_t tag_name;
//    string_t el_val;
//    FileInfo f_info;
//    size_t siz = xml_doc.size();
//    size_t i = 0;
//	size_t count = 0;
//    do {
//		if ((xml_doc.find(NAME_OPEN, i) + NAME_OPEN_SIZE) > i) {
//            if (xml_doc.substr(xml_doc.find(NAME_OPEN, i) + NAME_OPEN.size(), xml_doc.find(NAME_CLOSE, i) - (xml_doc.find(NAME_OPEN, i) + NAME_OPEN_SIZE)) == L"index.xml") {
//				++count;
//			}
//			i = xml_doc.find(NAME_CLOSE, i) + 1;
//		}
//		else {
//			i = siz;
//		}
//	} while (i < siz);
//	cout << count << endl;
//}

//void ReadIndexToString(string_t& xml_doc){
//    std::ifstream ifs("index.xml");
//    if (ifs.is_open()){
//        xml_doc = string_t(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
//    }
//}


//int main() {
//	for (int i = 0; i < 5; ++i) {
//		string_t xml_doc;
//        long s = clock();
//		ReadIndexToString(xml_doc);
//        long f = clock();
//		cout << ((double)f - (double)s) / CLOCKS_PER_SEC << endl;
//		s = clock();
//		Parse(xml_doc);
//		f = clock();
//		cout << ((double)f - (double)s) / CLOCKS_PER_SEC << endl << endl;
//	}
//    return 0;
//}
