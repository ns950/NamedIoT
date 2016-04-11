#include "common.hpp"
#include "IoTNodeCallBack.hpp"
#include "IoTNode.hpp"
#include "HttpGatewayHelper.hpp"

namespace iot {
class Facility : public IotNodeCallBack
{

public:
	Facility(std::string label,std::string uri,bool debug = false, int position=0){
		m_debug = debug;
		m_uri = uri;
		m_label=label;
		m_position=position;


	}


	void callFacility(std::string uri){

		helper.fromHttpService(uri);
		}

	Block onExactMatch(const Name prefix){

		callFacility(m_uri);
		static const std::string content = "Status : Ready";
		return ndn::encoding::makeBinaryBlock(Content, reinterpret_cast<const uint8_t*>(content.c_str()), content.size());

	}
	std::shared_ptr<Data> onDataForwarding(Name prefix, std::shared_ptr<Data> data){
		callFacility(m_uri);
		std::string content = std::string(reinterpret_cast<const char*>(data->getContent().value()), data-> getContent().value_size());
		std::cout <<  "Facility Data : " <<content <<std::endl;
		return data;
	}
	Interest onInterestForwarding(const Interest interest){
		callFacility(m_uri);
		return interest;
	}
private :
	HttpGatewayHelper helper;
	bool m_debug;
	int m_position;
	std::string m_uri, m_name, m_function, m_label;


};
} // namespace iot

static const std::string FacilityUsageMessage =
		/* argv[0] */ " - NDN IoT: Facility\n "
		"-h: show help message\n "
		"-d: enable debugging \n "
		"-n: Name to listen on\n "
		"-p: Position of facility\n "
		"-u: uri to call\n "
		"-f: function of the facility (Ambulance or Hospital)\n ";

int
main(int argc, char** argv)
{

	std::string name = "/Facility";
	std::string label = "/Ambulance";
	int position = 0;
	bool debug = false;
	std::string uri = "http://hasnae:9000/api";
	int opt;
	while ((opt = getopt(argc, argv, "hn:u:l:p:f:d")) != -1) {
		switch (opt) {
		case 'h':
			std::cout << argv[0] << FacilityUsageMessage << std::endl;
			return 1;
		case 'n':
			name = std::string(optarg);
			break;
		case 'p':
			position = atoi(std::string(optarg).c_str());
			break;
		case 'l':
			label = std::string(optarg);
			break;
		case 'u':
			uri = std::string(optarg);
			break;
		case 'd':
			debug = true;
			break;
		default:
			std::cout << "Facility name is: "<< name << std::endl;
			break;
		}
	}
	iot::IotNode node;
	iot::Facility a(label, uri,debug, position);
	try {
		if(debug){

			std::cout << "Starting the Facility... "<<name<< std::endl;
			std::cout << "Calling service... "<<uri<<name<< std::endl;
		}
		node.createIoTNode(name,&a,debug);
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return 2;
	}

	return 0;
}
