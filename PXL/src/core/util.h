#ifndef _UTIL_H
#define _UTIL_H


class Utils {
  public:
    static inline float getFileSize(const std::string & filename);

    static inline std::string remove_extension(const std::string & filename);

    static inline void gen_random(char & str, int len);

    static inline float mapValues(float rangeA, float rangeB, float value, unsigned int size = 2);

    static inline char cpToUTF8(int cp, char & str);

};
inline float Utils::getFileSize(const std::string & filename)
{
}

inline std::string Utils::remove_extension(const std::string & filename)
{
}

inline void Utils::gen_random(char & str, int len)
{
}

inline float Utils::mapValues(float rangeA, float rangeB, float value, unsigned int size)
{
}

inline char Utils::cpToUTF8(int cp, char & str)
{
}

#endif
