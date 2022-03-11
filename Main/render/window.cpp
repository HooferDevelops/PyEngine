#include "Window.h"

enum class Color : int { RED = -10, BLUE = 0, GREEN = 10 };


Window::Window(int w, int h, string n) {
	width = w;
	height = h;
	name = n;


	window.create(sf::VideoMode(w, h), n);

	cout << "Window Constructed" << endl;
}

void Window::display() {
	window.display();
}

void Window::clear() {
	window.clear();
}

void Window::close() {
	window.close();
}

void Window::setCursorVisibility(bool visible) {
	window.setMouseCursorVisible(visible);
}

vector<string> Window::getWindowState() {
	sf::Event event;

	vector<string> stateResults;

	while (window.pollEvent(event))
	{
		string_view eventName = magic_enum::enum_name(event.type);
		// convert eventName string_view to string
		string eventNameString(eventName.begin(), eventName.end());
		// add eventNameString to stateResults vector
		stateResults.push_back(eventNameString);
		
	}

	return stateResults;
}