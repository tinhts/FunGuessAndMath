#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

/* ----------------NEW-----------------------------
Global variables declaration
These variables are hard coded but can be set by command arguments or from config file
-------------------------------------------------*/
int min_guess_num = 0;	// Lower limit of guess number
int max_guess_num = 50; // Upper limit of guess number
int max_guess_times = 5; // Max times to try
int prime_divisors = 3;   // 
//

// This is hard coded to false but can change from command line or config file. If true, debug outputs will be to log file
bool log_on = false; 
ofstream log_file;
char log_file_name[] = "log.txt";

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

/* This same as cin but also checks to make sure the input is an integer only. It also accepts a string to display to user. So the class can be reused
*/
int input_integer(char passed_message[])
{
	int num;
	do
	{
			cout << passed_message;
			cin >> num;
			if(!cin.fail()) {
				return num;
			}
			cin.clear(); // This corrects the stream.
			cin.ignore(999,'\n' ); // This skips the left over stream data.
	}
	while (!cin.fail());
}

/* This take an array of found prime divisors and display them*/
void display_X(int *array, int length)
{
	for (int i = 0; i <= length-1; i++)
	{
		if (i==prime_divisors-1)
		{
			cout << array[i] << "\n";
		} else 
			cout << array[i] << " X ";
	}
}

/* --------------------------------------------------------------------------------------------------------------------------------------------------------
The games that let user do their math to find the X number, input it, and the function will copare with the found X number returned from find_x() function
	Input: Secret number  is an interger 
	Return: Found X number. Is a multiple of 2 prime numbers
---------------------------------------------------------------------------------------------------------------------------------------------*/
long int x_game(int secret)
{
	// User Input block
	int user_num;
	cout << "Think of an X number that is the closet bigger than the secret number and is a product of " << prime_divisors << " prime factors \n";
	cout << "Prove your best math, put in the X NUMBER" << endl;
	char input_message[] = "INTERGER ONLY please: ";
    user_num = input_integer(input_message);
	
	// Find X number block
	int X = secret + 1;									// Increase X to 1 since the X number must be greater than the secret number
	int count, X_num, X_array[20];			// X_array to store found divisors
	bool not_found=true;
	do 
	{
		count = 0;	
		X_num = 1;
		if (log_file.is_open()) log_file << "Secret Num = " << X << ":\n";
		// This For loop finds all primes who are sub-divisions of X. With each found it will count 1 and also muultiplies the founds together to accumulate X_num
		int i = 2;
		int tmp = X;
		do
		{
			if (is_prime(i) && tmp % i == 0) 
			{
				X_array[count] = i;
				count++;
				X_num = X_num*i;
				while (tmp%i == 0)
				{
					tmp = tmp/i;
					//if (log_file.is_open()) log_file << "Devisor = " << i << " | count = "<< count << " | X_num = " << X_num << " | tmp = " << tmp << endl;
				};
				if (log_file.is_open()) log_file << "Devisor = " << i << " | count = "<< count << " | X_num = " << X_num << " | tmp = " << tmp << endl;
			} else
			{
				if (log_file.is_open()) log_file << "Devisor = " << i << " | count = "<< count << " | X_num = " << X_num << " | tmp = " << tmp << endl;
			}
			i++;
		} while (tmp!=1);
		
		// This IF checks for conditions to exit the while loop. It will set not_found to false if found 2 primes & X_num == X. Otherwise, X is increase 1 and the DO-WHILE continues
		if (count==prime_divisors && X_num == X) 
		{ 
			not_found = false;
		} else {
			X++;
		}	
	}
	while (not_found); 
	if (log_file.is_open()) log_file << "DONE!!! - X_num = " << X_num << " " << "count = " << count << "X = " << X << "\n";
	//X number already found and stored in X_num
	
	// Compare the found X_num with user input
	if (user_num != X_num)
	{
		cout << "Wrong MATH !!!! Correct X number is: " << X_num << "\n" << "Which is equal to: ";
		display_X(X_array, prime_divisors);
	}
	else
	{
		cout << "Best MATH !!! You've found X number: " << X_num << "\n" << "Which is equal to: ";
		display_X(X_array, prime_divisors);
	}
}

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
This is the body of the 1st game. Allow user to guess the secret number. X is the secret number passed to the function. guess_num is internal variable, only for users to put in guessed numbers
This function return TRUE if the guess is correct, otherwise returns false
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void guess_game()
{
	cout << "Let's play a game shall we? \n";
    cout << "Now I'll choose a cecret number. You are NOT allowed to see my screen.\n";
    cout << "I'll input the secret number. Enter 0 and the number will be choosen randomly" << endl;
    char input_message[] = "Please input an integer ONLY: ";
    int secret_overide = 0;
    secret_overide = input_integer(input_message);
    if (secret_overide != 0)
    	secret_num = secret_overide;
    else 
	{
		srand(time(0));
		secret_num = rand() % max_guess_num + 0;
	}

    cout << "You'll need to guess a number from " << min_guess_num << " to " << max_guess_num << "\n";
    cout << "You will have " << max_guess_times << " tries to guess\n"; 
	char input_message_1[] = "Input an integer ONLY, please: ";	 
    int guess_num, tries=0;
    bool correct_guess = 0;
    // 3 times guess. If the guess is correct before 3 times. the loop will break and return true to correct_guess
	do 
	{
        //cout << "Please guess: ";    	
        //cin >> guess_num;
        guess_num = input_integer(input_message_1); // Call to make sure a valid integer is provided
       	tries++;
        if (guess_num < secret_num)	
        	cout << "Your guess is less, than the secret number. Try again.\n";
        else if (guess_num > secret_num)
        	cout << "Your guess is more than the secret number. Try again.\n";
        else
        {		
            //return true;
			correct_guess = true;									// The return will break the function
            break;
    	}
    }
	while (tries < max_guess_times);
	// Check if the guess is correct or NOT
	if (correct_guess)
	{
		cout << "You have proven to be a GUESS MASTER.\n";
	} else cout << "\nYou failed after " << max_guess_times << " times." << endl;
		
	cout << "The secret number is: " << secret_num << "\n";
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
	if (argc==6)				// For now, just simple check if number of arguments are 6 than get arguments from command line
	{
		min_guess_num = atoi(argv[1]);
		max_guess_num = atoi(argv[2]);
		max_guess_times = atoi(argv[3]);
		prime_divisors = atoi(argv[4]);
		log_on = atoi(argv[5]);
	} else if (argc!=1)
	{
		cout << "FunGuess accepts no arguments or 5 arguments only !!";
		return 0;
	}

	// Check if log mode is on
	if (log_on) 
	{
		log_file.open(log_file_name);
		log_file << "Log Mode is ON. Logging to file..." << endl;
	}
	
    // 1st Game
    guess_game();
	cout << "Now, move on to the next game shall we? \n\n";
	
	// 2nd Game
	x_game(secret_num);
	
	if (log_file.is_open())
	{
		log_file.close();
	}
	// This to pause the console and let user to see things. 
	//Without this the console will exist if program is launched directly, not from a parent console
	system("PAUSE");	
	return 0;
}
