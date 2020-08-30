#include "pch.h"
#include "MainMenu.h"


//CONSTRUCTORS & DESTRUCTORS
MainMenu::MainMenu(){}
MainMenu::~MainMenu(){}


//UTILTY

//load characters as passed by game manager
void MainMenu::setCharacters(std::vector<Character> characters) { this->characters = characters; }

///loads all the textures and sets up initial positions of objects
void MainMenu::prepare()
{
	stateChanges= sf::Vector2u(0,9);
	characterChoicePlayer2 = 9;
	//load the shaders from file
	shader.loadFromFile(Universals::PathManager::getDefaultPath().append("motionBlur.frag"), sf::Shader::Fragment);
	
	//set up all the menu items
	std::vector<std::string> mainMenuItems{ "NORMAL","ARENA","SETTINGS","EXIT" };
	mainMenu = Menu(mainMenuItems, sf::Vector2f(Universals::WindowManager::getScreenWidth()*0.8, (Universals::WindowManager::getScreenHeight()*0.45)), Universals::WindowManager::getScreenHeight()*0.1, 30);

	//set up the reflector
	light = Object(Universals::TextureManager::getTexture("reflector"),sf::Vector2u(12,1),0.1, sf::Vector2f(0,0),false);
	light.setAnimate(false);
	light.getShape().setColor(sf::Color(255, 255, 255, 200));
	light.setFrame(0);

	//character views
	front.c = characters[characterChoice];
	front.opacity = 1;
	front.scale = 1;
	front.position = frontPosition;
	front.base.setTexture(*Universals::TextureManager::getTexture("basePOne"));
	front.base.setOrigin(Universals::TextureManager::getTexture("base")->getSize().x / 2, Universals::TextureManager::getTexture("base")->getSize().y / 2);
	front.c.setOrgin(sf::Vector2f(Universals::TextureManager::getTexture("character")->getSize().x/2, Universals::TextureManager::getTexture("character")->getSize().y/2));
	front.health = Object(Universals::TextureManager::getTexture("health"), sf::Vector2u(10, 1), 1, sf::Vector2f(0, 0), false);
	front.health.setFrame((front.c.getMaxHealth() * 2) - 1);
	front.health.setOrgin(sf::Vector2f((Universals::TextureManager::getTexture("health")->getSize().x / 10) / 2, Universals::TextureManager::getTexture("health")->getSize().y));
	front.health.setPosition(sf::Vector2f(front.position.x, front.position.y - Universals::TextureManager::getTexture("character")->getSize().y - 10));
	front.health.setAnimate(false);
	front.characterName.setFont(*Universals::FontManager::getFont("retro"));
	front.characterName.setString(characters[characterChoice].getName());
	front.characterName.setOrigin(sf::Vector2f(((front.characterName.getCharacterSize()*front.characterName.getString().getSize()) / 2), front.characterName.getCharacterSize() / 2));
	front.characterName.setPosition(sf::Vector2f(front.position.x, 0));
	front.apply();

	back.c = characters[(characterChoice + 1) % characters.size()];
	back.opacity = 0.05;
	back.scale = 0.5;
	back.position = sf::Vector2f(frontPosition.x + 500, frontPosition.y - 200);
	back.base.setTexture(*Universals::TextureManager::getTexture("base"));
	back.base.setOrigin(Universals::TextureManager::getTexture("base")->getSize().x / 2, Universals::TextureManager::getTexture("base")->getSize().y / 2);
	back.c.setOrgin(sf::Vector2f(Universals::TextureManager::getTexture("character")->getSize().x / 2, Universals::TextureManager::getTexture("character")->getSize().y / 2));
	back.characterName.setFont(*Universals::FontManager::getFont("retro"));
	back.characterName.setString(characters[(characterChoice + 1) % characters.size()].getName());
	back.characterName.setOrigin(sf::Vector2f(((back.characterName.getCharacterSize()*back.characterName.getString().getSize()) / 2), back.characterName.getCharacterSize() / 2));
	back.characterName.setPosition(sf::Vector2f(back.position.x, back.position.y - Universals::TextureManager::getTexture("character")->getSize().y - 50));
	back.health = Object(Universals::TextureManager::getTexture("health"), sf::Vector2u(10, 1), 1, sf::Vector2f(back.characterName.getPosition().x, back.characterName.getPosition().y - 20), false);
	back.health.setOrgin(sf::Vector2f((Universals::TextureManager::getTexture("health")->getSize().x / back.health.animation.getFrameCount().x) / 2, Universals::TextureManager::getTexture("health")->getSize().y / 2));
	back.health.setPosition(sf::Vector2f(back.characterName.getPosition().x, back.characterName.getPosition().y - 20));
	back.health.setAnimate(false);
	back.health.animation.setFrame(back.c.getMaxHealth()*2);
	back.apply();

	helper.c = characters[(characterChoice + 2) % characters.size()];
	helper.opacity = -0.90;
	helper.scale = 0.0;
	helper.position = sf::Vector2f(frontPosition.x + 1000, frontPosition.y - 400);
	helper.base.setTexture(*Universals::TextureManager::getTexture("base"));
	helper.base.setOrigin(Universals::TextureManager::getTexture("base")->getSize().x / 2, Universals::TextureManager::getTexture("base")->getSize().y / 2);
	helper.c.setOrgin(sf::Vector2f(Universals::TextureManager::getTexture("character")->getSize().x / 2, Universals::TextureManager::getTexture("character")->getSize().y / 2));
	helper.characterName.setFont(*Universals::FontManager::getFont("retro"));
	helper.characterName.setString(characters[(characterChoice + 2) % characters.size()].getName());
	helper.characterName.setOrigin(sf::Vector2f(((back.characterName.getCharacterSize()*back.characterName.getString().getSize() )/ 2), back.characterName.getCharacterSize() / 2));
	helper.characterName.setPosition(sf::Vector2f(helper.position.x, helper.position.y - Universals::TextureManager::getTexture("character")->getSize().y - 50));
	helper.health = Object(Universals::TextureManager::getTexture("health"), sf::Vector2u(10, 1), 1, sf::Vector2f(0,0), false);
	helper.health.setOrgin(sf::Vector2f((Universals::TextureManager::getTexture("health")->getSize().x / helper.health.animation.getFrameCount().x) / 2, Universals::TextureManager::getTexture("health")->getSize().y / 2));
	helper.health.setPosition(sf::Vector2f(helper.characterName.getPosition().x, helper.characterName.getPosition().y - 20));
	helper.health.setAnimate(false);
	helper.health.animation.setFrame(helper.c.getMaxHealth()*2);
	helper.apply();

	//calculate and set the distance beetween two character views
	sf::Vector2f distance{ abs(frontPosition.x - back.position.x),abs(frontPosition.y - back.position.y) };
	characterView::setDistance(distance);


	this->reversePosition = sf::Vector2f(frontPosition.x - 500, frontPosition.y + 200);


	//set up the settingsmenu items
	std::vector<std::string> settingsMenuItems{ "CoopMode: OFF","other"};
	settingsMenu = Menu(settingsMenuItems, sf::Vector2f(mainMenu.getPosition().x + 100, mainMenu.getPosition().y), Universals::WindowManager::getScreenHeight()*0.05, 25);
	settingsMenu.setToogleOnoff(false);
}
///handles input control
void MainMenu::handleInput(sf::RenderWindow& window)
{
	//buffer controls how fast the player can move around the menu (so to avoid multiple actions at once)
		//if an action is performed, the buffer is set eg.10 and then decreases with each frame until it is again equal to zero (then actions can be performed again)
	if (!buffer == 0)buffer--;;
	//controls for when settingsView is on
	if (settingsOn) {
		settingsMenu.handleInput();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { if (buffer <= 0) { buffer = 10; hideSettings(); settingsOn = false; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) 
		{ 
			setting = settingsMenu.getCurrentlySelectedItem();
			//change CoopMode
			if (setting == 0 && buffer <= 0) 
			{ 
				buffer = 10; coOpOn = !coOpOn;
				if (coOpOn)
				{ 
					settingsMenu.changeMenuItem(0, "CoopMode: ON");
					characterChoicePlayer2 = (characterChoicePlayer1 + 1) % characters.size(); 
					if(characterChoicePlayer2 == (characterChoice + 1) % characters.size()) { back.base.setTexture(*Universals::TextureManager::getTexture("basePTwo")); }
				} 
				else 
				{ 
					settingsMenu.changeMenuItem(0, "CoopMode: OFF");
					if (characterChoicePlayer2 == (characterChoice + 1) % characters.size()) { back.base.setTexture(*Universals::TextureManager::getTexture("base")); }
					if (characterChoicePlayer2 == characterChoice) { front.base.setTexture(*Universals::TextureManager::getTexture("base")); }
					characterChoicePlayer2 =  9; 
				}
			}
		}
	}
	//when normal menu is on
	else {
		mainMenu.handleInput();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) { light.setAnimate(true); }
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !changeCharacter) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !changeCharacter)) { if (buffer <= 0) { helperPrep(false); characterView::setReverse(false); incrementCharacter(); } }
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !changeCharacter) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !changeCharacter)) { if (buffer <= 0) { helperPrep(true); characterView::setReverse(true); decreaseCharacter(); } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) { updateCharacterChoicePlayerOne(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) && coOpOn) { updateCharacterChoicePlayerTwo(); }

		//when an item is selected on the menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			int modeChoice = mainMenu.getCurrentlySelectedItem();
			if ((modeChoice == 0 || modeChoice == 1) && buffer == 0) { buffer = 100; this->stateChanges = sf::Vector2u(modeChoice + 1, characterChoicePlayer1 * 10 + characterChoicePlayer2); }
			if (modeChoice == 2 && buffer == 0) { buffer = 10; showSettings(); settingsOn = true; }
			if (modeChoice == 3 && buffer == 0) { window.close(); }
		}
		if (changeCharacter) { updateCharacters(); }
	}
		
}

