#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define VBOX_PATH "/Applications/VirtualBox.app/Contents/Resources/VirtualBoxVM.app/Contents/MacOS/VirtualBoxVM"

extern const char* _dyld_get_image_name(int);

int main(int argc, char** argv, char** envp, char** apple) {
	setreuid(501, 0);
	void* vbox = dlopen(VBOX_PATH, RTLD_LOCAL | RTLD_LAZY);
	for (int i = 0; ; i++) {
		if (!strcmp(_dyld_get_image_name(i), VBOX_PATH)) {
			fprintf(stderr, "%d\n", i);
			break;
		}
	}
	fprintf(stderr, "attach to %d\n", getpid());
	while (strcmp(_dyld_get_image_name(0), VBOX_PATH)) {
		sleep(1);
	}
	void* machHeader = dlsym(vbox, "_mh_execute_header");
	int (*pVboxMain)(int argc, char** argv, char** envp, char** apple) = machHeader + 0x17e0;
	return pVboxMain(argc, argv, envp, apple);
}
