#include "brokertcpserver.h"
#include "clientbrokerconnection.h"

#include <shv/iotqt/rpc/socket.h>

namespace shv {
namespace broker {
namespace rpc {

BrokerTcpServer::BrokerTcpServer(QObject *parent)
	: Super(parent)
{

}

ClientBrokerConnection *BrokerTcpServer::connectionById(int connection_id)
{
	return qobject_cast<rpc::ClientBrokerConnection *>(Super::connectionById(connection_id));
}

shv::iotqt::rpc::ServerConnection *BrokerTcpServer::createServerConnection(QTcpSocket *socket, QObject *parent)
{
	return new ClientBrokerConnection(new shv::iotqt::rpc::TcpSocket(socket), parent);
}

}}}
