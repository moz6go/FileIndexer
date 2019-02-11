#ifndef SERCHFILES_H
#define SERCHFILES_H

#include "statechecker.h"

class Indexer : public StateChecker {
    Q_OBJECT
    unsigned count_;
    unsigned c_dir_;
    unsigned search_res_count;
    SearchType type_;
    string_t key_;
    ofstream_t fout_;
    string_t xml_doc_;
    std::vector<string_t> drives_;
    string_t GetElement(const string_t& open_tag, const string_t& close_tag, const size_t& open_tag_size, const size_t& pos);
    void RecursiveSearchFiles(string_t path);
public:
    Indexer();
    ~Indexer();
#if defined(_WIN32)
    void GetWinDrives();
#endif
    void WriteIndexNode(FileInfo& node, ofstream_t& fout) const;
    void WriteIndex();
    void ReadIndex();
    void Search(SearchType type, string_t key);
    void SetCount(unsigned c_dir, unsigned c_obj);
    unsigned GetObjectCount() const;
    unsigned GetDirCount() const;

signals:
    void Message(QString mes);
    void MessageCount(unsigned res_coun);
    void SendInfoToView(FileInfo f_info);
};

#endif // SERCHFILES_H
