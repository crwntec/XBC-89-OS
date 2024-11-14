<p align="center">
    <img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" align="center" width="30%">
</p>
<p align="center"><h1 align="center">XBC-89-OS</h1></p>
<p align="center">
    <em><code>❯Xtremly Basic Calculator</code></em>
</p>
<p align="center">
    <!-- local repository, no metadata badges. --></p>
<p align="center">Built with the tools and technologies:</p>
<p align="center">
    <img src="https://img.shields.io/badge/GNU%20Bash-4EAA25.svg?style=default&logo=GNU-Bash&logoColor=white" alt="GNU%20Bash">
    <img src="https://img.shields.io/badge/C-A8B9CC.svg?style=default&logo=C&logoColor=black" alt="C">
    <img src="https://img.shields.io/badge/GitHub%20Actions-2088FF.svg?style=default&logo=GitHub-Actions&logoColor=white" alt="GitHub%20Actions">
</p>
<br>

##  Table of Contents

- [ Overview](#-overview)
- [ Features](#-features)
- [ Project Structure](#-project-structure)
  - [ Project Index](#-project-index)
- [ Getting Started](#-getting-started)
  - [ Prerequisites](#-prerequisites)
  - [ Installation](#-installation)
  - [ Usage](#-usage)
  - [ Testing](#-testing)
- [ Project Roadmap](#-project-roadmap)
- [ Contributing](#-contributing)
- [ License](#-license)
- [ Acknowledgments](#-acknowledgments)

---

##  Overview

<code>This Project is a 32-Bit x86 Operating system running a calculator that performs basic arithmetic operations. It consists of a custom bootloader written in NASM assembly that loads kernel and firmware from the disk and calls the kernel entry. The kernel then intializes Screen and Keyboard aswell as other basic things and runs the firmware containing the calculator code. The Firmware is written purely in C mostly without standard librarys and converts input into Reverse Polish Notation using the <a href="https://en.wikipedia.org/wiki/Shunting_yard_algorithm">Shunting Yard Algorithm</a></code>

---

##  Features

<code> 
    - Custom Bootloader
    - 32-Bit protected mode
    - VGA and Keyboard Drivers
    - Arithmetic Calculator

</code>

---

##  Project Structure

```sh
└── os/
    ├── .github
    │   └── workflows
    ├── README.md
    ├── build
    │   ├── boot.bin
    │   ├── cpu
    │   ├── drivers
    │   ├── firmware
    │   ├── kernel
    │   ├── kernel.bin
    ├── makefile
    ├── output
    │   └── image.bin
    ├── setup-gcc-debian.sh
    └── src
        ├── boot
        ├── cpu
        ├── drivers
        ├── firmware
        └── kernel
```


###  Project Index
<details open>
    <summary><b><code>XBC-89-OS/</code></b></summary>
    <details> <!-- __root__ Submodule -->
        <summary><b>__root__</b></summary>
        <blockquote>
            <table>
            <tr>
                <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/setup-gcc-debian.sh'>setup-gcc-debian.sh</a></b></td>
                <td><code>❯ Setup Code for installing cross-compiler chain on Debian</code></td>
            </tr>
            <tr>
                <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/makefile'>makefile</a></b></td>
                <td><code>❯ Makefile to build and run the project</code></td>
            </tr>
            </table>
        </blockquote>
    </details>
    <details> <!-- src Submodule -->
        <summary><b>src</b></summary>
        <blockquote>
            <details>
                <summary><b>kernel</b></summary>
                <blockquote>
                    <table>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/kernel/kernel_entry.asm'>kernel_entry.asm</a></b></td>
                        <td><code>❯ Kernel entry code calling main function</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/kernel/kernel.c'>kernel.c</a></b></td>
                        <td><code>❯ Kernel source</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/kernel/kernel.h'>kernel.h</a></b></td>
                        <td><code>❯ kernel header</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/kernel/util.c'>util.c</a></b></td>
                        <td><code>❯ Utility source</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/kernel/util.h'>util.h</a></b></td>
                        <td><code>❯ Utility header</code></td>
                    </tr>
                    </table>
                </blockquote>
            </details>
            <details>
                <summary><b>firmware</b></summary>
                <blockquote>
                    <table>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/firmware/eval.c'>eval.c</a></b></td>
                        <td><code>❯ Evaluation and Shunting source</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/firmware/eval.h'>eval.h</a></b></td>
                        <td><code>❯ Evaluation and Shunting header</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/firmware/xbc.c'>xbc.c</a></b></td>
                        <td><code>❯ Calculator source</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/firmware/xbc.h'>xbc.h</a></b></td>
                        <td><code>❯ Calculator header</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/firmware/tokenize.c'>tokenize.c</a></b></td>
                        <td><code>❯ Tokenizer source</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/firmware/tokenize.h'>tokenize.h</a></b></td>
                        <td><code>❯ Tokenizer header</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/firmware/util.c'>util.c</a></b></td>
                        <td><code>❯ Firmware utilities source</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/firmware/util.h'>util.h</a></b></td>
                        <td><code>❯ Firmware utilities header</code></td>
                    </tr>
                    </table>
                </blockquote>
            </details>
            <details>
                <summary><b>cpu</b></summary>
                <blockquote>
                    <table>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/cpu/low_level.c'>low_level.c</a></b></td>
                        <td><code>❯ Low Level source for communication with external devices</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/cpu/low_level.h'>low_level.h</a></b></td>
                        <td><code>❯ Low Level header</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/cpu/interrupt.asm'>interrupt.asm</a></b></td>
                        <td><code>❯ Assembly file redefining interrupt service routines (ISRs)</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/cpu/idt.c'>idt.c</a></b></td>
                        <td><code>❯ Interrupt Descriptor Table (IDT) source</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/cpu/idt.h'>idt.h</a></b></td>
                        <td><code>❯ IDT header</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/cpu/isr.c'>isr.c</a></b></td>
                        <td><code>❯ ISR definitions and init source</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/cpu/isr.h'>isr.h</a></b></td>
                        <td><code>❯ ISR header</code></td>
                    </tr>
                    </table>
                </blockquote>
            </details>
            <details>
                <summary><b>drivers</b></summary>
                <blockquote>
                    <table>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/drivers/libscreen.c'>libscreen.c</a></b></td>
                        <td><code>❯ VGA Display driver source</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/drivers/libscreen.h'>libscreen.h</a></b></td>
                        <td><code>❯ VGA Display driver header</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/drivers/libkey.c'>libkey.c</a></b></td>
                        <td><code>❯ PS/2 Keyboard driver source</code></td>
                    </tr>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/drivers/libkey.h'>libkey.h</a></b></td>
                        <td><code>❯ PS/2 Keyboard driver source</code></td>
                    </tr>
                    </table>
                </blockquote>
            </details>
            <details>
                <summary><b>boot</b></summary>
                <blockquote>
                    <table>
                    <tr>
                        <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/boot/boot.asm'>boot.asm</a></b></td>
                        <td><code>❯ Bootloader</code></td>
                    </tr>
                    </table>
                    <details>
                        <summary><b>include</b></summary>
                        <blockquote>
                            <table>
                            <tr>
                                <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/boot/include/disk.asm'>disk.asm</a></b></td>
                                <td><code>❯ Routines for disk loading</code></td>
                            </tr>
                            <tr>
                                <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/boot/include/print.asm'>print.asm</a></b></td>
                                <td><code>❯ Print routine for real mode</code></td>
                            </tr>
                            <tr>
                                <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/boot/include/switch_to_pm.asm'>switch_to_pm.asm</a></b></td>
                                <td><code>❯ Routines for switching to 32-Bit PM</code></td>
                            </tr>
                            <tr>
                                <td><b><a href='https://github.com/crwntec/XBC-89-OS/blob/main/src/boot/include/gdt.asm'>gdt.asm</a></b></td>
                                <td><code>❯ Global Descriptor Table (GDT)</code></td>
                            </tr>
                            </table>
                        </blockquote>
                    </details>
                </blockquote>
            </details>
        </blockquote>
    </details>
</details>

---
##  Getting Started

###  Prerequisites

Before getting started with os, ensure your runtime environment meets the following requirements:

- **Programming Language:** C and Assembly


###  Installation

Install os using one of the following methods:

**Build from source:**

1. Clone the os repository:
```sh
❯ git clone https://github.com/crwntec/XBC-89-OS.git
```

2. Navigate to the project directory:
```sh
❯ cd XBC-89-OS
```

3. Install the project dependencies:

echo './setup-gcc-debian.sh'



###  Usage
Run os using the following command:
echo 'make run'

---
##  Project Roadmap

- [X] **`Task 1`**: <strike>Implement working operating system.</strike>
- [X] **`Task 2`**: <strike>Implement calculator.</strike>
- [ ] **`Task 3`**: Extend calculator functionality.

---

##  Contributing

- **💬 [Join the Discussions](https://github.com/crwntec/XBC-89-OS/discussions)**: Share your insights, provide feedback, or ask questions.
- **🐛 [Report Issues](https://github.com/crwntec/XBC-89-OS/issues)**: Submit bugs found or log feature requests for the `os` project.

<details closed>
<summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your LOCAL account.
2. **Clone Locally**: Clone the forked repository to your local machine using a git client.
   ```sh
   git clone https://github.com/crwntec/XBC-89-OS.git
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to LOCAL**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.
8. **Review**: Once your PR is reviewed and approved, it will be merged into the main branch. Congratulations on your contribution!
</details>

<details closed>
<summary>Contributor Graph</summary>
<br>
<p align="left">
   <a href="https://github.com/crwntec/XBC-89-OS/graphs/contributors">
      <img src="https://contrib.rocks/image?repo=vboxuser/os">
   </a>
</p>
</details>

---

##  Acknowledgments

- Writing a Simple Operating System - from Scratch by Nick Blundell [Link](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf) (sadly incomplete :( )
- Making an OS (x86) series by Daedalus Community [Link](https://www.youtube.com/playlist?list=PLm3B56ql_akNcvH8vvJRYOc7TbYhRs19M)

---
