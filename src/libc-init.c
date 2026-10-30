#include <libc-init.h>

int main(int argc, char **argv, char **envp);

int _libc_start(int argc, char **argv, char **envp) {
    _libc_init_stdio();
    return main(argc, argv, envp);
}
