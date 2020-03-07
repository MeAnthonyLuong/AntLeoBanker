# The Jolly Banker

The Jolly Banker uses queues and binary search trees
to simulate a banking application. The program reads in a string of transactions from a file into an in-memory queue. It processes transactions of the following: Opening Accounts, Depositing Funds, Withdrawing Funds, Transfering Funds, and Displaying Transaction History. It is then read from the queue and processes the transactions in order. Once the queue has depleted, the program will print out all of the opened accounts and total balances in those accounts.

---

## Compile and Run

```
./simplecompile.sh
```

### Style Explanation
These options are defined in `.clang-tidy` file.

Perform all check except the following:

- cert-err58-cpp
- cppcoreguidelines-avoid-magic-numbers
- cppcoreguidelines-owning-memory: not using gsl
- cppcoreguidelines-pro-bounds-array-to-pointer-decay: do not give warnings on assert
- cppcoreguidelines-pro-bounds-constant-array-index
- cppcoreguidelines-pro-bounds-pointer-arithmetic
- cppcoreguidelines-special-member-functions: not defining move operator
- fuchsia-* do not need specific checks for "fuchsia" a modular, capability-based operating system
- google-build-using-namespace: for simplicity allow `using namespace std;`
- google-global-names-in-headers: for simplicity allow `using namespace std;`
- google-readability-braces-around-statements: allow compact code without `{`
- hicpp-braces-around-statements: allow compact code without `{` (this option
- hicpp-no-array-decay: need to use assert
- hicpp-special-member-functions: not defining move operator
- llvm-header-guard: not using full directory name
- modernize-pass-by-value
- modernize-use-trailing-return-type: not ready yet for `auto func() -> int` format
- readability-braces-around-statements
- readability-magic-numbers

## Misc

This file is part of a repository located at
https://github.com/jdelliot/banker
