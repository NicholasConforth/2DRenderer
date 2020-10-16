#include "Image.h"
#include <fstream>
#include <iostream>

bool Image::LoadImage(const std::string& filename, Uint8 alpha)
{
    std::ifstream stream(filename, std::ios::binary);
    if (stream.fail())
    {
        std::cout << "error, File " << filename << " cannot be opened" << std::endl;
        return false;
    }

    Uint8 header[54];
    stream.read((char*)header, 54);

    Uint16 type = *((Uint16*)(&header[0]));
    if (type != 'MB')
    {
        std::cout << "error, File " << filename << " is invalid" << std::endl;
        return false;
    }

    m_width = *((int*)(&header[18]));
    m_height = *((int*)(&header[22]));

    std::cout << "width: " << m_width << std::endl;
    std::cout << "height: " << m_height << std::endl;

    int dataSize = m_width * m_height * 3;

    std::vector<Uint8> imageData(dataSize);
    stream.read((char*)imageData.data(), dataSize);

    for (int i = 0; i < dataSize; i += 3)
    {
        SDL_Color color;
        color.b = imageData[i];
        color.g = imageData[i + 1];
        color.r = imageData[i + 2];
        color.a = alpha;

        m_buffer.push_back(color.r << 24 | color.g << 16 | color.b << 8 | color.a);
    }
    std::reverse(m_buffer.begin(), m_buffer.end());
    stream.close();

    return true;
}