void MainMenu::resetState()
{
	mainMenu.setBuffer(20);
	buffer = 20;
	stateChanges= sf::Vector2u(0,9);
}

void MainMenu::updateCharacterChoicePlayerOne() {
	if (characterChoice != characterChoicePlayer2)
	{ 
	characterChoicePlayer1 = characterChoice; 
	front.base.setTexture(*Universals::TextureManager::getTexture("basePOne")); 
	if (characterChoicePlayer2!=(characterChoicePlayer1+1)%characters.size()){ back.base.setTexture(*Universals::TextureManager::getTexture("base")); }
	}
}
void MainMenu::updateCharacterChoicePlayerTwo()
{
	if (characterChoice != characterChoicePlayer1)
	{
		characterChoicePlayer2 = characterChoice;
		front.base.setTexture(*Universals::TextureManager::getTexture("basePTwo"));
		if (characterChoicePlayer1 != (characterChoicePlayer2 + 1) % characters.size()) { back.base.setTexture(*Universals::TextureManager::getTexture("base")); }
	}
	
}
///draws all the objects
void MainMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mainMenu);
	//if(blink>30) target.draw(pressXtoSelect);

	if (settingsOn)	{target.draw(settingsMenu);}

	if (front.position.y > 0) target.draw(front, &shader);
	if (back.position.y > 0) target.draw(back, &shader);
	if (helper.position.y > 0)target.draw(helper, &shader);


	target.draw(light);
}
sf::Vector2u MainMenu::update(float deltaTime){
	light.update(deltaTime);

	if (stateChanges.x == 0) { return stateChanges; }
	else { sf::Vector2u temp = stateChanges; resetState(); return temp; }
}




