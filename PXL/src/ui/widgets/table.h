#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "../core/widget.h"

class Table : public Widget
{
public:
	Table(const glm::vec2& position, const glm::vec2& size, const std::string& font);
	~Table();

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);

	struct Column
	{
		std::string m_data;
		Column(const std::string& data) { m_data = data; }
		void setData(const std::string& data) { m_data = data; }
		const std::string& getData() { return m_data; }
	};

	struct Row 
	{
		std::vector<Column*> m_columns;
	
		Column* addColumn(const std::string& data) {
			Column* column = new Column(data);
			this->m_columns.emplace_back(column);
			return column;
		}

		bool removeColumn(Column* column)
		{
			if (column != nullptr) {
				m_columns.erase(std::remove(m_columns.begin(), m_columns.end(), column), m_columns.end());
				delete column;
				return true;
			}

			return false;
		}
	};

	inline std::vector<Row*> getRows() { return m_rows; }

	inline void* addRow() {
		Row* row = new Row();
		m_rows.emplace_back(row);
		return row;
	}

	inline bool removeRow(Row* row)
	{
		if (row != nullptr) {
			m_rows.erase(std::remove(m_rows.begin(), m_rows.end(), row), m_rows.end());
			delete row;
			return true;
		}

		return false;
	}

private:
	std::vector<Row*> m_rows;

	glm::vec4 m_margin;
	NVGalign m_align;
	std::string m_font;
	float m_fontSize;
	float m_blur;
	NVGcolor m_color;
	NVGcolor m_background;
	NVGcolor m_stripLines;
	NVGcolor m_borderColor;
};
