# Probability Final Project
NTU 2019 Spring Probability Final Project
### 一些想法
1) 把多人簡化成只有三人的情況  
&ensp;&ensp;1. 抓自己後兩順位的人，用三人情況決定打誰  
&ensp;&ensp;2. 將所有人分3份，用三人情況決定打誰，打各組最高的  
~~2) Markov's Chain~~

## Statistic
### 對照組

| 策略  | Basic 勝率 (%) |Adv. 勝率 （％）|
| :------------- | :-------------: | :-----------: |
| 跟大家一樣 |	10 | 10|
| 隨機	| 8.4 | 10|

### 根據準確率

| 策略  | Basic 勝率 (%) | Adv. 勝率（％）|
| :------------- | :-------------: |:------------:|
| 準確率最高  | **11.5**  | 9.4 |
| 準確率最低	| 7.6 | 9.9|
| 準確率中	| 8.6 | |
| 準確度第二 / 第三	| 5.5 / 6 | |
| 準確率接近自己 |9.5| **12.4** (11~14)(僅限第一位)|
| 準確率高低交叉（外而內）  | 9.0 | |
| 準確率高低交叉（內而外）  | 9.98 (分佈更平均) | |
| 準確率高低交叉（外而內 until death）
| 準確率高低交叉（內而外 until death）
| 高多打高，反之（外而內）|	7.2 | |
| 高多打高，反之（內而外）|	 |

### 根據存活率

| 策略  | Basic 勝率 (%) | Adv. 勝率（％）|
| :------------- | :-------------: | :------------: |
| 存活率高(含自己)| 8 | 11 |
| 存活率高(不含自己)| 10 | 10.2|
| 存活率低(含自己)	| **11.2** |9.6 |
| 存活率低(不含自己)	| 7 | 10.1|
| 存活率中(含自己)	| 8.6 | 8.2 |
| 存活率中(不含自己)	| 7.6 | 10.2 |
| 自己的存活率(誰可能打我我打誰) | **11.6** | 9.9 |
| 自己的存活率(機率) | 10.4 | 10.3 |
| 存活率機率選擇(含自己)| 8.1 | 10.3|
| 存活率機率選擇(不含自己)| 8.6 | 10.0|

### 根據準確率、存活率

| 策略  | Basic 勝率 (%) |Adv. 勝率（%）|
| :------------- | :-------------: | :-------------:|
| 存活率高、準確度高	| 同準確度高 | |
| 存活率高、準確度低	|  | |
| 存活率低、準確度高	| **11.7 (11:9)** | |
| 存活率低、準確度低	|  | |
