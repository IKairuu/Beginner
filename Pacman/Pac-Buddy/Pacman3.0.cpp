#include <iostream>
#include <graphics.h>
#include <fstream>
#include <unistd.h>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <mmsystem.h>
#include <vector>

std::ofstream outputHighscore("pacmanhighscore.txt", std::ios::app) ;
std::ifstream inputHighscore("pacmanhighscore.txt") ;

std::vector<int> colorHardMode = {0, 14} ;
std::vector<int> colorEnemy = {0, 4, 8} ;

int page = 0 ;
int startAngleRight = 60, endAngleRight = 300 ;
int startAngleDown = 330, endAngleDown = 570 ;
int startAngleUp = 150, endAngleUp = 390 ;
int startAngleLeft = 240, endAngleLeft = 480  ;
int speed = 2 ;
const int radius = 30 ;
const int frameSpeed = 8 ;
const int pacTime = 20000 ;
const int pacFoodRange = 20 ;
const int foodRangePacMan = 20 ;
const int enemyRadius = 100 ;
const int enemyRangeX = 90 ;
const int enemyRangeY = 50 ;
int foodCoordX ;
int foodCoordY ;
int backGroundColor ;
int angleRange ;
int objectColor ;
int pacmanColor = 14 ;
int cloneColor = 14 ;
int cloneColor2 = 14 ;
int pacmanEnemyColor = 4 ;
int enemyCoordX ;
int enemyCoordY ;
int enemyStartAngle ;
int enemyEndAngle ;
bool gameOver = false ;
bool right = true ;
bool down = false ;
bool upp = false ;
bool left = false ;
bool mouthRight = true ;
bool mouthLeft = true;
bool mouthUp = true ;
bool mouthDown = true ;
bool switchDirection = false, foodIsMoving = false ;
bool showMovingObject = false ;
bool changeDigits = false ;
bool threeDigits = false ;
bool playMemeSound = true ;
bool easyMode = true ;
bool activatePacmanClone = false ;
bool pacmanEnemy = false ;
bool enemyGenerate = true ;
bool spawnRight = false ;
bool spawnUp = false ;
bool spawnLeft = false ;
bool spawnDown = false ;
bool activatePacmanEnemy = false ;
bool setGameOver = false ;
bool flickerFood = false ;
bool objectHorizontal = true ;
std::string points = "0" ;
std::string highscore = "0" ;
void drawFood(int foodX, int foodY, int x, int y) ;
void pointSystem() ;
void startPacman(int x, int y) ;
void setFoodCoordX(int foodX) ;
void setFoodCoordY(int foodY) ;
void gameOverPacMan(int x, int y, int startAngle, int endAngle) ;
void movingObjects(int object1First) ;
void identifyDirection(int object1First) ;
void mainMenu() ;
void loading() ;
void hoverMainMenu(bool option1, bool option2, int startAngle, int endAngle) ;
void startPacMan() ;
void pacmanClone(int x, int y, int startAngle, int endAngle) ;
void drawPacmanEnemy(int x, int y) ;
void SoundGame() ;
void SoundStart();
void SoundOver() ;
void SoundEat() ;
void playMeme() ;
void playHardMode() ;
int getFoodCoordX() ;
int getFoodCoordY() ;

