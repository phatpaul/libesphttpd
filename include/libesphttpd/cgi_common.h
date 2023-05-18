/* Functions commonly used in cgi handlers for libesphttpd */

#ifndef CGI_COMMON_H
#define CGI_COMMON_H

#include "libesphttpd/httpd.h"
#include "cJSON.h"

// this should be more efficient than httpdSend(,,-1) using strlen() at runtime on constant strings
#define HTTP_SEND_CONST(connData, constString) httpdSend(connData, constString, sizeof(constString)-1) //-1 to skip sending the null-terminator

enum {
    CGI_ARG_ERROR = -1,
    CGI_ARG_NOT_FOUND = 0,
    CGI_ARG_FOUND = 1
};
int cgiGetArgDecS32(const char *allArgs, const char *argName, int *pvalue, char *buff, int buffLen);
int cgiGetArgDecU32(const char *allArgs, const char *argName, uint32_t *pvalue, char *buff, int buffLen);
int cgiGetArgHexU32(const char *allArgs, const char *argName, uint32_t *pvalue, char *buff, int buffLen);
int cgiGetArgString(const char *allArgs, const char *argName, char *buff, int buffLen);

void cgiJsonResponseHeaders(HttpdConnData *connData);
void cgiJavascriptResponseHeaders(HttpdConnData *connData);

/**
 * Example usage of cgiJsonResponseCommonMulti for multipart json response (i.e. larger than 1kB)
 * 
CgiStatus cgiFn(HttpdConnData *connData)
{
    cJSON *jsroot = NULL;
    if (connData->cgiData == NULL)
    {
        //First call to this cgi.
        jsroot = cJSON_CreateObject();
        ...
        cgiJsonResponseHeaders(connData);
    }
    return cgiJsonResponseCommonMulti(connData, &connData->cgiData, jsroot); // Send the json response!
}
 */
CgiStatus cgiJsonResponseCommonMulti(HttpdConnData *connData, void **statepp, cJSON *jsroot);
CgiStatus cgiJsonResponseCommonSingle(HttpdConnData *connData, cJSON *jsroot);

CgiStatus cgiJavascriptResponseCommon(HttpdConnData *connData, cJSON *jsroot, const char *jsObjName);

#endif //CGI_COMMON_H
