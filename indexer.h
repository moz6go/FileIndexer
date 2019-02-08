#ifndef SERCHFILES_H
#define SERCHFILES_H

#include "statechecker.h"

class Indexer : public StateChecker {
    Q_OBJECT
    unsigned count_;
    unsigned c_dir_;
    ofstream_t fout_;
    void WriteIndex(FileInfo& node, ofstream_t& fout) const;
    void RecursiveSearchFiles(string_t path);
public:
    Indexer();
    ~Indexer();
    void Index();
    unsigned GetObjectCount() const;
    unsigned GetDirCount() const;
    void SetCount(unsigned c_dir, unsigned c_obj);
};

#endif // SERCHFILES_H
