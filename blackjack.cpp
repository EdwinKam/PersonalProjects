//This program and its content is copy right of Shun Kam © Shun Kam 2019. All right reserved.
#include<iostream>
#include<ctime>
#include<string>
#include<stack>
#include<random>
#include<algorithm>

using namespace std;
//here
const int numset = 2; //how many set of card will be use
double percent = 0.65;//how many cards used before before shuffling
int gamenum = 103; //how many games you want
//function
//function
//function
//function
//function
void shuffle(int*, size_t); //shuffle card function
void create(int*, const int);//poker card generator 
void print(int*, const int);//function that print the the poker deck in order
void printf(string*, const int);//string function that print the the poker deck in order
int aceaction(int);//when player or dealer get ace
int splitaction(int);//when player can split
int paction(int);//player action
int intdis();//distributing card to player and dealer
void play(int);//play function
void dealeraction();//dealer action function
string display(int);
int value(int);//determine the value of the card
int sum(int*);//calculate the sum of hands
void coutcard(int*, string);//display players hand and sum
bool checkace(int*);//see if anyone has ace
void acevalue(int*);//determine ace value
void result();//result function
void dbust(int*);//check if dealer >21 player win count ++
void pbust(int*);//chck if player bomb >21 dealer win count ++
void intialhands(int*);//initialize player hands
bool blackjack(int*, string);//determine if anyone gets blackjack
//function
//function
//function
//string pokerName[1 + totalcard];
//int pokerValue[1 + totalcard];
int cardcount = 1;//distrube card
const int totalcard = numset * 52;
int poker[1 + totalcard];//number of card in play
int shuffnum[totalcard];
int dealer[10] = { 0,0,0,0,0,0,0,0,0,0 };
int player[10] = { 0,0,0,0,0,0,0,0,0,0 };
int player1[10] = { 0,0,0,0,0,0,0,0,0,0 };
int player2[10] = { 0,0,0,0,0,0,0,0,0,0 };
int psum, dsum; //dealer sum player sum
int playerhandcount = 1;
int dealerhandcount = 2;
double playercount = 0;
double dealercount = 0;
double bet;//bet value
int gamecount, positive;//count in intdis()
double playerwin, dealerwin, tie, split, doublerate;



int main()
{
	create(poker, numset);
	//print(poker, numset);
	while (gamecount < gamenum)
	{//loop until desired game amount played
		shuffle(poker, numset);
		print(poker, numset);//print the shuffled deck
		cardcount = 1;
		positive = 0;//initial posivity
		do {
			cout << "===================New Game==================\n";
			cout << "Game " << gamecount + 1 << endl;
			intialhands(player);
			intialhands(dealer);

			if (positive > 3)
			{
				bet = 4;
				cout << "$$$$$$$$$increased bet to $" << bet << endl;
			}
			else if (positive ==3)
			{
				bet = 2;
				cout << "$$$$$$$$$increased bet to $" << bet << endl;
			}
			else
			{
				bet = 1;
				cout << "$$bet is $" << bet << endl;
			}
			player[0] = intdis();//disturbiting cards
			player[1] = intdis();
			blackjack(player, "Player");//check if player has blackjack
			int temp = value(player[0]) + value(player[1]);//sum of player hands
			coutcard(player, "Player");//cout player hand
			dealer[0] = intdis();//disturbiting cards
			dealer[1] = intdis();
			cout << "Dealer has " << display(dealer[0]) << endl;//dealer exposed card
			coutcard(dealer, "Dealer");
			if (blackjack(player, "Player") && !blackjack(dealer, "Dealer"))
			{
				cout << "Dealer no blackjack\n";
				bet = bet * 1.5;
				cout << "Player gets $" << bet << endl;
			}
			else if (blackjack(dealer, "Dealer") && !blackjack(player, "Player"))
			{
				cout << "SORRY!!\n";
			}
			else if (!blackjack(dealer, "Dealer"))//if dealer no blackjack
			{
				if (player[0] == player[1] && player[0] < 10)//pairs except 10
				{
					cout << "!!!!!!!!!!!!!!!!!!";
					play(splitaction(player[0]));//go to splite with that card
				}
				else if (checkace(player)) //if player has an ace
				{
					play(aceaction(temp - 1));
				}
				else
				{
					play(paction(temp));//just keep playing
				}
			}
			result();
			cout << "Player win: $ " << playercount << "\tDealer win: $ " << dealercount << endl;
			cout << "Player net winning: $" << playercount - dealercount << endl;
			cout << "Postive: " << positive << endl;
			gamecount++;
		} while (cardcount < totalcard * percent);//how much of the card
		cout << "gamecount: " << gamecount << "    This set Used card count: " << cardcount << endl;

	}
	cout << "===============================================================================\n";
	cout << "Playerwin game: " << playerwin << "\t Playerwin rate: " << playerwin / gamecount << endl;
	cout << "Dealerwin game: " << dealerwin << "\t Dealerwin rate: " << dealerwin / gamecount << endl;
	cout << "TIE game: " << tie << "\tTie rate: " << tie / gamecount << endl;
	cout << "Double game: " << doublerate << "\t Double rate: " << doublerate / gamecount << endl;
	cout << "Split game : " << split << "\tSplit rate: " << split / gamecount << endl;
	cout << "Player win: $ " << playercount << "\tDealer win: $ " << dealercount << endl;
	cout << "Player net winning: $" << playercount - dealercount << endl;

}