int main()
{
	int gd = DETECT, gm, x = 200, y = 200, foodX, foodY, startAngle, endAngle, object1First = 0 ;
	initgraph(&gd, &gm, NULL) ;
	srand(time(NULL)) ;
	bool setRight = true, setDown = true, setUp = true, setLeft = true;
	inputHighscore >> highscore ;
	do
	{
		backGroundColor = (1 + (rand() % 14)) ;
		std::cout << backGroundColor << std::endl ;
	}while(backGroundColor > 14) ;
	do
	{
		foodX = speed+(speed*((60+(rand() % 640))/speed)), foodY = speed+(speed*((60+(rand() % 480))/speed)) ;
		setFoodCoordX(foodX) ;
		setFoodCoordY(foodY) ;
		std::cout << getFoodCoordX() << " " << getFoodCoordY() ;
	}while(getFoodCoordX() <= 80 || getFoodCoordX() >= 565 || getFoodCoordY() <= 80 || getFoodCoordY() >= 430 || getFoodCoordX() % speed != 0 || getFoodCoordY() % speed != 0) ;
	mainMenu() ;
	startPacMan() ;
	setbkcolor(backGroundColor) ;
	SoundGame() ;
	while(!gameOver)
	{
		setactivepage(page) ;
		setvisualpage(1-page) ;
		cleardevice() ;
		if(right)
		{
			angleRange = 180 ;
			if((startAngleRight <= 60 || endAngleRight >= 300) && setRight)
			{
				pointSystem() ;
				drawFood(getFoodCoordX(), getFoodCoordY(), x, y) ;
				switch(showMovingObject)
				{
					case true:
						movingObjects(object1First) ;
					break ;
				}
				setfillstyle(SOLID_FILL,pacmanColor) ;
				pieslice(x, y, startAngleRight, endAngleRight, radius) ;
				if(activatePacmanClone)
				{
					pacmanClone(x, y,startAngleRight, endAngleRight) ;
				}
				switch(activatePacmanEnemy)
				{
					case true:
						drawPacmanEnemy(x, y) ;
						break ;
				}
				startAngleRight -= frameSpeed ;
				endAngleRight += frameSpeed ;
				usleep(pacTime) ;
				if(startAngleRight <= 8 || endAngleRight >= 352)
				{
					setRight = false ;
				}
			}
			else if(!setRight)
			{
				pointSystem() ;
				if(!flickerFood)
				{
					drawFood(getFoodCoordX(), getFoodCoordY(), x, y) ;
				}
				switch(showMovingObject)
				{
					case true:
						movingObjects(object1First) ;
					break ;
				}
				setfillstyle(SOLID_FILL,pacmanColor) ;
				pieslice(x, y, startAngleRight, endAngleRight, radius) ;
				if(activatePacmanClone)
				{
					pacmanClone(x, y,startAngleRight, endAngleRight) ;
				}
				switch(activatePacmanEnemy)
				{
					case true:
						drawPacmanEnemy(x, y) ;
						break ;
				}
				startAngleRight += frameSpeed ;
				endAngleRight -= frameSpeed ;
				usleep(pacTime) ;
				if(startAngleRight >= 60 || endAngleRight <= 300)
				{
					setRight = true ;
				}
			}
			x += speed ;
				if(GetAsyncKeyState(VK_DOWN))
				{
					right = false ;
					down= true ;
					upp = false ;
					left = false ;
					startAngleRight = 60 ; 
					endAngleRight = 300 ;
					setRight = true ;
				}
				else if(GetAsyncKeyState(VK_UP))
				{
					right = false ;
					down= false ;
					upp = true ;
					left = false ;
					startAngleRight = 60 ; 
					endAngleRight = 300 ;
					setRight = true ;
				}
				else if(GetAsyncKeyState(VK_LEFT))
				{
					right = false ;
					down= false ;
					upp = false ;
					left = true ;
					startAngleRight = 60 ; 
					endAngleRight = 300 ;
					setRight = true ;
				}
		}
		else if(down)
		{
			angleRange = 450;
			if((startAngleDown <= 330 || endAngleDown >= 570) && setDown)
			{
				pointSystem() ;
				drawFood(getFoodCoordX(), getFoodCoordY(), x, y) ;
				switch(showMovingObject)
				{
					case true:
						movingObjects(object1First) ;
					break ;
				}
				setfillstyle(SOLID_FILL,pacmanColor) ;
				pieslice(x, y, startAngleDown, endAngleDown, radius) ;
				if(activatePacmanClone)
				{
					pacmanClone(x, y,startAngleDown, endAngleDown) ;
				}
				switch(activatePacmanEnemy)
				{
					case true:
						drawPacmanEnemy(x, y) ;
						break ;
				}
				startAngleDown -= frameSpeed ;
				endAngleDown += frameSpeed ;
				usleep(pacTime) ;
				if(startAngleDown <= 278 || endAngleDown >= 622)
				{
					setDown = false ;
				}
			}
			else if(!setDown)
			{
				pointSystem() ;
				if(!flickerFood)
				{
					drawFood(getFoodCoordX(), getFoodCoordY(), x, y) ;
				}
				switch(showMovingObject)
				{
					case true:
						movingObjects(object1First) ;
					break ;
				}
				setfillstyle(SOLID_FILL,pacmanColor) ;
				pieslice(x, y, startAngleDown, endAngleDown, radius) ;
				if(activatePacmanClone)
				{
					pacmanClone(x, y,startAngleDown, endAngleDown) ;
				}
				switch(activatePacmanEnemy)
				{
					case true:
						drawPacmanEnemy(x, y) ;
						break ;
				}
				startAngleDown += frameSpeed ;
				endAngleDown -= frameSpeed ;
				usleep(pacTime) ;
				if(startAngleDown >= 330 || endAngleDown <= 570)
				{
					setDown = true ;
				}
			}
			y += speed ;
				if(GetAsyncKeyState(VK_RIGHT))
				{
					right = true ;
					down= false ;
					upp = false ;
					left = false ;
					setDown = true ; 
					startAngleDown = 330 ;
					endAngleDown = 570 ;
				}
				else if(GetAsyncKeyState(VK_UP))
				{
					right = false ;
					down= false ;
					upp = true ;
					left = false ;
					setDown = true ; 
					startAngleDown = 330 ;
					endAngleDown = 570 ;
				}
				else if(GetAsyncKeyState(VK_LEFT))
				{
					right = false ;
					down= false ;
					upp = false ;
					left = true ;
					setDown = true ; 
					startAngleDown = 330 ;
					endAngleDown = 570 ;
				}
		}
		else if(upp)
		{
			angleRange = 270 ;
			if((startAngleUp <= 150 || endAngleUp >= 390) && setUp)
			{
				pointSystem() ;
				drawFood(getFoodCoordX(), getFoodCoordY(), x, y) ;
				switch(showMovingObject)
				{
					case true:
						movingObjects(object1First) ;
					break ;
				}
				setfillstyle(SOLID_FILL,pacmanColor) ;
				pieslice(x, y, startAngleUp, endAngleUp, radius) ;
				if(activatePacmanClone)
				{
					pacmanClone(x, y,startAngleUp, endAngleUp) ;
				}
				switch(activatePacmanEnemy)
				{
					case true:
						drawPacmanEnemy(x, y) ;
						break ;
				}
				startAngleUp -= frameSpeed ;
				endAngleUp += frameSpeed ;
				usleep(pacTime) ;
				if(startAngleUp <= 98 || endAngleUp >= 442)
				{
					setUp = false ;
				}
			}
			else if(!setUp)
			{
				pointSystem() ;
				if(!flickerFood)
				{
					drawFood(getFoodCoordX(), getFoodCoordY(), x, y) ;
				}
				switch(showMovingObject)
				{
					case true:
						movingObjects(object1First) ;
					break ;
				}
				setfillstyle(SOLID_FILL,pacmanColor) ;
				pieslice(x, y, startAngleUp, endAngleUp, radius) ;
				if(activatePacmanClone)
				{
					pacmanClone(x, y,startAngleUp, endAngleUp) ;
				}
				switch(activatePacmanEnemy)
				{
					case true:
						drawPacmanEnemy(x, y) ;
						break ;
				}
				startAngleUp += frameSpeed ;
				endAngleUp -= frameSpeed ;
				usleep(pacTime) ;
				if(startAngleUp >= 150 || endAngleUp <= 390)
				{
					setUp = true ;
				}
			}
			y -= speed ;
				if(GetAsyncKeyState(VK_DOWN))
				{
					right = false ;
					down= true ;
					upp = false ;
					left = false ;
					startAngleUp = 150 ; 
					endAngleUp = 390 ;
					setUp = true ;
				}
				else if(GetAsyncKeyState(VK_RIGHT))
				{
					right = true ;
					down= false ;
					upp = false ;
					left = false ;
					startAngleUp = 150 ; 
					endAngleUp = 390 ;
					setUp = true ;
				}
				else if(GetAsyncKeyState(VK_LEFT))
				{
					right = false ;
					down= false ;
					upp = false ;
					left = true ;
					startAngleUp = 150 ; 
					endAngleUp = 390 ;
					setUp = true ;
				}
		}
		else if(left)
		{
			angleRange = 360;
			if((startAngleLeft <= 240 || endAngleLeft >= 480) && setLeft)
			{
				pointSystem() ;
				drawFood(getFoodCoordX(), getFoodCoordY(), x, y) ;
				switch(showMovingObject)
				{
					case true:
						movingObjects(object1First) ;
					break ;
				}
				setfillstyle(SOLID_FILL,pacmanColor) ;
				pieslice(x, y, startAngleLeft, endAngleLeft, radius) ;
				if(activatePacmanClone)
				{
					pacmanClone(x, y,startAngleLeft, endAngleLeft) ;
				}
				switch(activatePacmanEnemy)
				{
					case true:
						drawPacmanEnemy(x, y) ;
						break ;
				}
				startAngleLeft -= frameSpeed ;
				endAngleLeft += frameSpeed ;
				usleep(pacTime) ;
				if(startAngleLeft <= 188 || endAngleLeft >= 532)
				{
					setLeft = false ;
				}
			}
			else if(!setLeft)
			{
				pointSystem() ;
				if(!flickerFood)
				{
					drawFood(getFoodCoordX(), getFoodCoordY(), x, y) ;
				}
				switch(showMovingObject)
				{
					case true:
						movingObjects(object1First) ;
					break ;
				}
				setfillstyle(SOLID_FILL,pacmanColor) ;
				pieslice(x, y, startAngleLeft, endAngleLeft, radius) ;
				if(activatePacmanClone)
				{
					pacmanClone(x, y,startAngleLeft, endAngleLeft) ;
				}
				switch(activatePacmanEnemy)
				{
					case true:
						drawPacmanEnemy(x, y) ;
						break ;
				}
				startAngleLeft += frameSpeed ;
				endAngleLeft -= frameSpeed ;
				usleep(pacTime) ;
				if(startAngleLeft >= 240 || endAngleLeft <= 480)
				{
					setLeft = true ;
				}
			}
			x -= speed ;
				if(GetAsyncKeyState(VK_DOWN))
				{
					right = false ;
					down= true ;
					upp = false ;
					left = false ;
					startAngleLeft = 240 ; 
					endAngleLeft = 480 ;
					setLeft = true ;
				}
				else if(GetAsyncKeyState(VK_RIGHT))
				{
					right = true ;
					down= false ;
					upp = false ;
					left = false ;
					startAngleLeft = 240 ; 
					endAngleLeft = 480 ;
					setLeft = true ;
				}
				else if(GetAsyncKeyState(VK_UP))
				{
					right = false ;
					down= false ;
					upp = true ;
					left = false ;
					startAngleLeft = 240 ; 
					endAngleLeft = 480 ;
					setLeft = true ;
				}
		}
		page = 1 - page ;
		std::cout << "x: " << x << " y: " << y << std::endl ;
		std::cout << "foodx: " << getFoodCoordX() << " foody: " << getFoodCoordY() << std::endl ;
		std::cout << "speed: " << speed << std::endl ;
		identifyDirection(object1First) ;
			switch(switchDirection)
			{
				case false:
					object1First += speed ;
					break ;
				case true:
					object1First -= speed ;
					break ;	
			}
		if(x >= 615 || y >= 455 || y <= 30 || x <= 20 || setGameOver)
		{
			gameOver = true ;
			if(right)
			{
				startAngle = startAngleRight ;
				endAngle = endAngleRight ;
			}
			else if(down)
			{
				startAngle = startAngleDown ;
				endAngle = endAngleDown ;
			}
			else if(upp)
			{
				startAngle = startAngleUp ;
				endAngle = endAngleUp ;
			}
			else if(left)
			{
				startAngle = startAngleLeft ;
				endAngle = endAngleLeft ;
			}
		}
	}
	if(gameOver)
	{
		gameOverPacMan(x, y, startAngle, endAngle) ;
	}
	
	return 0 ;
}
void drawFood(int foodX, int foodY, int x, int y)
{
	int pointsInt = std::stoi(points) ;
	srand(time(NULL)) ;
	if((x == getFoodCoordX() && y == getFoodCoordY()) || ((x+pacFoodRange >= getFoodCoordX() && x+pacFoodRange-foodRangePacMan <= getFoodCoordX()) && (y >= getFoodCoordY()-pacFoodRange && y <= getFoodCoordY()+pacFoodRange))|| ((y+pacFoodRange >= getFoodCoordY() && y+pacFoodRange-foodRangePacMan <= getFoodCoordY()) && (x >= getFoodCoordX()-pacFoodRange && x <= getFoodCoordX()+pacFoodRange)) || ((y-pacFoodRange <= getFoodCoordY() && y-pacFoodRange+foodRangePacMan >= getFoodCoordY()) && (x >= getFoodCoordX()-pacFoodRange && x <= getFoodCoordX()+pacFoodRange)) || ((x-pacFoodRange <= getFoodCoordX() && x-pacFoodRange+foodRangePacMan >= getFoodCoordX()) && (y >= getFoodCoordY()-pacFoodRange && y <= getFoodCoordY()+pacFoodRange)))
	{
		pointsInt++ ;
		std::string convertInt = std::to_string(pointsInt) ;
		points = convertInt ;
		do
		{
			if(pointsInt >= 85)
			{
				objectHorizontal = true ;
			}
			else if(pointsInt >= 80)
			{
				foodIsMoving = true ;
				flickerFood = true ;
				objectHorizontal = false ;
			}
			else if(pointsInt >= 70)
			{
				activatePacmanClone = true ;
				showMovingObject = true ;
				objectHorizontal = true ;
			}
			else if(pointsInt >= 50)
			{
				activatePacmanEnemy = true ;
				activatePacmanClone = false ;
				foodIsMoving = false ;
				showMovingObject = false ;
			}
			else if(pointsInt >= 40)
			{
				activatePacmanClone = true ;
				objectHorizontal = false ;
			}
			else if(pointsInt >= 30)
			{
				easyMode = false ;
			}
			else if(pointsInt >= 20)
			{
				showMovingObject = true ;
				if(pointsInt == 20)
				{
					objectColor = 14 ;
				}
			}
			foodX = speed+(speed*((60+(rand() % 640))/speed)), foodY = speed+(speed*((60+(rand() % 480))/speed)) ;
			setFoodCoordX(foodX) ;
			setFoodCoordY(foodY) ;
			std::cout << getFoodCoordX() << " " << getFoodCoordY() ;
		}while(getFoodCoordX() <= 80 || getFoodCoordX() >= 565 || getFoodCoordY() <= 80 || getFoodCoordY() >= 430 || getFoodCoordX() % speed != 0 || getFoodCoordY() % speed != 0) ;
		if(pointsInt % 10 == 0)
		{
			if(speed <= 20)
			{
				speed += 2 ;
			}
				switch(easyMode)
				{
					case true:
						{
							do
							{
								backGroundColor = 1 + (rand()%14) ;
								objectColor = 1 + (rand()%14) ;
							}while(backGroundColor > 14 || (objectColor > 14 || objectColor == backGroundColor)) ;	
							setbkcolor(backGroundColor) ;
						}
						break ;
					case false:
						{
							if(pointsInt == 30)
							{
								playMeme() ;
								foodIsMoving = true ;
								backGroundColor = 0 ;
								pacmanColor = 0 ;
								objectColor = 0 ;
								setbkcolor(backGroundColor) ;
							}
							else
							{
								int color = (1+(rand()%2));
								setbkcolor(colorHardMode.at(color - 1)) ;
								color = (1+(rand()%2));
								objectColor = colorHardMode.at(color - 1);
								color = (1+(rand()%2));
								pacmanColor = colorHardMode.at(color - 1);
								color = (1+(rand()%2));
								cloneColor = colorHardMode.at(color - 1);
								color = (1+(rand()%2));
								cloneColor2 = colorHardMode.at(color - 1);
							}
						}
						break ;
				}
			if(pointsInt >= 10 && pointsInt < 100)
			{
				changeDigits = true ;
			}
			else
			{
				threeDigits = true ;	
			}
			std::cout << "Speed: " << speed << std::endl ;
		}
	}
	if(!foodIsMoving)
	{
		setfillstyle(SOLID_FILL, GREEN) ;
		circle(getFoodCoordX(), getFoodCoordY(), 8) ;
		floodfill(getFoodCoordX(), getFoodCoordY(), 15) ;
	}
	else if(foodIsMoving)
	{
		if(objectHorizontal)
		{
			if(!switchDirection)
			{
				int coord = getFoodCoordX() + speed ;
				setFoodCoordX(coord) ;
			}
			else if(switchDirection)
			{
				int coord = getFoodCoordX() - speed ;
				setFoodCoordX(coord) ;
			}
		}
		else if(!objectHorizontal)
		{
			if(!switchDirection)
			{
				int coord = getFoodCoordY() + speed ;
				setFoodCoordY(coord) ;
			}
			else if(switchDirection)
			{
				int coord = getFoodCoordY() - speed ;
				setFoodCoordY(coord) ;
			}
		}
		setfillstyle(SOLID_FILL, GREEN) ;
		circle(getFoodCoordX(), getFoodCoordY(), 8) ;
		floodfill(getFoodCoordX(), getFoodCoordY(), 15) ;
	}
}
void gameOverPacMan(int x, int y, int startAngle, int endAngle)
{
	int currentScore = std::stoi(points) ;
	int currentHighScore = std::stoi(highscore) ;
	SoundOver() ;
	if(currentScore > currentHighScore)
	{
		highscore = points ;
		std::ofstream del ;
		del.open("pacmanhighscore.txt", std::ofstream::out | std::ofstream::trunc) ;
		del.close() ;
		outputHighscore << highscore ;
		outputHighscore.close() ;
	}
	for(int limit = angleRange ; startAngle <= limit && endAngle >= angleRange; startAngle += 5, endAngle -= 5)
	{
		setactivepage(page) ;
		setvisualpage(1-page) ;
		cleardevice() ;
		setfillstyle(SOLID_FILL, YELLOW) ;
		pieslice(x, y, startAngle, endAngle, radius) ;
		usleep(50000) ;
		page = 1 - page ;
	}
	do
	{
		setactivepage(page) ;
		setvisualpage(1 - page) ;
		cleardevice() ;
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 5) ;
		outtextxy(50, 50, "SCORE: ") ;
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 5) ;
		outtextxy(310, 50, const_cast<char *>(points.c_str())) ;
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 5) ;
		outtextxy(50, 100, "HIGHSCORE: " ) ;
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 5) ;
		outtextxy(450, 100, const_cast<char *>(highscore.c_str())) ;
		page = 1 - page ;
	}while(!GetAsyncKeyState(VK_RETURN)) ;
}
void pointSystem()
{
	if(!changeDigits)
	{
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 10) ;
		outtextxy(280, 35, const_cast<char *>(points.c_str())) ;
	}
	else if(changeDigits)
	{
		if(threeDigits)
		{
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 10) ;
			outtextxy(225, 35, const_cast<char *>(points.c_str())) ;
		}
		else
		{
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 10) ;
			outtextxy(255, 35, const_cast<char *>(points.c_str())) ;
		}
	}
}
void movingObjects(int object1First)
{
	if(objectHorizontal)
	{
		setfillstyle(SOLID_FILL, objectColor) ;
		rectangle(0, 20, object1First, 455) ;
		floodfill(5, 50, 15) ;
		setfillstyle(SOLID_FILL, objectColor) ;
		rectangle(object1First+100, 20, 640 , 455) ;
		floodfill(639, 50, 15) ;
	}
	else if(!objectHorizontal)
	{
		setfillstyle(SOLID_FILL, objectColor) ;
		rectangle(30, 0, 610, object1First) ;
		floodfill(300, 5, 15) ;
		setfillstyle(SOLID_FILL, objectColor) ;
		rectangle(30, object1First+100, 610 , 650) ;
		floodfill(300, 454, 15) ;
	}
}
void identifyDirection(int object1First)
{
	switch(objectHorizontal)
	{
		case true: 
		{
			if((object1First >= 510) && !switchDirection)
			{
				switchDirection = true ;
			}
			else if(switchDirection)
			{
				if(object1First <= 20)
				{	
					switchDirection = false ;
				}	
			}
		}
		break ;
		case false: 
		{
			if((object1First >= 320) && !switchDirection)
			{
				switchDirection = true ;
			}
			else if(switchDirection)
			{
				if(object1First <= 20)
				{	
					switchDirection = false ;
				}	
			}
		}
		break ;
	}
}
void mainMenu()
{
	int startAngle = 60, endAngle = 300, startAngleLimit = 8, endAngleLimit = 352 ;
	bool switchMouth = false, option1 = true, option2 = false ;
	do
	{
		if(GetAsyncKeyState(VK_UP))
		{
			option1 = true ;
			option2 = false ;
		}
		else if(GetAsyncKeyState(VK_DOWN))
		{
			option2 = true ;
			option1 = false ;
		}
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 3) ;
		outtextxy(300, 20, const_cast<char *>(highscore.c_str())) ;
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 3) ;
		outtextxy(40, 20, "HIGHSCORE: ");
		settextstyle(BOLD_FONT, HORIZ_DIR, 5) ;
		outtextxy(200, 200, "PA  - BUDDY") ;
		setfillstyle(SOLID_FILL, YELLOW) ;
		pieslice(280, 220, startAngle, endAngle, 20) ;
		settextstyle(BOLD_FONT, HORIZ_DIR, 5) ;
		outtextxy(200, 270, "START") ;
		settextstyle(BOLD_FONT, HORIZ_DIR, 5) ;
		outtextxy(200, 330, "EXIT") ;
		hoverMainMenu(option1, option2, startAngle, endAngle) ;
		if((startAngle <= 60 || endAngle >= 300) && !switchMouth)
		{
			startAngle -= frameSpeed ;
			endAngle += frameSpeed ;
			usleep(50000) ;
			if(startAngle <= 8 ||endAngle >= 352)
			{
				switchMouth = true ;
			}
		}
		else if(switchMouth)
		{
			startAngle += frameSpeed ;
			endAngle -= frameSpeed ;
			usleep(50000) ;
			if(startAngle >= 60 || endAngle <= 300)
			{
				switchMouth = false ;
			}
		}
		cleardevice() ;
	}while(!GetAsyncKeyState(VK_RETURN)) ;
	SoundEat() ;
	if(option1)
	{
		loading() ;
	}
	else if(option2)
	{
		exit(0) ;
	}
}
void loading()
{
	int startLoadingX = 130, endLoadingX = 460, pacManX = 125, pacManY = 280, startAngle = 60, endAngle = 300, radius = 30;
    for(int i=0;i<endLoadingX-startLoadingX;i++)
	{
    	setfillstyle(SOLID_FILL, YELLOW) ;
		pieslice(pacManX, pacManY, startAngle, endAngle, radius) ;
    	setcolor(WHITE);
    	rectangle(startLoadingX,270,endLoadingX,290);
    	setcolor(GREEN);
    	setfillstyle(SOLID_FILL, GREEN) ;
    	rectangle(startLoadingX+1, 271, startLoadingX+2+i, 289);
    	delay(10);
	}
	std::cout<< startLoadingX ;
	while(pacManX <= endLoadingX - 20)
	{
		while(startAngle >= 1 || endAngle <= 359)
		{
			cleardevice() ;
			setfillstyle(SOLID_FILL, GREEN) ;
			setcolor(WHITE) ;
    		rectangle(startLoadingX,270,endLoadingX,290);
    		floodfill(endLoadingX-1,280,WHITE) ;
    		setfillstyle(SOLID_FILL, YELLOW) ;
			pieslice(pacManX, pacManY, startAngle, endAngle, radius) ;
    		usleep(15000) ;
			startAngle -= frameSpeed ;
			endAngle += frameSpeed ;
			pacManX += speed ;
			startLoadingX += speed ;
		}
		while(startAngle <= 60 || endAngle >= 300)
		{
			cleardevice() ;
    		setfillstyle(SOLID_FILL, GREEN) ;
    		setcolor(WHITE) ;
    		rectangle(startLoadingX,270,endLoadingX,290);
    		floodfill(endLoadingX-1,280,WHITE) ;
    		setfillstyle(SOLID_FILL, YELLOW) ;
			pieslice(pacManX, pacManY, startAngle, endAngle, radius) ;
    		usleep(15000) ;
			startAngle += frameSpeed ;
			endAngle -= frameSpeed ;
			pacManX += speed ;
			startLoadingX += speed ;
		}
	}
	cleardevice();
}
void hoverMainMenu(bool option1, bool option2, int startAngle, int endAngle)
{
	if(option1)
	{
		pieslice(170, 290, startAngle, endAngle, 20) ;
	}
	else if(option2)
	{
		pieslice(170, 350, startAngle, endAngle, 20) ;
	}
}
void pacmanClone(int x, int y, int startAngle, int endAngle) 
{
	int number = std::stoi(points) ;
	setfillstyle(SOLID_FILL, cloneColor) ;
	pieslice(x-60, y, startAngle, endAngle, radius) ;
	pieslice(x, y-60, startAngle, endAngle, radius) ;
	pieslice(x+60, y, startAngle, endAngle, radius) ;
	pieslice(x, y+60, startAngle, endAngle, radius) ;
	if(number >= 80)
	{
		setfillstyle(SOLID_FILL, cloneColor2) ;
		pieslice(x-60, y+60, startAngle, endAngle, radius) ;
		pieslice(x-60, y-60, startAngle, endAngle, radius) ;
		pieslice(x+60, y-60, startAngle, endAngle, radius) ;
		pieslice(x+60, y+60, startAngle, endAngle, radius) ;
	}
}
void drawPacmanEnemy(int x, int y)
{
	srand(time(NULL)) ;
	std::string direction[4] = {"right", "left", "up", "down"} ;
	int enemySpawn, enemyColor ;
	if((enemyCoordX == x && enemyCoordY == y) || ((enemyCoordX+enemyRangeX >= x && enemyCoordX <= x) && (enemyCoordY+enemyRangeY >= y && enemyCoordY-enemyRangeY <= y)) || ((enemyCoordX-enemyRangeY <= x && enemyCoordX+enemyRangeY >= x) && (enemyCoordY+enemyRangeX >= y && enemyCoordY <= y)) || ((enemyCoordX-enemyRangeX <= x && enemyCoordX >= x) && (enemyCoordY+enemyRangeY >= y && enemyCoordY-enemyRangeY <= y)) || ((enemyCoordX-enemyRangeY <= x && enemyCoordX+enemyRangeY >= x) && (enemyCoordY-enemyRangeX <= y && enemyCoordY >= y)))
	{
		setGameOver = true ;
	}
	else if(enemyGenerate)
	{
		do
		{
	
			int coordEnemyX = (132+(rand()%478)) ;
			int coordEnemyY = (126+(rand()%358)) ;
			enemyColor = (1+(rand()%3));
			pacmanEnemyColor = colorEnemy.at(enemyColor - 1) ;
			enemySpawn = rand() % 3 ;
			enemyCoordX = coordEnemyX ;
			enemyCoordY = coordEnemyY ;
		}while(enemyCoordX > 478 || enemyCoordX < 132 || enemyCoordY > 358 || enemyCoordY < 126 || enemySpawn > 3 || enemyColor > 3) ;
		if(direction[enemySpawn] == "right") 
		{
			enemyCoordX = 665 ;
			int fromRightStart = 240, fromRightEnd = 480 ;
			setfillstyle(SOLID_FILL, pacmanEnemyColor) ;
			pieslice(enemyCoordX, enemyCoordY, fromRightStart, fromRightEnd, enemyRadius) ;
			enemyStartAngle = fromRightStart ;
			enemyEndAngle = fromRightEnd ;
			spawnRight = true ;
			enemyGenerate = false ;
		}
		else if(direction[enemySpawn] == "left")
		{
			enemyCoordX = -50 ;
			int fromLeftStart = 60, fromLeftEnd = 300 ;
			setfillstyle(SOLID_FILL, pacmanEnemyColor) ;
			pieslice(enemyCoordX, enemyCoordY, fromLeftStart, fromLeftEnd, enemyRadius) ;
			enemyStartAngle = fromLeftStart ;
			enemyEndAngle = fromLeftEnd ;
			spawnLeft = true ;
			enemyGenerate = false ;
		}
		else if(direction[enemySpawn] == "up")
		{
			enemyCoordY = -70 ;
			int fromUpStart = 330, fromUpEnd = 570 ;
			setfillstyle(SOLID_FILL, pacmanEnemyColor) ;
			pieslice(enemyCoordX, enemyCoordY, fromUpStart, fromUpEnd, enemyRadius) ;
			enemyStartAngle = fromUpStart ;
			enemyEndAngle = fromUpEnd ;
			spawnUp = true ;
			enemyGenerate = false ;
		}
		else if(direction[enemySpawn] == "down")
		{
			enemyCoordY = 650 ;
			int fromDownStart = 150, fromDownEnd = 390 ;
			setfillstyle(SOLID_FILL, pacmanEnemyColor) ;
			pieslice(enemyCoordX, enemyCoordY, fromDownStart, fromDownEnd, enemyRadius) ;
			enemyStartAngle = fromDownStart ;
			enemyEndAngle = fromDownEnd ;
			spawnDown = true ;
			enemyGenerate = false ;
		}
	}
	else if(!enemyGenerate)
	{
		 if(spawnRight)
		{
			if(enemyCoordX >= -200)
			{
				setfillstyle(SOLID_FILL, pacmanEnemyColor) ;
				pieslice(enemyCoordX, enemyCoordY, enemyStartAngle, enemyEndAngle, enemyRadius) ;
				std::cout << "STARTANGLE: " << enemyStartAngle << " ENDANGLE: " << enemyEndAngle << std::endl ;
				switch(mouthRight)
				{
					case true:
						{
							enemyStartAngle -= frameSpeed ;
							enemyEndAngle += frameSpeed ;
							if(enemyStartAngle <= 188 || enemyEndAngle >= 532)
							{
								mouthRight = false ;
							}
						}
						break ;
					case false:
						{
							enemyStartAngle += frameSpeed ;
							enemyEndAngle -= frameSpeed ;
							if(enemyStartAngle >= 240 || enemyEndAngle <= 480)
							{
								mouthRight = true ;
							}
						}
						break ;
				}
				enemyCoordX -= (speed-2)/2 ;
			}
			else
			{
				spawnRight = false ;
				mouthRight = true ;
				enemyGenerate = true ; 
			}
		}
		else if(spawnUp)
		{
			if(enemyCoordY <= 600)
			{
				setfillstyle(SOLID_FILL, pacmanEnemyColor) ;
				pieslice(enemyCoordX, enemyCoordY, enemyStartAngle, enemyEndAngle, enemyRadius) ;
				std::cout << "STARTANGLE: " << enemyStartAngle << " ENDANGLE: " << enemyEndAngle << std::endl ;
				switch(mouthUp)
				{
					case true:
						{
							enemyStartAngle -= frameSpeed ;
							enemyEndAngle += frameSpeed ;
							if(enemyStartAngle <= 278 || enemyEndAngle >= 622)
							{
								mouthUp = false ;
							}
						}
						break ;
					case false:
						{
							enemyStartAngle += frameSpeed ;
							enemyEndAngle -= frameSpeed ;
							if(enemyStartAngle >= 330 || enemyEndAngle <= 570)
							{
								mouthUp = true ;								
							}
						break ;
					}
				}
				enemyCoordY += (speed-2)/2 ;
			}
			else
			{
				spawnUp = false ;
				mouthUp = true ;
				enemyGenerate = true ; 
			}
		}
		else if(spawnLeft)
		{
			if(enemyCoordX <= 800)
			{
				setfillstyle(SOLID_FILL, pacmanEnemyColor) ;
				pieslice(enemyCoordX, enemyCoordY, enemyStartAngle, enemyEndAngle, enemyRadius) ;
				std::cout << "STARTANGLE: " << enemyStartAngle << " ENDANGLE: " << enemyEndAngle << std::endl ;
				switch(mouthLeft)
				{
					case true:
						{
							enemyStartAngle -= frameSpeed ;
							enemyEndAngle += frameSpeed ;
							if(enemyStartAngle <= 8 || enemyEndAngle >= 352)
							{
								mouthLeft = false ;
							}
						}
						break ;
					case false:
						{
							enemyStartAngle += frameSpeed ;
							enemyEndAngle -= frameSpeed ;
							if(enemyStartAngle >= 60 || enemyEndAngle <= 300)
							{
								mouthLeft = true ;								}
							}
						break ;
				}
				enemyCoordX += (speed-2)/2 ;
			}
			else
			{
				spawnLeft = false ;
				mouthLeft = true ;
				enemyGenerate = true ; 
			}
		}
		if(spawnDown)
		{
			if(enemyCoordY >= -200)
			{
				setfillstyle(SOLID_FILL, pacmanEnemyColor) ;
				pieslice(enemyCoordX, enemyCoordY, enemyStartAngle, enemyEndAngle, enemyRadius) ;
				std::cout << "STARTANGLE: " << enemyStartAngle << " ENDANGLE: " << enemyEndAngle << std::endl ;
				switch(mouthUp)
				{
					case true:
						{
							enemyStartAngle -= frameSpeed ;
							enemyEndAngle += frameSpeed ;
							if(enemyStartAngle <= 98 || enemyEndAngle >= 442)
							{
								mouthUp = false ;
							}
						}
						break ;
					case false:
						{
							enemyStartAngle += frameSpeed ;
							enemyEndAngle -= frameSpeed ;
							if(enemyStartAngle >= 150 || enemyEndAngle <= 390)
							{
								mouthUp = true ;
							}
						}
						break ;
				}
				enemyCoordY -= (speed-2)/2 ;
			}
			else
			{
				spawnDown = false ;
				mouthDown = true ;
				enemyGenerate = true ; 
			}
		}
	}

}

void setFoodCoordX(int foodX)
{
	foodCoordX = foodX ;
}
void setFoodCoordY(int foodY)
{
	foodCoordY = foodY ;
}
int getFoodCoordX()
{
	return foodCoordX ;
}
int getFoodCoordY()
{
	return foodCoordY ;
}
void startPacMan()
{
	SoundStart() ;
	do
	{
		setfillstyle(SOLID_FILL, YELLOW) ;
		pieslice(200, 200, 60, 300, 30) ;
		floodfill(200, 200, 15) ;
	}while(!GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT)) ;
}
void SoundGame()
{
	PlaySound(TEXT("PACMAN_NYAM.wav"), NULL, SND_LOOP | SND_ASYNC);

}
void SoundStart()
{
	PlaySound(TEXT("PACMAN START.wav"), NULL, SND_ASYNC);
}
void SoundOver()
{
	PlaySound(TEXT("PACMAN DEATH.wav"), NULL, SND_ASYNC);
}
void SoundEat()
{
	PlaySound(TEXT("PACMAN_EAT.wav"), NULL, SND_ASYNC);
}
void playMeme()
{
	PlaySound(TEXT("nani.wav"), NULL, SND_SYNC);
}



