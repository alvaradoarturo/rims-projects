
#include "RIMS.h"
volatile int TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}

const int Board_Size = 25;
int Player_One_Flag = 0;
int Player_Two_Flag = 0;
int Submit_Flag = 0;
// Delcares an array of size 25 
int Current_Board[25];
int Winner = 0;


enum Logic_STATES{ Logic_Init, Play_Ball, Winning_Screen}Logic_states;
void Game_Logic(){
    // Transactions
    
    switch(Logic_states)
    {
        case Logic_Init:
            Logic_states = Play_Ball;
            break;
        case Play_Ball:
            if(!Winner)
            {
                Logic_states = Play_Ball;
            }
            if(Winner)
            {
                Logic_states = Winning_Screen;
            } 
             break;
          case Winning_Screen:
               if(A7 && C6)
               {
                   Populate_Board(Current_Board, Board_Size);
                   Print_Board(Current_Board, Board_Size);
                   Logic_states = Play_Ball;
               }
               else
               {
                   Logic_states = Winning_Screen;
               }    
                break;
            default:
               Logic_states = Logic_Init;
               break;
               
               
        
        
        
    }
    // Actions
    switch(Logic_states)
    {
        case Logic_Init:
            break;
        case Play_Ball:
            // Top horizontal win for 1
            if(Current_Board[6] == 10 && Current_Board[7] == 10 &&       Current_Board[8] == 10)
            {
                
                // Print Player 1 Winning Text
                Winner = 1;
                Print_Winner(1);
            }
            // Middle Horizontal
            else if(Current_Board[11] == 10 && Current_Board[12]            ==  10 && Current_Board[13] == 10)
            {
                  
                // Print Player 1 Winning Text
                Winner = 1;
                Print_Winner(1);
            }                        
            // Bottom Horizontal
            else if(Current_Board[16] == 10 && Current_Board[17]            ==  10 && Current_Board[18] == 10)
            {
                  
                // Print Player 1 Winning Text
                Winner = 1;
                Print_Winner(1);
            }            
            // Left Vertical
            else if(Current_Board[6] == 10 && Current_Board[11]            ==  10 && Current_Board[16] == 10)
            {
                  
                // Print Player 1 Winning Text
                Winner = 1;
                Print_Winner(1);
            }            
            // Middle Vertical
            else if(Current_Board[7] == 10 && Current_Board[12]            ==  10 && Current_Board[17] == 10)
            {
                  
                // Print Player 1 Winning Text
                Winner = 1;
                Print_Winner(1);
            }                        
            // Right Vertical
            else if(Current_Board[8] == 10 && Current_Board[13]            ==  10 && Current_Board[18] == 10)
            {
                  
                // Print Player 1 Winning Text
                Winner = 1;
                Print_Winner(1);
            }  
            // Top Left to  Bottom right 
            else if(Current_Board[6] == 10 && Current_Board[12]            ==  10 && Current_Board[18] == 10)
            {
                  
                // Print Player 1 Winning Text
                Winner = 1;
                Print_Winner(1);
            }            
            // Bottom Left to Top Right
            else if(Current_Board[8] == 10 && Current_Board[12]            ==  10 && Current_Board[16] == 10)
            {
                  
                // Print Player 1 Winning Text
                Winner = 1;
                Print_Winner(1);
            } 
            // Top horizontal win for Player 2
            if(Current_Board[6] == 20 && Current_Board[7] == 20 &&       Current_Board[8] == 20)
            {
                
                // Print Player 2 Winning Text
                Winner = 1;
                Print_Winner(2);
            }
            // Middle Horizontal for player 2
            else if(Current_Board[11] == 20 && Current_Board[12]            ==  20 && Current_Board[13] == 20)
            {
                  
                // Print Player 2 Winning Text
                Winner = 1;
                Print_Winner(2);
            }                        
            // Bottom Horizontal for player 2
            else if(Current_Board[16] == 20 && Current_Board[17]            ==  20 && Current_Board[18] == 20)
            {
                  
                // Print Player 2 Winning Text
                Winner = 1;
                Print_Winner(2);
            }            
            // Left Vertical for player 2
            else if(Current_Board[6] == 20 && Current_Board[11]            ==  20 && Current_Board[16] == 20)
            {
                  
                // Print Player 2 Winning Text
                Winner = 1;
                Print_Winner(2);
            }            
            // Middle Vertical for player 2
            else if(Current_Board[7] == 20 && Current_Board[12]            ==  20 && Current_Board[17] == 20)
            {
                  
                // Print Player 2 Winning Text
                Winner = 1;
                Print_Winner(2);
            }                        
            // Right Vertical for player 2
            else if(Current_Board[8] == 20 && Current_Board[13]            ==  20 && Current_Board[18] == 20)
            {
                  
                // Print Player 2 Winning Text
                Winner = 1;
                Print_Winner(2);
            }  
            // Top Left to  Bottom right for player 2
            else if(Current_Board[6] == 20 && Current_Board[12]            ==  20 && Current_Board[18] == 20)
            {
                  
                // Print Player 2 Winning Text
                Winner = 1;
                Print_Winner(2);
            }            
            // Bottom Left to Top Right for plaer 2
            else if(Current_Board[8] == 20 && Current_Board[12]            ==  20 && Current_Board[16] == 20)
            {
                  
                // Print Player 2 Winning Text
                Winner = 1;
                Print_Winner(2);
            }
            else
            {
                if(Current_Board[6] !=0 && Current_Board[7] != 0
                   && Current_Board[8] !=0 && Current_Board[11] !=0
                   && Current_Board[12] !=0 && Current_Board[13]!=0
                   &&Current_Board[16] !=0 && Current_Board[17] !=0
                   &&Current_Board[18] !=0)
                   {
                       // Print Tie Screen
                       Winner = 1;
                       Print_Winner(3);
                   }
            }
        
        
    }
    
}

