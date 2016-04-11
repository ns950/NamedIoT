#ifndef IOT_HTTPGATEWAYHELPER_HPP
#define IOT_HTTPGATEWAYHELPER_HPP

#include "common.hpp"
#include "IoTNodeCallBack.hpp"
#include "common.hpp"
#include <cstdlib>
#include <cstring>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

namespace iot{


class HttpGatewayHelper
	{

	public:
	HttpGatewayHelper(bool debug=false);
	~HttpGatewayHelper();
		// Callback must be declared static, otherwise it won't link...
		size_t WriteMemoryCallback(char* ptr, size_t size, size_t nmemb);

private :
	void reInit();
	void* Realloc(void* ptr, size_t size);
	void print();
public:
	std::string fromHttpService(std::string url);
	std::string fromHttpServiceWithPost(std::string url);

private :
	bool _m_debug;

public :
	// Public member vars
	char* m_pBuffer;
	size_t m_Size;

	};
} // namespace iot

#endif
