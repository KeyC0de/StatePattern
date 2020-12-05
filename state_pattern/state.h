#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <string>

#define pass (void)0


class Graphics;

class Camera final
{
	float m_x;
	float m_y;
public:
	Camera()
		:
		m_x{0},
		m_y{0}
	{}
	Camera( float x, float y )
		:
		m_x{ x },
		m_y{ y }
	{}
	~Camera() = default;
};

class KeyManager final
{
	bool m_justPressed;
	bool m_ableToPress;
	bool m_up;
	bool m_right;
	bool m_down;
	bool m_left;
public:
	explicit KeyManager() = default;
	KeyManager( const KeyManager& rhs ) = delete;
	KeyManager& operator=( const KeyManager& rhs ) = delete;

	void update()
	{
		pass;
	}
};

class MouseManager final
{
	bool m_lmb;
	bool m_mmb;
	bool m_rmb;
	int m_x;
	int m_y;
public:
	MouseManager() = default;

	MouseManager( const MouseManager& rhs ) = delete;
	MouseManager& operator=( const MouseManager& rhs ) = delete;

	bool getm_lmb() const noexcept {
		return m_lmb;
	}
};


// a game component
class UIManager
{
public:
	explicit UIManager()
	{
		std::cout << "UIManager ctor" << '\n';
	}
	~UIManager()
	{
		std::cout << "UIManager dtor" << '\n';
	}

	void update() const
	{
		std::cout << "Updating ui\n";
	}

	void render( Graphics* gfx ) const
	{
		std::cout << "drawing ui\n";
		// use gfx to draw :)
	}
};

// a game component
class World
{
private:
	std::string m_worldPath;
public:
	explicit World( const std::string& path )
		:
		m_worldPath( path )
	{
		std::cout << "World ctor" << '\n';
	}
	~World()
	{
		std::cout << "World dtor" << '\n';
	}

	void update() const
	{
		std::cout << "Updating world "
			<< m_worldPath
			<< '\n';
	}

	void render( Graphics* gfx ) const
	{
		std::cout << "Drawing world\n";
		// use our gfx to draw!!! :)
	}
};

// the state class
class State
{
public:
	State()
	{
	//	m_pcurrentState.reset(this);
		std::cout << "base state ctor\n";
	}
	virtual ~State() noexcept
	{
		//m_pcurrentState.reset();
		//m_pcurrentState = nullptr;
		std::cout << "base state dtor\n";
	}
	//
	//State(const State& rhs) = delete;
	//State& operator=(const State& rhs) = delete;
	//
	//State(State&& rhs)
	//{
	//	m_pcurrentState.swap(rhs.m_pcurrentState);
	//}
	//State& operator=(State&& rhs)
	//{
	//	m_pcurrentState.swap(rhs.m_pcurrentState);
	//	return *this;
	//}

	virtual void update() = 0;
	virtual void render( Graphics* gfx ) const = 0;
};

class MenuState final
	: public State
{
	std::unique_ptr<UIManager> m_pUiManager;
public:
	explicit MenuState()
		:
		m_pUiManager( std::make_unique<UIManager>() )
	{
		std::cout << "MenuState ctor\n";
	}
	virtual ~MenuState() noexcept override
	{
		std::cout << "MenuState dtor\n";
	}

	//MenuState(const MenuState& rhs) = delete;
	//MenuState& operator=(const MenuState& rhs) = delete;
	//MenuState(MenuState&& rhs)
	//	: State(std::move(rhs)),
	//	m_pUiManager{ std::move(rhs.m_pUiManager) }
	//{
	//	std::cout << "MenuState mctor" << '\n';
	//}
	//MenuState& operator=(MenuState&& rhs)
	//{
	//	if (this != &rhs)
	//	{
	//		m_pcurrentState.swap(rhs.m_pcurrentState);
	//		std::swap(m_pUiManager, rhs.m_pUiManager);
	//		std::cout << "MenuState maop" << '\n';
	//	}
	//	return *this;
	//}

	void update() override
	{
		m_pUiManager->update();
	}

	void render( Graphics* gfx ) const override
	{
		m_pUiManager->render( gfx );
	}

public:
	UIManager* getUi() const noexcept {
		return m_pUiManager.get();
	}
	void setUi( UIManager* ui ) {
		m_pUiManager.reset( ui );
	}
};

