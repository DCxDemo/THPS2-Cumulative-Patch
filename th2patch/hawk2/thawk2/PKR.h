#pragma once


typedef struct Pkr2Header {
    uint32_t Magic;
    uint32_t unk1;
    uint32_t numFolders;
    uint32_t numFiles;
} Pkr2Header;

typedef struct Pkr2Folder {
    char Name[32];
    uint32_t Offset;
    uint32_t NumFiles;
} Pkr2Folder;

typedef struct Pkr2File {
    char Name[32];
    uint32_t CompressionType;
    char* DataPtr;
    uint32_t Size;
    uint32_t CompressedSize;
} Pkr2File;

enum class PkrError {
    Success,
    FileDoesntExist,
    ZeroFile
};


class Pkr2 {
private:
    void* data;

public:
    Pkr2Header* Header;
    Pkr2Folder* Folders;
    Pkr2File* Files;

    PkrError Load(char* filename);
    void ExportAll(char* path);
    void DebugPrint();
    ~Pkr2();

    //implement some key value conversion here for some fast search. maybe adopt checksum search?
    //need a table of checksum/pointer, then some scanning code. either presort and binary search or research map
    //checksum has to be generated from folder+path, cause thats how you look that up.
    //fall back to search file on the disk is required
};