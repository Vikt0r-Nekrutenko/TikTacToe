#include <cstdint>
#include <vector>

namespace stf {
    enum class Color : uint8_t
    {
    black = 30,
    dred = 31,
    dgreen = 32,
    dyellow = 33,
    dblue = 34,
    dpurple = 35,
    dcyan = 36,
    lgrey = 37,
    dgrey = 38,
    lred = 39,
    lgreen = 40,
    lyellow = 41,
    lblue = 42,
    lpurple = 43,
    lcyan = 44,
    white = 45
    };
    
class Renderer
{
   public:
   const uint8_t Width;
   const uint8_t Height;
   
   Renderer(const uint8_t w, const uint8_t h);
   void display();
   void clear();
   
   void drawPixel(const uint8_t x, const uint8_t y, const char sym, const Color col);
   void repaintPixel(const uint8_t x, const uint8_t y,  const Color col);
   void drawText(const uint8_t x, const uint8_t y, const char *txt, const Color col);
   void drawNumber(const uint8_t x, const uint8_t y, const int n, const Color col);
   void drawNumber(const uint8_t x, const uint8_t y, const double n, const Color col);
   private:
   struct pixel
   {
       uint8_t sym;
       Color   col;
   };
   
   std::vector<pixel> m_pixs;
};
}