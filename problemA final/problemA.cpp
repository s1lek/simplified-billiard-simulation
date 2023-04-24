#include <iostream>


struct position
{
	int x;
	int y;
};

int Vectorreduction(int a, int b)
{
	int div;
	if (a == 0 && b == 0) return 1;
	else
	{
		if (a == 0) return b;
		if (b == 0) return a;
	}
	while (true)
	{
		div = a % b;
		if (div == 0)
		{
			break;
		}
		else
		{
			a = b;
			b = div;
		}
	}
	if (b > 0) return b;
	else return -b;
}

int main()
{
	int T;
	std::cin >> T; //number of tests
	
	//assumptions: the table x dimension is always even, there is no friction in ball movement, incidence angle = reflection angle
	//ball must be exactly in the location of the pocket to fall into, ONFY FOR INTEGER DATA
	for (int i = 0; i < T; i++)
	{
		int reflect = 0;
		int Sx, Sy, Px, Py, Wx, Wy;
		std::cin >> Sx >> Sy >> Px >> Py >> Wx >> Wy; //Sx, Sy - dimensions of table; Px, Py - starting location of the ball; Wx, Wy - vector of ball movement
		 
		position ball = { Px, Py };
		position movvector = { Wx, Wy };
		//vector reduction if possible
		if (Vectorreduction(Wx, Wy) != 1)
		{
			movvector.x = (Wx / Vectorreduction(Wx, Wy));
			movvector.y = (Wy / Vectorreduction(Wx, Wy));
		}
		//ball movement simuation
		for (;;)
		{
			ball.x += movvector.x;
			ball.y += movvector.y;

			while (ball.x < 0 || ball.x > Sx || ball.y > Sy || ball.y < 0)			
			{
				if (ball.y > Sy)
				{
					ball.y -= 2 * (ball.y - Sy);
					movvector.y = -movvector.y;
					reflect++;
				}
				if (ball.y < 0)
				{
					ball.y += 2 * (0 - ball.y);
					movvector.y = -movvector.y;
					reflect++;
				}
				if (ball.x > Sx)
				{
					ball.x -= 2 * (ball.x - Sx);
					movvector.x = -movvector.x;
					reflect++;
				}
				if (ball.x < 0)
				{
					ball.x += 2 * (0 - ball.x);
					movvector.x = -movvector.x;
					reflect++;
				}
			}
			if (ball.x == 0 && ball.y == Sy)
			{
				std::cout << "Top left, " << reflect << " reflections" << std::endl;
				break;
			}
			if (ball.x == Sx && ball.y == Sy)
			{
				std::cout << "Top right, " << reflect << " reflections" << std::endl;
				break;
			}
			if (ball.x == (Sx / 2) && ball.y == Sy)
			{
				std::cout << "Top middle, " << reflect << " reflections" << std::endl;
				break;
			}
			if (ball.x == 0 && ball.y == 0)
			{
				std::cout << "Down left, " << reflect << " reflections" << std::endl;
				break;
			}
			if (ball.x == Sx && ball.y == 0)
			{
				std::cout << "Down right, " << reflect << " reflections" << std::endl;
				break;
			}
			if (ball.x == (Sx / 2) && ball.y == 0)
			{
				std::cout << "Down middle, " << reflect << " reflections" << std::endl;
				break;
			}
			if (ball.x == Px && ball.y == Py && movvector.x == Wx && movvector.y == Wy)
			{
				std::cout << "Never going to fall into pocket" << std::endl;
				break;
			}
		}
	}
}