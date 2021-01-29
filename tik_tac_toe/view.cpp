#include "view.hpp"

View::View(Model *model) : model(model) {}
  
void View::show(stf::Renderer &rend)
  {
    for(uint8_t y = 0; y < 13; y++)
    {
      for(uint8_t x = 0; x < 13; x++)
      {
        if(x % 4 == 0 || y % 4 == 0)
        {
          rend.drawPixel(x, y, '#', stf::Color::dred);
        }
        else
        {
          rend.drawPixel(x, y, ' ', stf::Color::white);
        }
      }
    }
    
    for(uint8_t y = 2; y < 11; y+=4)
    {
      for(uint8_t x = 2; x < 11; x+=4)
      {
        if(model->get(x / 5, y / 5) < 2)
        {
          rend.drawPixel(x, y, model->get(x / 5, y / 5) ? 'X' : 'O', stf::Color::dyellow);
        }
        else
        {
          rend.drawPixel(x, y, '_', stf::Color::dyellow);
        }
      }
    }
    
    rend.repaintPixel(px, py, stf::Color::dgreen);
  }
  
void View::keyEvents(const int key)
  {
    switch(key)
    {
      case 'w': if(py > 2) py-=4; break;
      case 's': if(py <10) py+=4; break;
      case 'a': if(px > 2) px-=4; break;
      case 'd': if(px <10) px+=4; break;
      case ' ': model->put(px / 5, py / 5); break;
    }
  }