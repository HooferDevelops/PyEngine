#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <magic_enum.hpp>

using namespace std;

class Window {
private:
	int width;
	int height;
	string name;

	sf::RenderWindow window;
public:
	Window(int w, int h, string n);
	void display();
	void clear();
	void close();
	vector<string> getWindowState();
};