#define GIT_VERSION "TEST"
#define COMPILE_TIMESTAMP 1337


namespace Polaris {
    const char* GetLibVersion() { return GIT_VERSION; }
    int GetTimeCompiled() { return COMPILE_TIMESTAMP; }
}