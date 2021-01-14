#include "renderer.hpp"

stf::Renderer::Renderer(const uint8_t w, const uint8_t h)
    :
    Width(w),
    Height(h)
{
    m_pixs = std::vector<pixel>(w * h);
}

void stf::Renderer::display()
{
    for(int i = 0; i < Width * Height; i++)
    {
        printf("\033[%d;%dH%c\033[%d;%dm", 
        i / Width, 
        i % Width, 
        m_pixs[i].sym,
        int(m_pixs[i].col > Color::lgrey ? 1 : 0),
        int(m_pixs[i].col > Color::lgrey ? Color(int(m_pixs[i].col) - 8) : m_pixs[i].col));
    }
}
    
void stf::Renderer::clear()
{
    for(int y = 0; y < Height; y++)
    {
        for(int x = 0; x < Width; x++)
        {
            m_pixs[Width * y + x].sym = '+';
            m_pixs[Width * y + x].col = Color::dgrey;
        }
    }
}

void stf::Renderer::drawPixel(const uint8_t x, const uint8_t y, const char sym, const Color col)
{
    if(x < 0 || y < 0 || x >= Width || y >= Height) return;
    m_pixs[Width * (y+1) + x+1].sym = sym;
    m_pixs[Width * (y+1) + x].col = col;
}

void stf::Renderer::drawText(const uint8_t x, const uint8_t y, const char *txt, const Color col)
{
    int len = strlen(txt);
    for(int i = 0; i < len; i++)
    {
        m_pixs[Width * (y+1) + (x+i+1)].sym = txt[i];
        m_pixs[Width * (y+1) + (x+i)].col = col;
    }
}