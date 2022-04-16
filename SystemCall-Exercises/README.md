# System Call Exercises

1. syscall_64.tbl:342
/usr/src/linux/arch/x86/entry/syscalls/syscall_64.tbl

2. syscalls.h:943
/usr/src/linux/include/linux/syscalls.h

3. Makefile:13
/usr/src/linux/kernel/Makefile

4. new_syscall.c
/usr/src/linux/kernel/new_syscall.c

5. Build
```Bash
cd /usr/src/linux
sudo make -j 4
sudo make modules_install
sudo make install
sudo reboot
```

6. Compile assignment code and execute
```Bash
cd ~
gcc assignment.c
./a.out
dmesg
```
