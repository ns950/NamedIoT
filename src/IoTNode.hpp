
#ifndef IOT_IOTNODE_HPP
#define IOT_IOTNODE_HPP

#include "common.hpp"
#include "IoTNodeCallBack.hpp"



// Additional nested namespace could be used to prevent/limit name contentions
namespace iot {

class IotNode
{
public:
	//~IotNode() {}
	void createIoTNode(std::string name, IotNodeCallBack* iotcb, bool debug);

private:
	void onInterestFromConsumer(const InterestFilter& filter, const Interest& interest);
	void onData(const Interest& interest, const Data& data);
	void onTimeout(const Interest& interest);
	void onRegisterFailed(const Name& prefix, const std::string& reason);
	void localOnMatch(const Interest& interest);
	void localOnForwarding(const Interest& interest);


private:
	bool m_debug;
	std::string m_name;
	Face m_face_i,m_face_o;
	KeyChain m_keyChain;
	IotNodeCallBack *m_iotcb;

};


} //namespace iot


#endif //IOT_IOTNODE_HPP
