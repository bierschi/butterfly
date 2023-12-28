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