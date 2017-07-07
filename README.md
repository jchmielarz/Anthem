# Anthem
>A new meta language inside C++
## Example
```cpp
using macro_test =
	ANTHEM_SCRIPT_BEGIN
		SET VAR(int_t), int,
		IF VAR(int_t), EQUALS int,
		THEN
			SET VAR(float_t), float,
		ELSE
			SET VAR(float_t), void,
		END_IF
	ANTHEM_SCRIPT_END

	using float_t = ANTHEM_GET_VAR(macro_test, float_t);
	static_assert(std::is_same_v<float_t, float>,"");
```
## Why?
Anthem is a project I created to play around with C++ templates. Although right now the idea doesn't seem very practical, I'm still going to explore the possibilities and see what interesting functionality I can get out of this. The library could provide a better structured and more readable type manipilation for complicated cases, for example to automatically bind new APIs with legacy code.
## What now?
The project is still extremely early in development.
My TODO list for now:
- update licence info
- foreach, while loops
- callable functions
- extending container functionality (list is extremely barebones right now)
- type traits
- and lots more...
