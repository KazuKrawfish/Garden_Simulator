//Copyright 2024, Supercontinent Software Ltd.
//
//	main.cpp
//
//Garden_Simulator.
//Built with SFML library.


#include <iostream>
#include <string_view>
#include <ctype.h>
#include <fstream>
#include <thread>
#include <vector>


//Everyone needs access to this at all times so it seems reasonable
const int rectArrayWidth = 20;
const int rectArrayHeight = 10;
std::vector <std::vector<sf::IntRect>> rectArray;


int initializeTextureArray(std::string directory, const std::vector <std::string>& imageNameList, std::vector <sf::Texture>& buttonTextureArray)
{
	//Need longer list of actual buttons

	for (int i = 0; i < buttonTextureArray.size(); i++)
	{
		if (!buttonTextureArray[i].loadFromFile(directory + "/" + imageNameList[i] + ".png"))
		{
			std::cout << "Couldn't load button: " << imageNameList[i] << std::endl;

		}
	}
	return 0;
}

int main()
{
	sf::Color colorWhite;
	//Determine size of desktop for window
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

	//Load topMenuButton textures
	//NOTE: There is one less texture than total top menu buttons, because top_Back is used twice. So every button after back #2 uses 
	//the index of that button's particular image + 1.
	std::vector <std::string> imageList = { "top_New_Game", "top_Load_Game", "top_Editor_Mode_Off",  "top_Editor_Mode_On",  "top_New_Campaign",
											"top_New_Sandbox", "top_Back" , "top_Quit", "upButton", "downButton", "Select" };
	std::vector <sf::Texture> topMenuButtonTextureArray;
	topMenuButtonTextureArray.resize(imageList.size());
	initializeTextureArray("topMenuButtons", imageList, topMenuButtonTextureArray);

	//Load gameMenuButton textures
	std::vector <std::string> gameMenuButtonImageList = { "exit_To_Main_Menu", "save_Game", "load_Game" , "restart", "sound_On", "sound_Off",  "end_Turn", };
	std::vector <sf::Texture> gameMenuButtonTextureArray;
	gameMenuButtonTextureArray.resize(gameMenuButtonImageList.size());
	initializeTextureArray("menuButtons", gameMenuButtonImageList, gameMenuButtonTextureArray);

	//Load other textures
	std::vector <std::string> otherImagesList = { "startScreenBackground", "topMenuBackground", "startScreenStatement", "topMenuBox", "Sidebar", "loadGameBackground",
													"newGameBackground","saveGameBackground",  "missionBriefingBackground", "victoryDefeatBackground",
													"dialogBox" , "gameplayBackground", "inGameMenu" , "remoteGameBackground" };
	std::vector <sf::Texture> otherTextureArray;
	otherTextureArray.resize(otherImagesList.size());
	initializeTextureArray("otherImages", otherImagesList, otherTextureArray);

	sf::Texture mainTexture;
	sf::Texture secondMainTexture;
	sf::Image terrain_images;

	std::vector <std::string> plant_image_names = { "corn_images.png" , "grass_images.png" };
	std::vector <sf::Image> plant_images;
	plant_images.resize(plant_image_names.size());


	//Initialize intRect grid
	const int tile_size = 70;
	rectArray.resize(rectArrayWidth + 1);
	for (int i = 0; i < rectArrayWidth; i++)
	{
		rectArray[i].resize(rectArrayHeight );
		for (int j = 0; j < rectArrayHeight; j++)
		{
			rectArray[i][j].left = i * (tile_size+ 2) + 1;
			rectArray[i][j].top = j * (tile_size + 2) + 1;
			rectArray[i][j].height = tile_size;
			rectArray[i][j].width = tile_size;
		}
	}

	sf::Font gameFont;
	sf::Font boldGameFont;

	//Load up image and use to initiate texture
	if (!terrain_images.loadFromFile("terrain_images.png"))
	{
		std::cout << "Couldn't load image!" << std::endl;
	}
	//Transfer Images to Textures
	terrain_images.createMaskFromColor(colorWhite.White);
	terrain_texture.loadFromImage(terrain_images);

	for (int i = 0; i < plant_images.size(); i++)
	{
		if (!plant_images.at(i).loadFromFile(plant_image_names.at(i)))
		{
			std::cout << "Couldn't load image: "<< plant_image_names.at(i) << std::endl;
		}
		else 
		{
			plant_images.at(i).createMaskFromColor(colorWhite.White);
			plant_textures.at(i).loadFromImage(plant_images.at(i));
		}
	}

	if (!gameFont.loadFromFile("Orbitron-Medium.ttf"))
	{
		std::cout << "Couldn't load fonts!" << std::endl;
	}

	if (!boldGameFont.loadFromFile("Orbitron-Black.ttf"))
	{
		std::cout << "Couldn't load fonts!" << std::endl;
	}


	sf::RenderWindow mainWindow(desktopMode, "Line of Command");	//, sf::Style::Fullscreen); For debug ease

	mainMenu MainMenu(&mainWindow, &mainTexture, &gameFont, &boldGameFont, &topMenuButtonTextureArray, &gameMenuButtonTextureArray, &otherTextureArray, &(gameMusicArray[0]), &factionTexturesArray, battleLabConfigFileName, mapListName);

	inputLayer InputLayer(&MainMenu, &mainWindow, &mainTexture, &secondMainTexture, &gameFont, &boldGameFont, &soundEffects, &MainMenu.gameMenuButtons, &statusTexturesArray, &(gameMusicArray[0]));
	MasterBoard GameBoard(&mainTexture, &secondMainTexture);

	MainMenu.introScreen(&GameBoard, &InputLayer);

	std::cout << "Complete" << std::endl;
	return 0;
}


