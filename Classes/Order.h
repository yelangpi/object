#pragma once
#ifndef _ORDER_H
#define _ORDER_H
#include<string>
#include"message.h"
//用order来记录所有过程之中发生的事件
//然后在update函数里要将其转换成能够发送的类
//两个函数 一个成员函数 将其装换成能发送的类型
//一个是将接来的字符串转换成指令
//添了一个变量的类型，储存当前的阵营
class Order {
public:
	enum { W, S, A, D, J, ONE, TWO, THR };
	Order() = default;
	chat_message orderToMessage();

public:
	bool KEY_W = false;
	bool KEY_S = false;
	bool KEY_A = false;
	bool KEY_D = false;
	bool KEY_J = false;
	bool KEY_1 = false;
	bool KEY_2 = false;
	bool KEY_3 = false;
	char FLAG = 'N';
};

//转换成能够被程序所解码的命令
Order messageToOrder(const std::string);
#endif