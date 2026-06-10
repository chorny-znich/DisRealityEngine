# Project structure
[parent_folder] -> config :
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

# Create the new app
- Create an engine class (for example GameEngine)  derived from dr::Engine class
- Override virtual methods from the base (dr::Engine) class: 
	* createStartScreen() - create a first screen using ScreenManager::addScreen<class_name>(std::string id)
	* init() - initialize resources
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