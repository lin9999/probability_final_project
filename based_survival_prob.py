import random
from bisect import bisect_left
import multiprocessing as mp
import time
import random
import numpy as np

def survivalRateList(acc, alive, you, withoutMe):
    ret = [0.0]
    acc = np.array(acc)
    alive = np.array(alive)
    
    if withoutMe:
        aliveSum = np.sum(acc[alive])
        alive[you] = False

    for beShoot in range(1, len(acc)):
        if alive[beShoot] == False:
            ret.append(0.0)
            continue

        survivalRate = 1.0
        for i in range(1, len(acc)):
            if alive[i] == False or i == beShoot:
                continue

            survivalRate *= (1 - (acc[beShoot]/(aliveSum-acc[i]) * acc[i]))

        ret.append(survivalRate)

    return ret

# TODO: basic
def shoot_next_1(acc, alive, you):
    prob_sum = 0.0
    cdf = [0.0]
    survival = survivalRateList(acc, alive, you, 1)

    for i in range(1, len(survival)):
        if i != you and alive[i]:
            prob_sum += survival[i]
        cdf.append(prob_sum)

    draw = random.uniform(0, prob_sum)
    return BS(cdf, draw)

# TODO: advanced
def shoot_next_2(acc, alive, turn):

    #random.seed(time.time())
    draw = random.randint(1, 10)
    while (not alive[draw]):
        draw = random.randint(1, 10)
    return draw

def BS(arr, x):
    return bisect_left(arr, x) 

class game:
    def __init__(self, N, M, mode):
        self.N = N # number of players
        self.M = M # your player index
        self.mode = mode # 1 for basic; 2 for advanced
        self.alive = [True for _ in range(self.N+1)]
        self.nxt = [i+1 for i in range(self.N+1)]
        self.prev = [i-1 for i in range(self.N+1)]
        self.nxt[self.N] = 1
        self.prev[1] = self.N
        self.acc = [random.random() for _ in range(self.N+1)]
        
    def revive(self):
        self.alive = [True for _ in range(self.N+1)]
        self.nxt = [i+1 for i in range(self.N+1)]
        self.prev = [i-1 for i in range(self.N+1)]
        self.nxt[self.N] = 1
        self.prev[1] = self.N
    
    def reset(self):
        self.acc = [random.random() for _ in range(self.N+1)]
        
    def decide(self, turn):
        if self.mode == 1:
            if turn == self.M:
                # your turn
                return shoot_next_1(self.acc, self.alive, turn)
            else:
                # others' turn
                prob_sum = 0.0
                cdf = [0.0]

                for i in range(1, len(self.acc)):
                    if i != turn and self.alive[i]:
                        prob_sum += self.acc[i]
                    cdf.append(prob_sum)

                draw = random.uniform(0, prob_sum)
                return BS(cdf, draw)
        else:
            # all shooters are same
            return shoot_next_2(self.acc, self.alive, turn)
    
    def shoot(self, p):
        if random.random() < p:
            return True
        else:
            return False
        
    def winner(self):
        for i in range(1, len(self.alive)):
            if self.alive[i]:
                return i
    
    def play(self, show=True, preempt=False):
        now = 1
        if show:
            print("accuracy:", self.acc[1:])
        
        while sum(self.alive) > 2:
            # get shooting target
            target = self.decide(now)
            if show:
                if target == 0:
                    print("\n", now, "PASS")
                else:
                    print("\n", now, "shoot", target)
            
            # invalid choice
            if (not self.alive[target]):
                print("player", target, "is OUT!")
                return 0
            
            # shoot
            if target == 0:
                pass
            elif self.shoot(self.acc[now]):
                self.alive[target] = False
                self.nxt[self.prev[target]] = self.nxt[target]
                self.prev[self.nxt[target]] = self.prev[target]
                if show:
                    print("TARGET DOWN!")
            else:
                if show:
                    print("MISSED...")
            
            # check if your are out for mode 1
            if preempt:
                if self.alive[self.M] == False:
                    break
            
            # get next shooter
            now = self.nxt[now]
                    
        win = self.winner()          
        if show:
            print("\nwinner:", win)
        return win
    
    def play_n(self, n):
        ret = 0
        self.reset()
        for _ in range(n):
            self.revive()
            win = self.play(show=False, preempt=True)
            if win == self.M:
                ret += 1
        return ret
                         
    def evaluate(self, sets, rounds, processes=4):
        with mp.Pool(processes=processes) as pool:
            results = pool.map(self.play_n, [rounds for _ in range(sets)])
        return sum(results) / (sets*rounds)
  
start = time.time()
g = game(10, 1, 1)
print("winning rate:", g.evaluate(1000, 1000, 8)*100)
print("time consumed:", time.time()-start)     