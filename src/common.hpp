#ifndef IOT_COMMON_HPP
#define IOT_COMMON_HPP

#include <iconv.h>
#include <sstream>
#include <ndn-cxx/face.hpp>
#include <ndn-cxx/interest.hpp>
#include <ndn-cxx/name.hpp>
#include <ndn-cxx/data.hpp>
#include <ndn-cxx/selectors.hpp>
#include <ndn-cxx/key-locator.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <ndn-cxx/security/validator-config.hpp>
#include <ndn-cxx/util/time.hpp>
#include <ndn-cxx/util/scheduler.hpp>
#include <ndn-cxx/encoding/block-helpers.hpp>

#include <boost/utility.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/geometric_distribution.hpp>

#include <map>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <iostream>
#include <functional>
#include <memory>

namespace iot {

using ndn::Face;
using ndn::Block;
using ndn::Name;
namespace name = ndn::name;
using ndn::Interest;
using ndn::InterestFilter;
using ndn::RegisterPrefixSuccessCallback;
using ndn::Selectors;
using ndn::Exclude;
using ndn::Data;
using ndn::KeyLocator;
using ndn::KeyChain;
using ndn::Scheduler;
using ndn::ValidatorConfig;
using ndn::tlv::Content;

using std::shared_ptr;
using std::make_shared;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;

using boost::noncopyable;

//using iot::IotNodeCallBack;
//using iot::IotNode;

typedef uint64_t ProcessId;
typedef uint64_t SegmentNo;

const int  INTEREST_LIFE_TIME = 5000;

} // namespace iot

#endif // IOT_COMMON_HPP
