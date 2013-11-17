#include "gamerecord.h"
#include <ifstream>

using namespace std;

GameRecord::GameRecord(Board * board,PlayerQueue * player_queue){
  string tmp;
  for (Player * p: player_queue){
    data += "P";
    tmp= p->stringify();
    data += tmp.length();
    data += tmp;
  }
  data += "B";
  tmp = board->stringify();
  data += tmp.length();
  data += board->stringify();
}

bool GameRecord::save(string filename){
  ifstream ifs(filename,ifstream::in);
  string data = ifs.getline();
}

bool GameRecord::load(){
  string tmp;
  player_queue = new PlayerQueue;
  if(data.length() == 0)
    return false;
  else{
    int pos= 0;
    char type = data[pos++];
    int len ;
    if(type == 'P'){
      len = atoi(data.substr(pos,pos+2));
      pos+=2;
      Player * p = new Player();
      tmp = data.substr(pos,pos+len);
      pos += len;
      p->loadfromstring(tmp);
      player_queue.add(p);
    }
    else if (type == 'B'){
      len = atoi(data.substr(pos,pos+2));
      pos += 2;
      board = new Board();
      tmp = data.substr(pos,pos+len);
      pos +=len;
      board->loadfromstring(tmp);
    }
    else {
      return false;
    }
    return true;
  }
}





