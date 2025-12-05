# Worksheet 2 Part 1 - Starting a Tiny OS

This assignment implements a minimal operating system that boots from scratch with a framebuffer driver.

## Tasks Completed

### Task 1: Boot Loader Setup
- Implemented multiboot-compliant boot loader
- Created loader.asm with proper magic numbers
- Set up kernel stack
- **Files:** `source/loader.asm`, `source/link.ld`

### Task 2: Calling C from Assembly
- Successfully transfers control from assembly to C
- Implements kmain() function as OS entry point
- **Files:** `source/kmain.c`

### Task 3: Framebuffer Driver
Comprehensive framebuffer driver with full 2D API:

**Features:**
- `fb_clear()` - Clear the screen
- `fb_move_cursor(x, y)` - Move cursor to position
- `fb_write_char(c)` - Write single character
- `fb_write_string(str)` - Write string
- `fb_set_color(fg, bg)` - Set text colors
- `fb_newline()` - Move to next line
- `fb_backspace()` - Handle backspace

**Colors supported:**
- Black, Blue, Green, Cyan, Red, Magenta, Brown
- Light variations of above colors
- White

**Files:** `drivers/frame_buffer.h`, `drivers/frame_buffer.c`

### Task 4: Documentation
Complete README with code snippets and explanations.

## Directory Structure

```
assignment2/
├── source/
│   ├── loader.asm      # Boot loader
│   ├── kmain.c         # Kernel main
│   ├── link.ld         # Linker script
│   ├── io.s            # I/O port operations
│   └── io.h            # I/O headers
├── drivers/
│   ├── frame_buffer.h  # Framebuffer API
│   └── frame_buffer.c  # Framebuffer implementation
├── iso/
│   └── boot/
│       └── grub/
│           └── menu.lst # GRUB config
├── Makefile
└── README.md
```

## How to Build

```bash
# Build kernel
make

# Create ISO image (requires stage2_eltorito in iso/boot/grub/)
make os.iso

# Run in QEMU (requires qemu-system-i386 and ISO image)
make run

# Clean build files
make clean
```

## Running the OS

The OS demonstrates:
1. Successful boot from scratch
2. Control transfer from assembly to C
3. Framebuffer initialization
4. Color support
5. Cursor positioning
6. String output

To quit QEMU when running in curses mode:
```bash
# In another terminal
telnet localhost 45454
# Then type: quit
```

## Implementation Notes

### Boot Process
1. GRUB loads the kernel at 0x00100000
2. loader.asm sets up stack and calls kmain()
3. kmain() initializes framebuffer and displays test messages

### Framebuffer
- Memory-mapped I/O at address 0x000B8000
- 80x25 character grid
- 16 foreground and 8 background colors
- Hardware cursor control via I/O ports 0x3D4/0x3D5

### I/O Operations
- `outb()` - Write byte to I/O port
- `inb()` - Read byte from I/O port

## Requirements

- NASM assembler
- GCC with 32-bit support (-m32)
- GNU ld linker
- genisoimage (for creating ISO)
- QEMU (for testing)
- GRUB stage2_eltorito file

## Testing

The kernel automatically runs tests on boot:
- Clear screen
- Write colored text
- Test cursor positioning
- Display multiple lines

All tests complete successfully if you see the welcome message and colored output.
