#ifndef IOT_IOTNODECALLBACK_HPP
#define IOT_IOTNODECALLBACK_HPP

#include "common.hpp"

// Additional nested namespace could be used to prevent/limit name contentions
namespace iot {

class IotNodeCallBack
{
public:
	//IotNodeCallBack() {}
	virtual Block onExactMatch(const Name prefix)=0;
	virtual Interest onInterestForwarding(const Interest interest)=0;
	virtual std::shared_ptr<Data> onDataForwarding(Name prefix, std::shared_ptr<Data> data)=0;
};

} //namespace iot


#endif //IOT_IOTNODECALLBACK_HPP
