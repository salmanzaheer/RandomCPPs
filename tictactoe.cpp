#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<cstdlib>

using namespace std;
char box[9];
bool won;


 //Print the grid
void printBox() {
	system("cls");
	cout<<"TIC TAC TOE"<<endl<<endl;
    for(int row = 0; row < 3;row++){
        for(int col = 0; col < 3;col++){
            cout<<" "<<box[row*3+col];
            if(col < 2)
                cout<<" | ";
        }
        if(row < 2)
            cout<<endl<<"---+----+---"<<endl;
    }
}


 //Check winner
int winnerCheck(){
    int possibility[8][3] = {
              {0,3,6},
              {1,4,7},
              {2,5,8},
              {0,1,2},
              {3,4,5},
              {6,7,8},
              {6,4,2},
              {0,4,8}
        };
    for(int i=0;i<8;++i)
    {
        if(box[possibility[i][0]] == box[possibility[i][1]] && box[possibility[i][1]] == box[possibility[i][2]])
        {
            printBox();
            cout<<endl<<endl<<box[possibility[i][0]]<<"\nWe have a winner!";
			won = true;
        }
    }
    return false;

}

int getChoice(){
    int choice;
    while(true){
        cin>>choice;
        if((choice < 10 && choice > 0) && (box[choice-1] != 'X' && box[choice-1] != 'O')){
	        return choice-1;
        }
		else{
			cout<<"Sorry, Please try again: ";
		}
    }
}

//adding to array
void newArray(){
	for (int i = 0; i < 9 ; i++) {
		box[i] = (i+1)+48; // adding ascii code
	}
}


//Game end
bool finishCheck()
{
	for (int i = 0; i < 9 ; i++) {
		if(box[i] != 'O' && box[i] != 'X')
			return false;
	}
	return true;
}

int main()
{
    char choice;
    char load;

	cout<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<setw(45)<<"*******************"<<endl<<endl;
	cout<<setw(45)<<"*   TIC TAC TOE   *"<<endl<<endl;
	cout<<setw(45)<<"*******************"<<endl<<endl;
	cout<<setw(46)<<"--- Salman Zaheer ---"<<endl;
	cout<<setw(46)<<"----Section: C -------"<<endl;
	cout<<setw(49)<<"--- Roll no: 15L-4120 ---"<<endl;
	cout<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<setw(80)<<"Press any key to continue.";
	_getch();
	system("cls");

	cout<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<setw(45)<< "**************************"<<endl<<endl;
	cout<<setw(46)<< "* Press 'n' for New Game *"<<endl<<endl;
	cout<<setw(46)<< "* Press 'l' to Load Game *"<<endl<<endl;
	cout<<setw(45)<< "**************************"<<endl<<endl;
	cin >> load;

	if(load == 'L' || load == 'l')
    {
        ifstream loader("c:\\temp\\data1.txt");
        cout << "Error while loading DATA." << endl;

    }
    else if(load == 'N' || load == 'n')
    {
        do
        {
            newArray();
            won = false;
            while(true) {
                //Player One
                if(won == false &&  finishCheck() == false){
                    printBox();
                    cout<<endl<<endl<<"Player 1: ";
                    choice = getChoice();
                    box[choice] = 'X';

                    // Winner Check
                    winnerCheck();
                }
                else {
                    break;
                }


                //Player Two
                if(won == false &&  finishCheck() == false){
                    printBox();
                    cout<<endl<<endl<<"Player 2: ";
                    choice = getChoice();
                    box[choice] = 'O';

                    // Winner Check
                    winnerCheck();
                }
                else {
                    break;
                }
            }


            if(won == false) {
                printBox();
                cout<<endl<<endl<<"The game ended in a draw.";
            }

            cout<<endl<<endl<<"Do you want to play again (Y/N): ";
            cin>>choice;
        }
        while(choice == 'Y' || choice == 'y');

        cout<<endl;
    }

    system("PAUSE");
    return 0;
}