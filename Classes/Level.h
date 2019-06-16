#pragma once
#ifndef _LEVEL_H
#define _LEVEL_H

#define LEVEL_1		0
#define LEVEL_2		100
#define LEVEL_3		200
#define LEVEL_4		300
#define LEVEL_5		400
#define LEVEL_6		500
#define LEVEL_7		600
#define LEVEL_8		700
#define LEVEL_9		800
#define LEVEL_10	900
#define LEVEL_11	1000
#define LEVEL_12	1100
#define LEVEL_13	1200
#define LEVEL_14	1300
#define LEVEL_15	1400
//
#define LEVEL_1_hp		300
#define LEVEL_2_hp		340
#define LEVEL_3_hp		380
#define LEVEL_4_hp		420
#define LEVEL_5_hp		460
#define LEVEL_6_hp		500
#define LEVEL_7_hp		540
#define LEVEL_8_hp		580
#define LEVEL_9_hp		620
#define LEVEL_10_hp		660
#define LEVEL_11_hp		700
#define LEVEL_12_hp		740
#define LEVEL_13_hp		780
#define LEVEL_14_hp		820
#define LEVEL_15_hp		850
//
#define LEVEL_1_mp		100
#define LEVEL_2_mp		140
#define LEVEL_3_mp		180
#define LEVEL_4_mp		220
#define LEVEL_5_mp		260
#define LEVEL_6_mp		300
#define LEVEL_7_mp		340
#define LEVEL_8_mp		380
#define LEVEL_9_mp		420
#define LEVEL_10_mp		460
#define LEVEL_11_mp		500
#define LEVEL_12_mp		540
#define LEVEL_13_mp		680
#define LEVEL_14_mp		720
#define LEVEL_15_mp		750
//
#define LEVEL_1_attack		30
#define LEVEL_2_attack		35
#define LEVEL_3_attack		40
#define LEVEL_4_attack		45
#define LEVEL_5_attack		50
#define LEVEL_6_attack		55
#define LEVEL_7_attack		60
#define LEVEL_8_attack		65
#define LEVEL_9_attack		70
#define LEVEL_10_attack		75
#define LEVEL_11_attack		80
#define LEVEL_12_attack		85
#define LEVEL_13_attack		90
#define LEVEL_14_attack		95
#define LEVEL_15_attack		100

#define LEVEL_1_defence		5
#define LEVEL_2_defence		6
#define LEVEL_3_defence		7
#define LEVEL_4_defence		8
#define LEVEL_5_defence		9
#define LEVEL_6_defence		10
#define LEVEL_7_defence		11
#define LEVEL_8_defence		12
#define LEVEL_9_defence		13
#define LEVEL_10_defence	14
#define LEVEL_11_defence	15
#define LEVEL_12_defence	16
#define LEVEL_13_defence	17
#define LEVEL_14_defence	18
#define LEVEL_15_defence	19

#define LEVEL_1_movingrate		10
#define LEVEL_2_movingrate		10
#define LEVEL_3_movingrate		10
#define LEVEL_4_movingrate		10
#define LEVEL_5_movingrate		10
#define LEVEL_6_movingrate		10
#define LEVEL_7_movingrate		11
#define LEVEL_8_movingrate		11
#define LEVEL_9_movingrate		11
#define LEVEL_10_movingrate		11
#define LEVEL_11_movingrate		11
#define LEVEL_12_movingrate		11
#define LEVEL_13_movingrate		12
#define LEVEL_14_movingrate		12
#define LEVEL_15_movingrate		13

#define LEVEL_HP(X) (300+(40*X))
#define LEVEL_MP(X) (200+(10*X))
#define LEVEL_ATTACK(X) (25+(X*5))
#define LEVEL_DEFENCE(X) (4+X)
#define LEVEL_RATE(X) (10+(X%10))
#define LEVEL(X) (100*(X-1))

#endif