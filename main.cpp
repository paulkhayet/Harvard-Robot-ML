//Final.cpp
//Paul Khayet, CISP 400
//12/01/19
//Recreates a Genetic Algorithm project first conducted at Harvard. The program controls robots that search for batteries. The more batteries it finds the more moves the robot can complete. The program uses the idea of 'genetics' to form a basic version of machine learning that causes the robot to perform better the longer the experiment is run.

#include <iostream>
#include <stdlib.h>
using namespace std; 

char map[10][10] = 
{{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
}; 

void printBoard(); 
void placeBattery(); 
void clearBoard(); 
void sortTurns(); 
void printTurns(); 
void createKids(); 
float genAverage(); 


int gen = 0; 

class bot{
  public: 
    int battery; 
    int x; 
    int y; 
    int genes[16][5]; 
    int turns;


    bot(){
      battery = 5; 
      x = rand() % 10; 
      y = rand() % 10; 
      if (gen == 0){
        for (int i = 0; i < 16; i++){
          for(int j = 0; j < 5; j++){
            genes[i][j] = rand() % 5; 
          }
        }
      turns = 0;  
        
      }
    } 

    void changeGenes(int x1, int y1, int g1){
      genes[x1][y1] = g1; 
    }

    int getGenes(int x1, int y1){
      return genes[x1][y1]; 
    }

    int sensorNorth(int x, int y){
      if (x == 0){
        return 1; 
      }
      else if (map[x+1][y] == '-'){
        return 0; 
      }
      else if (map[x+1][y] == 'B'){
        return 2; 
      }
      else 
        return 3; 
      
    }

    int sensorEast(int x, int y){
      if (y==9){
        return 1; 
      }
      else if (map[x][y+1] == '-'){
        return 0; 
      }
      else if (map [x][y+1] == 'B'){
        return 2;
      }
      else 
        return 3; 
    }

    //Sensor facing south
    int sensorSouth(int x, int y){
      if (x == 9){
        return 1; 
      }
      else if (map[x-1][y] == '-'){
        return 0; 
      }
      else if(map[x-1][y] == 'B'){
        return 2; 
      }
      else 
        return 3; 
    }

    //Sensor facing west
    int sensorWest(int x, int y){
      if(y == 0){
        return 1; 
      }
      else if (map[x][y-1] == '-'){
        return 0; 
      }
      else if(map[x][y-1] == 'B'){
        return 2; 
      }
      else 
        return 3; 
    }

    //Moves the bot north
    void moveNorth(){
      if(sensorNorth(x,y) != 1){
        if(sensorNorth(x,y) == 2){
          battery = battery + 5; 
          x--; 
        }
        else{
        x--; 
        }
      }
    }

    //Moves the bot South
    void moveSouth(){
      if(sensorSouth(x,y) != 1 ){
        if(sensorSouth(x,y) == 2){
          battery = battery + 5; 
          x++; 
        }
        else{
        x++; 
        }
      }
      else if (sensorSouth(x,y) == 1){
        cout << "Sorry hit a wall" << endl; 
      }
    }

    void moveEast(){
      if(sensorEast(x,y) != 1){
        if(sensorEast(x,y) == 2){
          battery = battery +5; 
          y++; 
        }
        else{
        y++; 
      }
      }
    }

    void moveWest(){
      if(sensorWest(x,y) != 1){
        if(sensorWest(x,y) == 2){
          battery = battery + 5; 
          y--; 
        }
        else{
         y--; 
      }
      }
    }

    void moveRandom(){
      int temp = rand() & 4; 
      if(temp == 0){
        moveNorth(); 
      }
      else if (temp == 1){
        moveSouth(); 
      }
      else if(temp == 2){
        moveEast(); 
      }
      else if(temp == 3){
        moveWest(); 
      }
    }

    void printGenes(){
      for (int i = 0; i < 16; i++){
          for(int j = 0; j < 5; j++){
            cout << genes[i][j]; 
          }
          cout << endl; 
      }
    }

    void move(){
      map[x][y] = '-'; 
      bool move = false; 
      for (int i = 0; i < 16; i++){
        if (genes[i][0] == sensorNorth(x,y) && genes[i][1] == sensorSouth(x,y) && genes[i][2] == sensorEast(x,y) && genes[i][3] == sensorWest(x,y)){
          if(genes[i][4] == 0){
            moveNorth(); 
            move = true; 
          }
          if(genes[i][4] == 1){
            moveSouth(); 
            move = true; 
          }
          if(genes[i][4] == 2){
            moveEast(); 
            move = true; 
          }
          if(genes[i][4] == 3){
            moveWest(); 
            move = true; 
          }
          if(genes[i][4] == 4 && sensorWest(x,y) != 1){
            moveRandom(); 
            move = true; 
          }
        }
      }
      if (move == false){
        if(genes[15][4] == 0){
          if(genes[15][4] == 0 ){
            moveNorth(); 
            move = true; 
          }

        }
        if(genes[15][4] == 1){
            if(x!=9){
            moveSouth(); 
            }
            move = true; 
          }
          if(genes[15][4] == 2){
            moveEast(); 
            move = true; 
          }
          if(genes[15][4] == 3){
            moveWest(); 
            move = true; 
          }
          if(genes[15][4] == 4){
            moveRandom(); 
            move = true; 
          }
      } 
        map[x][y] = 'X'; 
        battery--; 
        turns++; 
      }
    int getX(){
      return x; 
    }
    int getY(){
      return y; 
    }
    int getBattery(){
      return battery; 
    }
    int getTurns(){
      return turns; 
    }

    

}; 

bot bot1[200]; 

//main
//------------------------------------------------------------------------
int main() {
  cout << "Hello welcome to the genetic algorithm robot." << endl;
  cout << "Press any letter followed by enter to create a new generation of bots." << endl; 
  cout << "Press 'q' at any point to end the program." << endl; 
  char input; 
  cin >> input; 
  while(input != 'q'){
  for (int i = 0; i < 200; i++){
    placeBattery(); 
    while(bot1[i].getBattery() != 0){
      bot1[i].move(); 
    }  
    clearBoard(); 
  }
  sortTurns(); 
  printTurns(); 
  cout << "Genetic Fitness or 'Average amount of turns':" << genAverage() << endl; 
  createKids(); 
  cout << "Press any letter followed by enter to continue or type 'q' to quit."<< endl; 
  cin >> input; 

}
}

void printBoard(){
  for(int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      cout << map[i][j] << " "; 
    }
    cout << endl; 
  }
   cout << endl;  
}

