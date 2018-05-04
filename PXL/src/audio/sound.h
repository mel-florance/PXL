#ifndef _SOUND_H
#define _SOUND_H


class Sound {
  public:
     Sound(const std::string & name, const std::string & path, Mix_Chunk & data);

    inline void setLoaded(bool state);

    inline bool isloaded();

    inline void setPlaying(bool state);

    inline bool isPlaying();

    inline void setPath(const std::string & path);

    inline std::string getPath();

    inline void setName(const std::string & name);

    inline std::string getName();

    inline void setData(Mix_Chunk & data);

    inline Mix_Chunk getData();

     ~Sound();


  private:
    bool m_loaded;

    bool m_playing;

    std::string m_path;

    std::string m_name;

    Mix_Chunk m_data;

};
inline void Sound::setLoaded(bool state) {
}

inline bool Sound::isloaded() {
}

inline void Sound::setPlaying(bool state) {
}

inline bool Sound::isPlaying() {
}

inline void Sound::setPath(const std::string & path) {
}

inline std::string Sound::getPath() {
}

inline void Sound::setName(const std::string & name) {
}

inline std::string Sound::getName() {
}

inline void Sound::setData(Mix_Chunk & data) {
}

inline Mix_Chunk Sound::getData() {
}

#endif
