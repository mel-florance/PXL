#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H


class Sound;

class SoundManager {
  public:
     SoundManager();

    void play();

    Sound loadSound(const std::string & name, const std::string & path);

    void playSound(const std::string & name, int channel = -1, int loop = 0);

     ~SoundManager();


  private:
    Sound * m_sounds;

};
#endif
