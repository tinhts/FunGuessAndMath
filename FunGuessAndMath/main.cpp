#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

/* ------------------------------------------------
Global variables declaration
These variables are hard coded but can be set by command arguments or from config file
-------------------------------------------------*/
int min_guess_num = 0;	// Lower limit of guess number
int max_guess_num = 50; // Upper limit of guess number
int max_guess_times = 5; // Max times to try
int prime_divisors = 3;   // 
//
//int X_array[prime_divisors];			// Array to store found devisors
int X_array[10];			// Array to store found devisors

bool debug_mode = false; // This is hard coded to false but can change from command line or config file. If true, debug outputs will be to log file

// --- The secret number
int secret_num;



/* ------------------------------------------------
Check to see if $ARG is a Prime number
	Input: An Interger
	Return: TRUE if the number is a Prime number
-------------------------------------------------*/
bool is_prime(int X)
{
	if (X == 0 || X == 1)
		return false;
	for (int i = 2; i <= X / 2; i++)
		if (X % i == 0)
			return false;
	return true;
}

/* ----------------------------------------------------------
Find X number
	Input: Secret number is an interger 
	Return: Found X number. Is a multiple of 2 prime numbers
-----------------------------------------------------------*/
long int find_x(int X)
{
	int count;
	int X_num;
	bool not_found=true;
	do 
	{
		count = 0;	
		X_num = 1;
		// Uncommented below line for debuding purpose: 
		//cout << "Secret Num = " << X << ":\n";
		// This For loop finds all primes who are sub-divisions of X. With each found it will count 1 and also muultiplies the founds together to accumulate X_num
		for (int i = 2; i < X; i++)
		{
			if (is_prime(i) && X % i == 0)
			{
				X_array[count] = i;
				count++;
				X_num = X_num*i;	
				// Uncommented below line for debuding purpose: 
				//cout << "Devisor = " << i << " | count = "<< count << " | X_num = " << X_num << "\n";
				
			} else
			{
				// Uncommented below line for debuding purpose: 
				//cout << "Devisor = " << i << " | count = "<< count << " | X_num = " << X_num << "\n";
			}
		}
		// This IF checks for conditions to exit the while loop. It will set not_found to false if found 2 primes & X_num == X. Otherwise, X is increase 1 and the DO-WHILE continues
		if (count==prime_divisors && X_num == X) 
		{ 
			not_found = false;
		} else {
			X++;
		}	
	}
	while (not_found);
	// Uncommented below line for debuding purpose: 
	//cout << "DONE!!! - X_num = " << X_num << " " << "count = " << count << "X = " << X << "\n";
	return X;
}

void display_X()
{
	for (int i = 0; i <= prime_divisors-1; i++)
	{
		if (i==prime_divisors-1)
		{
			cout << X_array[i] << "\n";
		} else 
			cout << X_array[i] << " X ";
	}
}

/* --------------------------------------------------------------------------------------------------------------------------------------------------------
The games that let user do their math to find the X number, input it, and the function will copare with the found X number returned from find_x() function
----------------------------------------------------------------------------------------------------------------------------------------------------------*/
void x_game(int X)
{
	int user_num, x_num;
	cout << "Think of an X number that is the closet bigger than the secret number and is a product of " << prime_divisors << " prime factors \n";
    cout << "Prove your best math. Put in the X NUMBER: ";        		
    cin >> user_num;
    x_num = find_x(X+1); // Call find_x follow the instructions from the project is X must be bigger than secret number
	if (user_num != x_num)
	{
		cout << "Wrong MATH !!!! Correct X number is: " << x_num << "\n" << "Which is equal to: ";
		display_X();
	}
	else
	{
		cout << "Best MATH !!! You've found X number: " << x_num << "\n" << "Which is equal to: ";
		display_X();
	}
	
}

int input_integer()
{
	int num;
	//bool valid = false;
	do
	{
		//valid = true; // Assume the cin will be an integer.
		//cout << "Enter an integer value: ";
		
		//if(cin.fail()) // Checks to see if the value in the cin stream is the correct type, if not it returns true, false otherwise
		//{//
			cout << "Please enter an integer only: ";
			cin >> num;
			if(!cin.fail()) {
				return num;
			}
			cin.clear(); // This corrects the stream.
			cin.ignore(); // This skips the left over stream data.
			//valid = false; // The cin was not an integer so try again
		//}//
		//cout << "You entered: " << str(num) << endl;
		//system("PAUSE");
		//return num;
		
	}
	while (!cin.fail());
	//return num;
}

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
This is the body of the 1st game. Allow user to guess the secret number. X is the secret number passed to the function. guess_num is internal variable, only for users to put in guessed numbers
This function return TRUE if the guess is correct, otherwise returns false
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
bool guess_master()
{
	cout << "Let's play a game shall we? \n";
    cout << "I'll think of a number from " << min_guess_num << " to " << max_guess_num << "\n";
    cout << "You will have " << max_guess_times << " tries to guess \n";
    cout << "Now I'll choose the cecret number. You are NOT allowed to see my screen.\n";
    cout << "Input the secret number. Enter 0 and the number will be choosen randomly: ";
    int secret_overide = 0;
    cin >> secret_overide;
    if (secret_overide != 0)
    	secret_num = secret_overide;
    else 
	{
		srand(time(0));
		secret_num = rand() % max_guess_num + 0;
	}
    
    
    int guess_num, tries=0;
	do 
	{
        //cout << "Please guess: ";    	
        //cin >> guess_num;
        guess_num = input_integer(); // Call to make sure a valid integer is provided
       	tries++;
        if (guess_num < secret_num)	
        	cout << "Your guess is less, than the secret number. Try again.\n";
        else if (guess_num > secret_num)
        	cout << "Your guess is more than the secret number. Try again.\n";
        else
        {		
            return true;									// The return will break the function
    	}
    }
	while (tries < max_guess_times);
	return false;
}	

/* THE FUN GUESS GAME -------------
	This calls guess_master()
*/
void guess_game()
{
	if (guess_master()!=true) 
	{   	
		cout << "\nYou failed after " << max_guess_times << " times." << endl;		
	} else 
	{
		cout << "You have proven to be a GUESS MASTER.\n";
	}		
	cout << "The secret number is: " << secret_num << "\n";
	cout << "Now, move on to the next game shall we? \n\n";	
}

/* ------------------------------------------------
MAIN starts here
-------------------------------------------------*/
int main(int argc, char** argv) 
{    	
	/* --------------------------------------------------------------------------------------------
	Define global variables
	1 Agurment is:  min_guess_num
	2nd agurment is max_guess_num
	3 agurment is max_guess_times
	----------------------------------------------------------------------------------------------*/
	if (argc==5)				// For now, just simple check if number of arguments are 5 than get arguments from command line
	{
		min_guess_num = atoi(argv[1]);
		max_guess_num = atoi(argv[2]);
		max_guess_times = atoi(argv[3]);
		prime_divisors = atoi(argv[4]);
	} else if (argc!=1)
	{
		cout << "FunGuess accepts no arguments or 4 arguments only !!";
		return 0;
	}

    // 1st Game
    guess_game();
    
	// 2nd Game
	x_game(secret_num);
	system("PAUSE");	// This to pause the console and let user to see things. Without this the console will exist if program is launched directly, not from a parent console
	return 0;
}

