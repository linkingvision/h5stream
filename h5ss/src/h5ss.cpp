#include "h5slib.hpp"
#include <thread>
#include <mutex>
#include <chrono>
#include "h5s_mp4_sink.hpp"
#include "webserver.hpp"

int main(int argc, char *argv[])
{
	std::string docRoot = "www";
	std::string strPasswdPath = ".htpasswd";
	if (argc < 4)
	{
		printf("Usage ./h5ss url user passwd (./h5ss rtsp://192.168.0.1/stream1 admin admin)\n");
	}
	printf("  Url:%s (%s:%s)\n", argv[1], argv[2], argv[3]);
	//TODO ssl path
	printf("  Connect by http(https)://localhost:8801(8843), replace localhost with your ip\n");

	/* set htpasswd, when start a  */
	std::string strPasswd = "admin";

	const char *options[] = {
		"document_root", docRoot.c_str(), 
		"listening_ports", PORT, 
		//"ssl_certificate", SSL_CERT,
		//"global_auth_file", strPasswdPath.c_str(),
		//"authentication_domain", "h5stream.com",
		0};
    
	std::vector<std::string> cpp_options;
	for (int i=0; i<(sizeof(options)/sizeof(options[0])-1); i++) {
	    cpp_options.push_back(options[i]);
	}

	H5SSWebServer *  pWebServer = new H5SSWebServer(cpp_options, argv[1], argv[2], argv[3]);
	
	
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}