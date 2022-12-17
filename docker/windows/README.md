## Ubuntu

Build the windows image
<pre><code>
docker build -t windows:butterfly -f Dockerfile.windows --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=develop .
</code></pre>

Run docker container 
<pre><code>
docker run -it windows:butterfly /bin/bash
</code></pre>