enum Game_STATES{ Init, Coin_Flip, Player_One, Player_Two, Won_Game}Game_states;

void Game_Play(){
    int coin;
    // Transitions
    switch(Game_states)
    {
        case Init:
            B = 0;
            D0 = 0;
            Game_states = Coin_Flip;
            break;
        case Coin_Flip:
         // Rand function to give each player equally probability
            srand(15);
            coin = rand();
            if( coin % 2 == 0)
            {
                B7 = 1; 
                Player_One_Flag = 1;
                Game_states = Player_One;
               
            }  
            else 
            {
                D6 = 1;
                Game_states = Player_Two;
            }   
            break;
         case Player_One:
            if(!A7)
            {
               Game_states = Player_One;
            }
            if(A7){
                Player_One_Flag = 0;
                Player_Two_Flag = 1;
                D6 = 1;
                B7 = 0;
                Game_states = Player_Two;
            }
            break;
         case Player_Two:
            if(!C6)
            {
               Game_states = Player_Two;
            }
            if(C6){
                Player_One_Flag = 1;
                Player_Two_Flag = 0;
                D6 = 0;
                B7 = 1;
                Game_states = Player_One;
            }         
            break;
         case Won_Game:
            break;
         default:
            break;
    }
    // Actions
    switch(Game_states)
    { 
           case Init:
               break;
           case Coin_Flip:
               break;
           case Player_One:
               if(A6 && (!Submit_Flag)){
                   
                  if(A == 65)
                  {
                     Current_Board[6] = 10;
                     Print_Board(Current_Board, Board_Size);
                  }
                  else if(A == 66)
                  {
                     Current_Board[7] = 10;
                     Print_Board(Current_Board, Board_Size);
                  } 
                  else if(A == 67)
                  {
                     Current_Board[8] = 10;
                     Print_Board(Current_Board, Board_Size);
                  }             
                  else if(A == 68)
                  {
                     Current_Board[11] = 10;
                     Print_Board(Current_Board, Board_Size);
                  }               
                  else if(A == 69)
                  {
                     Current_Board[12] = 10;
                     Print_Board(Current_Board, Board_Size);
                  }               
                  else if(A == 70)
                  {
                     Current_Board[13] = 10;
                     Print_Board(Current_Board, Board_Size);
                  }
                  else if(A == 71)
                  {
                     Current_Board[16] = 10;
                     Print_Board(Current_Board, Board_Size);
                  }    
                  else if(A == 72)
                  {
                     Current_Board[17] = 10;
                     Print_Board(Current_Board, Board_Size);
                  }   
                  else if(A == 73)
                  {
                     Current_Board[18] = 10;
                     Print_Board(Current_Board, Board_Size);
                  }    
                  else
                  {    
                      printf("%s", "Invalid Input");
                  }
               }   
               break;
             case Player_Two:
               if(C5 && (!Submit_Flag)){
                   
                  if(C0 && !C1 && !C2 && !C3)
                  {
                     Current_Board[6] = 20;
                     Print_Board(Current_Board, Board_Size);
                  }
                  else if(!C0 && C1 && !C2 && !C3)
                  {
                     Current_Board[7] = 20;
                     Print_Board(Current_Board, Board_Size);
                  } 
                  else if(C0 && C1 && !C2 && !C3)
                  {
                     Current_Board[8] = 20;
                     Print_Board(Current_Board, Board_Size);
                  }             
                  else if(!C0 && !C1 && C2 && !C3)
                  {
                     Current_Board[11] = 20;
                     Print_Board(Current_Board, Board_Size);
                  }               
                  else if(C0 && !C1 && C2 && !C3)
                  {
                     Current_Board[12] = 20;
                     Print_Board(Current_Board, Board_Size);
                  }               
                  else if(!C0 && C1 && C2 && !C3)
                  {
                     Current_Board[13] = 20;
                     Print_Board(Current_Board, Board_Size);
                  }
                  else if(C0 && C1 && C2 && !C3)
                  {
                     Current_Board[16] = 20;
                     Print_Board(Current_Board, Board_Size);
                  }    
                  else if(!C0 && !C1 && !C2 && C3)
                  {
                     Current_Board[17] = 20;
                     Print_Board(Current_Board, Board_Size);
                  }   
                  else if(C0 && !C1 && !C2 && C3)
                  {
                     Current_Board[18] = 20;
                     Print_Board(Current_Board, Board_Size);
                  }    
                  else
                  {    
                      printf("%s", "Invalid Input");
                  }
               }
             break;  
                       
    }
}   
    
