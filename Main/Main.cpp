// Main.cpp : Defines the entry point for the application.
//

#include "render/window.h"

#include <iostream>

#include <chrono>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

using namespace std;
using namespace std::chrono_literals;
namespace py = pybind11;

bool ticking = false;

void disableTicking() {
	ticking = false;
}


PYBIND11_EMBEDDED_MODULE(test, m) {
	// Main Window Class
	py::class_<Window>(m, "Window")
		.def(py::init<int, int, string>())
		.def("display", &Window::display)
		.def("close", &Window::close)
		.def("getWindowState", &Window::getWindowState);
	// Function for Disabling Running
	m.def("stopTick", &disableTicking);
}

constexpr std::chrono::nanoseconds timestep(16ms);

int main()
{
	ticking = true;

	cout << "Hello world!" << endl;

	py::initialize_interpreter();
	//py::scoped_interpreter guard();
	
	try {
		auto mainModule = py::module::import("scripts.main");
		auto loaderFunction = mainModule.attr("load");
		auto tickFunction = mainModule.attr("tick");
		bool shouldTickLoop = false;

		if (pybind11::hasattr(mainModule, "load")) {
			loaderFunction();
		}
		else {
			std::cout << "WARNING: No load() function was provided in scripts.main.py" << std::endl;
		}

		if (pybind11::hasattr(mainModule, "tick")) {
			shouldTickLoop = true;
		}
		else {
			std::cout << "WARNING: No tick() function was provided in scripts.main.py" << std::endl;
		}

		// Main clocking function for ticking

		using clock = chrono::high_resolution_clock;
		std::chrono::nanoseconds lag(0ns);
		auto time_start = clock::now();

		while (shouldTickLoop && ticking) {
			auto delta_time = clock::now() - time_start;
			time_start = clock::now();
			lag += chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

			while (lag >= timestep) {
				lag -= timestep;
			}

			auto alpha = (float)lag.count() / timestep.count();

			tickFunction(delta_time.count());
		}
	}
	catch (py::error_already_set& e) {
		std::cout << e.what() << std::endl;
	}

	/*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}*/

	return 0;
}
