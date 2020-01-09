#include <SFML/Graphics.hpp>

using namespace sf;

class point
{
public:
	int x, y;
};

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(376, 600), "Doodle Jump (no eto ne tochno)", Style::Close);
	window.setFramerateLimit(60);


	Texture t, t1, t2, t3;
	t.loadFromFile("images/Doodler.png");
	t1.loadFromFile("images/plat.png");
	t2.loadFromFile("images/background.png"); 
	t3.loadFromFile("images/lose.png");

	Sprite doodlerSpr(t), background(t2), platSpr(t1), loseS(t3);

	loseS.setPosition(40, 150);
	doodlerSpr.setPosition(130, 200);

	float dy = 0, dx = 0, h=200;
	int score = 0;

	point doodler;
	doodler.x = 130;
	doodler.y = 200;

	point plat[10];
	for (int i = 0; i < 10; i++)
	{
		plat[i].x = rand() % 306;
		plat[i].y = rand() % 600;
	}


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		window.draw(background);


		for (int i = 0; i < 10; i++)
		{
			platSpr.setPosition(plat[i].x, plat[i].y);
			window.draw(platSpr);
		}



		dy += 0.35;
		if (dy > 500) dy -= 10;
		doodler.y += dy;


		if (Keyboard::isKeyPressed(Keyboard::Right)) doodler.x += 5;
		if (Keyboard::isKeyPressed(Keyboard::Left)) doodler.x -= 5;


		if (doodler.y < h)
		{
			for (int i = 0; i < 10; i++)
			{
				doodler.y = h;
				plat[i].y -= dy;
				score += dy;
				if (plat[i].y > 600)
				{
					plat[i].y = -10;
					plat[i].x = rand() % 306;
				}
			}
		}


		for (int i = 0; i < 10; i++)
		{
			if ((doodler.x + 64 > plat[i].x) && (doodler.x < plat[i].x + 70)
				&& (doodler.y + 84 > plat[i].y) && (doodler.y + 84 < plat[i].y + 15) && dy > 0) // ytytytyty
			{
				dy = 0;
				dy -= 12;
			}
		}

		if (doodler.y > 600)
		{
			window.draw(loseS);
		}

		doodlerSpr.setPosition(doodler.x, doodler.y);

		window.draw(doodlerSpr);
		window.display();
		window.clear();
	}

    return 0;
}