// Creates an empty board
void Populate_Board(int Current_Board[], int size )
{
    
    int i ;
    for(i = 0; i < size ; ++i){      
      if(i <=4 || i >= 20){
         Current_Board[i] =3;
      }
      else if(i == 5 || i == 9 || i == 10 || i == 14 || i == 15 ||i == 19 ){
         Current_Board[i] = 4;
      }
      else if((i > 5 && i < 9)  || (i > 10 && i < 14) || (i > 15 && i < 19)){
         Current_Board[i] = 0;
        }
      else{
        printf("error");
      }
    }
}

void Print_Board(int Current_Board[], int size)
{
   int i;
   char newline[] = "\n";
   char dash[] = " --";
   char bar[] = " | ";
   char blank[] = " _ ";
   char EX[] = " X ";
   char OH[] = " O ";
   for(i = 0; i < size ; ++i)
   {
       if(Current_Board[i] == 3)
       {
           printf("%s", dash);
       }
       else if(Current_Board[i] == 4){
          printf("%s" , bar);
       }
        else if(Current_Board[i] == 10){
          printf("%s" , EX);
       }
        else if(Current_Board[i] == 20){
          printf("%s" , OH);
       }      
       else{
         printf("%s", blank);  
       }
       
       if(i == 4 || i == 9 || i == 14 || i == 19 | i == 24)
       {
           printf("%s\n", newline);
       }
   }  
}
void Print_Winner(int n){
    if( n == 1)
    {
        printf("%s\n", "Playey 1 has won!");
    }
    else if (n == 2)
    {
        printf("%s\n", "Playey 2 has won!");
    }
    else 
    {
        printf("%s\n", "TIE GAME!");
    }
}
void main()
{
   printf("\n");
   Populate_Board(Current_Board, Board_Size);
   
   
   
   Print_Board(Current_Board, Board_Size);
   
   Game_states = Init;
   Logic_states = Logic_Init;
      
   while (1) { 
      Game_Play();
      Game_Logic();
 /*     while(!TimerFlag);
      TimerFlag=0; */
   } 
}