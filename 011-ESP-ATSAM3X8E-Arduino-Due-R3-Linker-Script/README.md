# ⚡ ATSAM3X8E ARM Cortex-M3 (Arduino Due R3) Linker Script
---
## 🎥 Youtube Channel : @rebwar_ai
## link : https://www.youtube.com/@rebwar_ai
---
## 🎬  Bare-Metal Embedded Systems (AVR & ARM) in C & Assembly – Arm Cortex-M3 Linker Script
## 📺 Here’s the link to this episode: https://youtu.be/oYVLB_smRTI
---

🚀 Understanding the Linker Script from Scratch (ATSAM3X8E | ARM Cortex-M3)
In this video, we take a deep dive into one of the most important topics in bare-metal embedded systems: the linker script.
If you're working without an OS, the linker script is what defines your entire memory layout — FLASH, SRAM, stack, heap, .data, .bss, and more.
We build everything step by step and explain exactly what each line does.
This video is part of my bare-metal series on the ATSAM3X8E — the microcontroller used in the Arduino Due.
📚 What You’ll Learn
🔹 What the linker actually does
🔹 Why embedded systems need a custom linker script
🔹 Defining memory with MEMORY
🔹 Setting the entry point with ENTRY()
🔹 Placing the interrupt vector table
🔹 Understanding .text, .rodata, .data, and .bss
🔹 FLASH vs SRAM (volatile vs non-volatile memory)
🔹 How initialized variables are copied at startup
🔹 What _sdata, _edata, _sbss, _ebss, _sidata, _estack really mean
🔹 Why KEEP() is critical for the vector table
🔹 How alignment works with ALIGN(4)
🧠 Topics Covered
📦 Object files and linking
🧩 Section placement
💾 FLASH vs SRAM memory model
📍 Load address vs runtime address
⚙️ Startup code interaction with linker symbols
🔁 Copying .data from FLASH to SRAM
🧹 Zeroing .bss at reset
