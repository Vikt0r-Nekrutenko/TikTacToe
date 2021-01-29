#include <ctime>
#include <unistd.h>
#include <list>

#include "stf/utils.hpp"
#include "stf/renderer.hpp"

class Model
{
  public:
  
  Model()
  {
    for(uint8_t &i : map) i = 2;
  }
  
  void put(const uint8_t x, const uint8_t y)
  {
    if(get(x, y) != 2) return;
    
    map[3 * y + x] = curplr;
    
    for(int j = 0; j < 3; j++)
    {
      if((get(0,j) == curplr &&
         get(1,j) == curplr &&
         get(2,j) == curplr) ||
         (get(j, 0) == curplr &&
         get(j, 1) == curplr &&
         get(j, 2) == curplr) ||
         (get(0, 0) == curplr &&
         get(1, 1) == curplr &&
         get(2, 2) == curplr) ||
         (get(2, 0) == curplr &&
         get(1, 1) == curplr &&
         get(0, 2) == curplr))
      {
        for(uint8_t &i : map) i = 2;
      }
    }
    for(int i = 0; i < 3; i++)
    {
        
    }  
    curplr ^= 1;
  }
  uint8_t get(const uint8_t x, const uint8_t y) const
  {
    return map[3 * y + x];
  }
  private:
  uint8_t map[9];
  uint8_t curplr = 0;
};

class View
{
  private:
  Model *model;
  uint8_t px = 2, py = 2;
  public:
  
  View(Model *model) : model(model) {}
  
  virtual void show(stf::Renderer &rend)
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
  
  void keyEvents(const int key)
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
};

class Game
{
    stf::Renderer rend;
    View view;
    public:
    
    Game(const uint8_t w, const uint8_t h) 
        : rend(w, h),
        view(new Model)
    {
        
    }
    
    void update(const float dt)
    {
      view.show(rend);
    }
    
    void keyEvents(const int key)
    {
      view.keyEvents(key);
    }
    
    int run()
    {
        float dt = 0.f, elpsdTime = 0.f, fps = 0.f;
        uint32_t cntdFrms = 0u;
        
        fputs("\e[?25l", stdout);
        while(true)
        {
            if (elpsdTime > 1.f)
            {
                fps = cntdFrms / elpsdTime;
                elpsdTime = cntdFrms = 0;
            }
            int sym = 0;
            time_t begin = clock();
            stf::set_mode(1);
            if((sym = stf::get_key()))
            {
                if(sym == 'q') 
                {
                    break;
                }
                keyEvents(sym);
            }
            usleep(10000);
            rend.clear();
            rend.drawNumber(0, 0, fps, stf::Color::dred);
            update(dt);
            rend.display();
            
            dt = (clock() - begin) / 1000000.f;
            elpsdTime += dt;
            cntdFrms++;
        }
        return 0;
    }
};

int main()
{
  winsize ws = stf::getws();
	Game game(ws.ws_col, ws.ws_row);
	return game.run();
}
