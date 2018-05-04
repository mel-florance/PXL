#ifndef _TABLE_H
#define _TABLE_H


#include "widget.h"
#include "nanovg.h"

struct CallbackData;
class Scrollbar;

class Table : public Widget {
  public:
     Table(const glm::vec2 & position, const glm::vec2 & size, const std::string & font);

     ~Table();

    void update(double delta);

    void draw(NVGcontext & ctx, double delta);

    static void onScrollbarDragged(const CallbackData & data);

    inline void setOffsetScroll(float value);

    void onMouseWheel(const SDL_Event & event);

    void onMouseMove(const SDL_Event & event);

    void onMouseUp(const SDL_Event & event);

    void onMouseDown(const SDL_Event & event);

    struct Column {
        std::string m_data;

        inline  Column(const std::string & data);

        inline void setData(const std::string & data);

        inline std::string getData();

    };
    
    struct Row {
        Column * m_columns;

        inline Column addColumn(const std::string & data);

        inline bool removeColumn(Column & column);

    };
    
    inline std::vector<Row*> getRows();

    inline void addRow();

    inline bool removeRow(Row & row);

    inline void setMargin(const glm::vec4 & margin);

    inline glm::vec4 getMargin();

    inline void setMarginTop(float value);

    inline float getMarginTop();

    inline void setMarginRight(float value);

    inline float getMarginRight();

    inline void setMarginBottom(float value);

    inline float getMarginBottom();

    inline void setMarginLeft(float value);

    inline float getMarginLeft();


  private:
    Row * m_rows;

    glm::vec4 m_margin;

    NVGalign m_align;

    std::string m_font;

    float m_fontSize;

    float m_blur;

    NVGcolor m_color;

    NVGcolor m_background;

    NVGcolor m_stripLines;

    NVGcolor m_borderColor;

    Scrollbar * m_scrollbar;

    float m_offsetScroll;

};
inline void Table::setOffsetScroll(float value) {
}

inline  Table::Column::Column(const std::string & data) {
}

inline void Table::Column::setData(const std::string & data) {
}

inline std::string Table::Column::getData() {
}

inline Table::Column Table::Row::addColumn(const std::string & data) {
}

inline bool Table::Row::removeColumn(Table::Column & column) {
}

inline std::vector<Row*> Table::getRows() {
}

inline void Table::addRow() {
}

inline bool Table::removeRow(Table::Row & row) {
}

inline void Table::setMargin(const glm::vec4 & margin) {
}

inline glm::vec4 Table::getMargin() {
}

inline void Table::setMarginTop(float value) {
}

inline float Table::getMarginTop() {
}

inline void Table::setMarginRight(float value) {
}

inline float Table::getMarginRight() {
}

inline void Table::setMarginBottom(float value) {
}

inline float Table::getMarginBottom() {
}

inline void Table::setMarginLeft(float value) {
}

inline float Table::getMarginLeft() {
}

#endif
