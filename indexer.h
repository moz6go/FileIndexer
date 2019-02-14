#ifndef SERCHFILES_H
#define SERCHFILES_H

#include "statechecker.h"

class Indexer : public StateChecker {
    Q_OBJECT
    unsigned count_;
    unsigned c_dir_;
    unsigned search_res_count_;
    SearchType type_;
    string_t key_;
    ofstream_t fout_;
    string_t xml_doc_;
    std::vector<string_t> drives_;

    void RecursiveSearchFiles(string_t path);
    void WriteIndexNode(FileInfo& node, ofstream_t& fout) const;
    bool isObjExist(FileInfo& f_info);
#if defined(_WIN32)
    void GetWinDrives();
#endif
public:
    Indexer();
    ~Indexer();
    void WriteIndex();
    void ReadIndex();
    void Search(SearchType type, string_t key);
    void SetCount(unsigned c_dir, unsigned c_obj);
    unsigned GetObjectCount() const;
    unsigned GetDirCount() const;

signals:
    void Message(QString mes);
    void MessageSearchCount(unsigned count);
    void CurrDir(QString path, unsigned count);
    void SendInfoToView(FileInfo f_info);
};

#endif // SERCHFILES_H
