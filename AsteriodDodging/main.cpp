#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <ctime>
#include <sstream>

int main() {
    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dodge the Asteroids!");
    window.setFramerateLimit(60);
    
    // Load font for score and game over text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // If font fails to load, use default
        font = sf::Font();
    }
    
    // Player setup
    sf::RectangleShape player(sf::Vector2f(50, 30));
    player.setFillColor(sf::Color::Green);
    player.setPosition(400, 550);
    float playerSpeed = 5.0f;
    
    // Asteroid setup
    std::vector<sf::CircleShape> asteroids;
    float asteroidSpeed = 3.0f;
    float spawnTimer = 0;
    float spawnInterval = 1.0f;
    
    // Score setup
    int score = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    
    // Game over setup
    bool gameOver = false;
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over!\nPress R to Restart");
    gameOverText.setPosition(200, 250);
    
    // Clock for delta time
    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && gameOver) {
                if (event.key.code == sf::Keyboard::R) {
                    // Reset game
                    asteroids.clear();
                    player.setPosition(400, 550);
                    score = 0;
                    gameOver = false;
                    asteroidSpeed = 3.0f;
                    spawnInterval = 1.0f;
                }
            }
        }
        
        if (!gameOver) {
            float deltaTime = clock.restart().asSeconds();
            
            // Player movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x > 0)
                player.move(-playerSpeed, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x < 750)
                player.move(playerSpeed, 0);
            
            // Spawn asteroids
            spawnTimer += deltaTime;
            if (spawnTimer >= spawnInterval) {
                sf::CircleShape asteroid(20);
                asteroid.setFillColor(sf::Color::Red);
                float x = static_cast<float>(std::rand() % 760);
                asteroid.setPosition(x, -20);
                asteroids.push_back(asteroid);
                spawnTimer = 0;
                
                // Increase difficulty
                asteroidSpeed += 0.05f;
                if (spawnInterval > 0.3f) spawnInterval -= 0.01f;
            }
            
            // Update asteroids
            for (auto& asteroid : asteroids) {
                asteroid.move(0, asteroidSpeed);
            }
            
            // Remove off-screen asteroids
            asteroids.erase(
                std::remove_if(asteroids.begin(), asteroids.end(),
                    [](const sf::CircleShape& a) { return a.getPosition().y > 600; }),
                asteroids.end()
            );
            
            // Collision detection
            for (const auto& asteroid : asteroids) {
                if (player.getGlobalBounds().intersects(asteroid.getGlobalBounds())) {
                    gameOver = true;
                    break;
                }
            }
            
            // Update score
            score += static_cast<int>(deltaTime * 10);
            std::stringstream ss;
            ss << "Score: " << score;
            scoreText.setString(ss.str());
        }
        
        // Render
        window.clear(sf::Color::Black);
        if (!gameOver) {
            window.draw(player);
            for (const auto& asteroid : asteroids)
                window.draw(asteroid);
            window.draw(scoreText);
        } else {
            window.draw(gameOverText);
            window.draw(scoreText);
        }
        window.display();
    }
    
    return 0;
}