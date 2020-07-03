clang++ -shared -Wall -o libDevPlayground.dylib \
	-I/Users/zhuowei/Documents/nobackup/vbox/VirtualBox-6.1.10/include \
	-DIN_RING3 \
	-DGC_ARCH_BITS=64 \
	DevPlayground.cpp \
	/Applications/VirtualBox.app/Contents/MacOS/VBoxRT.dylib
