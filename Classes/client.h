#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "message.h"
#include "cocos2d.h"
using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

//class Client;

//static Client*              this_client = nullptr;      ///指向client对象的指针


class chat_client
{
public:
	static chat_client* Create(boost::asio::io_context& io_service, const tcp::resolver::results_type& endpoints)
	{
		chat_client* c = new chat_client(io_service, endpoints);
		return c;
	}

	//需要一个iocontext和endpoints进行初始化
	chat_client(boost::asio::io_context& io_service, const tcp::resolver::results_type& endpoints)
		: io_service_(io_service), socket_(io_service)
	{

		boost::asio::async_connect(socket_, endpoints,
			boost::bind(&chat_client::handle_connect, this, boost::asio::placeholders::error));
	}
	//接受一个chat_message对象，异步回调do_write;
	void write(const chat_message& msg)
	{
		io_service_.post(boost::bind(&chat_client::do_write, this, msg));
	}
	//关闭，异步回调do_close
	void close()
	{
		io_service_.post(boost::bind(&chat_client::do_close, this));
	}
public:
	//连接回调函数，进行异步调用handle_read_header
	void handle_connect(const boost::system::error_code& error)
	{
		if (!error)
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), chat_message::header_length),
				boost::bind(&chat_client::handle_read_header, this, boost::asio::placeholders::error));
		}
	}
	//读取文件头，进行异步调用handle_read_body
	void handle_read_header(const boost::system::error_code& error)
	{
		if (!error && read_msg_.decode_header())
		{
			boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&chat_client::handle_read_body, this, boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			t_lock.lock();
			chat_message* newMsg = new chat_message();
			std::strcpy(newMsg->body(), read_msg_.body());
			newMsg->body_length(read_msg_.body_length());
			read_msg_list_.push_back(newMsg);
			t_lock.unlock();
			boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), chat_message::header_length),
				boost::bind(&chat_client::handle_read_header, this, boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void do_write(chat_message msg)
	{
		//检查私有数据成员
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);

		//
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&chat_client::handle_write, this, boost::asio::placeholders::error));
		}
	}
	//异步操作do_write完成后的回调函数
	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&chat_client::handle_write, this, boost::asio::placeholders::error));
			}
		}
		else
		{
			do_close();
		}
	}

	void do_close()
	{
		socket_.close();
	}

public:
	boost::mutex                t_lock;
	boost::asio::io_service&    io_service_;    ///asio的核心类, 用于创建socket
	tcp::socket                 socket_;        ///tcp类套接字
	std::deque<chat_message*>   read_msg_list_;
	chat_message                read_msg_;      ///每次循环所读取的数据对象
	chat_message_queue          write_msgs_;    ///等待被发送的数据对象
};