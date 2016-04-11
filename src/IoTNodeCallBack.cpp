#include "IoTNodeCallBack.hpp"

// Additional nested namespace could be used to prevent/limit name contentions
namespace iot {

//IotNodeCallBack::IotNodeCallBack() {}

Block IotNodeCallBack::onExactMatch(const Name prefix){


	static const std::string content = "Temperature";
	return ndn::encoding::makeBinaryBlock(Content, reinterpret_cast<const uint8_t*>(content.c_str()), content.size());



}
std::shared_ptr<Data> IotNodeCallBack::onDataForwarding(Name prefix, std::shared_ptr<Data> data){
	return data;
}
Interest IotNodeCallBack::onInterestForwarding(const Interest interest){
	return interest;
}

} // namespace iot

