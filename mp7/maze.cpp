/* Your code here! */
#include <iostream>
#include <queue>
#include "maze.h"
using namespace std;

SquareMaze::SquareMaze()
{
    w = 0;
    h = 0;
}

void SquareMaze::makeMaze(int width, int height)
{
   //if the table exists, erase it 
    if (w!=0 || h!=0)
        table.clear();
   //make a new table
    if(width == 0 || height == 0) return;
    w = width;
    h = height;
    //first bool stands for right wall, second -> down
    std::pair<bool,bool> a = std::make_pair(false,false);
    //the wall we want to delete
    std::vector<std::pair<int,int>> wall;
    for (int i = 0; i < (w * h); i ++){
        table.push_back(a);
        std::pair<int,int> rwall (i,0);
        std::pair<int,int> dwall (i,1);
        wall.push_back(rwall);
        wall.push_back(dwall);
    }
    cycle.addelements(w*h);
    //start from the first cell
    int size = w*h;
    int count = 0;
    while (count!=size-1){//while there is a wall we can delete
        //wanty is the wall we want to delete
        srand ((unsigned) time(0));
        int want = rand()% wall.size();
        std::pair<int,int> wanty = wall[want];//the wall we want
        int room = wanty.first;
        int wantwall = wanty.second;//the wall in the room
        wall[want] = wall.back();
        wall.pop_back();//change order to make it O(1)

        if (room == (w*h)-1) continue;
     
        else if( (room+1)%w == 0) {//rightest
            if(wantwall == 1){
            if(cycle.find(room)!= cycle.find(room+w) && table[room].second!=true){
            table[room].second = true;
            cycle.setunion(room,room+w);
            count++;
            }
        }
        }

        else if ( (room >= (w*h)-w)){//lowest
            if(wantwall == 0){
            if(cycle.find(room)!=cycle.find(room+1) && table[room].first!=true){
                    table[room].first = true;
                     cycle.setunion(room,room+1);
                    count++;
            }
        }
        }
        else{//middle!
        if(cycle.find(room)!=cycle.find(room+1) && table[room].first!= true){
        table[room].first = true;
         cycle.setunion(room,room+1);
        count++;
        }
        else{
        if(cycle.find(room)!= cycle.find(room+w)&& table[room].second != true){   
        table[room].second = true;
         cycle.setunion(room,room+w);
        count++;
             }
        }
    
    }//middle else
 }//while
}//end

bool SquareMaze::canTravel(int x , int y, int dir) const
{
    if (dir == 0) return table[x+y*w].first;
    if (dir == 1) return table[x+y*w].second;
    if (dir == 2) {
        if ((x+y*w)%w == 0) return false;//most left
        else return table[x+y*w-1].first;
    }
    else {
        if (y==0) return false;
        else return table[x+ y*w -w].second;
    }
}

void SquareMaze::setWall(int x, int y , int dir, bool exists)
{
    if (dir == 0)
    table[x + w*y ].first = (!exists);
    else 
    table[x+w*y].second = (!exists);
}

std::vector<int> SquareMaze::solveMaze()
{
  
  //find the length from origin to every point  
  std::queue<int> rooms;
  std::vector<int> length;
  std::vector<bool> visit;
  std::vector<int> prev;
  length.resize(w*h);
  prev.resize(w*h);
  visit.push_back(true);
 // cout<<"1"<<endl;
  for (int i = 1; i < w*h; i++)
      visit.push_back(false);
  rooms.push(0);
  length.push_back(0);
  int count = 0;
 // cout<<"2"<<endl;
  while (!rooms.empty()){
   int room = rooms.front();
   rooms.pop();
   int x = room%w;
   int y = room/w;
    count++;
    //right
    if (canTravel(x,y,0)){
        if(!visit[room+1]){
        rooms.push(room+1);
        length[room+1] = count;
        visit[room+1] = true;
        prev[room+1] = room;
        }
    }
    if (canTravel(x,y,1)){
        if(!visit[room+w]){
        rooms.push(room+w);
        length[room+w] = count;
        visit[room+w] = true;
        prev[room+w] = room;
        }
    }
    if (canTravel(x,y,2)){
        if(!visit[room-1]){
            rooms.push(room-1);
            length[room-1] = count;
            visit[room-1] = true;
            prev[room-1] = room;
        }
    }
    if (canTravel(x,y,3)){
        if(!visit[room-w]){
            rooms.push(room-w);
            length[room-w] = count;
            visit[room-w] = true;
            prev[room-w] = room;
        }
    }

  
  }

  //  cout<<"length"<<endl;
  //find the largest length
  int maxroom = w*h-w;
  int max = length[w*h-w];  
  for(int i = w*h-w+1 ; i<w*h; i++){
    if(length[i]>max){
        maxroom = i;
        max = length[i];
    }
  }

  
//  cout<<"largest"<<endl;
  
  
  //find the solution
  std::vector<int> reverse;
  std::vector<int> soln; 
    int res = maxroom;
    while(res!=0){
    int prevroom = prev[res];
    if(prevroom-res == -1)
        reverse.push_back(0);
    else if (prevroom-res == -w)
        reverse.push_back(1);
    else if (prevroom -res == 1)
        reverse.push_back(2);
    else 
        reverse.push_back(3);
    
    res = prevroom;
    }
  for (int i = reverse.size()-1; i>=0 ; i--){
      soln.push_back(reverse[i]);
  }
//  cout<<"solution"<<endl;
  return soln;
}