//CHARACTER SELECTION
///used to select next character
void MainMenu::incrementCharacter() 
{
	characterChoice++; characterChoice=characterChoice%characters.size();
	changeCharacter = true;
}
///used to select previous character
void MainMenu::decreaseCharacter()
{
	characterChoice--; if(characterChoice==-1)characterChoice = characters.size()-1;
	changeCharacter = true;
}

///updates the views on which the characters are shown
void MainMenu::updateCharacters()
{
	if (!characterView::getReverse())
	{
		if ((int)back.position.x == (int)frontPosition.x)
		{
			changeCharacter = false;
			shader.setUniform("blur_radius", 0.f);
			//set helper as back and back as front
			front = back;
			back = helper;

			helper.opacity = 0; //set helpers opacity at zero so that it doesnt overlay with the back

			helper.apply();
			front.apply();
			back.apply();
			return;
		}

		front.update(true);
		back.update(false);
		helper.update(false);
	}
	else 
	{
		if ((int)helper.position.x == (int)frontPosition.x)
		{
			changeCharacter = false;
			//set helper as back and back as front
			shader.setUniform("blur_radius", 0.f);
			characterView tempp = front;
			front = helper;
			back = tempp;

			//set helpers opacity at zero so that it cant be seen poking out the screen
			helper.opacity = 0;
			
			helper.apply();
			front.apply();
			back.apply();
			return;
		}

		front.update(false);
		back.update(false);
		helper.update(true);


	}
}