void shuffle(int* arr, size_t numset)
{
	srand(time(0));
	for (int i = 0; i < 52000 * numset; i++)
	{
		int a = rand() % 52 * numset + 1;
		int b = rand() % 52 * numset + 1;
		swap(arr[a], arr[b]);


	}
	cout << "****Shuffling******";
}

void create(int* poker, const int numset)
{
	poker[0] = 0;
	for (int i = 0; i < 4 * numset; i++)//new set of card
	{
		poker[1 + i * 13] = 1;
		poker[2 + i * 13] = 2;
		poker[3 + i * 13] = 3;
		poker[4 + i * 13] = 4;
		poker[5 + i * 13] = 5;
		poker[6 + i * 13] = 6;
		poker[7 + i * 13] = 7;
		poker[8 + i * 13] = 8;
		poker[9 + i * 13] = 9;
		poker[10 + i * 13] = 10;
		poker[11 + i * 13] = 12;
		poker[12 + i * 13] = 13;
		poker[13 + i * 13] = 14;

	}//for
}

void print(int* arr, const int numset)
{
	cout << "  " << numset << " set of card in play. Shuffled deck: ";
	int totalcard = numset * 52;
	for (int i = 1; i <= totalcard; i++)
	{
		cout << display(arr[i]) << " ";
	}
	cout << endl;
}

void printf(string* arr, const int numset)
{
	int totalcard = numset * 52;
	cout << "Shuffled deck: ";
	for (int i = 1; i <= totalcard; i++)
	{
		cout << arr[i] << " ";
	}
}

int intdis()
{
	if (poker[cardcount] <= 6 && poker[cardcount] >= 2)//2-6 positive
	{
		positive++;
	}
	else if (poker[cardcount] > 9 || poker[cardcount] == 1)//10 and A negetive
	{
		positive--;
	}
	return poker[cardcount++];//distribute the next card

}

