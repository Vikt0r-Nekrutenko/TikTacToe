#include "view.hpp"

View::View(Model *model) : model(model) {}
  
void View::show(stf::Renderer &rend)
  {
    px = rend.Width / 2 - VW / 2;
    py = rend.Height / 2 - VH / 2;
    
    for(uint8_t y = 0; y < VH; y++)
    {
      for(uint8_t x = 0; x < VW; x++)
      {
        if(x % 4 == 0 || y % 4 == 0)
        {
          rend.drawPixel(px+x, py+y, '#', stf::Color::dred);
        }
        else
        {
          rend.drawPixel(px+x, py+y, ' ', stf::Color::white);
        }
      }
    }
    
    for(uint8_t y = 2; y < 11; y+=4)
    {
      for(uint8_t x = 2; x < 11; x+=4)
      {
        if(model->get(x / 5, y / 5) < 2)
        {
          rend.drawPixel(px+x, py+y, model->get(x / 5, y / 5) ? 'X' : 'O', stf::Color::dyellow);
        }
        else
        {
          rend.drawPixel(px+x, py+y, '_', stf::Color::dyellow);
        }
      }
    }
    
    rend.repaintPixel(px+sx, py+sy, stf::Color::dgreen);
  }
  
void View::keyEvents(const int key)
  {
    switch(key)
    {
      case 'w': if(sy > 2) sy-=4; break;
      case 's': if(sy <10) sy+=4; break;
      case 'a': if(sx > 2) sx-=4; break;
      case 'd': if(sx <10) sx+=4; break;
      case ' ': model->put(sx / 5, sy / 5); break;
    }
  }