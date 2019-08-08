<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/00-Table-of-Contents.md" rel="Return to TOC"> Return to TOC </a>

# Intro to Debugging

![](/assets/debugging.jpg)

## Objectives

Upon completion of this topic, the student should have a basic understanding of the following concepts:


* **What is Debugging**
* **What tools can be used for debugging**
* **The Debugging Process**

## What is debugging?

By now, you have more than likely experienced C code that would not compile. You probably asked yourself, 

* **Why did this happen?** 
* **What can I do to fix this?**

Or maybe you asked yourself,

* **Why isn't my code passing this test case?**
* **My code compiled, what do these warnings mean though?**
    * **Why is my program doing something I didn't expect?**

Debugging is using a tool that doesn't necessarily give us the answer; but helps us find it.  This can be in the compilation process or some incorrect code. 
**De** means to denote removal. **Bug** is just an error, flaw, failure or fault within a program.

## Tools Used

Identified below are some of the different tools that we can utilize for debugging.  When debugging, keep in mind the development when choosing your debugging tool.

* GDB
* `<stdio>`
* CLion
* VS Code
* Terminal Output
* IDA Pro

## Debugging Process

There are two general questions to ask yourself when you run into a bug:

* **What did you expect your code to do?**
* **What happaned instead?**

Once you have those questions answered, there are five general steps to take when debugging:

1. Reproduce the bug
   1. If it's a compilation issue... try compiling again... and maybe one more time. If you are receiving the same compile error and the code still doesn't compile, then it's time to look at **why**. 
   2. If the code compiles but the program crashes, repeat the above and observe what is happening. Can you reproduce this bug?
   3. If the code compiles and everything works fine, but you notice it's not what you expected to happen. Can you reproduce this?
2. Describe the bug
3. Capture a snapshot of your program when the bug happens. Take note of all the variable's values, location of code (if applicable), states of the program, etc. 
4. Analyse the snapshot. Based on the details, try to determine the cause of the bug. This can be done in a number of ways. But generally it falls to the process of confirming the many things you believe are true, until you find something that's not. 
5. Fix the bug, be sure to check new bugs don't occur after fixing. 

Sounds kind of simple... right? Well, this has the potential to be a daunting task. This is where TDD really comes into play; to prevent as many bugs as possible during development. There are many tools, as listed above, that make this entire process easier. We will be going over a multitude of ways to identify, confirm, capture, anaylse and fix said bug. 

---

### Step One: Reproduce the Bug

Being able to reproduce the bug is extremely important. This helps identify if it's even a bug at all. This also gives us crucial data for the remaining steps. 

* **What happened?**
* **What did you expect to happen?**
* **When did it happen?**
* **How did you manage to reproduce it?**

Here's the first step. Attempted to compile your code. You expected at least one major thing to happen. 

#### Did your code compile?

If no, then there is a bug. Something in your code is causing a compilation error. Run it again to be sure that it's not your IDE causing the error or some **"glitch"**. If it still fails, mark it down as a compilation bug. If you managed to **reproduce** it, just by re-compiling the code. Move on to step 2. 

If yes, then you are solid. Continue.

#### Did the program compile, yet crashes on launch or at some point when it's not expected to crash?

If yes, then something in your code has been done wrong. **Can you reproduce this?** Yes? **How did you reproduce this?** Mark it down as a critical bug, move on to step 2. 

If no, then continue. 

#### Did the program do as you expected? Or did your test case pass?

If no:
* **Something in your code has been done wrong or** 
* **You programmed your test case incorrectly** 
* **Can you reproduce this output? If yes,** 
* **How did you reproduce it**
* **Does it sometimes return the correct expectation?** 
* **Mark it down as a bug, move on to step 2** 

If yes, then your code is fine. 

---

### Step 2: Describe the Bug

Step 2 is deeply involved. Our questions will describe the bug for us. Of course, not all questions apply below. 

* **Is it reproduceable?**
* **How can you make it happen?**
* **What happened?**
* **What should of happened?**
* **Is it correct sometimes?**
* **When did it happen?**
* **What can support this?**
* **How critical is it?**
The above is often called a **bug report.**

---

### Step 3: Snapshot

Taking a snapshot of the program requires us to gather all information about the program when the bug is present. 
Things such as: 

* **variable values**
* **stack information**
* **resources**
* **error/warning messages**
* **test assertions**
* **compile errors**
* **IDE break on exceptions**
* **etc**

We gather this information by using tools such as debuggers, I/O, test assertions, etc. 

---

### Step 4: Analyze Snapshot

`Confirm the things you believe to be true... until you find something that's not true`

Analyze all of the information we have gathered from the snapshot. 

To do this:
* **Confirm conditions, variables, stack allignment, etc.**

When we find something in code that is producing an output we didn't expect; attempt to discover **Why**. 

This analysis often requires backstepping to the first thing we find to be false and continuing until we run into a series of things we find to be true. 

Generally this location in code contains the bug. 
## Sometimes, it can be more complicated than that.

We will of course go over many different methods of analyzing and identifying bugs during this chapter. 

---

### Step 5: Fix the Bug

Fixing the bug is pretty straight forward

* Once the cause of the bug has been identified; **Fix the Code**. 

* After fixing the code, we need to ensure no further bugs were created by our "fixing" the previous bug. 

* To do this, re-run the code, or create an identical snapshot and re-analyze the original "ladder".

---
<a href="https://github.com/CyberTrainingUSAF/06-Debugging-Assembly/blob/master/01_Debugging/02_IO_Debugging.md" rel="Continue to Next Topic"> Continue to Next Topic </a>
