## Ubuntu

Build the debian 11 image
<pre><code>
docker build -t debian11:butterfly -f Dockerfile.debian11 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=develop .
</code></pre>

Run docker container 
<pre><code>
docker run -it debian11:butterfly /bin/bash
</code></pre>