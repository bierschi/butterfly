# Docs

Install doxygen and graphviz package
<pre><code>
sudo apt-get install doxygen graphviz
</code></pre>

To enable the latex pdf output, install also
<pre><code>
sudo apt-get install texlive-latex-base texlive-latex-recommended texlive-fonts-recommended texlive-pictures texlive-latex-extra
</code></pre>

Create the doxygen reports
<pre><code>
doxygen butterfly
</code></pre>

Build the latex docu
<pre><code>
cd latex/
make
</code></pre>