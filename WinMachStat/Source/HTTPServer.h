#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <http.h>

#pragma comment(lib, "httpapi.lib")

#include <string>
#include <vector>

#define ALLOC_MEM(cb) HeapAlloc(GetProcessHeap(), 0, (cb))
#define FREE_MEM(ptr) HeapFree(GetProcessHeap(), 0, (ptr))
#define INITIALIZE_HTTP_RESPONSE( resp, status, reason )    \
    do                                                      \
    {                                                       \
        RtlZeroMemory( (resp), sizeof(*(resp)) );           \
        (resp)->StatusCode = (status);                      \
        (resp)->pReason = (reason);                         \
        (resp)->ReasonLength = (USHORT) strlen(reason);     \
    } while (FALSE)
#define ADD_KNOWN_HEADER(Response, HeaderId, RawValue)               \
    do                                                               \
    {                                                                \
        (Response).Headers.KnownHeaders[(HeaderId)].pRawValue =      \
                                                          (RawValue);\
        (Response).Headers.KnownHeaders[(HeaderId)].RawValueLength = \
            (USHORT) strlen(RawValue);                               \
    } while(FALSE)


namespace WinMachStat {
	typedef int(*HTTPRequestHandler)(HANDLE hReqQ);
	class HTTPServer {
	private:
		ULONG           retCode; /* Last HTTP API return code */
		HANDLE          hReqQueue;
		int             UrlAdded ;
		const HTTPAPI_VERSION HttpApiVersion ;
		
		HTTP_SERVER_SESSION_ID serverSessionID;
		HTTP_URL_GROUP_ID urlGroupID;
		std::vector<std::wstring> urls;

		HTTPRequestHandler reqHandler;

		int reqHandled = 0;

		HTTPServer(void) = delete;
		DWORD	sendHttpResponse(
				IN HANDLE        hReqQueue,
				IN PHTTP_REQUEST pRequest,
				IN USHORT        StatusCode,
				IN PSTR          pReason,
				IN PSTR          pEntity
			);

	public:
		HTTPServer(std::vector<std::wstring> urls, HTTPRequestHandler rH) ;

		int Listen();
	};
}