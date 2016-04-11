#include "common.hpp"
#include "IoTNodeCallBack.hpp"
#include "IoTNode.hpp"

// Additional nested namespace could be used to prevent/limit name contentions
namespace iot {
class Actuator : public IotNodeCallBack
{

public:
	Actuator(bool debug = false){
		m_debug = debug;
	}

	Block onExactMatch(const Name prefix){

		//std::cout << "Actuator::onExactMatch with name: " << prefix << std::endl;

		static const std::string content = "Status : Active";
		return ndn::encoding::makeBinaryBlock(Content, reinterpret_cast<const uint8_t*>(content.c_str()), content.size());



	}
	std::shared_ptr<Data> onDataForwarding(Name prefix, std::shared_ptr<Data> data){
		std::string content = std::string(reinterpret_cast<const char*>(data->getContent().value()), data-> getContent().value_size());
		std::cout << "Actuator Data : " << content << std::endl;
		return data;
	}
	Interest onInterestForwarding(const Interest interest){


		//std::cout << "Actuator::onInterestForwarding with interest" << interest << std::endl;

		return interest;
	}
private :
	bool m_debug;

};
} // namespace iot

static const std::string actuatorUsageMessage =
		/* argv[0] */ " - NDN IoT: Actuator\n "
		"-h: show help message\n "
		"-d: enable debugging \n "
		"-n: Name to listen on\n  ";



int
main(int argc, char** argv)
{
	std::string name = "/actuator";
	bool debug = false;
	int opt;
	while ((opt = getopt(argc, argv, "hn:d")) != -1) {
		switch (opt) {
		case 'h':
			std::cout << argv[0] << actuatorUsageMessage << std::endl;
			return 1;
		case 'n':
			name = std::string(optarg);
			break;
		case 'd':
			debug = true;
			break;
		default:
			std::cout << "setting name to "<< name << std::endl;
			break;
		}
	}
	iot::IotNode node1;
	iot::Actuator a(debug);
	try {
		if(debug){
			std::cout << "Starting the node ... " <<  name << std::endl;
		}
		node1.createIoTNode(name,&a,debug);
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return 2;
	}

	return 0;
}
