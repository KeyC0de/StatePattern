<h1 align="center">
	<a href="https://github.com/KeyC0de/StatePattern">State Pattern</a>
</h1>
<hr>


This is a demonstration of the State Design Pattern in C++ with a groovy example that sticks (hopefully).

The state pattern allows an object to alter its behavior at runtime when its internal state changes. There is a base `State` class and various concrete derives state classes. The state class hierarchy make up a state machine and the desired object can be at any single state at a time. State is an alternative behavioral software design pattern to the [Strategy](https://keyc0de.com/posts/48.html) pattern.

<p style="text-align: center;">
	<img src="_present/state.jpg" />
</p>

Design

- State Interface: Define an interface for encapsulating the behavior associated with a particular state of the context.
- State: each concrete state implements the state interface's behavior. We define a fixed set of State classes that the class can be in.
- Context: maintains the data of the current state.
- the class can be in only one state at a time.
- the class starts from a default state.
- various conditions can trigger the transition from one state to another. Changing states changes the behavior of the class (at runtime).

Note that when the object's internal state changes it will look to the outside world as if the class is changed.

Enumerations prove to be quite useful for the selection of states. For example:

```
enum class State
{
	STANDING,
	JUMPING,
	DUCKING,
	DIVING,
	SWIMMING
};

class Hero
{
	State m_currentState;

	void handleInput()
	{
		switch( m_currentState )
		{
		case State::STANDING:
			// do this
			break;
		case State::JUMPING:
			// do that
			break;
		// ...
		default:
			// do w/e (whatever)
			break;
		}
	}
	// ...
};
```

I used Windows 8.1 x86_64, Visual Studio 2017, C++17 to build the project.


# License

Distributed under the GNU GPL V3 License. See "GNU GPL license.txt" for more information.
