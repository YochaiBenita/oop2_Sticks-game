#pragma once
#include <SFML/Graphics.hpp>
#include <string>


const int NUM_OF_BUTTONS = 6;
const int NUM_OF_BACKGROUNDS = 3;
const int NUM_OF_MESSAGES = 4; //win, loss, 2 exceptions
const int NUM_OF_DATA_TEXTURES = 2; //for time and score

//const auto TOPLEFT = sf::Vector2f(100.f, 0.f);

//const int DELAY_TIME = 5;


class Resources 
{
public:
	static Resources& getInstance();

	const sf::Texture* getTextureMs(int) const;
	const sf::Texture* getDataTexure(int) const;
	const sf::Texture* getBackground(int) const;
	const sf::Texture* getTextureButtons(int) const;

	const sf::Font* getFont() const;

private:
	Resources();
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

	void readData(sf::Texture[], std::string[], int);
	sf::Texture m_dataTexures[NUM_OF_DATA_TEXTURES];
	sf::Texture m_backgroungs[NUM_OF_BACKGROUNDS];
	sf::Texture m_buttonsTexures[NUM_OF_BACKGROUNDS];
	sf::Texture m_messagesTexures[NUM_OF_MESSAGES];
	sf::Font m_font;

	std::string m_dataTexturesNames[NUM_OF_DATA_TEXTURES] = {
	/*"level.png",
	"clock-60.png",
	"heart.png",
	"star.png",
	"key-60.png"*/
	};

	std::string m_backgroundsNames[NUM_OF_BACKGROUNDS] = {
	/*"backgroundmenu.png",
	"help.png",
	"backgroundtile.png",
	"backgrounddata.png"*/
	};

	std::string m_button[NUM_OF_BUTTONS] = {
	/*"play button.png",
	"help button.png",
	"exit button.png",*/
	};


	std::string m_messages[NUM_OF_MESSAGES] = {
		/*"game over.png",
		"winner.png"*/
	};

	std::string m_fontName = "LoveDays-2v7Oe.ttf";
};