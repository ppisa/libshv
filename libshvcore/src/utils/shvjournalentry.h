#ifndef SHV_CORE_UTILS_SHVJOURNALENTRY_H
#define SHV_CORE_UTILS_SHVJOURNALENTRY_H

#include "../shvcoreglobal.h"

#include <shv/chainpack/rpcvalue.h>

namespace shv {
namespace core {
namespace utils {

class SHVCORE_DECL_EXPORT ShvJournalEntry
{
public:
	static const char *DOMAIN_VAL_CHANGE; /// see shv::chainpack::Rpc::SIG_VAL_CHANGED
	static const char *DOMAIN_VAL_FASTCHANGE; /// see shv::chainpack::Rpc::SIG_VAL_FASTCHANGED
	static const char *DOMAIN_VAL_SERVICECHANGE; /// see shv::chainpack::Rpc::SIG_SERVICE_VAL_CHANGED

	enum CourseType {Continuous = 0, Discrete};
	static const char* courseTypeToString(CourseType ct);
	static CourseType courseTypeFromString(CourseType ct);

	static constexpr int NO_SHORT_TIME = -1;

	std::string path;
	shv::chainpack::RpcValue value;
	int shortTime = NO_SHORT_TIME;
	std::string domain;
	CourseType course = Continuous;

	ShvJournalEntry() {}
	ShvJournalEntry(std::string path, shv::chainpack::RpcValue value, std::string domain, int short_time, CourseType course)
		: path(std::move(path))
		, value{value}
		, shortTime(short_time)
		, domain(std::move(domain))
		, course(course)
	{
	}
	ShvJournalEntry(std::string path, shv::chainpack::RpcValue value)
		: ShvJournalEntry(path, value, DOMAIN_VAL_CHANGE, NO_SHORT_TIME, Continuous) {}
	ShvJournalEntry(std::string path, shv::chainpack::RpcValue value, int short_time)
		: ShvJournalEntry(path, value, DOMAIN_VAL_FASTCHANGE, short_time, Continuous) {}
	ShvJournalEntry(std::string path, shv::chainpack::RpcValue value, std::string domain)
		: ShvJournalEntry(path, value, std::move(domain), NO_SHORT_TIME, Continuous) {}

	bool isValid() const {return !path.empty() && value.isValid();}
	void setShortTime(int short_time) {shortTime = short_time;}
};

} // namespace utils
} // namespace core
} // namespace shv

#endif // SHV_CORE_UTILS_SHVJOURNALENTRY_H
