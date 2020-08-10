#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    // Parameters
    int logs_per_line = 4;
    int lines = 4;
    int log_spacing = 60;
    float base_speed = 1;
    float log_speed;
    float playerXVel = 0;
    float playerYVel = 0;
    bool dead = false;
    bool wKey = false;
    bool aKey = false;
    bool sKey = false;
    bool dKey = false;
    std::vector<std::vector<sf::RectangleShape>> all_lines;

    // Game objects
    sf::RenderWindow window(sf::VideoMode(800, 600), "Frogger");
    window.setFramerateLimit(60);

    sf::RectangleShape river(sf::Vector2f(window.getSize().x, 200));
    river.setPosition(0, 100);
    river.setFillColor(sf::Color::Blue);

    sf::CircleShape frog(20);
    frog.setOrigin(20, 20);
    frog.setPosition(window.getSize().x/2, 40);
    frog.setFillColor(sf::Color::Green);

    // Log size parameter (relies on window and river)
    int log_size[] = {window.getSize().x/logs_per_line-log_spacing, river.getSize().y/lines};
    int total_log_size = log_size[0] + log_spacing;

    // Builds logs
    for (int i = 0;i < lines;i ++) {
        std::vector<sf::RectangleShape> line;
        for (int j = 0;j <= logs_per_line;j ++) {
            sf::RectangleShape log(sf::Vector2f(log_size[0], log_size[1]));
            log.setFillColor(sf::Color(101, 67, 33, 255));
            log.setPosition(0 + total_log_size * j, 100 + log_size[1] * i);
            line.push_back(log);
        }
        all_lines.push_back(line);
    }

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) wKey = true;
                if (event.key.code == sf::Keyboard::A) aKey = true;
                if (event.key.code == sf::Keyboard::S) sKey = true;
                if (event.key.code == sf::Keyboard::D) dKey = true;
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) wKey = false;
                if (event.key.code == sf::Keyboard::A) aKey = false;
                if (event.key.code == sf::Keyboard::S) sKey = false;
                if (event.key.code == sf::Keyboard::D) dKey = false;
            }
        }
        //Game logic
        if (wKey == true) playerYVel = -3;
        if (aKey == true) playerXVel = -3;
        if (sKey == true) playerYVel = 3;
        if (dKey == true) playerXVel = 3;
        frog.move(playerXVel, playerYVel);
        playerXVel = playerYVel = 0;

        for (unsigned long int i = 0;i < all_lines.size();i ++) {
            for (unsigned long int j = 0;j < all_lines[i].size();j ++) {
                if (i == 1 || i == 3) {
                    log_speed = -(base_speed + i);
                    all_lines[i][j].move(log_speed, 0);
                    if (all_lines[i][j].getPosition().x < -log_size[0]) {
                        all_lines[i][j].setPosition(window.getSize().x + log_spacing, all_lines[i][j].getPosition().y);
                    }
                    if (all_lines[i][j].getGlobalBounds().intersects(frog.getGlobalBounds())) {
                        playerXVel += log_speed;
                    }
                }
                else {
                    log_speed = base_speed + i;
                    all_lines[i][j].move(log_speed, 0);
                    if (all_lines[i][j].getPosition().x > 800) {
                        all_lines[i][j].setPosition(-total_log_size, all_lines[i][j].getPosition().y);
                    }
                    if (all_lines[i][j].getGlobalBounds().intersects(frog.getGlobalBounds())) {
                        playerXVel += log_speed;
                    }
                }
            }
        }
        
        // Window updating
        window.clear(sf::Color(28, 79, 66, 200));
        window.draw(river);
        for (unsigned long int i = 0;i < all_lines.size();i ++) {
            for (unsigned long int j = 0;j < all_lines[i].size();j ++) {
                window.draw(all_lines[i][j]);
            }
        }
        window.draw(frog);
        window.display();
    }
}