int paction(int choice)//without Ace
{
	//1 = hit;
	//2 = double
	//3 = stand
	//4 = split
	switch (choice)
	{
	case 5:
	case 6:
	case 7:
	case 8:
	{
		//cout << "*******player called hit" << endl;
		return 1;
	}
	break;
	case 9:
		if (value(dealer[0]) <= 6 && value(dealer[0]) > 2)
		{
			//cout << "*******player called double" << endl;
			return 2;

		}
		else
		{
			//cout << "*******player called hit" << endl;
			return 1;
		}

		break;
	case 10:
		if (value(dealer[0]) <= 9 && value(dealer[0]) > 1)
		{
			//cout << "*******player called double" << endl;
			return 2;

		}
		else
		{
			//cout << "*******player called hit" << endl;
			return 1;
		}


		break;
	case 11:
		if (value(dealer[0]) > 1)
		{
			//cout << "*******player called double" << endl;
			return 2;
		}
		else
		{
			//cout << "*******player called hit" << endl;
			return 1;
		}

		break;
	case 12:
		if (value(dealer[0]) >= 4 && value(dealer[0]) <= 6)
		{
			//cout << "*******player called stand" << endl;
			return 3;

		}
		else
		{
			//cout << "*******player called hit" << endl;
			return 1;
		}

		break;
	case 13:
	case 14:
	case 15:
	case 16:
		if (value(dealer[0]) <= 6 && value(dealer[0]) > 1)
		{
			//cout << "*******player called stand" << endl;
			return 3;

		}
		else
		{
			//cout << "*******player called hit" << endl;
			return 1;
		}

		break;
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	{
		//cout << "*******player called stand" << endl;
		return 3;
	}


	break;
	}
}

int aceaction(int hand)
{
	switch (hand)
	{
	case 2:
	case 3:
		if (value(dealer[0]) <= 4 || value(dealer[0]) >= 7)//1-4, 7-10
		{
			//cout << "*******player called hit" << endl;
			return 1;
		}
		else
		{
			//cout << "*******player called double" << endl;
			return 2;
		}
		break;
	case 4:
	case 5:
		if (value(dealer[0]) <= 3 || value(dealer[0]) >= 7)//1-3,7-10
		{
			//cout << "*******player called hit" << endl;
			return 1;
		}
		else
		{
			//cout << "*******player called double" << endl;
			return 2;
		}
		break;
	case 6:
		if (value(dealer[0]) >= 3 && value(dealer[0]) <= 6)//3-6
		{
			//cout << "*******player called double" << endl;
			return 2;
		}
		else
		{
			//cout << "*******player called hit" << endl;
			return 1;
		}
		break;
	case 7:
		if (value(dealer[0]) == 9 || value(dealer[0]) == 10 || value(dealer[0]) == 1)//9, 10 , 1
		{
			//cout << "*******player called hit" << endl;
			return 1;
		}
		else if (value(dealer[0]) == 2 || value(dealer[0]) == 7 || value(dealer[0]) == 8)//2, 7 , 8
		{
			//cout << "*******player called stand" << endl;
			return 3;
		}
		else
		{
			//cout << "*******player called double" << endl;
			return 2;
		}
		break;
	case 8:
	case 9:
	case 10: //cout << "*******player called stand" << endl;
		return 3;
		break;

	}
}

int splitaction(int hand)
{
	switch (hand)
	{
	case 1:
		cout << "*******player called split" << endl;
		return 4;
		break;
	case 2:
	case 3:
		if (value(dealer[0]) >= 4 || value(dealer[0]) <= 7)
		{
			cout << "*******player called split" << endl;
			return 4;
		}
		else
		{
			cout << "*******player called hit" << endl;
			return 1;
		}
		break;
	case 4:
		if (value(dealer[0]) >= 5 || value(dealer[0]) <= 6)
		{
			cout << "*******player called split" << endl;
			return 4;
		}
		else
		{
			cout << "*******player called hit" << endl;
			return 1;
		}
	case 5:
		if (value(dealer[0]) == 1 || value(dealer[0]) == 10)
		{
			cout << "*******player called hit" << endl;
			return 1;
		}
		else
		{
			cout << "*******player called double" << endl;
			return 2;
		}
		break;
	case 6:
		if (value(dealer[0]) >= 2 || value(dealer[0]) <= 6)
		{
			cout << "*******player called split" << endl;
			return 4;
		}
		else
		{
			cout << "*******player called hit" << endl;
			return 1;
		}
		break;
	case 7:
		if (value(dealer[0]) >= 2 || value(dealer[0]) <= 7)
		{
			cout << "*******player called split" << endl;
			return 4;
		}
		else
		{
			cout << "*******player called hit" << endl;
			return 1;
		}
		break;
	case 8:
		cout << "*******player called split" << endl;
		return 4;
		break;

	case 9:
		if (value(dealer[0]) == 7 || value(dealer[0]) == 10 || value(dealer[0]) == 1)
		{
			cout << "*******player called stand" << endl;
			return 3;
		}
		else
		{
			cout << "*******player called split" << endl;
			return 4;
		}
		break;
	}
}