void MainMenu::helperPrep(bool b) {
	int temp = 0;
	//if it is to animate backward
	if (b)
	{
		helper.opacity = 0.05;
		temp = characterChoice - 1; if (temp < 0) { temp = characters.size() - 1; }
		helper.c = characters[temp];
		helper.c.setOrgin(sf::Vector2f(Universals::TextureManager::getTexture("character")->getSize().x / 2, Universals::TextureManager::getTexture("character")->getSize().y / 2));
		helper.scale = 1.5;
		helper.position = reversePosition;
		helper.characterName.setString(characters[(characterChoice + 2) % characters.size()].getName());
		helper.characterName.setOrigin(sf::Vector2f((back.characterName.getCharacterSize()*back.characterName.getString().getSize() / 2), back.characterName.getCharacterSize() / 2));
		helper.characterName.setPosition(sf::Vector2f(helper.position.x, helper.position.y - Universals::TextureManager::getTexture("character")->getSize().y - 50));
	}
	//if it is to animate forward
	if (!b)
	{
		helper.opacity = -0.90;
		temp = (characterChoice + 2) % characters.size();
		helper.c = characters[temp];
		if ((characterChoice + 2) % characters.size() == characterChoicePlayer1) { helper.base.setTexture(*Universals::TextureManager::getTexture("basePOne")); }
		if ((characterChoice + 2) % characters.size() == characterChoicePlayer2) { helper.base.setTexture(*Universals::TextureManager::getTexture("basePTwo")); }
		helper.scale = 0.0;
		helper.c.setOrgin(sf::Vector2f(Universals::TextureManager::getTexture("character")->getSize().x / 2, Universals::TextureManager::getTexture("character")->getSize().y / 2));
		helper.position = sf::Vector2f(frontPosition.x + 1000, frontPosition.y - 400);
		helper.characterName.setString(characters[(characterChoice + 2) % characters.size()].getName());
		helper.characterName.setOrigin(sf::Vector2f((helper.characterName.getCharacterSize()*helper.characterName.getString().getSize() / 2), helper.characterName.getCharacterSize() / 2));
		helper.characterName.setPosition(sf::Vector2f(helper.position.x, helper.position.y - Universals::TextureManager::getTexture("character")->getSize().y - 50));
	}
	//set motion blur
	shader.setUniform("blur_radius", (float)0.0035);

	//modify the base if the chosen character is the helper
	if (temp == characterChoicePlayer1 || temp == characterChoicePlayer2)
	{
		if (temp == characterChoicePlayer1) { helper.base.setTexture(*Universals::TextureManager::getTexture("basePOne")); }
		else { helper.base.setTexture(*Universals::TextureManager::getTexture("basePTwo")); }
	}
	else { helper.base.setTexture(*Universals::TextureManager::getTexture("base")); }
}


//SETTINGS
void MainMenu::showSettings() { mainMenu.move(sf::Vector2f(-180, 0)); settingsMenu.setToogleOnoff(true);}
void MainMenu::hideSettings() { mainMenu.move(sf::Vector2f(180, 0)); settingsMenu.setToogleOnoff(false); }







