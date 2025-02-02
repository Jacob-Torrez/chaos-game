// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main(){
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	// Seeding rand()
	srand(time(NULL));

	// Creating and positioning the text
	Text messageText;
	Font font;
	font.loadFromFile("Fonts/arial.ttf");
	messageText.setFont(font);
	messageText.setString("Select five vertices");
	messageText.setCharacterSize(75);
	messageText.setFillColor(Color::White);
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 75);


	while (window.isOpen()){
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event)){
		    if (event.type == Event::Closed){
					// Quit the game when the window is closed
					window.close();
		    }
		    
			if (event.type == sf::Event::MouseButtonPressed)
		    {
				if (event.mouseButton.button == sf::Mouse::Left){
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
		
					if(vertices.size() < 5){
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						
						// changes text
						if (vertices.size() == 5) {
							messageText.setString("Choose a point within the pentagon to start");
							FloatRect textRect = messageText.getLocalBounds();
							messageText.setOrigin(textRect.left +
								textRect.width / 2.0f,
								textRect.top +
								textRect.height / 2.0f);
							messageText.setPosition(1920 / 2.0f, 75);
						}
					}
					else if(points.size() == 0){
						///fourth click
						///push back to points vector
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
				}
		    }
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0){
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			for (int i = 0; i < 5; i++){
					int vertice = rand() % 5;
					float x = ((vertices.at(vertice).x - points.back().x) * 0.618) + points.back().x;
					float y = ((vertices.at(vertice).y - points.back().y) * 0.618) + points.back().y;
					points.push_back(Vector2f(x, y));
			}
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();

		if (vertices.size() < 5 || points.size() == 0) {
			window.draw(messageText);
		}

		for(int i = 0; i < vertices.size(); i++){
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}

		for (int i = 0; i < points.size(); i++) {
			RectangleShape rect(Vector2f(5, 5));
			rect.setPosition(points[i].x, points[i].y);
			rect.setFillColor(Color::Red);
			window.draw(rect);
		}


		window.display();
	}
}
