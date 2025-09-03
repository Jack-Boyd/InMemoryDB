#pragma once
#include "QueryEngine.hpp"
#include <boost/asio.hpp>
#include <memory>
#include <string>

class Session : public std::enable_shared_from_this<Session> {
public:
  Session(boost::asio::ip::tcp::socket socket, QueryEngine& engine);
  void start();
private:
  void doRead();
  void doWrite(const std::string& response);

  boost::asio::ip::tcp::socket m_socket;
  boost::asio::streambuf m_buffer;
  QueryEngine& m_engine;
};

class Server {
public: 
  Server(boost::asio::io_context& io_context, short port, QueryEngine& engine);
private:
  void doAccept();
  boost::asio::ip::tcp::acceptor m_acceptor;
  QueryEngine& m_engine;
};