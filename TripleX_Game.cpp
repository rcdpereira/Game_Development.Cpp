#include <iostream>
#include <ctime>
#include <windows.h>

// Text output as if it was being FAST typed
void Type_Text(const std::string& Text)
{
	// Loop through each character in the text
	for (std::size_t i = 0; i < Text.size(); ++i)
	{
		// Output one character
		// Flush to make sure the output is not delayed
		std::cout << Text[i] << std::flush;
		
		// Sleep
		Sleep(40);
	}
}

// Text output as if it was being SLOW typed
void Type_Count(const std::string& Text)
{
	// Loop through each character in the text
	for (std::size_t i = 0; i < Text.size(); ++i)
	{
		// Output one character
		// Flush to make sure the output is not delayed
		std::cout << Text[i] << std::flush;
		
		// Sleep
		Sleep(600);
	}
}

void GameIntro(int Bombs, int Strikes)
{
    std::cout << "\n" <<
    "  __  __           _                 ______________       ____________        \n" <<
    " |  \\/  | __ _ ___| |_ ___ _ __     |  _     _  _  |     (__((__((___()      \n" <<
    " | |\\/| |/ _` / __| __/ _ \\ '__|    | | | o | | _| |----(__((__((___()()    \n" <<
    " | |  | | (_| \\__ \\ ||  __/ |       | |_| o |_| _| |---(__((__((___()()()   \n" <<
    " |_|  |_|\\__,_|___/\\__\\___|_|       |______________|  (__((__((___()()()() \n" <<
    "    _          _   _       ____                  _                            \n" <<
    "   / \\   _ __ | |_(_)     | __ )  ___  _ __ ___ | |__   ___ _ __             \n" <<
    "  / _ \\ | '_ \\| __| |_____|  _ \\ / _ \\| '_ ` _ \\| '_ \\ / _ \\ '__|      \n" <<
    " / ___ \\| | | | |_| |_____| |_) | (_) | | | | | | |_) |  __/ |               \n" <<
    "/_/   \\_\\_| |_|\\__|_|     |____/ \\___/|_| |_| |_|_.__/ \\___|_|           \n" <<
    "\nTo become a Master Anti-Bomber you have to deactivate " << Bombs << " bombs.\n" <<
    "You only have " << Strikes << " strikes total, otherwise you'll explode.      \n" <<
    "GOOD LUCK!!!\n";                 
}

void GameOrientation(int Difficulty, int MaxLevel)
{
    // Print welcome messages to the terminal
    if (Difficulty <= MaxLevel)
    {
        std::cout << "\nAnti-Bomber, you have to deactivate bomb number ";
        std::cout << Difficulty;
        std::cout << ".\nEnter the correct codes to prevent an explosion!\n";
    }
}

bool PlayGame(int Difficulty, int MaxLevel)
{
    GameOrientation(Difficulty, MaxLevel);

    // Declare 3 number code
    const int CodeA {rand() % Difficulty + Difficulty};
    const int CodeB {rand() % Difficulty + Difficulty};
    const int CodeC {rand() % Difficulty + Difficulty};

    const int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProd = CodeA * CodeB * CodeC;

    // Print sum and product to the terminal
    std::cout << "\n-There are 3 numbers in the code.";
    std::cout << "\n-The sum of the numbers is: " << CodeSum;
    std::cout << "\n-The product of the numbers is: " << CodeProd;

    // Store players inputs
    int GuessA, GuessB, GuessC;
    // Guide playability
    std::cout << "\n\nInput the codes separated by a space and press enter at the end.\n";
    std::cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProd = GuessA * GuessB * GuessC;

    // Check if the players guess is correct
    if (GuessSum == CodeSum && GuessProd == CodeProd)
    {
        if (Difficulty < MaxLevel)
        {
            Type_Text("\n*** Bomb deactivated. Move on to the next bomb. ***\n");
        }              
        return true;
    }
    else
    {
        return false;
    }
}

void StrikeWarning (int Strike, int MaxStrike)
{
    if (Strike == 1)
    {
        Type_Text("\nYou have 1 strike. Try again!\n");
    }
    else if (Strike == MaxStrike)
    {
        Type_Text("\nYou've used your last strike. DO NOT MISS AGAIN!\n");
    }
    else if (Strike > MaxStrike)
    {
        Type_Text("\nNo more chances...\n");
    }
    else
    {
        Type_Text("\nYou have ");
        std::cout << Strike;
        Type_Text(" strikes. Try again!\n");
    }
}

void WinGame()
{
    // Print game closing message
    Type_Text("\n*** All bombs deactivated successfully. ***\n");
    Type_Text("\n*** CONGRATULATIONS! YOU ARE A MASTER ANTI-BOMBER! ***.\n");
}

void GameOver()
{
    Type_Text("\nExploding in ");
    Type_Count("3 2 1\n");
    std::cout <<    
    "        --_--        \n" <<
    "     (  -_    _).    ########    #######    #######   ##     ## \n" <<
    "   ( ~       )   )   ##     ##  ##     ##  ##     ##  ###   ### \n" <<
    " (( )  (    )  ()  ) ##     ##  ##     ##  ##     ##  #### #### \n" <<
    "  (.   )) (       )  ########   ##     ##  ##     ##  ## ### ## \n" <<
    "    ``..     ..``    ##     ##  ##     ##  ##     ##  ##     ## \n" <<
    "         | |         ##     ##  ##     ##  ##     ##  ##     ## \n" <<
    "       (=| |=)       ########    #######    #######   ##     ## \n" <<
    "         | |         \n" <<
    "     (../( )\\.))    \n";
    Type_Text("\n!!! G A M E  O V E R !!!\n");
}

void StartGame(); // Forward declaration

void PlayAgain()
{
    std::cout << "\nDo you want to play again? [y/n]";
    char Replay{'n'};
    std::cin >> Replay;
    if (Replay == 'y')
    {
        StartGame();
    }
}

void StartGame() // Define the max levels and max strikes here
{
    int Strike{0};
    constexpr int MaxStrike{2};
    int Level{1};
    constexpr int MaxLevel{5};

    GameIntro(MaxLevel, MaxStrike);

    // Loop the game until all levels completed or total strikes reached
    while  (Level <= MaxLevel && Strike <= MaxStrike) 
    {
        bool bLevelComplete{PlayGame(Level, MaxLevel)};
        std::cin.clear();
        std::cin.ignore();

        if (bLevelComplete)
        {
            ++Level;   
        }
        else
        {
            ++Strike;
            StrikeWarning(Strike, MaxStrike);
        }
    }
    if (Level > MaxLevel)
    {
        WinGame();
        PlayAgain();
    }
    else if (Strike > MaxStrike)
    {
        GameOver();
        PlayAgain();
    }
}

int main()
{
    srand(time(NULL)); // create new random sequence based on time of day
    
    StartGame();    

    return 0;
}
