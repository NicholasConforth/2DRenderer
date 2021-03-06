#pragma once
#include "Canvas.h"
#include <string>

class Image
{
public:
	Image() {}
	~Image() {}

	friend class Canvas;

	bool LoadImage(const std::string& filename, Uint8 alpha = 255);

private:
	std::vector<pixel_t> m_buffer;

	int m_width{ 0 };
	int m_height{ 0 };
};