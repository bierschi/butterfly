## Ubuntu

Build the ubuntu 1804 image
<pre><code>
docker build -t ubuntu1804:butterfly -f Dockerfile.ubuntu1804 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=develop .
</code></pre>

Build the ubuntu 2004 image
<pre><code>
docker build -t ubuntu2004:butterfly -f Dockerfile.ubuntu2004 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=develop .
</code></pre>

Build the ubuntu 2204 image
<pre><code>
docker build -t ubuntu2204:butterfly -f Dockerfile.ubuntu2204 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=develop .
</code></pre>

Run docker container 
<pre><code>
docker run -it ubuntu2004:butterfly /bin/bash
</code></pre>