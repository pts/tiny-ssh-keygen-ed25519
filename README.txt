tiny-ssh-keygen-ed25519: tiny ssh-keygen for ed25519 keypairs in standard C
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
tiny-ssh-keygen-ed25519 is a command-line tool implemented in standard C for
generating unencrypted ed25519 keypairs (public and private keys) to be used
with OpenSSH.

tiny-ssh-keygen-ed25519 is a self-contained implementation optimized for
executable file size. It contains ed25519 elliptic curve crypto code (taken
from TweetNaCl), an SHA-512 checksum computation (also taken from
TweetNaCl), a Base64 encoder and some glue code to generate in the proper
file format, to parse to command-line flags and to write the result to file.

Usage for keypair generation (as a replacement for ssh-keygen):

  ./ssh_keygen_ed25519 -t ed25519 -f <output-file> [-C <comment>]

Compile with any of:

* make
* gcc -s -Os -ansi -pedantic -W -Wall -Wextra -Werror -o ssh_keygen_ed25519.dynamic ssh_keygen_ed25519.c
* i686-w64-mingw32-gcc -mconsole -ansi -pedantic -W -Wall -Wextra -Werror -s -Os -o ssh_keygen_ed25519.exe ssh_keygen_ed25519.c
* xtiny gcc -ansi -pedantic -W -Wall -Wextra -Werror -s -Os -o ssh_keygen_ed25519 ssh_keygen_ed25519.c
* You can also use g++ instead of gcc, ssh_keygen_ed25519.c is also a valid
  C++ program.

For an alternative self-contained implementation in Python, see
https://github.com/pts/py_ssh_keygen_ed25519

Incompatibilities with the ssh-keygen command in OpenSSH:

* ssh-keygen supports many more command-line flags and other key types (such
  as `-t rsa').
* ssh-keygen doesn't overwrite the key file if it already exist.
* ssh-keygen uses a more sophisticated default comment containing the
  username and the password. The default comment in tiny-ssh-keygen-ed25519
  is "key" (without the quotes).

tiny-ssh-keygen-ed25519 is licensed under GNU GPL v2.

Operating system compatibility:

* tiny-ssh-keygen-ed25519 works on Unix systems (including Linux and macOS)
  and Windows. Probably it's easy to port it to other systems as well.
* tiny-ssh-keygen-ed25519 needs GCC to compile (probably it also works with
  Clang), the recommended version is GCC >= 4.8. The MinGW GCC also works
  both when run on Windows or as a cross-compiler.
* tiny-ssh-keygen-ed25519 compiles with uClibc and pts-xstatic
  (https://raw.githubusercontent.com/pts/pts-clang-xstatic/master/README.pts-xstatic.txt)
  as well.
* tiny-ssh-keygen-ed25519 compiles with pts-xtiny
  (https://github.com/pts/pts-xtiny) as well. In fact for Linux i386 or
  amd64 (x86_64) it's recommended to compile it with pts-xtiny.

How small is tiny-ssh-keygen-ed25519?

* If compiled with pts-xtiny (see the `xtiny gcc' command above) for Linux
  i386, the ELF executable size is 7568 bytes. It doesn't need any libc.
* If compiled for Linux amd64, linked dynamically to glibc, the ELF
  executable size is about 14504 bytes.
* If compiled for Win32 (see the i686-w64-mingw32-gcc command avove), the
  .exe file is 19968 bytes.
* tiny-ssh-keygen-ed25519 doesn't need any external libraries. If compiled
  with pts-xtiny, it doesn't need any libc either.

__END__
