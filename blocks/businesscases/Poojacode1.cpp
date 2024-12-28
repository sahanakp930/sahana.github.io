<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Styled C++ Code</title>
    <style>
        /* General Styles */
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        body {
            font-family: 'Poppins', sans-serif;
            background-color: #fffdfd;
            margin: 0;
            padding: 20px;
            min-height: 100vh;
        }
        section {
            align-content: center;
            background-color: #e2d5c9;
            padding: 4rem;
            width: 100%;
            max-width: 1200px;
            box-shadow: 0 4px 15px rgba(0, 0, 0, 0.1);
            border-radius: 15px;
            margin: 30px auto;
        }
        h1 {
            text-align: center;
            color: #343ef2;
            font-size: 2rem;
            margin-bottom: 1.5rem;
        }
        pre {
            background-color: #181414;
            color: #ffffff;
            padding: 1rem;
            border-radius: 8px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            font-family: 'Courier New', Courier, monospace;
            overflow-x: auto;
        }
        code {
            font-size: 1rem;
            line-height: 1.6;
        }
        a {
            color: black;
            text-decoration: none;
            font-weight: bold;
        }
        a:hover {
            text-decoration: underline;
        }
        /* Header */
        header {
            background-color: #343ef2;
            color: rgb(244, 234, 234);
            padding: 2rem;
            border-radius: 8px;
            margin-bottom: 1.5rem;
            text-align: center;
        }
        header h1 {
            font-size: 2rem;
            margin: 0;
        }
        header p {
            margin: 1rem 0 0;
        }
    </style>
</head>
<body>
    <header>
        <h1>Welcome to My Styled Page</h1>
        <p>Here is an example of C++ code with styling!</p>
    </header>
    <section>
        <h2>C++ Code Example</h2>
        <pre>
<code>#include &lt;iostream&gt;
using namespace std;

int main() {
    cout &lt;&lt; "Hello, World!" &lt;&lt; endl;
    return 0;
}</code>
        </pre>
    </section>
</body>
</html>