void play(int action)
{

	switch (action)
	{
	case 1: //hit
		cout << "*******Player called hit\n";
		player[++playerhandcount] = intdis();//distribute from play[2]
		psum = sum(player);//player sum
		coutcard(player, "Player");//display card;

		if (sum(player) < 12 && checkace(player))//check whether stand with ace
		{
			if (aceaction(sum(player) - 1) == 1 || aceaction(sum(player) - 1) == 1)//if supposed hit or double//both changed to 1 hit
			{
				play(1);//play(hit)
			}
			else
			{
				play(3);//play(stand)

			}
		}
		else if (sum(player) < 22)//without ace but <22
		{
			if (paction(sum(player)) == 1 || paction(sum(player)) == 2)//if supposed hit or double
			{
				play(1);//play(hit)
			}
			else
			{
				play(3);//play(stand)

			}
		}
		else
			pbust(player);//player busts
		break;
	case 2: //double
		doublerate++;
		bet = bet * 2;//double the bet
		cout << "*******player called double2" << endl;
		cout << "$$bet of $" << bet << endl;
		player[2] = intdis();
		acevalue(player);//determine ace value
		coutcard(player, "Player");
		pbust(player);//check player busts
		cout << "-------Dealer turn\n";
		dealeraction();//dealer action
		break;
	case 3://stand
		cout << "*******Player called stand.\n";
		acevalue(player);
		coutcard(player, "Player");
		cout << "-------Dealer turn\n";
		dealeraction();//dealeraction
		break;
	case 4: //split
		split++;
		intialhands(player);
		intialhands(dealer);//set everything =0
		player[0] = 19;
		player[1] = 2;
		dealer[0] = 19;
		dealer[1] = 2;//so they tie
		cout << "Assign new card value to make them tie\n";
		coutcard(player, "player");

		//cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		play(3);//player stand
		break;
		/*
		coutcard(player, "playererrrorororr");
		cout << "*******Player called split\n";
		player1[0] = player[0];//assign same card to two different hand
		player2[0] = player[0];
		if (checkace(player1))
		{
			player1[1] = intdis();
			player2[1] = intdis();
			cout << "Only card is distributed for each hand.\n";
			coutcard(player1, "Player first set: ");
			coutcard(player2, "Player second set: ");
			play(3);//stand after ditributing need to work on result and play()

		}
		else
		{
			player1[1] = intdis();
			player2[1] = intdis();
			coutcard(player1, "Player first set: ");
			coutcard(player2, "Player second set: ");
		}
	}*/


	}
}
void dealeraction()
{
	playerhandcount = 1;//initial playerhand
	if (sum(dealer) > 21)
	{
		dbust(dealer);//cehck dealer busts
	}
	else if (!checkace(dealer) && sum(dealer) > 16)//dealer sum >17
	{
		cout << "Dealer stand\n";
		coutcard(dealer, "Dealer");//dealer stand and display
	}
	else if (checkace(dealer) && sum(dealer) > 7 && sum(dealer) < 12)//dealer has ace and dealer sum-1 is 7-10
	{
		cout << "++++++++++++++++++++++++++++++++++++Dealer has Ace, check here\n";
		acevalue(dealer);
		cout << "Dealer stand\n";
		coutcard(dealer, "Dealer");//display
	}
	else if (checkace(dealer) && (sum(dealer) - 1) == 6) //soft 17, ace and 6
	{
		cout << "Dealer soft 17!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		dealer[dealerhandcount++] = intdis();
		acevalue(dealer);
		coutcard(dealer, "Dealer");
		dbust(dealer);//check dealer busts
		if (sum(dealer) < 17)//if still <17 
		{
			dealer[dealerhandcount] = intdis();//distribute third card
			dealerhandcount++;
			coutcard(dealer, "Dealer");
			dealeraction();//do dealer action again
		}
	}
	else if (sum(dealer) < 17)//if still <17 
	{
		dealer[dealerhandcount] = intdis();//distribute third card
		dealerhandcount++;
		coutcard(dealer, "Dealer");
		dealeraction();//do dealer action again
	}




}

