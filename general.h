#ifndef GENERAL
#define GENERAL

#include <QApplication>
#include <QtDebug>
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMainWindow>
#include <QToolBar>
#include <QComboBox>
#include <QFileSystemModel>
#include <QTextEdit>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>
#include <QTableWidget>
#include <QTreeView>
#include <QSplitter>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QDesktopServices>

#include <locale>
#include <string>
#include <cstring>
#include <fstream>
#include <iterator>
#if defined(_WIN32)
    #include <Windows.h>
    #include <wchar.h>
#else
    #include <dirent.h>
    #include <sys/stat.h>
#endif


#if defined(_WIN32)
    typedef std::wstring string_t;
    typedef std::wofstream ofstream_t;
    typedef unsigned long f_size_t;

    const int SIZE_WID = 24;
    const string_t INDEX_FILE = L"index.xml";

    const string_t HEADER_TAG = L"<?xml version = \"1.0\"?>";
    const string_t REM_TAG = L"<!-- Filesystem index -->";
    const string_t FS_OPEN_TAG = L"<filesystem>";
    const string_t FS_CLOSE_TAG = L"</filesystem>";

    const string_t OBJECT_OPEN_TAG = L"<object path =\"";
    const string_t OBJECT_CLOSE_TAG_ATTR = L"\">";
    const string_t OBJECT_CLOSE_TAG = L"</object>";
    const size_t OBJECT_OPEN_TAG_SIZE = 15;

    const string_t NAME_OPEN_TAG = L"<name>";
    const string_t NAME_CLOSE_TAG = L"</name>";
    const size_t NAME_OPEN_TAG_SIZE = 6;

    const string_t EXT_OPEN_TAG = L"<extension>";
    const string_t EXT_CLOSE_TAG = L"</extension>";
    const size_t EXT_OPEN_TAG_SIZE = 11;

    const string_t SIZE_OPEN_TAG = L"<size>";
    const string_t SIZE_CLOSE_TAG = L"</size>";
    const size_t SIZE_OPEN_TAG_SIZE = 6;

    const string_t DATE_OPEN_TAG = L"<date>";
    const string_t DATE_CLOSE_TAG = L"</date>";
    const size_t DATE_OPEN_TAG_SIZE = 6;

#else
    typedef std::string string_t;
    typedef std::ofstream ofstream_t;
    typedef long f_size_t;

    const int SIZE_WID = 32;
    const string_t INDEX_FILE = "index.xml";

    const string_t HEADER_TAG = "<?xml version = \"1.0\"?>";
    const string_t REM_TAG = "<!-- Filesystem index -->";
    const string_t FS_OPEN_TAG = "<filesystem>";
    const string_t FS_CLOSE_TAG = "</filesystem>";

    const string_t OBJECT_OPEN_TAG = "<object path =\"";
    const string_t OBJECT_CLOSE_TAG_ATTR = "\">";
    const string_t OBJECT_CLOSE_TAG = "</object>";
    const size_t OBJECT_OPEN_TAG_SIZE = 15;

    const string_t NAME_OPEN_TAG = "<name>";
    const string_t NAME_CLOSE_TAG = "</name>";
    const size_t NAME_OPEN_TAG_SIZE = 6;

    const string_t EXT_OPEN_TAG = "<extension>";
    const string_t EXT_CLOSE_TAG = "</extension>";
    const size_t EXT_OPEN_TAG_SIZE = 11;

    const string_t SIZE_OPEN_TAG = "<size>";
    const string_t SIZE_CLOSE_TAG = "</size>";
    const size_t SIZE_OPEN_TAG_SIZE = 6;

    const string_t DATE_OPEN_TAG = "<date>";
    const string_t DATE_CLOSE_TAG = "</date>";
    const size_t DATE_OPEN_TAG_SIZE = 6;
#endif

#define S_TYPE QStringList() << "Name" << "Extension" << "Size" << "Date"


enum SearchType {
    BY_NAME = 1,
    BY_EXTANSION,
    BY_DATE,
    BY_SIZE
};

enum Condition {
    DEFAULT = 1,
    START,
    STOP,
    PAUSE,
    SEARCH,
    DISABLED
};

struct FileInfo {
    string_t name;
    string_t path;
    string_t extension;
    f_size_t size;
    string_t/*time_t*/ date;
};

#endif

