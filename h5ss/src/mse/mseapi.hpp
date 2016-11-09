#ifndef __MSE_API_H__
#define __MSE_API_H__

#include "CivetServer.h"
#include "h5slib.hpp"
#include "h5s_mp4_sink.hpp"
#include <thread>
#include <mutex>
#include <chrono>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

class H5SMSEConnection :public H5SMP4Callback
{
public:
	H5SMSEConnection(struct mg_connection * conn, std::string strUrl, 
		std::string strUser, std::string strPasswd)
	:m_conn(conn), m_mp4Sink(*this), m_pClient(new H5SLibRTSP(strUrl, 
	 strUser, strPasswd))
	{

	}
	~H5SMSEConnection()
	{
		if (m_pClient)
		{
			delete m_pClient;
		}
	}
public:
	bool Start()
	{	
		if (m_pClient)
		{
			m_pClient->Start();
			m_pClient->RegCallback(&m_mp4Sink, &m_mp4Sink);
		}
		return true;
	}
public:
	virtual bool  onH5SMP4Data(unsigned char* buffer, int size)
	{	
		if (!m_conn)
		{
			return false;
		}
		int ret = mg_websocket_write(m_conn, WEBSOCKET_OPCODE_BINARY, (char *)buffer, size);
		//printf("%s %s %d  %d\n", __FUNCTION__, __FILE__, __LINE__, ret);

		return true;
	}
public:
	struct mg_connection *m_conn;
	H5SMP4Sink m_mp4Sink;
	H5SLibRTSP *m_pClient;	

};

typedef std::map<struct mg_connection *, H5SMSEConnection *> H5SMSEConnectionsMap;

class H5SMSEAPI : public CivetWebSocketHandler
{
public:
	H5SMSEAPI(std::string strUrl, 
		std::string strUser, std::string strPasswd)
	:m_strUrl(strUrl), m_strUser(strUser), m_strPasswd(strPasswd)
	{
	}
	
	~H5SMSEAPI()
	{
	}
	
	bool handleConnection(CivetServer *server,
	                              const struct mg_connection *conn)
	{
		return true;
	}							  
								  
	bool handleData(CivetServer *server,
	                        struct mg_connection *conn,
	                        int bits,
	                        char *data,
	                        size_t data_len)
	{
		printf("%s %d\n", __FUNCTION__, data_len);
		//mg_websocket_write(conn, WEBSOCKET_OPCODE_TEXT, "data1", 5);
		return true;
	}
	void handleClose(CivetServer *server,
	                         const struct mg_connection *conn)
	{
		std::lock_guard<std::mutex> guard(m_pLock);
		printf("%s Close\n", __FUNCTION__);

	 	if (m_pConnMap[(struct mg_connection *)conn] != NULL)
	 	{
	 		delete m_pConnMap[(struct mg_connection *)conn];			
	 	}
		m_pConnMap.erase((struct mg_connection *)conn);
	 	return;
	}
	void handleReadyState(CivetServer *server,
	                              struct mg_connection *conn)
	{
		std::lock_guard<std::mutex> guard(m_pLock);
		
		printf("%s Start\n", __FUNCTION__);
		
		H5SMSEConnection * pConn = new H5SMSEConnection(conn, 
			m_strUrl,m_strUser, m_strPasswd);

		pConn->Start();

		m_pConnMap[conn] = pConn;
	}

private:
	std::mutex m_pLock;
	H5SMSEConnectionsMap m_pConnMap;
	std::string m_strUrl;
	std::string m_strUser;
	std::string m_strPasswd;

};

#endif /* __MSE_API_H__ */
