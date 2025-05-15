#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

RenderWindow m_Window;
vector<Particle> m_particles;

//This part done by Anna
Engine::Engine()
{

    unsigned int screenWidth = VideoMode::getDesktopMode().width / 2;
    unsigned int screenHeight = VideoMode::getDesktopMode().height / 2;

    m_Window.create(VideoMode(screenWidth, screenHeight), "P A R T I C L E S"); //fixed

    Font newFont;
    newFont.loadFromFile("./ZillaSlab-Bold.ttf"); //put a new font
    //mine is https://fonts.google.com/specimen/Roboto
}
//End of Anna's contribution to this part

void Engine::run()
{
  Clock clock;
  
  cout << "Starting Particle unit tests..." << endl;
  Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
  p.unitTests();
  cout << "Unit tests complete.  Starting engine..." << endl;

  while(m_Window.isOpen())
    {
      Time time1 = clock.restart();
      float sec = time1.asSeconds();
        
      input();
      update(sec);
      draw();
    }
}

void Engine::input()
{
  Event event;
  
  while(m_Window.pollEvent(event))
  {
      if(event.type == Event::Closed)
      {
          m_Window.close();
      }
  
      if(event.type == Event::MouseButtonPressed)
      {
          if(event.mouseButton.button == Mouse::Left)
          {
              //Sprite
              if(!texture.loadFromFile("Yippee.png"))
              {
                  cout << "Error loading png" << endl;
              }
              yippe.setTexture(texture);
              //m_Window.draw(yippe);
              //sf::SoundBufffer buffer;
              if (!buffer.loadFromFile("click.wav"))
              {
                cout << "Failed to load sound" << endl;
              }
              //Sound yippee;
              yippee.setBuffer(buffer);
              yippee.play();
            
            Vector2i mouse_Pos = Mouse::getPosition(m_Window);
            
              for(int i = 0; i < 5; i++)
              {
                int numPoints = rand() % 26 + 25;
                
                Particle particle(m_Window, numPoints, mouse_Pos);
                
                m_particles.push_back(particle);

                /*sf::SoundBuffer buffer;
                buffer.loadFromFile("./yippee-original-sound-effect-made-with-Voicemod.wav");
                Sound yippee;
                yippee.setBuffer(buffer);
                yippee.play();*/
              }
              yippe.setPosition((Vector2f)mouse_Pos);
          }
      }
      if (Keyboard::isKeyPressed(Keyboard::Escape))
      {
          m_Window.close();
      }
  
  } 
}

void Engine::update(float dtAsSeconds)
{//Fix: m_particles is vector & not int, so cant use 'int i = 0'
    for (size_t i = 0; i < m_particles.size();) //Fix: needs to have semi-colon, even if its not incremented
    {
        if (m_particles[i].getTTL() > 0.0f)
        {
            m_particles[i].update(dtAsSeconds);
            i++;
        }
        else
        {
            m_particles.erase(m_particles.begin() + i);
        }
    }
}

void Engine::draw()
{
  m_Window.clear();
  //using this for loop would keep the vector the same and not change any of the info in the vector
  for(const auto& Particle : m_particles)
    {
      //Will go through each particle in the vector and put it in m_window.draw where it will call the Particle draw function
      m_Window.draw(Particle);
    }
    m_Window.draw(yippe);
  m_Window.display();
}
