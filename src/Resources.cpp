#include "Resources.h"

Resources::Resources()
{
	//texures
	//readData(m_texures, m_FileNames, NUM_OF_TEXTURES);
	//readData(m_dataTexures, m_dataTexturesNames, NUM_OF_DATA_TEXTURES);
	readData(m_backgroungs, m_backgroundsNames, NUM_OF_BACKGROUNDS);
	readData(m_buttonsTexures, m_buttonMenu, NUM_OF_BUTTONS_MENU);
	readData(m_buttonsBoardTexures, m_buttonBoard, NUM_OF_BUTTONS_BOARD);

	//readData(m_messagesTexures, m_messages, NUM_OF_MESSAGES);

	/*m_backgroungs[2].setRepeated(true);
	m_backgroungs[3].setRepeated(true);*/

	//sounds
	/*for (int i = 0; i < NUM_OF_SOUNDES; i++)
	{
		m_sound_buffer[i].loadFromFile(m_SoundNames[i]);
	}*/

	//font
	m_font.loadFromFile(m_fontName);

}

Resources& Resources::getInstance()
{
	static Resources instance;
	return instance;
}

//const sf::Texture* Resources::getTextureMs(int index) const
//{
//	return &(m_messagesTexures[index]);
//}
//
//const sf::Texture* Resources::getDataTexure(int index) const
//{
//	return &(m_dataTexures[index]);
//}

const sf::Texture* Resources::getBackground(int index) const
{
	return &(m_backgroungs[index]);
}

const sf::Texture* Resources::getTextureButtons(int index) const
{
	return &(m_buttonsTexures[index]);
}

const sf::Texture* Resources::getTextureBoardButtons(int index) const
{
	return &(m_buttonsBoardTexures[index]);
}

const sf::Font* Resources::getFont() const
{
	return &m_font;
}

void Resources::readData(sf::Texture arr[], std::string names[], int num_of_objects)
{
	for (int i = 0; i < num_of_objects; i++)
		{
			arr[i].loadFromFile(names[i]);
		}
}

