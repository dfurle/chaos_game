#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <unistd.h>
#include <random>
#include <time.h>


#define Vec sf::Vector2f

const int SIZE = 800;

class Point: public sf::CircleShape{
public:
  Point(float x, float y){
    this->setFillColor(sf::Color::Black);
    this->setRadius(0.5f);
    this->setOrigin(Vec(this->getLocalBounds().width/2.f,this->getLocalBounds().height/2.f));
    this->setPosition(Vec(x,y));
  }
  Point(){
    this->setFillColor(sf::Color::Black);
    this->setRadius(0.5f);
    this->setOrigin(Vec(this->getLocalBounds().width/2.f,this->getLocalBounds().height/2.f));
    this->setPosition(Vec(SIZE/2,SIZE/2));
  }
};


int main(int argc, char* argv[]){
  srand(time(NULL));
  if(argc < 2){
    printf("parameters: int sides\n");
    return 1;
  }
  unsigned int sides = std::atoi(argv[1]);
  if(sides < 3 || sides > 6){
    printf("side value too low/high (3-6)\n");
    return 1;
  }


  sf::RenderWindow window(sf::VideoMode(SIZE,SIZE),"Chaos Theory", sf::Style::Titlebar | sf::Style::Close);
  std::vector<Vec> points;
  std::vector<Vec> pointsABC;
  unsigned int prev_vertex[2];
  int SIZE_OFF = SIZE / 2;
  double dAngle = 2 * M_PI / (double)sides;
  double size = 350.; // 350 is a good
  double initAngle = 3 * M_PI_2;
  if (sides == 4)
    double initAngle = M_PI_4;
  else if(sides == 6){

  }
  for(int i = 0; i < sides; i++){
    pointsABC.push_back(Vec(cos(initAngle)*size+SIZE_OFF,sin(initAngle)*size+SIZE_OFF));
    initAngle += dAngle;
  }

  window.clear(sf::Color::White);
  for(auto x : pointsABC){
    Point p(x.x,x.y);
    window.draw(p);
  }

  float init_x = rand() % SIZE;
  float init_y = rand() % SIZE;
  points.push_back(Vec(init_x,init_y));
  Point p(points.back().x,points.back().y);
  window.draw(p);

  while(window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      }
    }
      unsigned int rand_num;
      if(sides == 3){
        rand_num = rand() % sides;
      } else if(sides >= 4){
        do{
          rand_num = rand() % sides;
        } while(rand_num == prev_vertex[0]);
        prev_vertex[0] = rand_num;
      }
      Vec targetPoint = pointsABC[rand_num];
      Vec oldPoint = points.back();
      double dx = targetPoint.x - oldPoint.x;
      double dy = targetPoint.y - oldPoint.y;

      dx = dx * 0.5;
      dy = dy * 0.5;

      points.push_back(Vec(oldPoint.x+dx,oldPoint.y+dy));
      Point p(points.back().x,points.back().y);
      window.draw(p);
    window.display();
    usleep(10);


    // window.clear(sf::Color::White);
    // for(auto x : pointsABC){
    //   Point p(x.x,x.y);
    //   window.draw(p);
    // }
    // for(auto x : points){
    //   Point p(x.x,x.y);
    //   window.draw(p);
    // }

    // window.display();
    // usleep(10);


  }
  return 0;
}