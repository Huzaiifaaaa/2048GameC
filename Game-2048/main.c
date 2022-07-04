#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
//including the respective header files

bool CheckPossibleMoves(int grid[4][4]);
bool AuthenticateGrid(int array[4][4], int array2[4][4]);
//function prototype declarations

//main function
//execution starts here
int main()
{
    NEWGAME: ;
	//variable declarations & initializations
	int i;
	int j;
	int k;
	int repeat;
	int temp1=0;
	int temp2=0;
	int score=0;
    int maxNumber=0;
	int grid[4][4];
	int grid2[4][4];
	char input;
	bool gameOverFlag = false;
	bool continueFlag = false;
	bool emptySpace = false;
	bool validInput = false;

	system("cls");
    // displaying startup menu
    printf("\n     Welcome To 2048!!");
    printf("\n\n     Controls:");
    printf("\n\t w:up , s:down , a: left , d:right , n:new game , q:quit");

    printf("\n\n     Press Enter To Start The Game!!");
    getchar();

	//initializing 4*4 array/grid by zero
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
             grid[i][j] = 0;
        }
    }

    srand(time(NULL));//randomizing the seed

    for (k = 0; k < 2; k++)//setting the first two numbers in grid at random position
    {
        do//generating random positions for grid
        {
            i = rand() % 4;
            j = rand() % 4;
        }
        while (i == temp1 && j == temp2);//till i & j are zero

        temp1 = i;
        temp2 = j;
        grid[i][j] = rand() % 100;//placing at random positions i & j, numbers <100

        if (grid[i][j] < 90)//if <90 set it two
        {
            grid[i][j] = 2;
        }
        else//if >90 & <100 set it 4
        {
            grid[i][j] = 4;
        }
    }//end of for loop

    do
    {
        system("cls");

        printf("\n     Welcome To 2048!!");
        printf("\n\n     Controls:");
        printf("\n\t w:up , s:down , a: left , d:right , n:new game , q:quit\n\n");

        printf("\n");
        printf("      Score : %d", score);
        printf("\n\n");

        //printing the game layout here
        printf("     -------------------------------------\n\n");
        for (i = 0; i < 4; i++)
        {
            printf("     |");
            for (j = 0; j < 4; j++)
            {
                if (grid[i][j] != 0)
                {
                    printf(" %4d   |", grid[i][j]);
                }
                else
                {
                    printf(" %4c   |", ' ');
                }
            }
            printf("\n\n");
        }
        printf("     -------------------------------------\n\n");

        if (CheckPossibleMoves(grid) == false)
        {
            printf("\n      Game Over!");
            printf("\n      Your Score : %d", score);
            gameOverFlag = true;
            continueFlag = false;

            printf("\n\n      Press Enter To Continue!");
            getchar();

            do//asking user if he want to play again
            {
                printf("\n      New Game[y/n] : ");
                scanf(" %c", &input);
                while (getchar() != '\n');
            }
            while (input != 'y' && input != 'n');

            if (input == 'n')//if not, exit game
            {
                exit(0);
            }
            else if (input == 'y')//if yes, goto newgame
            {
                goto NEWGAME;
            }

        }

        if (maxNumber == 2048 && continueFlag == false)//if max number is acheived
        {
            printf("\n      You Won!");
            printf("\n      Your Score : %d", score);//printing message & score

            do//asking user if he want to play again
            {
                printf("      New Game[y/n] : ");
                scanf(" %c", &input);
                while (getchar() != '\n');
            }
            while (input != 'y' && input != 'n');

            if (input == 'n')//if not, exit game
            {
                exit(0);
            }
            else if (input == 'y')//if yes, goto newgame
            {
                goto NEWGAME;
            }
        }

        if (gameOverFlag == true)
        {
            break;
        }

		for (i = 0; i < 4; i++)//assigning grid1 values to grid2 for comparison purposes
        {
            for (j = 0; j < 4; j++)
            {
                grid2[i][j] = grid[i][j];//assigning
            }
        }

        validInput = true;
        printf("\n     Input: ");//asking user for input
        scanf(" %c", &input);//getting input
        while (getchar() != '\n');//checking if new line character is entered

        switch (input)//switching wrt to user inputs
        {
            case 'a'://case a, if user enters a
            {
                for (repeat = 1; repeat <= 3; repeat++)
                {
                    for (i = 0; i < 4; i++)//looping through grid
                    {
                        for (j = 0; j < 3; j++)//looping through grid
                        {
                            if (!grid[i][j] && repeat != 2)//if numbers does not match
                            {
                                for (k = j + 1; k < 4; k++)
                                {
                                    if (grid[i][k])
                                    {
                                            grid[i][j] = grid[i][k];
                                            grid[i][k] = 0;
                                            break;
                                    }
                                }
                            }
                            else if (grid[i][j] && grid[i][j] == grid[i][j + 1] && repeat == 2)//if numbers match
                            {
                                grid[i][j] += grid[i][j + 1];
                                score += grid[i][j];
                                if (grid[i][j] > maxNumber)
                                {
                                    maxNumber = grid[i][j];
                                }
                                grid[i][j + 1] = 0;
                            }
                        }//end of for
                    }//end of for
                }//end of for
                break;
            }//end of case

            case 'd'://case d, if user enters d
            {
                for (repeat = 1; repeat <= 3; repeat++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        for (j = 3; j > 0; j--)
                        {
                            if (!grid[i][j] && repeat != 2)//if numbers does not match
                            {
                                for (k = j - 1; k >= 0; k--)
                                {
                                    if (grid[i][k])
                                    {
                                        grid[i][j] = grid[i][k];
                                        grid[i][k] = 0;
                                        break;
                                    }
                                }
                            }
                            else if (grid[i][j] && grid[i][j] == grid[i][j - 1] && repeat == 2) // if numbers match
                            {
                                grid[i][j] += grid[i][j - 1];
                                score += grid[i][j];
                                if (grid[i][j] > maxNumber)
                                {
                                    maxNumber = grid[i][j];
                                }
                                    grid[i][j - 1] = 0;
                            }
                        }//end of for
                    }//end of for
                }//end of for
                break;
            }//end of case

            case 'w'://case w, if user enters w
            {
                for (repeat = 1; repeat <= 3; repeat++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        for (j = 0; j < 3; j++)
                        {
                            if (!grid[j][i] && repeat != 2)//if numbers does not match
                            {
                                for (k = j + 1; k < 4; k++)
                                {
                                    if (grid[k][i])
                                    {
                                        grid[j][i] = grid[k][i];
                                        grid[k][i] = 0;
                                        break;
                                    }
                                }
                            }
                            else if (grid[j][i] && grid[j][i] == grid[j + 1][i] && repeat == 2) // if numbers match
                            {
                                grid[j][i] += grid[j + 1][i];
                                score += grid[j][i];
                                if (grid[j][i] > maxNumber)
                                {
                                    maxNumber = grid[j][i];
                                }
                                grid[j + 1][i] = 0;
                            }
                        }//end of for
                    }//end of for
                }//end of for
            break;
        }//end of case

            case 's'://case s, if user enters s
            {
                for (repeat = 1; repeat <= 3; repeat++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        for (j = 3; j > 0; j--)
                        {
                            if (!grid[j][i] && repeat != 2)//if numbers does not match
                            {
                                for (k = j - 1; k >= 0; k--)
                                {
                                    if (grid[k][i])
                                    {
                                        grid[j][i] = grid[k][i];
                                        grid[k][i] = 0;
                                        break;
                                    }
                                }
                            }
                            else if (grid[j][i] && grid[j][i] == grid[j - 1][i] && repeat == 2) // if numbers match
                            {
                                grid[j][i] += grid[j - 1][i];
                                score += grid[j][i];
                                if (grid[j][i] > maxNumber)
                                {
                                    maxNumber = grid[j][i];
                                }
                                grid[j - 1][i] = 0;
                            }
                        }//end of for
                    }//end of for
                }//end of for
                break;
            }//end of case

            case 'n'://case n, for new game
            {
                do//asking for new game
                {
                    printf("\n     New Game[y/n] : ");
                    scanf(" %c", &input);
                    while (getchar() != '\n');
                }
                while (input != 'y' && input != 'n');

                if (input == 'n')//if not, exit game
                {
                    continue;
                }
                else if (input == 'y')//if yes, goto new game
                {
                    goto NEWGAME;
                }
                break;
            }//end of case

            case 'q'://case q, for quitting game
            {
                do//asking user if he wants to quit
                {
                    printf("\n     Quit Game[y/n] : ");
                    scanf(" %c", &input);
                    while (getchar() != '\n');
                }
                while (input != 'y' && input != 'n');

                if (input == 'n')//if not, exit game continue
                {
                    continue;
                }
                else if (input == 'y')//if yes, exit
                {
                    exit(0);
                }
                break;
            }//end of case

            default://default case
            {
                validInput = false;
                break;
            }//end of case
        }//end of switch block

        emptySpace = false;

        for (i = 0; i < 4; i++)//checking if there is any empty space left
        {
            for (j = 0; j < 4; j++)
            {
                if (!grid[i][j])//if left
                {
                    emptySpace = true;//setting true
                }
            }
        }//end of for

        if (emptySpace == true && AuthenticateGrid(grid, grid2) == true && validInput == true)
        {
            do
            {
                i = rand() % 4;
                j = rand() % 4;
            }
            while(grid[i][j]);

            grid[i][j] = rand() % 100;

            if (grid[i][j] < 80)
            {
                grid[i][j] = 2;
            }
            else
            {
                grid[i][j] = 4;
            }
        }
    }
    while (score != -1);//looping infinite times

	return 0;//returning zero
}//end of main function

