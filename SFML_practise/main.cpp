#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

const int width = 800;
const int height = 400; 

enum GameState 
{
	MENU,
	PLAYING,
	LOADING,
	SCORE
};

GameState GS = MENU; 

int main()
{
	//creating window
	sf::RenderWindow window(sf::VideoMode({width, height}), "New game!");
	sf::Style::Default; 
	sf::Clock clock;
	sf::Vector2f PlayerSize(20.0f, 60.0f); 

	// system Variables
	float BaseSpeed = 350; 
	float BallSpeed = 300;
	float Increase_x = 1.0f;
	float Increase_y = 1.0f; 
	int Player1Score = 0;
	int Player2Score = 0;
	bool running = false;
	bool ShowDefaultScreen = true; 
	bool mQuit = false;
	bool backtomenu = false;
	bool backtogame = false; 
	int Max_score = 5;

	//making all the objects
	sf::RectangleShape player1; 
	sf::RectangleShape player2; 
	sf::RectangleShape ball; 
	sf::RectangleShape Line;
	sf::RectangleShape StartBox;
	sf::RectangleShape QuitBox;
	sf::Font MenuFont;
	sf::Font BasicFont;
	sf::Text Player1Stext(BasicFont); 
	sf::Text Player2Stext(BasicFont); 
	sf::Text TitleText(MenuFont);
	sf::Text StartText(BasicFont);
	sf::Text QuitText(BasicFont);
	sf::Text LoadingText(MenuFont);
	sf::Text WinnerText(BasicFont); 
	sf::Text DefaultText(BasicFont);
	sf::Text AfterText(BasicFont);

	//Default parameters Player 1 
	player1.setSize(PlayerSize);
	player1.setPosition(sf::Vector2f(25.0f, height/2));
	player1.setFillColor(sf::Color::Yellow);


	//Default parameters Player 2
	player2.setSize(PlayerSize); 
	player2.setPosition(sf::Vector2f(width - PlayerSize.x - 25.0f, height / 2));
	player2.setFillColor(sf::Color::Yellow);

	//Default parameters Ball
	ball.setSize(sf::Vector2f(10.0f, 10.0f));
	ball.setFillColor(sf::Color::White);
	ball.setPosition(sf::Vector2f(100.0f, 100.0f));

	if (!BasicFont.openFromFile("C:\\Users\\91813\\source\\repos\\SFML_practise\\SFML_practise\\fonts\\Pixel Sans Serif.ttf"))
	{
		std::cout << "Font not loaded!";
	};
	if (!MenuFont.openFromFile("C:\\Users\\91813\\source\\repos\\SFML_practise\\SFML_practise\\fonts\\Game Paused DEMO.otf"))
	{
		std::cout << "Font not loaded!";
	};

	// Drawing each of the Menus
	
	//---->Menu<-----
	//Title text
	TitleText.setString("PING PONG GAME!");
	TitleText.setCharacterSize(60.0f);
	float bounds = TitleText.getLocalBounds().getCenter().x;
	TitleText.setPosition(sf::Vector2f(bounds, 60.0f));

	//Start Text
	StartText.setString("START");
	StartText.setCharacterSize(30.0f);
	StartText.setPosition(sf::Vector2f(bounds + 110.0f, 180.0f));

	//Start box
	StartBox.setSize(sf::Vector2f(170.0f, 44.0f));
	StartBox.setFillColor(sf::Color::Transparent);
	StartBox.setOutlineThickness(3.0f);
	StartBox.setOutlineColor(sf::Color::White);
	StartBox.setPosition(sf::Vector2f(bounds + 98.0f, 177.0f));

	//Quit text
	QuitText.setString("QUIT");
	QuitText.setCharacterSize(30.0f);
	QuitText.setPosition(sf::Vector2f(bounds + 123.0f, 280.0f));
	
	//Quit box
	QuitBox.setSize(sf::Vector2f(150.0f, 44.0f));
	QuitBox.setFillColor(sf::Color::Transparent);
	QuitBox.setOutlineThickness(3.0f);
	QuitBox.setOutlineColor(sf::Color::White);
	QuitBox.setPosition(sf::Vector2f(bounds + 108.0f, 277.0f));

	//---->Playing<-----
	//Score parameters (player - 1)
	Player1Stext.setString("0");
	Player1Stext.setFillColor(sf::Color::Color(178, 190, 181, 30));
	Player1Stext.setCharacterSize(250.0f);
	Player1Stext.setPosition(sf::Vector2f(100.0f, 50.0f));

	//Score parameters (player - 2)
	Player2Stext.setString("0");
	Player2Stext.setFillColor(sf::Color::Color(178, 190, 181, 30));
	Player2Stext.setCharacterSize(250.0f);
	Player2Stext.setPosition(sf::Vector2f(500.0f, 50.0f));

	//A line for whatever reason
	Line.setSize(sf::Vector2f(20.0f, height));
	Line.setFillColor(sf::Color::Color(211, 211, 211, 10));
	Line.setPosition(sf::Vector2f(width / 2, 0.0f));
	
	//---->Loading<-----
	LoadingText.setString("LOADING");
	LoadingText.setCharacterSize(100.0f);
	LoadingText.setPosition(sf::Vector2f(225.0f, 100.0f));

	
	//--->Show score<----
	WinnerText.setCharacterSize(35.0f);
	WinnerText.setPosition(sf::Vector2f(90.0f, 150.0f));

	AfterText.setString("Enter to play the game or press esc to go to the start menu");
	AfterText.setCharacterSize(15.0f);
	AfterText.setPosition(sf::Vector2f(20.0f, 300.0f));

	//--->DefaultScreen<---
	DefaultText.setString("Press enter to start!");
	DefaultText.setCharacterSize(25);
	DefaultText.setPosition(sf::Vector2f(170.0f, 160.0f));

	while (window.isOpen())
	{
		float GetElapsedTime = clock.restart().asSeconds();
		sf::Vector2f vPlayer1Position = player1.getPosition();
		sf::Vector2f vPlayer2Position = player2.getPosition();
		sf::Vector2f vBallPosition = ball.getPosition();

		sf::Vector2f vPlayer1(0.0f, 0.0f);
		sf::Vector2f vPlayer2(0.0f, 0.0f);
		sf::Vector2f vBall(0.0f, 0.0f); 

		sf::FloatRect fPlayer1GlobalBounds = player1.getGlobalBounds();
		sf::FloatRect fPlayer2GlobalBounds = player2.getGlobalBounds();
		sf::FloatRect fBallGlobalBounds = ball.getGlobalBounds();

		sf::Vector2i MouseLocation = sf::Mouse::getPosition(window);
		sf::Vector2f MouseLocationRelative = window.mapPixelToCoords(MouseLocation);
		sf::FloatRect bStart = StartText.getGlobalBounds();

		float GetCenterPlayer1 = (vPlayer1Position.y + PlayerSize.y) / 2.0f; 
		float GetCenterPlayer2 = (vPlayer2Position.y + PlayerSize.y) / 2.0f;
		float GetCenterBall= (vBallPosition.y + 10.0f) / 2.0f;
		
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			if (GS == MENU)
			{
				if (mQuit)
				{
					window.close();
				}
			}

			if (GS == PLAYING)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter))
				{
					running = true;
					ShowDefaultScreen = false;
				}
			}

			if (backtomenu)
			{
				GS = MENU;
				backtomenu = false;
				ShowDefaultScreen = false;

				Player1Score = 0;
				Player2Score = 0;
				Player1Stext.setString("0");
				Player2Stext.setString("0");
				ball.setPosition(sf::Vector2f(100.0f, 100.0f));
				vPlayer1Position.y = height / 2.0f;
				vPlayer2Position.y = height / 2.0f;
				running = false;

			}
			if (backtogame)
			{
				GS = PLAYING;
				backtogame = false;
				ShowDefaultScreen = true;

				Player1Score = 0;
				Player2Score = 0;
				Player1Stext.setString("0");
				Player2Stext.setString("0");
				ball.setPosition(sf::Vector2f(100.0f, 100.0f));
				vPlayer1Position.y = height / 2.0f;
				vPlayer2Position.y = height / 2.0f;
				ShowDefaultScreen = true;
				running = false;
			}
		}

		if (GS == MENU)
		{
			window.clear();
			ShowDefaultScreen = true; 
			if (StartBox.getGlobalBounds().contains(MouseLocationRelative))
			{
				StartText.setFillColor(sf::Color::Black);
				StartBox.setFillColor(sf::Color::White);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button()))
				{
					GS = LOADING;
				}
			}
			else
			{
				StartText.setFillColor(sf::Color::White);
				StartBox.setFillColor(sf::Color::Transparent);
			}

			if (QuitBox.getGlobalBounds().contains(MouseLocationRelative))
			{
				QuitText.setFillColor(sf::Color::Black);
				QuitBox.setFillColor(sf::Color::White);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button()))
				{
					mQuit = true; 
				}
			}
			else
			{
				QuitText.setFillColor(sf::Color::White);
				QuitBox.setFillColor(sf::Color::Transparent);
			}

			window.draw(TitleText);
			window.draw(StartBox);
			window.draw(QuitBox);
			window.draw(QuitText);
			window.draw(StartText);

			window.display();
		}

		else if (GS == LOADING)
		{
			window.clear();
			window.draw(LoadingText);
			window.display();
			sf::sleep(sf::seconds(2));
			GS = PLAYING;
		}

		else if (GS == PLAYING) {
			window.clear();
			if (Player1Score == Max_score || Player2Score == Max_score)
			{
				GS = SCORE;
			}

			//keyboard input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
			{
				vPlayer1 += sf::Vector2f(0.0f, -1.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
			{
				vPlayer1 += sf::Vector2f(0.0f, +1.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::O))
			{
				vPlayer2.y -= 1.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::K))
			{
				vPlayer2.y += 1.0f;
			}

			// checking if the player is going outside the screen
			if (player1.getPosition().y < 0.0f)
			{
				player1.setPosition(sf::Vector2f(player1.getPosition().x, 0.0f));
			}
			if (player1.getPosition().y + PlayerSize.y > height)
			{
				player1.setPosition(sf::Vector2f(player1.getPosition().x, height - PlayerSize.y));
			}
			if (player2.getPosition().y < 0.0f) 
			{
				player2.setPosition(sf::Vector2f(player2.getPosition().x, 0.0f));
			}
			if (player2.getPosition().y + PlayerSize.y > height)
			{
				player2.setPosition(sf::Vector2f(player2.getPosition().x, height - PlayerSize.y));
			}
			//collision checking 
			if (fPlayer1GlobalBounds.findIntersection(fBallGlobalBounds))
			{
				Increase_x = std::abs(Increase_x);

				if (GetCenterBall > GetCenterPlayer1)
				{
					Increase_y = std::abs(Increase_y);
				}
				else
				{
					Increase_y = -std::abs(Increase_y);
				}
			}
			if (fPlayer2GlobalBounds.findIntersection(fBallGlobalBounds))
			{
				Increase_x = -std::abs(Increase_x);

				if (GetCenterBall > GetCenterPlayer2)
				{
					Increase_y = std::abs(Increase_y);
				}
				else
				{
					Increase_y = -std::abs(Increase_y);
				}
			}

			// Bottom collision
			if (vBallPosition.y >= height)
			{
				Increase_y = -std::abs(Increase_y);
			}
			// Top collision
			if (vBallPosition.y <= 0.0)
			{
				Increase_y = std::abs(Increase_y);
			}

			//score
			if (vBallPosition.x <= 0.0f)
			{
				Player2Score += 1;
				Player2Stext.setString(std::to_string(Player2Score));
				Increase_x = std::abs(Increase_x);

				if (vBallPosition.y <= height / 2.0f)
				{
					Increase_y = std::abs(Increase_y);
				}
				else
				{
					Increase_y = -std::abs(Increase_y);
				}
			}
			if (vBallPosition.x >= width)
			{
				Player1Score += 1;
				Increase_x = -std::abs(Increase_x);
				Player1Stext.setString(std::to_string(Player1Score));
				if (vBallPosition.y <= height/ 2.0f)
				{
					Increase_y = std::abs(Increase_y);
				}
				else
				{
					Increase_y = -std::abs(Increase_y);
				}
			}

			if (running)
			{
				vBall.x += Increase_x;
				vBall.y += Increase_y;
			}
			//Movement
			player1.move(vPlayer1 * GetElapsedTime * BaseSpeed);
			player2.move(vPlayer2 * GetElapsedTime * BaseSpeed);
			ball.move(vBall * GetElapsedTime * BallSpeed);

			if (ShowDefaultScreen)
			{
				window.draw(DefaultText);
			}
			else {
				window.draw(Player1Stext);
				window.draw(Player2Stext);
				window.draw(Line);
				window.draw(player1);
				window.draw(player2);
				window.draw(ball);
			}
			window.display();
		}

		else if (GS == SCORE)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter))
			{
				backtogame = true;
			};
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
			{
				backtomenu = true;
			};

			if (Player1Score > Player2Score)
			{
				WinnerText.setString("PLAYER 1 IS THE WINNER"); 
				window.clear();
				window.draw(WinnerText);
				window.draw(AfterText);
				window.display();
			}
			else if (Player2Score > Player1Score)
			{
				WinnerText.setString("PLAYER 2 IS THE WINNER");
				window.clear();
				window.draw(WinnerText);
				window.draw(AfterText);
				window.display();
			}
		};
	}

	return 0; 
}

// maybe boundaries can work as of now, add menu, game variables, and score thing. 
// 1. score thing (done)
// 2. game Variable (done)
// 3. Menu thing
// Bonus: add music as well.