#include "common.hpp"
#include "IoTNodeCallBack.hpp"
#include "IoTNode.hpp"
#include "IoTHttpWrapper.hpp"
// Regular expressions are a standardized way to express patterns to be matched against sequences of characters.
#include <regex>


#define MAX_FILE_LENGTH 20000


// Additional nested namespace could be used to prevent/limit name contentions
namespace iot {
class GatewayProcessor : public IotNodeCallBack
{

public:
	GatewayProcessor(bool debug = false){
		this->m_debug = debug;
		this->m_pBuffer = NULL;
		this->m_pBuffer = (char*) malloc(MAX_FILE_LENGTH * sizeof(char));
		this->m_Size = 0;
	};
	~GatewayProcessor()
	{
		if (this->m_pBuffer)
			free(this->m_pBuffer);
	};


	// Callback must be declared static, otherwise it won't link...
	size_t WriteMemoryCallback(char* ptr, size_t size, size_t nmemb)
	{
		// Calculate the real size of the incoming buffer
		size_t realsize = size * nmemb;
		// (Re)Allocate memory for the buffer
		m_pBuffer = (char*) Realloc(m_pBuffer, m_Size + realsize);
		// Test if Buffer is initialized correctly & copy memory
		if (m_pBuffer == NULL) {
			realsize = 0;
		}
		memcpy(&(m_pBuffer[m_Size]), ptr, realsize);
		m_Size += realsize;
		// return the real size of the buffer...
		return realsize;
	};

	Block onExactMatch(const Name prefix){

		if(m_debug){
			std::cout << "Calling onExactMatch " << std::endl;
		}
		static const std::string content = fromHttpService(prefix.toUri());
		return ndn::encoding::makeBinaryBlock(Content, reinterpret_cast<const uint8_t*>(content.c_str()), content.size());
		if(m_debug){
			print();
			std::cout << "onExactMatch Called " << std::endl;
		}


	}
	std::shared_ptr<Data> onDataForwarding(Name prefix, std::shared_ptr<Data> data){
		std::string decodedUrl = UrlCodec::urldecode(encodedUrl);
		std::string content = fromHttpService(decodedUrl);
		//content = std::to_string(v);
		std::cout << "Content sent :  "<< content << std::endl;
		if (content.size() > ndn::MAX_NDN_PACKET_SIZE)
			content = "Data size exceeds maximum limit";
		if(m_debug){
			std::cout << "Content sent :  "<< content << std::endl;
			std::cout << "onDataForwarding Prefix :  "<< prefix << std::endl;
		}
		Block b = ndn::encoding::makeBinaryBlock(Content, reinterpret_cast<const uint8_t*>(content.c_str()), content.size());
		data->setContent(b);

		std::string olddataName = data->getName().toUri();

		std::string delimiter = prefix.toUri();
		std::string procName = olddataName.substr(0, olddataName.find(delimiter));

		Name nameProcUrl= Name(procName+"/"+encodedUrl);
		data->setName(nameProcUrl.append(prefix));

		Name dataName = data->getName();

		if(m_debug){
			std::cout << "onDataForwarding data name :  "<< dataName << std::endl;
		}

		return data;
	}

	Interest onInterestForwarding(const Interest interest){
		if(m_debug){
			std::cout << "onInterestForwarding Interest :  "<< interest << std::endl;
		}
		std::string newName = interest.getName().toUri();
		newName.erase(0, 1);
		std::string delimiter = "/";
		encodedUrl = newName.substr(0, newName.find(delimiter));
		if(m_debug){
			std::cout << "ecodedURL :  "<< encodedUrl << std::endl;
		}
		//the prefix to forward
		newName=newName.erase(0, encodedUrl.length());
		if(m_debug){
			std::cout << "remaining prefix :  "<< newName << std::endl;
		}
		Name iName(newName);
		Interest interest_o;
		interest_o.setName(iName);
		interest_o.setInterestLifetime(ndn::time::milliseconds(1000));
		interest_o.setMustBeFresh(true);
		if(m_debug){
			std::cout << "interest to forward :  "<< interest_o << std::endl;
		}
		return interest_o;
	}
private :


	void reInit(){
		if (this->m_pBuffer)
			free(this->m_pBuffer);
		this->m_pBuffer = NULL;
		this->m_pBuffer = (char*) malloc(MAX_FILE_LENGTH * sizeof(char));
		this->m_Size = 0;
	};
	void* Realloc(void* ptr, size_t size)
	{
		if(ptr)
			return realloc(ptr, size);
		else
			return malloc(size);
	};

	void print()
	{
		std::cout << "Size: " << m_Size << std::endl;
		std::cout << "Content: " << std::endl << m_pBuffer << std::endl;
	}


	std::string fromHttpService(std::string url){

		try
		{
			reInit();

			curlpp::Cleanup cleaner;
			curlpp::Easy request;

			// Set the writer callback to enable cURL
			// to write result in a memory area
			curlpp::types::WriteFunctionFunctor functor(this,
					&GatewayProcessor::WriteMemoryCallback);
			curlpp::options::WriteFunction *test = new curlpp::options::WriteFunction(functor);
			request.setOpt(test);
			// Setting the URL to retrieve.
			request.setOpt(new curlpp::options::Url(url));
			if(m_debug){
				request.setOpt(new curlpp::options::Verbose(true));
			}

			request.perform();



			if(m_debug){
				std::string effURL;
				curlpp::infos::EffectiveUrl::get(request, effURL);
				std::cout << "Effective URL: " << effURL << std::endl;

				//other way to retrieve URL
				std::cout << std::endl
						<< "Effective URL: "
						<< curlpp::infos::EffectiveUrl::get(request)
				<< std::endl;

				std::cout << "Response code: "
						<< curlpp::infos::ResponseCode::get(request)
				<< std::endl;

				std::cout << "SSL engines: "
						<< curlpp::infos::SslEngines::get(request)
				<< std::endl;
			}
		}
		catch ( curlpp::LogicError & e ) {
			std::cout << e.what() << std::endl;
			return std::string(e.what());
		}
		catch ( curlpp::RuntimeError & e ) {
			std::cout << e.what() << std::endl;
			return std::string(e.what());
		}

		return std::string(m_pBuffer);
	}


private :
	bool m_debug;
	std::string encodedUrl;

public :
	// Public member vars
	char* m_pBuffer;
	size_t m_Size;

};
} // namespace iot

static const std::string motionUsageMessage =
		/* argv[0] */ " - NDN IoT: HTTP Wrapper Gateway Processor\n "
		"-h: show help message\n "
		"-d: enable debugging \n "
		"-n: Name to listen on\n  ";



int
main(int argc, char** argv)
{
	std::string name = "/processor/http";
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
			std::cout << "setting name to "<< name << std::endl;
			break;
		}
	}
	iot::IotNode node1;
	iot::GatewayProcessor m(debug);
	try {
		if(debug){
			std::cout << "Starting the node ... " <<  name << std::endl;
		}
		node1.createIoTNode(name,&m,debug);

	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return 2;
	}

	return 0;
}