string display(int value)
{
	switch (value)
	{
	case 1: return "A";
		break;
	case 2: return "2";
		break;
	case 3: return "3";
		break;
	case 4: return "4";
		break;
	case 5: return "5";
		break;
	case 6: return "6";
		break;
	case 7: return "7";
		break;
	case 8: return "8";
		break;
	case 9: return "9";
		break;
	case 10: return "10";
		break;
	case 11: return"A";
		break;
	case 12: return "J";
		break;
	case 13: return "Q";
		break;
	case 14: return "K";
		break;
	case 19: return "19";
		break;


	}

}

int value(int value)//return card value
{
	if (value < 12 || value == 19)
	{
		return value;
	}
	else//for 12, 13, 14
	{
		return 10;
	}
}

int sum(int* arr)
{
	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum += value(arr[i]);
	}
	return sum;
}

void coutcard(int* arr, string name)
{
	cout << name << " card: ";
	for (int i = 0; i < 10; i++)
	{
		if (arr[i] != 0) {
			cout << display(arr[i]) << ", ";
		}
	}
	cout << "\t" << name << " sum: " << sum(arr) << endl;
}

bool checkace(int* arr)
{
	for (int i = 0; i < 5; i++)
	{
		if (arr[i] == 1) {
			return true;

		}
	}
	return false;
}

void acevalue(int* arr)
{

	for (int j = 0; j < 10; j++)
	{
		if (arr[j] == 1 && sum(arr) < 12)//if after stand gets an ace No explod if a=11
		{
			arr[j] = 11;
			//cout << "in ace stand" << endl;
			//coutcard(player, "Player");//display card;
		}

	}
}

void result()
{
	if (sum(player) < 22 && sum(dealer) < 22) {
		if (sum(player) > sum(dealer))
		{
			cout << "========Player won!!!!!" << endl;
			playerwin++;
			playercount += bet;//in case if player doubles
		}
		else 	if (sum(player) < sum(dealer))
		{
			cout << "========Dealer won!!!!!" << endl;
			dealerwin++;
			dealercount += bet;//in case if player doubles
		}
		else
		{
			cout << "====TIE Game======" << endl;
			tie++;
		}
	}
}

void dbust(int* arr)
{
	if (sum(arr) > 21)
	{
		cout << "==== Dealerbusts >21" << endl;
		cout << "=========Player won!!!!!" << endl;
		playerwin++;
		playercount += bet;//in case if player doubles
	}

}

void pbust(int* arr)
{
	if (sum(arr) > 21)
	{
		cout << "== Playerbusts >21" << endl;
		cout << "==========Dealer won!!!!!" << endl;
		dealercount += bet;//in case if player doubles
		dealerwin++;
	}

}
void intialhands(int* arr)
{
	for (int i = 0; i < 10; i++)
	{
		arr[i] = 0;
	}
	dealerhandcount = 2;
	playerhandcount = 1;
}

bool blackjack(int* arr, string name)
{
	if (sum(arr) == 21)
	{
		return true;
	}
	else if (checkace(arr) && sum(arr) == 11)
	{
		for (int j = 0; j < 2; j++)
		{
			if (arr[j] == 1)//Ace and 10
			{
				arr[j] = 11;//set ace to 11

			}

		}
		cout << "========" << name << " has blackjack!!!\n";
		return true;
	}
	else return false;
}
