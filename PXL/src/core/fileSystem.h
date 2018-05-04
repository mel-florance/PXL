#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H


class FileSystem {
  public:
     FileSystem();

    static inline float getFileSize(const std::string & path);

    static inline bool dirExists(const std::string & path);

     ~FileSystem();

};
inline float FileSystem::getFileSize(const std::string & path)
{
}

inline bool FileSystem::dirExists(const std::string & path)
{
}

#endif
