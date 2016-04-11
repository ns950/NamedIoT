#include "common.hpp"
#include "IoTHttpWrapper.hpp"
#include "IoTNode.hpp"
#include <cstdlib>

void delay(int seconds){
	std::cout << "Starting delay" << std::endl;
	std::clock_t start;
	start = std::clock();
	while(start <seconds*1000000){
		start = std::clock();
	}
}
bool exit_flag=false;
namespace iot {
namespace runner {


class Runner : noncopyable
{
public:
	void
	run(std::string name, int id, int next_runner_id,std::string label, int runTime, bool debug, std::string script)
	{
		m_name = name;
		m_label = label;
		m_next_runner_id=next_runner_id;
		m_runTime=runTime;
		m_debug=debug;
		m_id=id;
		m_script=script;

		// advertise runner
				const char* advertiseRunner= std::string("nlsrc advertise /runner/"+m_id).c_str();
//				int rv1=system(advertiseRunner);
//				std::cout<<"Return value: "<< rv1 <<std::endl;
//				if(m_debug && rv1==32512){
//				}else{
//					std::cout<<">> Advertising runner /runner/"<< m_id << " Failed !!!"<<std::endl;
//				}
				std::cout<<">> Advertising runner /runner/"<< m_id <<std::endl;
		m_face_i.setInterestFilter(m_name+"/"+std::to_string(m_id),
				bind(&Runner::onInterest, this,_1,_2),
				RegisterPrefixSuccessCallback(),
				bind(&Runner::onRegisterFailed, this,_1,_2));

		m_face_i.processEvents();

	}
private:
	void
	onInterest(const InterestFilter& filter, const Interest& interest)
	{
		Name dataName(interest.getName());
		dataName
		.append("ACK");
		static const std::string content = "ROGER THAT";

		shared_ptr<Data> data = make_shared<Data>();
		data->setName(dataName);
		data->setFreshnessPeriod(ndn::time::seconds(0));
		data->setContent(reinterpret_cast<const uint8_t*>(content.c_str()), content.size());
		m_keyChain.sign(*data);
		if(m_debug){
			std::cout<< ">> Data to send: " << *data <<std::endl;
		}
		m_face_i.put(*data);

		if(m_debug){
			std::cout<<">> Incoming interest: " <<interest <<std::endl;
			std::cout<<">> Executing script..." <<std::endl;
		}


		const char* command = m_script.c_str();
		int rv1,rv2,rv3;
		rv1=system(command);
		if(m_debug && rv1==0){

			std::cout<<">> Script executed with success!"<<std::endl;
		}
		std::string facilityName = m_script.substr(m_script.find("-n")+3,3);
		if(m_debug){
			std::cout<<">> Script executed with success!"<<std::endl;
		}


		// advertise facility
		std::cout<<facilityName<<std::endl;
		const char* advertiseFacility=("nlsrc advertise "+facilityName).c_str();
		rv2=system(advertiseFacility);
		if(m_debug && rv2==0){
			std::cout<<">> Advertising facility "<< facilityName <<std::endl;
		}

		// wait until facility runtime
		delay(m_runTime);

		// withdraw facility
		const char* withdrawFacility=("nlsrc withdraw "+facilityName).c_str();
		rv3=system(withdrawFacility);
		if(m_debug && rv3==0){
			std::cout<<">> Withdrawing facility "<< facilityName <<std::endl;
		}


		if(m_debug){
			std::cout<<"Name to forward: " << m_name+"/"+std::to_string(m_next_runner_id) <<std::endl;
		}
		Name nextName;
		nextName = Name(m_name+"/"+std::to_string(m_next_runner_id));
		Interest interestToNode(nextName);
		interestToNode.setInterestLifetime(ndn::time::milliseconds(1000));
		interestToNode.setMustBeFresh(true);
		std::cout<<"interestToNode: "<<interestToNode.getName()<<std::endl;
		m_face_o.expressInterest(interestToNode,
				bind(&Runner::onData, this,_1,_2),
				bind(&Runner::onTimeout, this,_1));
		std::cout<<"Sending interest: " <<interestToNode <<" to Node: /runner/+"<<m_next_runner_id<<std::endl;

		m_face_o.processEvents();

	}
private:
	void
	onData(const Interest& interest, const Data& data)
	{

		if(m_debug){
			std::cout<< ">> Data received: " << data <<std::endl;
		}
	}
	//exit(EXIT_SUCCESS);

	void
	onRegisterFailed(const Name& prefix, const std::string& reason)
	{
		std::cerr<<  "ERROR: Failed to register prefix \""
				<< prefix << "\" in local hub's daemon (" << reason << ")"<< std::endl;
		m_face_i.shutdown();
	}
	void
	onTimeout(const Interest& interest)
	{
		std::cout<<"Timeout: " << interest<< std::endl;
	}

private:
	bool m_debug;
	int m_runTime, m_next_runner_id, m_id;
	std::string m_name,m_label,m_script;
	Face m_face_i,m_face_o;
	KeyChain m_keyChain;
};
}
}

static const std::string runnerUsageMessage =
		/* argv[0] */ " - NDN IoT: runner\n "
		"-h: show help message\n "
		"-d: enable debugging \n "
		"-n: Name to listen on\n"
		"-i: Id of runner\n"
		"-l: Label of script to run\n"
		"-s: Script to run\n"
		"-o: Next runner Id\n"
		"-t: Run time (in seconds)\n";

int main(int argc, char** argv)
{

	std::string name = "/runner", label="I am node "+name;
	std::string script = "./git/FIA/IoT/show.sh No given script";
	std::vector<std::string> url;
	bool debug = false;
	int id=1, opt, next_runner_id=2, runTime=5;
	while ((opt = getopt(argc, argv, "hdn:l:u:i:s:t:o:")) != -1) {
		switch (opt) {
		case 'h':
			std::cout << argv[0] << runnerUsageMessage << std::endl;
			return 1;
		case 'o':
			next_runner_id = atoi(std::string(optarg).c_str());
			break;
		case 'n':
			name = std::string(optarg);
			break;
		case 'i':
			id = atoi(std::string(optarg).c_str());
			break;
		case 's':
			script = std::string(optarg);
			break;
		case 't':
			runTime = atoi(std::string(optarg).c_str());
			break;
		case 'l':
			label = std::string(optarg)+" "+name;
			break;
		case 'd':
			debug = true;
			break;
		default:
			std::cout << "setting name to "<< name << std::endl;
			break;
		}
	}

	iot::runner::Runner ambulanceRunner;
	try {
		if(debug){
			std::cout << ">>> Starting the facility runner ..." <<  name+"/"+std::to_string(id) << std::endl;
			std::cout << ">>> With id: " << id << std::endl;
		}
		for(;;){
			ambulanceRunner.run(name,id,next_runner_id, label,runTime, debug, script);
		}

	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return 2;
	}

	return 0;
}

