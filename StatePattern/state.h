#pragma once

#include <memory>
#include <string>


class Graphics;

class Camera final
{
	float m_x;
	float m_y;
public:
	Camera();
	Camera( float x, float y );
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

	void update();
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

	bool getm_lmb() const noexcept;
};


// a game component
class UIManager
{
public:
	explicit UIManager();
	~UIManager();

	void update() const;
	void render( Graphics* gfx ) const;
};

// a game component
class World
{
private:
	std::string m_worldPath;
public:
	explicit World( const std::string& path );
	~World();

	void update() const;
	void render( Graphics* gfx ) const;
};

// the state class
class State
{
public:
	State();
	virtual ~State() noexcept;

	virtual void update() = 0;
	virtual void render( Graphics* gfx ) const = 0;
};

class MenuState final
	: public State
{
	std::unique_ptr<UIManager> m_pUiManager;
public:
	explicit MenuState();
	virtual ~MenuState() noexcept override;

	void update() override;
	void render( Graphics* gfx ) const override;
public:
	UIManager* getUi() const noexcept;
	void setUi( UIManager* ui );
};

// Updates and Renders the Game State (our main state)
class GameState final
	: public State
{
	std::unique_ptr<World> m_pWorld;
public:
	explicit GameState();
	virtual ~GameState() noexcept override;

	void update() override;
	void render( Graphics* gfx ) const override;
public:
	World* getWorld() const noexcept;
	void setWorld( World* world );
};

// the graphics "brush"
class Graphics final
{
	UIManager* m_pUi;
	World* m_pWorld;
public:
	void draw( State* state );
};

// the Game class - this is the class with togglable states
class Game final
{
	bool m_bRunning;
	unsigned int m_width;
	unsigned int m_height;
	float m_aspectRatio;
	std::string m_title;
	std::unique_ptr<State> m_pCurrentState;
	Graphics m_graphics;
	Camera m_camera;
	KeyManager m_keyManager;
	MouseManager m_mouseManager;
public:
	explicit Game( unsigned w, unsigned h, const std::string& title );
	~Game();

	Game( const Game& rhs ) = delete;
	Game& operator=( const Game& rhs ) = delete;

	// initialization stuff
	bool start();
	// contains the game loop
	bool run();
	// termination stuff
	bool stop();

	void setState( State* newState );
	State* getState() noexcept;
};
