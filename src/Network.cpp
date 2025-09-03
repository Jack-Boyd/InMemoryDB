#include "Network.hpp"
#include <iostream>

using boost::asio::ip::tcp;

Session::Session(tcp::socket socket, QueryEngine& engine)
  : m_socket(std::move(socket)), m_engine(engine) {}

void Session::start() {
  std::cout << "New client connected\n";
  doRead();
}

void Session::doRead() {
  auto self(shared_from_this());
  boost::asio::async_read_until(
    m_socket, m_buffer, '\n',
    [this, self](boost::system::error_code ec, std::size_t length) {
      if (!ec) {
        std::istream is(&m_buffer);
        std::string command;
        std::getline(is, command);

        if (command == "EXIT" || command == "QUIT") {
          doWrite("Goodbye\n");
          m_socket.close();
          return;
        }

        std::cout << "Command: " << command << "\n";
        std::string result = m_engine.execute(command);
        doWrite(result + "\n");
      }
    }
  );
}

void Session::doWrite(const std::string& response) {
  auto self(shared_from_this());
  boost::asio::async_write(
    m_socket, boost::asio::buffer(response),
    [this, self](boost::system::error_code ec, std::size_t) {
      if (!ec) {
        doRead();
      }
    }
  );
}

Server::Server(boost::asio::io_context& io_context, short port, QueryEngine& engine)
  : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)), m_engine(engine) {
  doAccept();
}

void Server::doAccept() {
  m_acceptor.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket) {
      if (!ec) {
        std::make_shared<Session>(std::move(socket), m_engine)->start();
      }
      doAccept();
    }
  );
}