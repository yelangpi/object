#pragma once
#ifndef _ORDER_H
#define _ORDER_H
#include<string>
#include"message.h"
//��order����¼���й���֮�з������¼�
//Ȼ����update������Ҫ����ת�����ܹ����͵���
//�������� һ����Ա���� ����װ�����ܷ��͵�����
//һ���ǽ��������ַ���ת����ָ��
//����һ�����������ͣ����浱ǰ����Ӫ
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

//ת�����ܹ������������������
Order messageToOrder(const std::string);
#endif