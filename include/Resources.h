#pragma once
#include <SFML/Graphics.hpp>
#include <string>

const int WIDTH = 20;
const int MIN_LEN = 150;
const int BORDER = 20;
const int NUM_OF_COLORS = 3;
const long double PI = 3.14159265358979323846;

const sf::Vector2f SCREEN_SIZE(900, 600);
const sf::Vector2f MESSAGE_SCREEN_SIZE(600, 300);
const sf::Vector2f BOARD_SIZE(600, 600);
const int NUM_OF_DATA = 5;
const int HINT_PRICE = -20;
const int WORNG_STICK_FINE = -5;


const std::pair <sf::Color, int> COLOR_AND_SCORE[NUM_OF_COLORS] = {
	{sf::Color::Red, 20},
	{sf::Color::Color(50,160,70), 10},
	{sf::Color::Blue, 15}
};

const std::string FILE_NAME = "sticks.txt";

const int NUM_OF_BACKGROUNDS = 2;
const std::string BACKGROUNDS_FILE_NAMES[NUM_OF_BACKGROUNDS] = {
	"background.jpg",
	"help.jpg"
};

const int NUM_OF_BUTTONS_MENU = 4;
const std::string BOTTUNS_FILE_NAMES[NUM_OF_BUTTONS_MENU] = {
	"play.png",
	"continue.png",
	"rules.png",
	"exit.png"
};

const int NUM_OF_BUTTONS_BOARD = 2;
const std::string BOTTUNS_BOARD_FILE_NAMES[NUM_OF_BUTTONS_BOARD] = {
"hint.png",
"save.png"
};

const std::string FONT_FILE_NAME = "LoveDays-2v7Oe.ttf";


class Resources 
{
public:
	static Resources& getInstance();

	const sf::Texture* getBackground(int) const;
	const sf::Texture* getTextureButtons(int) const;
	const sf::Texture* getTextureBoardButtons(int) const;

	const sf::Font* getFont() const;

private:
	Resources();
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

	void readData(sf::Texture[], const std::string[], int);
	sf::Texture m_backgroungs[NUM_OF_BACKGROUNDS];
	sf::Texture m_buttonsTexures[NUM_OF_BUTTONS_MENU];
	sf::Texture m_buttonsBoardTexures[NUM_OF_BUTTONS_MENU];
	sf::Font m_font;

};