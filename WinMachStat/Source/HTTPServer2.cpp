#include "HTTPServer.h"
#include <iostream>
#include "Exception.h"
#include "Logger.h"

namespace WinMachStat {
	HTTPServer::HTTPServer(std::vector<std::string> urls, HTTPRequestHandler rH) :
			reqHandler(rH), HttpApiVersion(HTTPAPI_VERSION_2)
	{
		retCode = HttpInitialize(
			HttpApiVersion,
			HTTP_INITIALIZE_SERVER,    // Flags
			NULL                       // Reserved
		);

		if (retCode != NO_ERROR) {
			throw Exception(errno, ExceptionFormatter() << "Failed to Initialize HTTP Service: " << retCode);
		}

		retCode = HttpCreateHttpHandle(
			&hReqQueue,        // Req Queue
			0                  // Reserved
		);

		if (retCode != NO_ERROR)
		{
			throw Exception(errno, ExceptionFormatter() << "Failed to Create HTTP Service: " << retCode);
		}
	}

	int HTTPServer::Listen()
	{
		ULONG              result;
		HTTP_REQUEST_ID    requestId;
		DWORD              bytesRead;
		PHTTP_REQUEST      pRequest;
		PCHAR              pRequestBuffer;
		ULONG              RequestBufferLength;

		LoggerStream &slog = WinMachStat::Logger::getLogger("HTTPServer");

		HTTP_SET_NULL_ID(&requestId);

		for (;;) {
			for (HTTP_SET_NULL_ID(&requestId);
				(retCode=HttpReceiveHttpRequest(
					hReqQueue,
					requestId,
					0,
					pRequest,
					RequestBufferLength,
					&bytesRead,
					NULL
				)) != NO_ERROR;
				HTTP_SET_NULL_ID(&requestId)) {

			}
			LOG_INFO(slog) << "Error occured while receiving request:" << retCode;
		}
	}
}