#ifndef __VE_WEB_SERVER_H__
#define __VE_WEB_SERVER_H__

#include "CivetServer.h"
#include "mse/mseapi.hpp"

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#define DOCUMENT_ROOT "."
//#define PORT "8801,8843"
#define PORT "8801"
#define SSL_CERT "./ssl/server.pem"


class H5SSWebServer 
{
public:
	H5SSWebServer(std::vector<std::string> cpp_options, std::string strUrl, 
		std::string strUser, std::string strPasswd)
		:pServer(new CivetServer(cpp_options)), server(*pServer), 
		h_mse(strUrl, strUser, strPasswd)
	{
		server.addWebSocketHandler("/h5sws", h_mse);
		//TODO add raw websocket streaming server for native client

	}
	~H5SSWebServer(){}
	
private:
	H5SMSEAPI h_mse;
	CivetServer *pServer;
	CivetServer &server;
};

#endif /* __VE_WEB_SERVER_H__ */
