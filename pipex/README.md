<p>The <strong>pipex</strong> project at 42 Academy involved implementing a program in C that enables connecting processes using pipes, similar to piping in Linux (e.g., <code>ls | grep</code>). The goal of this project was to understand how inter-process communication works, how to use pipes, manage processes, and redirect input and output streams.</p>

<p>As part of the <strong>pipex</strong> project, I also completed the bonus part, which included handling multiple pipes (multi-pipe). This allowed me to chain several processes, just like more complex pipelines, such as <code>cmd1 | cmd2 | cmd3 ...</code>.</p>

<p>Key elements of the project included:</p>

<ul>
    <li><strong>Pipe handling</strong>: The implementation allowed redirecting the output of one process to the input of the next, enabling the chaining of multiple commands.</li>
    <li><strong>Process forking</strong>: Each command was executed in a new process using the <code>fork()</code> function, and communication between processes was handled through pipes.</li>
    <li><strong>Stream redirection</strong>: The program had to correctly redirect standard input and output so that data could flow smoothly between processes.</li>
    <li><strong>Multi-pipe handling</strong>: As part of the bonus, I added functionality to handle multiple commands connected in a long chain of pipes.</li>
</ul>

<p>The prompt for the bonus part, executed with <code>make bonus</code>, looked like this:</p>

<pre><code>$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2</code></pre>

<p>This behaved like the following Linux command:</p>

<pre><code>&lt; file1 cmd1 | cmd2 | cmd3 ... | cmdn &gt; file2</code></pre>

<p>For the regular version of the program, executed with <code>make</code>, the prompt looked like this:</p>

<pre><code>$> ./pipex infile "ls -l" "wc -l" outfile</code></pre>

<p>It must behave exactly the same as the shell command below:</p>

<pre><code>$> &lt; infile ls -l | wc -l &gt; outfile</code></pre>

<p>The <strong>pipex</strong> project helped me better understand inter-process communication in Unix systems and taught me how to manage processes and pipes efficiently and securely.</p>
