/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014,  National Institute of Standards and Technology.
 *
 * This file is part of NDN iot-api (In-Network Composition).
 * See AUTHORS.md for complete list of iot-api authors and contributors.
 *
 * iot-api is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * iot-api is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * iot-api, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

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
