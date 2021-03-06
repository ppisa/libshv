#include <shv/chainpack/chainpackreader.h>
#include <shv/chainpack/chainpackwriter.h>
#include <shv/chainpack/rpcmessage.h>
//#include <shv/chainpack/chainpackprotocol.h>

#include <cassert>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <type_traits>

#include <QtTest/QtTest>
#include <QDebug>

using namespace shv::chainpack;
using std::string;

// Check that ChainPack has the properties we want.
#define CHECK_TRAIT(x) static_assert(std::x::value, #x)
CHECK_TRAIT(is_nothrow_constructible<RpcValue>);
CHECK_TRAIT(is_nothrow_default_constructible<RpcValue>);
CHECK_TRAIT(is_copy_constructible<RpcValue>);
CHECK_TRAIT(is_nothrow_move_constructible<RpcValue>);
CHECK_TRAIT(is_copy_assignable<RpcValue>);
CHECK_TRAIT(is_nothrow_move_assignable<RpcValue>);
CHECK_TRAIT(is_nothrow_destructible<RpcValue>);

namespace {
QDebug operator<<(QDebug debug, const std::string &s)
{
	//QDebugStateSaver saver(debug);
	debug << s.c_str();

	return debug;
}

std::string binary_dump(const RpcValue::String &out)
{
	std::string ret;
	for (size_t i = 0; i < out.size(); ++i) {
		uint8_t u = (uint8_t)out[i];
		//ret += std::to_string(u);
		if(i > 0)
			ret += '|';
		for (size_t j = 0; j < 8*sizeof(u); ++j) {
			ret += (u & (((uint8_t)128) >> j))? '1': '0';
		}
	}
	return ret;
}

}

class TestRpcMessage: public QObject
{
	Q_OBJECT
private:
	void rpcmessageTest()
{
	qDebug() << "============= chainpack rpcmessage test ============\n";
	qDebug() << "------------- RpcRequest";
	{
		RpcRequest rq;
		rq.setRequestId(123)
				.setMethod("foo")
				.setParams({{
								{"a", 45},
								{"b", "bar"},
								{"c", RpcValue::List{1,2,3}},
							}});
		rq.setMetaValue(RpcMessage::MetaType::Tag::ShvPath, "aus/mel/pres/A");
		std::stringstream out;
		RpcValue cp1 = rq.value();
		{ ChainPackWriter wr(out); rq.write(wr); }
		ChainPackReader rd(out);
		RpcValue cp2 = rd.read();
		qDebug() << cp1.toCpon() << " " << cp2.toCpon() << " len: " << out.str().size() << " dump: " << binary_dump(out.str());
		QCOMPARE(cp1.type(), cp2.type());
		RpcRequest rq2(cp2);
		QVERIFY(rq2.isRequest());
		QCOMPARE(rq2.requestId(), rq.requestId());
		QCOMPARE(rq2.method(), rq.method());
		QCOMPARE(rq2.params(), rq.params());
	}
	qDebug() << "------------- RpcResponse";
	{
		RpcResponse rs;
		rs.setRequestId(123).setResult(42u);
		std::stringstream out;
		RpcValue cp1 = rs.value();
		{ ChainPackWriter wr(out); rs.write(wr); }
		ChainPackReader rd(out);
		RpcValue cp2 = rd.read();
		qDebug() << cp1.toCpon() << " " << cp2.toCpon() << " len: " << out.str().size() << " dump: " << binary_dump(out.str());
		QVERIFY(cp1.type() == cp2.type());
		RpcResponse rs2(cp2);
		QVERIFY(rs2.isResponse());
		QCOMPARE(rs2.requestId(), rs.requestId());
		QCOMPARE(rs2.result(), rs.result());
	}
	{
		RpcResponse rs;
		rs.setRequestId(123)
				.setError(RpcResponse::Error::create(RpcResponse::Error::InvalidParams, "Paramter length should be greater than zero!"));
		std::stringstream out;
		RpcValue cp1 = rs.value();
		{ ChainPackWriter wr(out); rs.write(wr); }
		ChainPackReader rd(out);
		RpcValue cp2 = rd.read();
		qDebug() << cp1.toCpon() << " " << cp2.toCpon() << " len: " << out.str().size() << " dump: " << binary_dump(out.str());
		QVERIFY(cp1.type() == cp2.type());
		RpcResponse rs2(cp2);
		QVERIFY(rs2.isResponse());
		QCOMPARE(rs2.requestId(), rs.requestId());
		QCOMPARE(rs2.error(), rs.error());
	}
	qDebug() << "------------- RpcNotify";
	{
		RpcRequest rq;
		rq.setMethod("foo")
				.setParams({{
							   {"a", 45},
							   {"b", "bar"},
							   {"c", RpcValue::List{1,2,3}},
						   }});
		qDebug() << rq.toCpon();
		QVERIFY(rq.isSignal());
		std::stringstream out;
		RpcValue cp1 = rq.value();
		{ ChainPackWriter wr(out); rq.write(wr); }
		ChainPackReader rd(out);
		RpcValue cp2 = rd.read();
		qDebug() << cp1.toCpon() << " " << cp2.toCpon() << " len: " << out.str().size() << " dump: " << binary_dump(out.str());
		QVERIFY(cp1.type() == cp2.type());
		RpcRequest rq2(cp2);
		QVERIFY(rq2.isSignal());
		QCOMPARE(rq2.method(), rq.method());
		QCOMPARE(rq2.params(), rq.params());
	}
}
private slots:
	void initTestCase()
	{
		//qDebug("called before everything else");
	}
	void tests()
	{
		rpcmessageTest();
	}

	void cleanupTestCase()
	{
		//qDebug("called after firstTest and secondTest");
	}
};

QTEST_MAIN(TestRpcMessage)
#include "tst_chainpack_rpcmessage.moc"