void placeBattery(){
  for(int i = 0; i < 10; i++){
      int q = 0; 
      int w = 0; 
      int e = 0; 
      int r = 0; 
    while (q == w || q == e || q == r || w == e || w == r|| e == r){
      q = rand() % 10; 
      w = rand() % 10;
      e = rand() % 10;
      r = rand() % 10;
    }
    map[i][q] = 'B'; 
    map[i][w] = 'B'; 
    map[i][e] = 'B'; 
    map[i][r] = 'B'; 
    }
  }

  void clearBoard(){
    for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
        map[i][j] = '-'; 
      }
    }
  }

  void sortTurns(){
    int i, j, min; 
    bot temp; 
    for (i = 0; i < 200 - 1; i++) {
      min = i;
      for (j = i + 1; j < 200; j++)
         if (bot1[j].getTurns() > bot1[min].getTurns())
            min = j;
         temp = bot1[i];
         bot1[i] = bot1[min];
         bot1[min] = temp;
   }
  
  }

void printTurns(){
  for(int i = 0; i < 200; i++){
    cout << "Bot #" << i+1 << ": " << bot1[i].getTurns() << endl; 
  }
}

void createKids(){ 
  for(int k = 0; k<103; k=k+2){
  int mutation = rand() % 20; 
  //Papa Genes
  for (int i = 0; i<16; i++){
    for(int j = 0; j<6; j++){
      bot1[k + 100].genes[i][j] = bot1[k].genes[i][j];


      //Gives the 5 percent chance of mutation
      if (mutation == 1 && j==4){
        bot1[k+100].genes[i][j] = rand() % 4; 
      }

    }
  }
  //Mama genes
  for (int i = 8; i<16; i++){
    for(int j = 0; j<6; j++){
      bot1[k + 100].genes[i][j] = bot1[k+1].genes[i][j];


      //Gives the 5 percent chance of mutation
      if (mutation == 1 && j==4){
        bot1[k+100].genes[i][j] = rand() % 4; 
      }

    }
  }
  }
}

float genAverage(){
  float average = 0; 
  for(int i = 0; i < 200; i++){
    average = average + bot1[i].getTurns(); 
  }
  return (average/200); 
}
