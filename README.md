# fdopendir-safe-analysis
This repo focuses on the analysis of fdopendir with three concepts.

# 🚀 Compiler Expert - Embedded Software Engineer - Mustafa Acar 🌟

Welcome to the **fdopendir Safety Analysis** project! This repository showcases advanced techniques and testing methodologies for analyzing and understanding safety concepts like **MT-Safe**, **AS-safe Heap**, and **AC-safe** within the glibc library.

---

## 🔍 Overview
This project is designed to:
- 🛠️ Test the `fdopendir` function for thread safety (MT-Safe).
- 💡 Analyze its behavior with asynchronous signals (AS-Unsafe).
- 🔗 Investigate memory and file descriptor management (AC-Unsafe).

------------

## 📂 Project Structure

```plaintext
📦 fdopendir-safe-analysis
├── 📁 src
│   ├── 📁 AC_UNSAFE
│   │   ├── fdopendir_ac_unsafe_test.c
│   │   ├── ...
│   ├── 📁 AS_UNSAFE_HEAP
│   │   ├── fdopendir_as_unsafe_heap_test.c
│   │   ├── ...
│   ├── 📁 MT_SAFE
│       ├── fdopendir_mt_safe_test.c
│       ├── ...
├── 📁 docs
│   ├── testing-methodology.md
│   ├── conclusions.md
├── 📁 scripts
│   ├── compile_and_run_with_valgrind.sh
├── LICENSE
├── README.md

# Fdopendir Safety Analysis

## Overview
This repository evaluates the safety of `fdopendir` in terms of:
- **MT-Safe**: Multi-thread safety.
- **AS-Unsafe Heap**: Issues related to heap memory allocation.
- **AC-Unsafe Mem FD**: Handling of memory and file descriptors.

The project provides code samples and tests to explain and verify these concepts.

## Structure
- **`src/AC_UNSAFE/`**: Tests for `AC-Unsafe`.
- **`src/AS_UNSAFE_HEAP/`**: Tests for `AS-Unsafe Heap`.
- **`src/MT_SAFE/`**: Tests for `MT-Safe`.
- **`scripts/`**: Includes scripts for automated testing.
- **`docs/`**: Documentation and explanations.

## How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/mustafaacarinfo/fdopendir-safe-analysis.git

2. cd fdopendir-safe-analysis

3. check your ldd --version  [exmple output: ldd (Ubuntu GLIBC 2.27-3ubuntu1.6) 2.27]
    
4. ./scripts/compile_and_run_with_valgrind.sh

    Test Selection: Follow the interactive prompts to choose the desired test:

    Option 1: AC-Unsafe Test
    Option 2: AS-Unsafe Heap Test
    Option 3: MT-Safe Test

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
🌟 About Mustafa Acar
👨‍💻 Compiler Expert & Safety Enthusiast
🎓 Passionate about low-level programming, advanced debugging.
💡 Always looking for ways to optimize, analyze, safe and understand complex systems.
