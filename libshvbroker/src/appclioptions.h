#pragma once

#include "shvbrokerglobal.h"

#include <shv/chainpack/rpcvalue.h>
#include <shv/core/utils/clioptions.h>

#include <QSet>

namespace shv {
namespace broker {

class SHVBROKER_DECL_EXPORT AppCliOptions : public shv::core::utils::ConfigCLIOptions
{
private:
	using Super = shv::core::utils::ConfigCLIOptions;
public:
	AppCliOptions();
	//~AppCliOptions() Q_DECL_OVERRIDE {}

	CLIOPTION_GETTER_SETTER(std::string, l, setL, ocale)
	CLIOPTION_GETTER_SETTER2(int, "server.port", s, setS, erverPort)
#ifdef WITH_SHV_WEBSOCKETS
	CLIOPTION_GETTER_SETTER2(int, "server.websocket.port", s, setS, erverWebsocketPort)
#endif
	CLIOPTION_GETTER_SETTER2(std::string, "server.publicIP", p, setP, ublicIP)
	//CLIOPTION_GETTER_SETTER2(std::string, "sql.host", s, setS, qlHost)
	//CLIOPTION_GETTER_SETTER2(int, "sql.port", s, setS, qlPort)
	//CLIOPTION_GETTER_SETTER2(bool, "rpc.metaTypeExplicit", is, set, MetaTypeExplicit)
	CLIOPTION_GETTER_SETTER2(std::string, "etc.acl.fstab", f, setF, stabFile)
	CLIOPTION_GETTER_SETTER2(std::string, "etc.acl.users", u, setU, sersFile)
	CLIOPTION_GETTER_SETTER2(std::string, "etc.acl.grants", g, setG, rantsFile)
	CLIOPTION_GETTER_SETTER2(std::string, "etc.acl.paths", p, setP, athsFile)
	CLIOPTION_GETTER_SETTER2(shv::chainpack::RpcValue, "masters.connections", m, setM, asterBrokersConnections)
	CLIOPTION_GETTER_SETTER2(bool, "masters.enabled", is, set, MasterBrokersEnabled)
};

}}
