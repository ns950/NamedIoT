
#include "IoTNode.hpp"

// Additional nested namespace could be used to prevent/limit name contentions
namespace iot {

//IotNode::IotNode(){

//}
void IotNode::createIoTNode(std::string name, IotNodeCallBack* iotcb, bool debug){

	m_debug = debug;
	m_iotcb = iotcb;
	m_name = name;
	m_face_i.setInterestFilter(m_name,
			bind(&IotNode::onInterestFromConsumer, this, _1, _2),
			RegisterPrefixSuccessCallback(),
			bind(&IotNode::onRegisterFailed, this, _1, _2));
	m_face_i.processEvents();
	if(m_debug){
		std::cout << "Node creation successful " << std::endl;
	}

}

void IotNode::localOnMatch(const Interest& interest){

	if(m_debug){
		std::cout << "IotNode::localOnMatch with interest" << interest << std::endl;
	}
	//
	Name dataName(m_name);
	dataName
	.appendVersion();  // add "version" component (current UNIX timestamp in milliseconds)

	Block content = m_iotcb->onExactMatch(interest.getName());
	// Create Data packet
	shared_ptr<Data> data = make_shared<Data>();
	data->setName(dataName);
	data->setFreshnessPeriod(ndn::time::seconds(10));
	data->setContent(content);
	m_keyChain.sign(*data);
	std::cout << ">> D: " << *data << std::endl;
	m_face_i.put(*data);
}

void IotNode::localOnForwarding(const Interest& interest){


	if(m_debug){
		std::cout << "IotNode::localOnForwarding with interest: " << interest << std::endl;
	}
	Interest interest_o;
	// Use delimiter with the interest name ex :/n1/n2/n3 --> /n2/n3

	std::string newName = interest.getName().toUri();

	if(m_debug){
		std::cout << "newName by getName=: " << newName << std::endl;
	}

	std::string delimiter = m_name;

	newName.erase(0, delimiter.length());

	if(m_debug){
		std::cout << "newName by erase m_name=: " << newName << std::endl;
	}

	Name iName(newName);


	interest_o.setName(iName);
	interest_o.setInterestLifetime(ndn::time::milliseconds(INTEREST_LIFE_TIME));
	interest_o.setMustBeFresh(true);

	if(m_debug){
		std::cout << "IotNode::localOnForwarding calling Specific Implementation with: " << interest_o << std::endl;
	}
	interest_o = m_iotcb->onInterestForwarding(interest_o);

	if(m_debug){
		std::cout << "IotNode::localOnForwarding IoT call back at address " << m_iotcb << std::endl;
		std::cout << "IotNode::localOnForwarding with interest out: " << interest_o << std::endl;
	}

	m_face_o.expressInterest(interest_o,
			bind(&IotNode::onData, this,  _1, _2),
			bind(&IotNode::onTimeout, this, _1));

	if(m_debug){
		std::cout << "Sending " << interest_o << std::endl;
	}
	// processEvents will block until the requested data received or timeout occurs
	m_face_o.processEvents();

}

void IotNode::onInterestFromConsumer(const InterestFilter& filter, const Interest& interest)
{
	if(m_debug){
		std::cout << "IotNode::onInterestFromConsumer with interest: " << interest << std::endl;
	}

	Name interestName = interest.getName();
	// Verify that this is the EXACT MATCH
	bool isMatch=interest.matchesName(Name(m_name));

	if  (isMatch==true)
	{
		if(m_debug){
			std::cout << "IotNode::onInterestFromConsumer Exact match " << std::endl;
		}
		localOnMatch(interest);

	}
	else

	{
		if(m_debug){
			std::cout << "IotNode::onInterestFromConsumer NOT Exact match " << std::endl;
		}
		localOnForwarding(interest);

	}

}

void  IotNode::onData(const Interest& interest, const Data& data)
{
	if(m_debug){
		std::cout << "IotNode::onData with data: " << data << std::endl;
	}
	Name name= Name(m_name);
	shared_ptr<Data> data_to_forward = make_shared<Data>();
	data_to_forward->setName(name.append(data.getName()));
	data_to_forward->setFreshnessPeriod(ndn::time::seconds(10));
	data_to_forward->setContent(data.getContent());

	if(m_debug){
		std::cout << "IotNode::onData  Calling Specific Implementation with data to forward : " << data_to_forward << std::endl;
	}
	data_to_forward = m_iotcb->onDataForwarding(data.getName(), data_to_forward);
	if(m_debug){
		std::cout << "IotNode::onData  data to forward updated : " << data_to_forward << std::endl;
	}


	m_keyChain.sign(*data_to_forward);
	if(m_debug){
		std::cout << ">> D: " << *data_to_forward << std::endl;
	}
	m_face_i.put(*data_to_forward);
}

void IotNode::onTimeout(const Interest& interest)
{
	if(m_debug){
		std::cout << "Timeout: " << interest << std::endl;
	}
}

void IotNode::onRegisterFailed(const Name& prefix, const std::string& reason)
{
	if(m_debug){
		std::cerr << "ERROR: Failed to register prefix \""
				<< prefix << "\" in local hub's daemon (" << reason << ")"
				<< std::endl;
		m_face_i.shutdown();
	}
}


} // namespace iot


