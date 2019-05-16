#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include "HitRateStrategy.h"
using namespace std;

/* winning rate : 8.4% */
int shootRandom(vector<player> hitRateRank, ITER shooter){
	for (int i = 0; i < hitRateRank.size(); i++) {
		if (hitRateRank[i].num == shooter->first) // ME
			hitRateRank.erase(hitRateRank.begin() + i);
	}
	int index = rand() % (hitRateRank.size());
	return hitRateRank[index].num;	
}

/* strategy : if I have a high hit rate, shoot the player who has the lowest hit rate
 			  else shoot the player who has the hightest rate
 * winning rate : 7.3%*/
int shootMost(vector<player> hitRateRank, ITER shooter){
	int aliveNum = hitRateRank.size();
	for (int i = 0; i < aliveNum; i++) {
		if (hitRateRank[i].num == shooter->first) {
			if (i < aliveNum/2) { // high hitRate > low hitRate
				return hitRateRank[aliveNum-1].num;
			} else { // high hitRate <= low hitRate
				return hitRateRank[0].num;
			}
		}
	}	
}

/* winning rate : 8.6% */
int shootMid(vector<player> hitRateRank, ITER shooter){
	for (int i = 0; i < hitRateRank.size(); i++) {
		if (hitRateRank[i].num == shooter->first) // ME
			hitRateRank.erase(hitRateRank.begin() + i);
	}
	return hitRateRank[hitRateRank.size()/2].num;
}

/* winning rate : 7.6% */
int shootLowest(vector<player> hitRateRank, ITER shooter){
	for (int i = 0; i < hitRateRank.size(); i++) {
		if (hitRateRank[i].num == shooter->first)
			hitRateRank.erase(hitRateRank.begin() + i);
	}
	return hitRateRank[0].num;
}

/* winning rate : 11.5% */
int shootHighest(vector<player> hitRateRank, ITER shooter){
	for (int i = 0; i < hitRateRank.size(); i++) {
		if (hitRateRank[i].num == shooter->first)
			hitRateRank.erase(hitRateRank.begin() + i);
	}
	return hitRateRank[hitRateRank.size()-1].num;	
}

/* strategy : shoot the player who has the highest/lowest hit rate by turns
/* winning rate : 9.0% no matter start from the high or the low*/
int shootByTurnsOut(vector<player> hitRateRank, ITER shooter){
	for (int i = 0; i < hitRateRank.size(); i++) {
		if (hitRateRank[i].num == shooter->first) // ME
			hitRateRank.erase(hitRateRank.begin() + i);
	}
	if (flag) { // low
		flag = 0;
		return hitRateRank[0].num;
	} else { // high
		flag = 1;
		return hitRateRank[hitRateRank.size()-1].num;
	}
}
