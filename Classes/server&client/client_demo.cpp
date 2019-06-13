#include"boost/asio.hpp"
#include"boost/array.hpp"
#include<iostream>
//Echo client
/*
	实现功能：
	接收客户输入的信息
	发送到服务端
	接收从服务端发送的信息
*/
using namespace boost::asio::ip;

int main(int argc,char* argv[]) {
	try{
		if (argc != 3) {
			std::cerr << "Usage" << argv[0] << "<host><post>";
			return 1;
		}
	//
	enum { BUFF_SIZE = 1024 };
	boost::asio::io_context ioc;
	tcp::resolver resolver(ioc);
	auto endpoints = resolver.resolve(tcp::v4(), argv[1], argv[2]);
	tcp::socket socket(ioc);
	boost::asio::connect(socket, endpoints);
	//
	char buff[BUFF_SIZE];
	std::size_t request_length = 0;
	do {
		std::cout << "Enter a sentence here:"<< std::endl;
		std::cin.getline(buff, BUFF_SIZE);
		request_length = std::strlen(buff);
	} while (request_length == 0);
	boost::asio::write(socket, boost::asio::buffer(buff, request_length));
	//
	char reply[BUFF_SIZE];
	std::size_t reply_length= boost::asio::read(
		socket, boost::asio::buffer(reply, request_length)
	);

	std::cout.write(reply, reply_length);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}