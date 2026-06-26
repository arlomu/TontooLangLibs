// fileops.c — TontooSL File Operations Implementierung
// Wird von clang automatisch gelinkt wenn als .c im Projekt vorhanden

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define getcwd _getcwd
#define mkdir _mkdir
#define stat _stat
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#else
#include <unistd.h>
#endif

// Heap-Speicher für Strings die wir zurückgeben
static char g_buf[65536];

const char* tonto_read_file(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) return "";
    size_t n = fread(g_buf, 1, sizeof(g_buf) - 1, f);
    g_buf[n] = '\0';
    fclose(f);
    return g_buf;
}

int tonto_write_file(const char* path, const char* content) {
    FILE* f = fopen(path, "w");
    if (!f) return 0;
    fputs(content, f);
    fclose(f);
    return 1;
}

int tonto_append_file(const char* path, const char* content) {
    FILE* f = fopen(path, "a");
    if (!f) return 0;
    fputs(content, f);
    fclose(f);
    return 1;
}

int tonto_file_exists(const char* path) {
    FILE* f = fopen(path, "r");
    if (f) { fclose(f); return 1; }
    return 0;
}

int tonto_file_size(const char* path) {
    struct stat st;
    if (stat(path, &st) != 0) return -1;
    return (int)st.st_size;
}

int tonto_copy_file(const char* src, const char* dst) {
    FILE* in = fopen(src, "rb");
    if (!in) return 0;
    FILE* out = fopen(dst, "wb");
    if (!out) { fclose(in); return 0; }
    char buf[8192];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), in)) > 0) {
        fwrite(buf, 1, n, out);
    }
    fclose(in);
    fclose(out);
    return 1;
}

int tonto_move_file(const char* src, const char* dst) {
    return rename(src, dst) == 0 ? 1 : 0;
}

int tonto_create_dir(const char* path) {
#ifdef _WIN32
    return _mkdir(path) == 0 ? 1 : 0;
#else
    return mkdir(path, 0755) == 0 ? 1 : 0;
#endif
}

int tonto_remove_dir(const char* path) {
    return rmdir(path) == 0 ? 1 : 0;
}

const char* tonto_get_cwd() {
    char buf[4096];
    if (getcwd(buf, sizeof(buf))) {
        strncpy(g_buf, buf, sizeof(g_buf));
        return g_buf;
    }
    return "";
}

const char* tonto_temp_dir() {
#ifdef _WIN32
    const char* t = getenv("TEMP");
    if (!t) t = getenv("TMP");
    if (!t) t = "C:\\Temp";
#else
    const char* t = getenv("TMPDIR");
    if (!t) t = "/tmp";
#endif
    strncpy(g_buf, t, sizeof(g_buf));
    return g_buf;
}
