/*
 * author : 林恩廷
 * strategy : if I have a high hit rate, shoot the player who has the lowest hit rate
 *			  else shoot the player who has the hightest rate
 * winning rate : 7.3%
 * 
 * parameter : use 'g++ [file name] -D SHOWMESSAGE' 
 *                          to show detail message of each round.
 * add your code at line 60, remember that you can't shoot your self!
 */

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

const int T = 100000; // # of experiments
const int N = 10; // # of player
const int ME = 0; // My number

void printHitRate(map<int, double> &players) {
	puts(" ===== hit rate information ===== ");
	for (ITER i = players.begin(); i != players.end(); i++)
		printf("|    player  %d   :   %f    |\n", i->first, i->second);
	puts(" ================================ ");
}

bool cmp(player p1, player p2) {
	return p1.hitRate < p2.hitRate;
}

double init(map<int, double> &players, vector<player> &hitRateRank) {
	double hitRateSum = 0.0;
	for (int i = 0; i < N; i++) { // set players' hit rate
		player newPlayer = {
			i, // num
			(rand() / (double)RAND_MAX) // hitRate	
		};
		players.insert(make_pair(newPlayer.num, newPlayer.hitRate));
		hitRateRank[i] = newPlayer;
		hitRateSum += newPlayer.hitRate;
	}
	sort(hitRateRank.begin(), hitRateRank.end(), cmp);

#ifdef SHOWMESSAGE
	printHitRate(players);
#endif
	return hitRateSum;
}

int choosBeShot(map<int, double> players, vector<player> hitRateRank, ITER shooter, double hitRateSum, bool isMe) {
	
	if (isMe) { // TODO (add your strategy, remember do not shoot yourself !!)
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
	} else { // others
		// a shooter can't shoot himself
		players.erase(shooter->first);
		hitRateSum -= shooter->second;
		double randomIndex = hitRateSum * (rand() / (double)RAND_MAX);
		for (ITER iter = players.begin(); iter != players.end(); iter++) {
			if (randomIndex < iter->second)
				return iter->first;
			randomIndex -= iter->second;
		}	
	}
	
	return -1;
}

bool judge(double hitRate) {
	return (rand() / (double)RAND_MAX) < hitRate;
}

void printWinRate(vector<int> &winner) {
	puts(" ========= winning rate ========= ");
	printf("|\tT = %d N = %d\t|\n", T, N);
	for (int i = 0; i < N; i++) {
		if (i == ME) {
			printf("|  (ME) player %d : %f\t|\n", i, winner[i] / (double)T);
		} else {
			printf("|\tplayer %d : %f\t|\n", i, winner[i] / (double)T);
		}
	}
	puts(" ================================ ");
}

int main () {
	srand((unsigned)time(NULL));

	vector<int> winner(N, 0);
	for (int t = 0; t < T; t++) { // T experiments
		map<int, double> players;
		vector<player> hitRateRank(N);
		double hitRateSum = init(players, hitRateRank);

		ITER shooter = players.begin(); // start from shooter 0
		int beShot;
		while (players.size() != 1) {
			beShot = choosBeShot(players, hitRateRank, shooter, hitRateSum, shooter->first == ME);
			if (shooter->first == beShot || beShot == -1) {
				printf("*** %d shoot %d ***\n\n", shooter->first, beShot);
				printf("find beShot error!!");
				exit(1);
			}

			if (judge(players[shooter->first])) {
#ifdef SHOWMESSAGE				
				printf("*** %d shoot %d : Success !! ***\n\n", shooter->first, beShot);
#endif				
				// delete player
				hitRateSum -= players[beShot];
				players.erase(beShot);
				for (int i = 0; i < hitRateRank.size(); i++) {
					if (hitRateRank[i].num == beShot)
						hitRateRank.erase(hitRateRank.begin() + i);
				}
			}

#ifdef SHOWMESSAGE	
			else	printf("*** %d shoot %d : Failed ***\n\n", shooter->first, beShot);
#endif

			shooter++;
			if (shooter == players.end())
				shooter = players.begin();
		}
		winner[players.begin()->first]++; // winner is the only one who is alive

#ifdef SHOWMESSAGE
		printf("=== round %d , winner is %d ===\n\n", t+1, players.begin()->first);
#endif
	}
	printWinRate(winner);
	return 0;
}
