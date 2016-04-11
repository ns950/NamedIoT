#include "common.hpp"
#include "IoTHttpWrapper.hpp"
#include "IoTNode.hpp"

namespace iot {

namespace consumer {

class Consumer : noncopyable
{
public:
	void
	run(std::string name,std::vector<std::string> url, bool debug)
	{
		std::string flag = "{URL}";
		size_t pos=name.find(flag, 0);
		int i=0;

		while(pos != std::string::npos)
		{
			name.replace(name.find(flag),flag.length(),UrlCodec::urlencode(url.at(i)));
			pos=name.find(flag, 0);
			i++;
		}


		std::cout << "New Interest: "<< name << std::endl;

		Name iName(name);
		Interest interest(iName);
		interest.setInterestLifetime(ndn::time::milliseconds(INTEREST_LIFE_TIME));
		interest.setMustBeFresh(true);

		m_face.expressInterest(interest,
				bind(&Consumer::onData, this,  _1, _2),
				bind(&Consumer::onTimeout, this, _1));

		if(debug){
			std::cout << "Sending " << interest << std::endl;
		}

		// processEvents will block until the requested data received or timeout occurs
		m_face.processEvents();
	}

private:
	void onData(const Interest& interest, const Data& data)
	{
		std::cout << data << std::endl;
	}

	void onTimeout(const Interest& interest)
	{
		std::cout << "Timeout " << interest << std::endl;
	}

private:
	Face m_face;
};

} // namespace consumer
} // namespace iot
static const std::string consumerUsageMessage =
		/* argv[0] */ " - NDN IoT: Consumer\n "
		"-h: show help message\n "
		"-d: enable debugging \n "
		"-n: Name to ask for\n  "
		"-u: URL to use with the placeholder \"URL\" in the name\n  ";



int
main(int argc, char** argv)
{
	std::string name = "/actuator/processor/http/{URL}/sensor";
	std::vector<std::string> url;
	bool debug = false;
	int opt,index;
	while ((opt = getopt(argc, argv, "hdn:u:")) != -1) {
		switch (opt) {
		case 'h':
			std::cout << argv[0] << consumerUsageMessage << std::endl;
			return 1;
		case 'n':
			name = std::string(optarg);
			break;
		case 'u':
			index = optind -1;
			while(index < argc){
				char* next=argv[index];
				if(next[0] != '-'){
					url.push_back(next);
				}
				index++;
			}
			break;
		case 'd':
			debug = true;
			break;
		default:

			std::cout << "setting name to "<< name << std::endl;
			break;
		}
	}
	iot::consumer::Consumer consumer;
	try {
		if(debug){
			std::cout << "Starting the consumer ..." <<  name << std::endl;
		}
		consumer.run(name, url, debug);
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return 2;
	}

	return 0;
}
