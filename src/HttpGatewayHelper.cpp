#include "HttpGatewayHelper.hpp"
#include "IoTHttpWrapper.hpp"
#define MAX_FILE_LENGTH 20000
std::string encodedUrl;

namespace iot {

HttpGatewayHelper::HttpGatewayHelper(bool debug){
		_m_debug = debug;
		this->m_pBuffer = NULL;
		this->m_pBuffer = (char*) malloc(MAX_FILE_LENGTH * sizeof(char));
		m_Size = 0;
	}
HttpGatewayHelper::~HttpGatewayHelper()
	{
		if (this->m_pBuffer)
			free(this->m_pBuffer);
	}


	// Callback must be declared static, otherwise it won't link...
	size_t HttpGatewayHelper::WriteMemoryCallback(char* ptr, size_t size, size_t nmemb)
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
	}


	void HttpGatewayHelper::reInit(){
		if (this->m_pBuffer)
			free(this->m_pBuffer);
		this->m_pBuffer = NULL;
		this->m_pBuffer = (char*) malloc(MAX_FILE_LENGTH * sizeof(char));
		this->m_Size = 0;
	}
	void* HttpGatewayHelper::Realloc(void* ptr, size_t size)
	{
		if(ptr)
			return realloc(ptr, size);
		else
			return malloc(size);
	}

	void HttpGatewayHelper::print()
	{
		std::cout << "Size: " << m_Size << std::endl;
		std::cout << "Content: " << std::endl << m_pBuffer << std::endl;
	}


	std::string HttpGatewayHelper::fromHttpService(std::string url){

		try
		{
			reInit();

			curlpp::Cleanup cleaner;
			curlpp::Easy request;

			// Set the writer callback to enable cURL
			// to write result in a memory area
			curlpp::types::WriteFunctionFunctor functor(this,
					&HttpGatewayHelper::WriteMemoryCallback);
			curlpp::options::WriteFunction *test = new curlpp::options::WriteFunction(functor);
			request.setOpt(test);
			// Setting the URL to retrieve.
			request.setOpt(new curlpp::options::Url(url));
			if(_m_debug){
				request.setOpt(new curlpp::options::Verbose(true));
			}

			request.perform();



			if(_m_debug){
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

	std::string HttpGatewayHelper::fromHttpServiceWithPost(std::string url){
		try
				{
			CURL *curl;
			  CURLcode res;

			  /* In windows, this will init the winsock stuff */
			  curl_global_init(CURL_GLOBAL_ALL);

			  /* get a curl handle */
			  curl = curl_easy_init();
			  if(curl) {
			    /* First set the URL that is about to receive our POST. This URL can
			       just as well be a https:// URL if that is what should receive the
			       data. */
			    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:9000/api/things");
			    /* Now specify the POST data */
			    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=ambulance1&info=vehicle&position=1&type=transport&active=true");

			    /* Perform the request, res will get the return code */
			    res = curl_easy_perform(curl);
			    /* Check for errors */
			    if(res != CURLE_OK)
			      fprintf(stderr, "curl_easy_perform() failed: %s\n",
			              curl_easy_strerror(res));

			    /* always cleanup */
			    curl_easy_cleanup(curl);
			  }
			  curl_global_cleanup();
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


} // namespace iot


