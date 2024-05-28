#pragma once
#include <SFML/Graphics.hpp>
#include <string>

//const int NUM_OF_MESSAGES = 4; //win, loss, 2 exceptions
//const int NUM_OF_DATA_TEXTURES = 2; //for time and score

const sf::Vector2f MESSAGE_SCREEN_SIZE(600, 300);
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




//const auto TOPLEFT = sf::Vector2f(100.f, 0.f);

//const int DELAY_TIME = 5;


class Resources 
{
public:
	static Resources& getInstance();

	//const sf::Texture* getTextureMs(int) const;
	//const sf::Texture* getDataTexure(int) const;
	const sf::Texture* getBackground(int) const;
	const sf::Texture* getTextureButtons(int) const;
	const sf::Texture* getTextureBoardButtons(int) const;

	const sf::Font* getFont() const;

private:
	Resources();
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

	void readData(sf::Texture[], const std::string[], int);
	//sf::Texture m_dataTexures[NUM_OF_DATA_TEXTURES];
	sf::Texture m_backgroungs[NUM_OF_BACKGROUNDS];
	sf::Texture m_buttonsTexures[NUM_OF_BUTTONS_MENU];
	sf::Texture m_buttonsBoardTexures[NUM_OF_BUTTONS_MENU];
	//sf::Texture m_messagesTexures[NUM_OF_MESSAGES];
	sf::Font m_font;

	//std::string m_dataTexturesNames[NUM_OF_DATA_TEXTURES] = {
	///*"level.png",
	//"clock-60.png",
	//"heart.png",
	//"star.png",
	//"key-60.png"*/
	//};

	//std::string m_backgroundsNames[NUM_OF_BACKGROUNDS] = {
	//"background.jpg",
	//"help.jpg"
	//};

	//std::string m_buttonMenu[NUM_OF_BUTTONS_MENU] = {
	//"play.png",
	//"continue.png",
	//"rules.png",
	//"exit.png"
	//};


	//std::string m_buttonBoard[NUM_OF_BUTTONS_BOARD] = {
	//"hint.png",
	//"save.png"
	//};


	////std::string m_messages[NUM_OF_MESSAGES] = {
	////	/*"game over.png",
	////	"winner.png"*/
	////};

	//std::string m_fontName = "LoveDays-2v7Oe.ttf";
};