#include "common.hpp"


namespace iot {

class User : noncopyable
{
public:
  void
  run()
  {
    Interest interest(Name("/runner/1")); ///example/testApp/randomData   /nist/antd/img/1
    interest.setInterestLifetime(ndn::time::milliseconds(2000));
    interest.setMustBeFresh(true);

    m_face.expressInterest(interest,
                           bind(&User::onData, this,  _1, _2),
                           bind(&User::onTimeout, this, _1));

    std::cout << "Sending " << interest << std::endl;

    // processEvents will block until the requested data received or timeout occurs
    m_face.processEvents();
  }

private:
  void
  onData(const Interest& interest, const Data& data)
  {
    std::cout << data << std::endl;
  }

  void
  onTimeout(const Interest& interest)
  {
    std::cout << "Timeout " << interest << std::endl;
  }

private:
  Face m_face;
};


} // namespace iot

int
main(int argc, char** argv)
{
	iot::User my_user;
  try {
    my_user.run();
  }
  catch (const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }
  return 0;
}
