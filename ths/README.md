# Tor Hidden Service

## Torrc Settings

Install tor with
<pre><code>
sudo apt-get install tor
</code></pre>

Edit torrc file in `/etc/tor`. Adapt the ip and port where the bflyServerApp is running
<pre><code>
HiddenServiceDir /var/lib/tor/hidden_service/
HiddenServicePort 80 127.0.0.1:5000
</code></pre>

Restart the tor service
<pre><code>
sudo systemctl restart tor
</code></pre>

Get the hostname from `/var/lib/tor/hidden_service/`
<pre><code>
cat hostname
y55reqejevhbvyrl6r3yahz5ctsrz7v4glkrcklvyso4a3whht3lhfyd.onion
</code></pre>

Check tor settings
<pre><code>
https://check.torproject.org/
</code></pre>

## Deploy bflyServerApp

<pre><code>
pip3 install bflyServerApp-*-py3-none-any.whl
</code></pre>

## Apache Settings (If needed)




## Test your onion service with firefox
Settings -> Network Settings
<pre><code>
Manual Proxy Configuration
SOCKS Host: 127.0.01  Port: 9050
SOCKSv5
No proxy for: 127.0.0.1
Proxy DNS when using SOCKS v5
</code></pre>

Open your browser and insert the hostname
<pre><code>
http://y55reqejevhbvyrl6r3yahz5ctsrz7v4glkrcklvyso4a3whht3lhfyd.onion/
</code></pre>

<pre><code>
http://y55reqejevhbvyrl6r3yahz5ctsrz7v4glkrcklvyso4a3whht3lhfyd.onion/api/v1/decryption/counter/
</code></pre>
