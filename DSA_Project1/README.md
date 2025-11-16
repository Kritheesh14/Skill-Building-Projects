Give executable permission to `run.sh` :
```bash
chmod +x run.sh
```

Make sure GTK is installed on machine.

---

##### Objective
Design a simple calculator that can evaluate input expression of a certain size, which must include the workflow:
- Input Expression
- Set expression size
- Calculate expression value
- Input multiple expressions simultaneously (reading from a file)
- Input negative numbers


**Workflow:**

We start with two empty stacks: one [numstack] to hold the numerical values (operands) and one [opstack] to hold the operators $(+, -, \times, /)$ and parentheses. We begin scanning the input expression string character by character from left to right.

As we scan each character, we decide what to do based on its type:

* **If it's Whitespace:** Skip it and move to the next character.
* **If it's a Number (Digit or Decimal Point):**
    * We must read the entire number (e.g., if we see '1', we keep reading to get '15.5').
    * We convert this string of digits into a numerical value (a double).
    * We **push** this numerical value onto the **Number Stack**.
* **Special Case: Unary Negation (Negative Sign):**
    * If we see a minus sign ('-') right at the start of the expression or immediately after an opening parenthesis '(', we know it's a unary negative sign, not a subtraction operator.
    * We read the number following it, treat it as negative, and **push** the resulting negative number onto the **Number Stack**.
* **If it's an Opening Parenthesis ('('):**
    * Since parentheses dictate a new, higher level of precedence, we simply **push** the '(' onto the **Operator Stack**.
* **If it's a Closing Parenthesis (')'):**
    * This signals the end of a sub-expression. We must process everything inside the parentheses first.
    * We start a loop: while the top of the **Operator Stack** is NOT the matching '(', we perform an operation:
        1.  **Pop** two numbers from the **Number Stack** (these are the operands).
        2.  **Pop** one operator from the **Operator Stack**.
        3.  Apply the operator to the two numbers.
        4.  **Push** the result back onto the **Number Stack**.
    * Once the matching '(' is found, we pop and discard it.
* **If it's a Binary Operator $(+, -, \times, /)$:**
    * This is the core of precedence handling. We compare the current operator's precedence with the operator currently at the top of the **Operator Stack**.
    * We start a loop: while the operator stack is NOT empty and the precedence of the top operator is **higher than or equal to** the current operator's precedence, we perform an operation (Pop two numbers, pop one operator, apply, push result) to ensure high-precedence operations are done first.
    * Once the top operator has lower precedence (or the stack is empty), we **push** the current operator onto the **Operator Stack**.

* **Cleanup:** Once the entire expression string has been scanned, there may be remaining operators and numbers in the stacks (e.g., from $10+5$).
* **Final Loop:** We enter a final loop: while the **Operator Stack** is not empty, we repeat the basic operation steps (pop two numbers, pop the operator, apply, and push the result).
When the **Operator Stack** is finally empty, the very last value remaining on the **Number Stack** is the final result of the entire expression. We pop and return this value.
