#include <Shunya.h>



class PlayGround : public Shunya::Application
{
public:
   PlayGround()
   {
   }
   ~PlayGround()
   {
   }
};

Shunya::Application* Shunya::CreateApplication()
{
   return new PlayGround();
}
