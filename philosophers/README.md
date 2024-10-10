<p>The <strong>philosophers</strong> project involved implementing the classic "dining philosophers" problem in C, using threads and synchronization mechanisms like mutexes. The goal of this project was to understand issues related to concurrency, process synchronization, avoiding deadlocks, and optimal management of shared resources between threads.</p>

<p>Key elements of the <strong>philosophers</strong> project included:</p>

<ul>
    <li><strong>Thread creation</strong>: Each philosopher was represented as a separate thread, independently cycling through eating, thinking, and sleeping phases.</li>
    <li><strong>Synchronization with mutexes</strong>: To prevent collisions when accessing shared resources (forks), I implemented mutex-based locking mechanisms that synchronized the threads' actions.</li>
    <li><strong>Managing hunger and death</strong>: The program monitored each philosopher's state to ensure they didn’t starve and managed the time spent on thinking, eating, and sleeping accordingly.</li>
    <li><strong>Deadlock prevention</strong>: The implementation required careful handling to avoid situations where philosophers could become indefinitely blocked while waiting for resources (forks), which involved particular attention to process synchronization.</li>
</ul>

<p>The program is compiled using <strong>make</strong>, and the usage is as follows:</p>

<pre><code>$> ./philo 5 800 200 200 7
$> ./philo &lt;number_of_philosophers&gt; &lt;time_to_die&gt; &lt;time_to_eat&gt; &lt;time_to_sleep&gt;</code></pre>

<p>The <strong>philosophers</strong> project helped me gain experience in multithreaded programming, managing shared resources, and implementing synchronization techniques that are crucial for solving concurrency issues in computer systems.</p>
