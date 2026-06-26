// TontooHTTP - Complete HTTP/HTTPS Library for TontooLang
// Uses libcurl for HTTP requests

#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total = size * nmemb;
    char **response = (char **)userp;
    *response = realloc(*response, (total + 1) * sizeof(char));
    if (*response) {
        memcpy(*response, contents, total);
        (*response)[total] = '\0';
    }
    return total;
}

// http_get(url: String) -> String
int http_get(const char *url, char *response_buffer, int buffer_size) {
    CURL *curl = curl_easy_init();
    if (!curl) { response_buffer[0] = '\0'; return 0; }
    
    char *response = NULL;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    
    CURLcode res = curl_easy_perform(curl);
    int success = (res == CURLE_OK);
    
    if (success && response) {
        strncpy(response_buffer, response, buffer_size - 1);
        response_buffer[buffer_size - 1] = '\0';
        free(response);
    } else {
        response_buffer[0] = '\0';
    }
    
    curl_easy_cleanup(curl);
    return success;
}

// http_post(url: String, body: String) -> String  
int http_post(const char *url, const char *body, char *response_buffer, int buffer_size) {
    CURL *curl = curl_easy_init();
    if (!curl) { response_buffer[0] = '\0'; return 0; }
    
    char *response = NULL;
    curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    CURLcode res = curl_easy_perform(curl);
    int success = (res == CURLE_OK);
    
    if (success && response) {
        strncpy(response_buffer, response, buffer_size - 1);
        response_buffer[buffer_size - 1] = '\0';
        free(response);
    } else {
        response_buffer[0] = '\0';
    }
    
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return success;
}

// http_put(url: String, body: String) -> String
int http_put(const char *url, const char *body, char *response_buffer, int buffer_size) {
    CURL *curl = curl_easy_init();
    if (!curl) { response_buffer[0] = '\0'; return 0; }
    
    char *response = NULL;
    curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    CURLcode res = curl_easy_perform(curl);
    int success = (res == CURLE_OK);
    
    if (success && response) {
        strncpy(response_buffer, response, buffer_size - 1);
        response_buffer[buffer_size - 1] = '\0';
        free(response);
    } else {
        response_buffer[0] = '\0';
    }
    
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return success;
}

// http_delete(url: String) -> String
int http_delete(const char *url, char *response_buffer, int buffer_size) {
    CURL *curl = curl_easy_init();
    if (!curl) { response_buffer[0] = '\0'; return 0; }
    
    char *response = NULL;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    CURLcode res = curl_easy_perform(curl);
    int success = (res == CURLE_OK);
    
    if (success && response) {
        strncpy(response_buffer, response, buffer_size - 1);
        response_buffer[buffer_size - 1] = '\0';
        free(response);
    } else {
        response_buffer[0] = '\0';
    }
    
    curl_easy_cleanup(curl);
    return success;
}

// http_patch(url: String, body: String) -> String
int http_patch(const char *url, const char *body, char *response_buffer, int buffer_size) {
    CURL *curl = curl_easy_init();
    if (!curl) { response_buffer[0] = '\0'; return 0; }
    
    char *response = NULL;
    curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    CURLcode res = curl_easy_perform(curl);
    int success = (res == CURLE_OK);
    
    if (success && response) {
        strncpy(response_buffer, response, buffer_size - 1);
        response_buffer[buffer_size - 1] = '\0';
        free(response);
    } else {
        response_buffer[0] = '\0';
    }
    
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return success;
}

// http_head(url: String) -> String
int http_head(const char *url, char *response_buffer, int buffer_size) {
    CURL *curl = curl_easy_init();
    if (!curl) { response_buffer[0] = '\0'; return 0; }
    
    char *response = NULL;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "HEAD");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    
    CURLcode res = curl_easy_perform(curl);
    int success = (res == CURLE_OK);
    
    if (success && response) {
        strncpy(response_buffer, response, buffer_size - 1);
        response_buffer[buffer_size - 1] = '\0';
        free(response);
    } else {
        response_buffer[0] = '\0';
    }
    
    curl_easy_cleanup(curl);
    return success;
}

// http_options(url: String) -> String
int http_options(const char *url, char *response_buffer, int buffer_size) {
    CURL *curl = curl_easy_init();
    if (!curl) { response_buffer[0] = '\0'; return 0; }
    
    char *response = NULL;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "OPTIONS");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    CURLcode res = curl_easy_perform(curl);
    int success = (res == CURLE_OK);
    
    if (success && response) {
        strncpy(response_buffer, response, buffer_size - 1);
        response_buffer[buffer_size - 1] = '\0';
        free(response);
    } else {
        response_buffer[0] = '\0';
    }
    
    curl_easy_cleanup(curl);
    return success;
}

// http_get_status(url: String) -> Int
int http_status(const char *url) {
    CURL *curl = curl_easy_init();
    if (!curl) return 0;
    
    long response_code = 0;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
    
    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }
    
    curl_easy_cleanup(curl);
    return (int)response_code;
}

// http_request(method: String, url: String, body: String, headers: String) -> String
int http_request(const char *method, const char *url, const char *body, const char *headers_str, char *response_buffer, int buffer_size) {
    CURL *curl = curl_easy_init();
    if (!curl) { response_buffer[0] = '\0'; return 0; }
    
    char *response = NULL;
    curl_slist *headers = NULL;
    
    // Parse headers (format: "Header1: Value1; Header2: Value2")
    if (headers_str && strlen(headers_str) > 0) {
        char *headers_copy = strdup(headers_str);
        char *token = strtok(headers_copy, ";");
        while (token) {
            // Trim whitespace
            while (*token == ' ') token++;
            headers = curl_slist_append(headers, token);
            token = strtok(NULL, ";");
        }
        free(headers_copy);
    }
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method);
    if (body && strlen(body) > 0) {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    CURLcode res = curl_easy_perform(curl);
    int success = (res == CURLE_OK);
    
    if (success && response) {
        strncpy(response_buffer, response, buffer_size - 1);
        response_buffer[buffer_size - 1] = '\0';
        free(response);
    } else {
        response_buffer[0] = '\0';
    }
    
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return success;
}