PNG* SquareMaze::drawMaze() const
{
    PNG * output = new PNG();
    int width = w*10 + 1;
    int height = h*10 +1;
    (*output).resize(width,height);
    for (int i = 10; i <width; i ++){
        (*output)(i,0)->red = 0;
        (*output)(i,0)->green = 0;
        (*output)(i,0)->blue  = 0;
    }
    for (int i = 0; i <height ; i++){
     (*output)(0,i)->red = 0;
     (*output)(0,i)->green = 0;
     (*output)(0,i)->blue  = 0;
    }
    for (unsigned long i = 0; i < table.size(); i ++){
        //coordinate
        int x = i % w;
        int y = i/w;
        if (table[i].first == false){
            for(int k = 0; k <=10 ; k++){
                (*output)((x+1)*10,y*10+k)->red = 0;
                (*output)((x+1)*10,y*10+k)->green = 0;
                (*output)((x+1)*10,y*10+k)->blue = 0;
        }
        }
        if (table[i].second == false){
            for(int k = 0; k <=10 ; k++){
                (*output)(x*10+k,(y+1)*10)->red = 0;
                (*output)(x*10+k,(y+1)*10)->green = 0;
                (*output)(x*10+k,(y+1)*10)->blue = 0;
            }

    }
    }
    return output;
}

PNG*SquareMaze::drawMazeWithSolution()
{
     PNG * output = drawMaze();
     std::vector<int> soln = solveMaze();
     int des = 0;
     int x = 5;
     int y = 5;
     for (unsigned long i = 0 ; i < soln.size(); i++){
        if(soln[i] == 0){
            des += 1;
            for (int j = 0; j <=10; j ++){
                (*output)(x+j,y)->red = 255;
                (*output)(x+j,y)->green = 0;
                (*output)(x+j,y)->blue = 0;
            }
            x += 10;
        }
        else if (soln[i] == 1){
            des = des + w;
            for (int j = 0; j <=10; j ++){
              (*output)(x,y+j)->red = 255;
             (*output)(x,y+j)->green = 0;
                (*output)(x,y+j)->blue = 0;
            }
            y += 10;
        }
        else if (soln[i]==2){
            des = des - 1;
            for (int j = 0; j <=10 ; j++){
                (*output)(x-j,y)->red = 255;
                (*output)(x-j,y)->green = 0;
                (*output)(x-j,y)->blue = 0;
            }
            x += -10;
        }
        else {
            des = des - w;
            for (int j = 0; j <= 10; j++){
                (*output)(x,y-j)->red = 255;
                (*output)(x,y-j)->green = 0;
                (*output)(x,y-j)->blue = 0;
            }
            y += -10;
        }
     }

     //cout<<"ded"<<endl;
     int desx = des%w;
     int desy = des/w;
     for (int k = 1; k < 10; k++){
        (*output)(desx*10+k,(desy+1)*10)->red = 255;
        (*output)(desx*10+k,(desy+1)*10)->green = 255;
        (*output)(desx*10+k,(desy+1)*10)->blue = 255;
     }
     return  output;
}

