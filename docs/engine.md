# Project structure
[parent_folder] -> [config] :
	engine_config.ini - create window
	```
	[general]
	title=DisReality Engine template application
	[window]
	resolution_state=NATIVE
	resolution_x=1920
	resolution_y=1080
	window_mode=FULLSCREEN
	```
[parent_folder] -> [data] : ini files with game's data:
	text-style.ini - styles for sf::Text object from the SFML3
	```
	[size]
	size=10
	[style_0]
	id=main_button
	font=main_font
	character_size=50
	color_component_red=0
	color_component_green=0
	color_component_blue=0
	color_component_alpha=255
	```
	
	Lists of resources like textures, fonts, sounds
	font-list.ini - list of fonts
	texture.list.ini - list of textures
	```
	[assets]
	main_font=assets/font/brushtype.ttf
	```
	
	strings.ini - all game's text
	```
	[strings]
	about_app_content=The template for the minimal DisReality Engine application
	back_button=BACK
	
[parent_folder]/assets -> all assets:
	/font - fonts
	/img - images

# Create the new app
- Create an engine class (for example GameEngine)  derived from dr::Engine class
- Override virtual methods from the base (dr::Engine) class: 
	* createStartScreen() - create a first screen using ScreenManager::addScreen<class_name>(std::string id)
	* init() - initialize resources
		call dr::Engine::Init() for resources initialization
- Use run() method to start the app

# Work with screens
- Create a screen class.
- Override virtual methods from the base (dr::Screen) class:
```c++
class AboutScreen : public dr::Screen
{
public:
	void init() override;
	void handleInput(const sf::Event& event);
	void update(float dt) override;
	void render(sf::RenderWindow& window) override;
};
```
# Managers
## Text manager
Ini file with text style is in: [parent_folder]/data/text-style.ini
