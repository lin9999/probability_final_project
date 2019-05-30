#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
using namespace std;

typedef map<int, double>::iterator ITER;
typedef struct PLAYER {
	int num;
	double hitRate;
} player;

int shootRandom(vector<player> hitRateRank, ITER shooter);
int shootMost(vector<player> hitRateRank, ITER shooter);
int shootMid(vector<player> hitRateRank, ITER shooter);
int shootLowest(vector<player> hitRateRank, ITER shooter);
int shootHighest(vector<player> hitRateRank, ITER shooter);
int shootByTurnsOut(vector<player> hitRateRank, ITER shooter);


