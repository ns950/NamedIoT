#include "common.hpp"
#include "IoTNodeCallBack.hpp"
#include "IoTNode.hpp"

// Additional nested namespace could be used to prevent/limit name contentions
namespace iot {
class MotionProcessor : public IotNodeCallBack
{

public:
	MotionProcessor(bool debug = false){
		m_debug = debug;
	}
	Block onExactMatch(const Name prefix){


		static const std::string content = "NOT ALLOWED OPERATION";
		return ndn::encoding::makeBinaryBlock(Content, reinterpret_cast<const uint8_t*>(content.c_str()), content.size());
		if(m_debug){
			std::cout << "Calling onExactMatch not allowed " << std::endl;
		}


	}
	std::shared_ptr<Data> onDataForwarding(Name prefix, std::shared_ptr<Data> data){
		std::string content = std::string(reinterpret_cast<const char*>(data->getContent().value()), data-> getContent().value_size());
		std::cout << "Content received :  "<< content << std::endl;
		int v = std::stoi(content);
		v++;
		content = std::to_string(v);
		std::cout << "Content sent :  "<< content << std::endl;
		Block b = ndn::encoding::makeBinaryBlock(Content, reinterpret_cast<const uint8_t*>(content.c_str()), content.size());
		data->setContent(b);
		return data;
	}

	Interest onInterestForwarding(const Interest interest){
		if(m_debug){
		std::cout << "onInterestForwarding Interest :  "<< interest << std::endl;
		}
		return interest;
	}
private :
	bool m_debug;

};
} // namespace iot

static const std::string motionUsageMessage =
		/* argv[0] */ " - NDN IoT: Motion Processor\n "
		"-h: show help message\n "
		"-n: Name to listen on\n  ";



int
main(int argc, char** argv)
{
	std::string name = "/processor/motion";
	bool debug = false;
	int opt;
	while ((opt = getopt(argc, argv, "hn:d")) != -1) {
		switch (opt) {
		case 'h':
			std::cout << argv[0] << motionUsageMessage << std::endl;
			return 1;
		case 'n':
			name = std::string(optarg);
			break;
		case 'd':
			debug = true;
			break;
		default:
			if(debug){
			std::cout << "setting name to "<< name << std::endl;
			}
			break;
		}
	}
	iot::IotNode node1;
	iot::MotionProcessor m(debug);
	try {
		if(debug){
		std::cout << "Starting the node ..." <<  name << std::endl;
		}
		node1.createIoTNode(name,&m,debug);

	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return 2;
	}

	return 0;
}

