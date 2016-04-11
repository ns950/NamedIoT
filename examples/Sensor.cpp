#include "common.hpp"
#include "IoTNodeCallBack.hpp"
#include "IoTNode.hpp"

// Additional nested namespace could be used to prevent/limit name contentions
namespace iot {

class Sensor : public IotNodeCallBack
{

public:


	Block onExactMatch(const Name prefix){


		//static const std::string content = "Temperature";
		return ndn::encoding::makeBinaryBlock(Content, reinterpret_cast<const uint8_t*>(m_value.c_str()), m_value.size());

	}
	std::shared_ptr<Data> onDataForwarding(Name prefix, std::shared_ptr<Data> data){
		return data;
		std::cout << "Sensor Data : " << data << std::endl;
	}
	Interest onInterestForwarding(const Interest interest){
		return interest;
	}
	Sensor(std::string value, bool debug = false){
		m_value = value;
		m_debug = debug;
	}
private :
	std::string m_value;
	bool m_debug;

};
} // namespace iot

static const std::string sensorUsageMessage =
		/* argv[0] */ " - NDN IoT: Sensor\n "
		"-h: show help message\n "
		"-d: enable debugging \n "
		"-n: Name to listen on\n  ";



int
main(int argc, char** argv)
{
	std::string name = "/sensor";
	bool debug = false;
	std::string value = "1";
	int opt;
	while ((opt = getopt(argc, argv, "hn:v:d")) != -1) {
		switch (opt) {
		case 'h':
			//			if(m_debug){
			//			std::cout << argv[0] << sensorUsageMessage << std::endl;
			//			}
			return 1;
		case 'n':
			name = std::string(optarg);
			break;
		case 'v':
			value = std::string(optarg);
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
	iot::Sensor s(value,debug);
	try {
		//		if(m_debug){
		//		std::cout << "Starting the node ..." <<  name << std::endl;
		//		}
		node1.createIoTNode(name,&s,debug);
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return 2;
	}

	return 0;
}