//takes array
//return true or false
//checks if there is any move possible
bool CheckPossibleMoves(int grid[4][4])
{
	int i=0;
	int j=0;//variable declarations & initialization

	//checking for empty spaces in grid/array
	for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if(!grid[i][j])//if no empty spaces, return true
            {
                return true;
            }
        }//end of for
    }//end of for

	//checking for possible moves
	for (i = 0; i < 4; i++)//moving along x axis
    {
        for (j = 0; j < 3; j++)//moving along y axis(up to down)
		{
			if (grid[i][j] && grid[i][j] == grid[i][j + 1])
			{
				return true;
			}
			else if (grid[j][i] && grid[j][i] == grid[j + 1][i])
			{
				return true;
			}
		}//end of for
    }//end of for

	//checking for possible moves to up and right to left
	for (i = 0; i < 4; i++)//moving along x axis
    {
		for (j = 3; j > 0; j--)//moving along y axis(down to up)
		{
			if (grid[i][j] && grid[i][j] == grid[i][j - 1])
			{
				return true;
			}
			if (grid[j][i] && grid[j][i] == grid[j - 1][i])
			{
				return true;
			}
		}//end of for
    }//end of for

	return false;//returning
}//end of function

//takes arrays
//returns true or false
//checks authenticity of arrays/grids
bool AuthenticateGrid(int array[4][4], int array2[4][4])
{
	int i=0;
	int j=0;

	for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
		{
		    if (array[i][j] != array2[i][j])
            {
                return true;
            }
		}//end of for
    }//end of for

	return false;//returning
}//end of function
