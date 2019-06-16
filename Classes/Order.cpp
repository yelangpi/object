#include"Order.h"
//a表示这个位置是false
//b表示这个位置是true
//将一个Order命令转换成一个chat message类
chat_message Order::orderToMessage() {
	char msg[10] = {"aaaaaaaaa"};
	if (this->KEY_W) msg[W] = 'b';
	else msg[W] = 'a';
	//
	if (this->KEY_S) msg[S] = 'b';
	else msg[S] = 'a';
	//
	if (this->KEY_A) msg[A] = 'b';
	else msg[A] = 'a';
	//
	if (this->KEY_D) msg[D] = 'b';
	else msg[D] = 'a';
	//
	if (this->KEY_J) msg[J] = 'b';
	else msg[J] = 'a';
	//
	if (this->KEY_1) msg[ONE] = 'b';
	else msg[ONE] = 'a';
	//
	if (this->KEY_2) msg[TWO] = 'b';
	else msg[TWO] = 'a';
	//
	if (this->KEY_3) msg[THR] = 'b';
	else msg[THR] = 'a';
	//表明阵营
	msg[8] = this->FLAG;
	msg[9] = '\0';
	chat_message send;
	send.body_length(std::strlen(msg));
	memcpy(send.body(), msg, send.body_length());
	send.encode_header();

	return send;
}

//修改了order，加了一个阵营变量
//并且这个变量是存在了第9个位置
Order messageToOrder(const std::string order)
{	
	Order command;
	if (order[0] == 'b')command.KEY_W = true;
	if (order[1] == 'b')command.KEY_S = true;
	if (order[2] == 'b')command.KEY_A = true;
	if (order[3] == 'b')command.KEY_D = true;
	if (order[4] == 'b')command.KEY_J = true;
	if (order[5] == 'b')command.KEY_1 = true;
	if (order[6] == 'b')command.KEY_2 = true;
	if (order[7] == 'b')command.KEY_3 = true;
	command.FLAG = order[8];
	return command;
}
