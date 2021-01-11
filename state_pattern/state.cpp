#include <iostream>
#include "state.h"


Camera::Camera()
	:
	m_x{0},
	m_y{0}
{}

Camera::Camera( float x,
	float y )
	:
	m_x{ x },
	m_y{ y }
{}

void KeyManager::update()
{
	pass;
}

bool MouseManager::getm_lmb() const noexcept
{
	return m_lmb;
}


UIManager::UIManager()
{
	std::cout << "UIManager ctor" << '\n';
}

UIManager::~UIManager()
{
	std::cout << "UIManager dtor" << '\n';
}

void UIManager::update() const
{
	std::cout << "Updating ui\n";
}

void UIManager::render( Graphics* gfx ) const
{
	std::cout << "drawing ui\n";
	// use gfx to draw :)
}

World::World( const std::string& path )
	:
	m_worldPath( path )
{
	std::cout << "World ctor" << '\n';
}

World::~World()
{
	std::cout << "World dtor" << '\n';
}

void World::update() const
{
	std::cout << "Updating world "
		<< m_worldPath
		<< '\n';
}

void World::render( Graphics* gfx ) const
{
	std::cout << "Drawing world\n";
	// use our gfx to draw!!! :)
}

State::State()
{
//	m_pcurrentState.reset(this);
	std::cout << "base state ctor\n";
}

State::~State() noexcept
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

MenuState::MenuState()
	:
	m_pUiManager( std::make_unique<UIManager>() )
{
	std::cout << "MenuState ctor\n";
}

MenuState::~MenuState() noexcept
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

void MenuState::update()
{
	m_pUiManager->update();
}

void MenuState::render( Graphics* gfx ) const
{
	m_pUiManager->render( gfx );
}

UIManager* MenuState::getUi() const noexcept
{
	return m_pUiManager.get();
}
void MenuState::setUi( UIManager* ui )
{
	m_pUiManager.reset( ui );
}

GameState::GameState()
	:
	m_pWorld( std::make_unique<World>( "resources/worlds/world2.txt" ) )
{
	std::cout << "GameState ctor\n";
}

GameState::~GameState() noexcept
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

void GameState::update()
{
	m_pWorld->update();
}

void GameState::render( Graphics* gfx ) const
{
	m_pWorld->render( gfx );
}

World* GameState::getWorld() const noexcept
{
	return m_pWorld.get();
}

void GameState::setWorld( World* world )
{
	m_pWorld.reset( world );
}

void Graphics::draw( State* state )
{
	state->render( this );
}

Game::Game( unsigned w,
	unsigned h,
	const std::string& title )
	:
	m_running{ false },
	m_width{ w },
	m_height{ h },
	m_aspectRatio( (float)w / h ),
	m_title{ title },
	m_pcurrentState{std::make_unique<MenuState>()}
{
	std::cout << "Game ctor" << '\n';
}

Game::~Game()
{
	std::cout << "Game dtor" << '\n';
}

bool Game::start()
{
	m_running = true;
	std::cout << "Game " << m_title << " starting up!" << '\n';

	return run();
}

bool Game::run()
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

bool Game::stop()
{
	m_running = false;
	std::cout << " shutting down.." << '\n';
	return EXIT_SUCCESS;
}

void Game::setState( State* newState )
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

State* Game::getState() noexcept
{
	return m_pcurrentState.get();
}
