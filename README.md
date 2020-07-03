Example for running VirtualBox's virtual PCI device sample on macOS.

VirtualBox's standard macOS installation is sandboxed and prevents loading third-party virtual devices.

This repo provides a launcher that disables VirtualBox's sandbox, and a build script for VirtualBox's DevPlayground device sample.

This is tested against VirtualBox 6.1.8 - you might need to fix the hardcoded offset in vboxlauncher.c.

## To run:

```
cd ironsand
vim build2.sh # Fix the include path to your VirtualBox source
./build2.sh
```


Create a VirtualBox VM with ICH9 chipset. Then:

```
sudo cp libDevPlayground.dylib /opt/ironsand/
VBoxManage setextradata vmname VBoxInternal/PDM/Devices/playground/Path /opt/ironsand/libDevPlayground.dylib
VBoxManage setextradata vmname VBoxInternal/Devices/playground/0/Config/Whatever1 0
```

```
clang -o vboxlauncher vboxlauncher.c
sudo ./vboxlauncher --startvm vmname
```

It will print:

```
39
attach to 57113
```

run

```
sudo lldb -p 57113
```

then

```
breakpoint set -F _dyld_get_image_name -c "$rdi==0" -C "print $rdi=39" -C "c"
```

## License

The sample code is taken from VirtualBox, which is dual-licensed under GPL and CDDL.
