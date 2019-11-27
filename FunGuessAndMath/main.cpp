#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;
int number, guess;

bool is_Prime(int X)
{
	if (X == 0 || X == 1)
	
		return false;
		
	for (int i = 2; i <= X / 2; i++)
	
		if (X % i == 0)
		
			return false;
			
	return true;	
}

bool check_divisor(int X)
{
	int a;
	
	 for (int i = 2; i <= X / 2; i++)
	 
		if (X % i == 0)
		{
				a = X/i; 			
				
			if (is_Prime(a) == true && is_Prime(i) == true && a != i)
			
				return true;	 
		}
	return false;
}

int the_X(int number)
{
	if (check_divisor(number) == true)
		
		return number;
			
	else
		
		return the_X(number + 1);
}

void guessing_game(int guess)
	{
		int count, tries = 0;
		
		do 
			{
        	cout << "Enter your estimate: ";
        	
        	cin >> guess;
        	
       		tries++;
       		
        	if (guess < number)
        	
            cout << "Your estimate is less, than the secret number \n\n";
            
        	else if (guess > number)
        	
            cout << "Your estimate is more, than the secret number \n\n";
            
        	else
        		{	
        	
            		cout << "Your guess is correct! ^w^ \n\n";
            		
            		cout << "Now on to the next game shall we? \n\n";
            		
            		cout << "Think of an X that is bigger than the the one you've found but also the smallest one \n\n";
            		
            		cout << "That only have 2 divisors is prime also \n\n";
            		
            		cout << "What number is  X?  ";
            		
					int X;
					
            		cin >> X;
			
					if(X == the_X(number + 1))
						
						cout << "Congratulation you are the Numbers Master! ^w^";
						
					else
					{
						cout << "Your X is incorrect! You Lose! TwT" << endl;
						
						cout << "The correct number is: " << the_X(number + 1);
					}
    			}
    		}
		while (guess != number && tries < 3);
		
		if (guess != number)
			{
		
				cout << "You lose! TwT" << endl;
				
				cout << "The correct number is: " << number;
			}
	}	
	
int main() 
{
	
    srand(time(0));
	  
    number = rand() % 21;
    
    cout << "Let's play a game shall we? \n\n";
    
    cout << "I'll think of a number from 0 to 20 \n\n";
    
    cout << "You will have 3 tries to guess \n\n";
    
    guessing_game(guess);

}

