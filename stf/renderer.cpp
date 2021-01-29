#include "renderer.hpp"
#include "utils.hpp"

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
        printf("\033[%d;%dm\033[%d;%dH%c", 
        int(m_pixs.at(i).col > Color::lgrey ? 1 : 0),
        int(m_pixs.at(i).col > Color::lgrey ? Color(int(m_pixs.at(i).col) - 8) : m_pixs.at(i).col),
        i / Width+1, 
        i % Width+1,
        m_pixs.at(i).sym);
    }
}
    
void stf::Renderer::clear(const char sym, const Color col)
{
    for(int y = 0; y < Height; y++)
    {
        for(int x = 0; x < Width; x++)
        {
          if(x==0 || y==0 || x==Width-1 || y==Height-1)
          {
            drawPixel(x, y, '*', Color::dgrey);
          }
          else drawPixel(x, y, sym, col);
        }
    }
}

void stf::Renderer::drawPixel(const uint8_t x, const uint8_t y, const char sym, const Color col)
{
    if(x >= Width || y >= Height) return;
    m_pixs.at(Width * y + x).sym = sym;
    m_pixs.at(Width * y + x).col = col;
}

void stf::Renderer::repaintPixel(const uint8_t x, const uint8_t y, const Color col)
{
  if(x >= Width || y >= Height) return;
  m_pixs.at(Width * y + x).col = col;
}

void stf::Renderer::drawText(const uint8_t x, const uint8_t y, const char *txt, const Color col)
{
    int len = strlen(txt);
    for(int i = 0; i < len; i++)
    {
      drawPixel(x + i, y, txt[i], col);
    }
}

void stf::Renderer::drawNumber(const uint8_t x, const uint8_t y, const int n, const Color col)
{
    char buff[32];
    drawText(x, y, itostr(n, buff), col);
}

void stf::Renderer::drawNumber(const uint8_t x, const uint8_t y, const double n, const Color col)
{
    char buff[32];
    drawText(x, y, ftostr(n, buff), col);
}