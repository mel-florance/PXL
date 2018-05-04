#ifndef _TEXTURE_H
#define _TEXTURE_H


class Texture {
  public:
     Texture(const std::string & filename);

     Texture(const std::string & filename, bool generateMipmaps);

    virtual  ~Texture();

    inline void setLoadBias(float & value);

    inline float getLodBias();

    GLuint m_texture;

    Texture load();

    void bind(unsigned int unit);

    void unbind();

    std::string m_filename;

    bool m_generateMipmaps;

    float m_lodBias;

};
inline void Texture::setLoadBias(float & value) {
}

inline float Texture::getLodBias() {
}

#endif
