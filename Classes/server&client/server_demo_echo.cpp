#include"boost/asio.hpp"
#include"boost/array.hpp"
#include<iostream>
//Echo Sever
using namespace boost::asio::ip;
void Session(tcp::socket socket) {
	enum { BUF_SIZE = 1024 };
	try {
		while (true) {
			boost::array<char, BUF_SIZE> data;
			boost::system::error_code ec;
			std::size_t length = socket.read_some(boost::asio::buffer(data), ec);

			if (ec == boost::asio::error::eof) {
				std::cout << "Has been closed" << std::endl;
				break;
			}
			else if (ec) {
				throw boost::system::system_error(ec);
			}

			boost::asio::write(socket, boost::asio::buffer(data, length));
		}
	}
	catch (const std::exception&e) {
		std::cerr << "Exception:" << e.what() << std::endl;
	}
}

int main(int argc,char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << "<port>" << std::endl;
		return 1;
	}
	unsigned short port = std::atoi(argv[1]);

	boost::asio::io_context ioc;

	//Acceptor Listener to listen the new connect
	tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), port));

	try {
		while (true) {
			Session(acceptor.accept());
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception " << e.what() << std::endl;
	}

	return 0;
}