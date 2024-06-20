#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include<iostream>
#include <SFML/Window/VideoMode.hpp>
using namespace sf;

int main() {
  sf::RenderWindow window(sf::VideoMode(640, 480), "Simple Game");
  window.setFramerateLimit(60); // sets setFramerateLimit

  CircleShape hoop;
  int dir = 0;
  hoop.setRadius(50.f);
  hoop.setFillColor(Color::Black);
  hoop.setOutlineThickness(2.f);
  hoop.setOutlineColor(Color::Blue);
  hoop.setPosition(Vector2f(50.f, 0.f));

  CircleShape ball;
  bool isShot = false;
  ball.setRadius(20.f);
  ball.setFillColor(Color::Red);
  ball.setPosition(Vector2f(0, window.getSize().y - ball.getRadius() * 3));
  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape))
      window.close();

    // update hoop
    if (hoop.getPosition().x <= 0) {
      dir = 1;
    } else if (hoop.getPosition().x + (2 * hoop.getRadius()) >=
               window.getSize().x) {
      dir = 0;
    }

    if (dir == 0) {
      hoop.move(-5.f, 0);

    } else {
      hoop.move(5.f, 0);
    }

    // update ball

    if (Mouse::isButtonPressed(Mouse::Left) && !isShot) {
      isShot = true;
    }

    if (!isShot)
      ball.setPosition(Mouse::getPosition(window).x, ball.getPosition().y);
    else
      ball.move(0, -5.f);

    // Collision ball
    if (ball.getPosition().y < 0 ||
        ball.getGlobalBounds().intersects(hoop.getGlobalBounds())) {
      // resets ball
      isShot = false;
      ball.setPosition(Vector2f(0, window.getSize().y - ball.getRadius() * 3));
    }

    // draw
    window.clear(Color::White);

    // draw everything
    window.draw(ball);
    window.draw(hoop);
    window.display();
  }

  return 0;
}