// Updates and Renders the Game State (our main state)
class GameState final
	: public State
{
	std::unique_ptr<World> m_pWorld;
public:
	explicit GameState()
		:
		m_pWorld( std::make_unique<World>( "resources/worlds/world2.txt" ) )
	{
		std::cout << "GameState ctor\n";
	}
	virtual ~GameState() noexcept override
	{
		std::cout << "GameState dtor\n";
	}

	//GameState(const GameState& rhs) = delete;
	//GameState& operator=(const GameState& rhs) = delete;
	//GameState(GameState&& rhs)
	//	: State(std::move(rhs)),
	//	m_pWorld{ std::move(rhs.m_pWorld) }
	//{
	//	std::cout << "GameState mctor" << '\n';
	//}
	//GameState& operator=(GameState&& rhs)
	//{
	//	if (this != &rhs)
	//	{
	//		m_pcurrentState.swap(rhs.m_pcurrentState);
	//		std::swap(m_pWorld, rhs.m_pWorld);
	//		std::cout << "GameState maop" << '\n';
	//	}
	//	return *this;
	//}

	void update() override {
		m_pWorld->update();
	}

	void render( Graphics* gfx ) const override {
		m_pWorld->render( gfx );
	}

public:
	World* getWorld() const noexcept
	{
		return m_pWorld.get();
	}

	void setWorld( World* world )
	{
		m_pWorld.reset( world );
	}
};

// the graphics "brush"
class Graphics final
{
	UIManager* m_pUi;
	World* m_pWorld;
public:
	void draw( State* state )
	{
		state->render( this );
	}
};

// the Game class - this is the class with togglable states
class Game final
{
	bool m_running;
	unsigned int m_width;
	unsigned int m_height;
	float m_aspectRatio;
	std::string m_title;
	std::unique_ptr<State> m_pcurrentState;
	Graphics m_graphics;
	Camera m_camera;
	KeyManager m_keyManager;
	MouseManager m_mouseManager;
public:

	explicit Game( unsigned w,
		unsigned h,
		const std::string& title )
		:
		m_running{ false },
		m_width{ w },
		m_height{ h },
		m_aspectRatio( w / h ),
		m_title{ title },
		m_pcurrentState{std::make_unique<MenuState>()}
	{
		std::cout << "Game ctor" << '\n';
	}

	~Game()
	{
		std::cout << "Game dtor" << '\n';
	}

	Game( const Game& rhs ) = delete;
	Game& operator=( const Game& rhs ) = delete;

	// initialization stuff
	bool start()
	{
		m_running = true;
		std::cout << "Game " << m_title << " starting up!" << '\n';

		return run();
	}

	// contains the game loop
	bool run()
	{
		std::cout << "running ..." << '\n';
		m_pcurrentState->update();
		m_graphics.draw( m_pcurrentState.get() );
		std::cout << '\n';
		
		// changing states
		setState( new GameState{} );
		m_pcurrentState->update();
		m_graphics.draw( m_pcurrentState.get() );
		return stop();
	}

	// termination stuff
	bool stop()
	{
		m_running = false;
		std::cout << " shutting down.." << '\n';
		return EXIT_SUCCESS;
	}

	void setState( State* newState )
	{
		//if (m_pcurrentState.get() != nullptr)
		//{
		//	std::cout << "whaaaa" << '\n';
		//	m_pcurrentState.reset();
		//}
		//m_pcurrentState.swap(newState->m_pcurrentState);
		//std::swap()
		m_pcurrentState.reset( newState );
		 //= 
		//*this = *newState;
	}

	State* getState() noexcept
	{
		return m_pcurrentState.get();
	}
};
