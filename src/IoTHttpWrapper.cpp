
#include "IoTHttpWrapper.hpp"

// Additional nested namespace could be used to prevent/limit name contentions
namespace iot {

std::string UrlCodec::urlencode(std::string &source)
{
	CURL *curl = curl_easy_init();
	char *cres = curl_easy_escape(curl, source.c_str(), source.length());
	std::string res(cres);
	curl_free(cres);
	curl_easy_cleanup(curl);
	return res;
}


std::string UrlCodec::urldecode(std::string &encoded)
{
	CURL *curl = curl_easy_init();
	int outlength;
	char *cres = curl_easy_unescape(curl, encoded.c_str(), encoded.length(), &outlength);
	std::string res(cres, cres + outlength);
	curl_free(cres);
	curl_easy_cleanup(curl);

	//if it's UTF-8, convert it to ISO_8859-1. Based on http://stackoverflow.com/questions/11156473/is-there-a-way-to-convert-from-utf8-to-iso-8859-1/11156490#11156490
	iconv_t cd = iconv_open("ISO_8859-1", "UTF-8");

	char *in_buf = (char*)res.c_str();
	size_t in_left = res.length();

	char *output = new char[res.length() + 1];
	std::fill(output, output + res.length() + 1, '\0');
	char *out_buf = &output[0];
	size_t out_left = res.length();

	do {
		if (iconv(cd, &in_buf, &in_left, &out_buf, &out_left) == (size_t)-1) {
			//failed to convert, just return the value received from curl
			delete[] output;
			iconv_close(cd);
			return res;
		}
	} while (in_left > 0 && out_left > 0);

	std::string outputString(output);
	delete[] output;
	iconv_close(cd);

	return outputString;
}

} // namespace iot


