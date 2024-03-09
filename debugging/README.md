# Debugging

## Core Dumps

Enable core dumps

<pre><code>
ulimit -S -c unlimited
</code></pre>

Check core_pattern path

<pre><code>
cat /proc/sys/kernel/core_pattern
</code></pre>

Change path with

<pre><code>
sudo sysctl -w kernel.core_pattern=/home/christian/coredumps/core-%e-%s-%u-%g-%p-%t
</code></pre>

Analyze the generated core dump file

<pre><code>
gdb butterfly &lt;coredump-file> -tui
</code></pre>

Useful commands
<pre><code>
where
bt full
info locals
info registers
</code></pre>

## GDB

Enable debugging symbols with cmake
<pre><code>
-DCMAKE_BUILD_TYPE=Debug
</code></pre>

Check with command `file butterfly`
<pre><code>
butterfly: ELF 64-bit LSB pie executable, x86-64, version 1 (GNU/Linux), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=afc91fcaa442503bfd3157f3d6263c39333b6300, for GNU/Linux 3.2.0, with debug_info, not stripped
</code></pre>

Run gdb with butterfly binary
<pre><code>
gdb ./butterfly
</code></pre>

Useful commands
<pre><code>
lay next
break main
run
show args
set args
continue 
next
nexti
step
stepi
finish
watch
print
bt
bt full
info registers
info source 
info sharedlibrary
</code></pre>