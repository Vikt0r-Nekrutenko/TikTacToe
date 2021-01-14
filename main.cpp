#include <ctime>
#include <unistd.h>

#include "stf/utils.hpp"
#include "stf/renderer.hpp"

class Game
{
    stf::Renderer rend;
    public:
    
    Game(const uint8_t w, const uint8_t h) 
        : rend(w, h)
    {
        
    }
    
    void update(const float dt)
    {
        
    }
    
    void keyEvents(const int key)
    {
        
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
            rend.drawText(1, 1, "somthing", stf::Color::dred);
            rend.display();
            
            dt = (clock() - begin) / 1000.f;
            elpsdTime += dt;
            cntdFrms++;
        }
        return 0;
    }
};

int main()
{
	Game game(10, 10);
	return game.run();
}
