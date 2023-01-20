# Stack Smashing on x86_64 Linux

This is a simple proof-of-concept implementation of stack smashing on x86_64
Linux.

## Disclaimer

Stack smashing, just like other buffer overflow vulnerabilities, can be
dangerous. You should act with caution, and be responsible for what you do.

## Usage

You may build the executable with GNU Make. Run the executable, and you should
get a shell.

```plaintext
make
./smash
```

## Credits

This project is inspired by Aleph One's article, *Smashing The Stack For Fun And
Profit*, originally published on the
[Phrack Manazine](http://phrack.org/issues/49/14.html).

## License

This project is [GPLv3-licensed](LICENSE).
