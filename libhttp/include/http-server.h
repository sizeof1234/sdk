#ifndef _http_server_h_
#define _http_server_h_

#ifdef __cplusplus
extern "C" {
#endif

// Initialize/Finalize
// call once only
int http_server_init();
int http_server_cleanup();

void* http_server_create(const char* ip, int port);
int http_server_destroy(void* http);

// Options
void http_server_set_timeout(void *server, int recv, int send);
void http_server_get_timeout(void *server, int *recv, int *send);


// Request

/// Get client request HTTP header field by name
/// @param[in] session handle callback session parameter
/// @param[in] name request http header field name
/// @return NULL-don't found field, other-header value
const char* http_server_get_header(void* session, const char *name);

/// Get Client post data(raw data)
/// @param[in] session handle callback session parameter
/// @param[out] content data pointer(don't need free)
/// @param[out] length data size
/// @return 0-ok, other-error
int http_server_get_content(void* session, void **content, size_t *length);


// Response

/// Reply
/// @param[in] session handle callback session parameter
/// @param[in] code HTTP status-code(200-OK, 301-Move Permanently, ...)
/// @param[in] bundle create by http_bundle_alloc
/// @return 0-ok, other-error
int http_server_send(void* session, int code, void* bundle);

/// Reply
/// @param[in] session handle callback session parameter
/// @param[in] code HTTP status-code(200-OK, 301-Move Permanently, ...)
/// @param[in] bundles bundle array
/// @param[in] num array elementary number
/// @return 0-ok, other-error
int http_server_send_vec(void* session, int code, void** bundles, int num);

/// Reply a server side file(must be local regular file)
/// @param[in] session handle callback session parameter
/// @param[in] code HTTP status-code(200-OK, 301-Move Permanently, ...)
/// @param[in] localpath local regular file pathname
/// @return 0-ok, other-error
int http_server_send_file(void* session, int code, const char* localpath);

/// Set response http header field(every reply must set it again)
/// @param[in] session handle callback session parameter
/// @param[in] name header name
/// @param[in] value header value
/// @return 0-ok, other-error
int http_server_set_header(void* session, const char* name, const char* value);

/// Set response http header field(every reply must set it again)
/// @param[in] session handle callback session parameter
/// @param[in] name header name
/// @param[in] value header value
/// @return 0-ok, other-error
int http_server_set_header_int(void* session, const char* name, int value);

/// Set response http header Content-Type field value(every reply must set it again)
/// @param[in] session handle callback session parameter
/// @param[in] value content-type value
/// @return 0-ok, other-error
int http_server_set_content_type(void* session, const char* value);


// Handler

/// Set request handler(call on every request)
/// @param[in] param user-defined parameter
/// @param[in] session http session id(use for get request info and set reply)
/// @param[in] method http request method(get/post...)
/// @param[in] path http request uri(e.g. /api/a.html?xxxx)
/// @return 0-ok, other-error
typedef int (*http_server_handler)(void* param, void* session, const char* method, const char* path);

/// Set request handler(call on every request)
/// @param[in] http http server id
/// @param[in] handler callback function
/// @param[in] param user-defined parameter
/// @return 0-ok, other-error
int http_server_set_handler(void* http, http_server_handler handler, void* param);

// Bundle
void* http_bundle_alloc(size_t size);
int http_bundle_free(void* bundle);
void* http_bundle_lock(void* bundle);
int http_bundle_unlock(void* bundle, size_t size);

#ifdef __cplusplus
}
#endif
#endif /* !_http_server_h_ */
