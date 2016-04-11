
#ifndef IOT_HTTP_WRAPPER_HPP
#define IOT_HTTP_WRAPPER_HPP

#include "common.hpp"
#include <cstdlib>
#include <cstring>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>



// Additional nested namespace could be used to prevent/limit name contentions
namespace iot {


class UrlCodec
{
public:

	static std::string urlencode(std::string &s);
	static std::string urldecode(std::string &s);

};

} //namespace iot


#endif //IOT_HTTP_WRAPPER_HPP
