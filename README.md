# Randall: Modular Random Byte Stream Generator

This project modularizes and improves the 'randall' random byte stream generator. It enhances the original implementation by splitting the program into distinct modules, adding command-line options, implementing basic testing, and enabling performance comparison across different data sources and output methods.

## Features

- Modular C implementation with separate source files:
  - 'options.c': Handles command-line argument parsing
  - 'output.c': Handles output to stdio or raw system calls
  - 'rand64-hw.c': Uses 'rdrand' for hardware RNG
  - 'rand64-sw.c': Uses 'mrand48_r' for software RNG
- 'randall.c' contains the 'main' function and program glue
- 'Makefile' supports builds, tests, and tarball generation
- 'make check' runs sanity tests on output size and behavior
- Robust error handling for all system calls and options
- Logging via 'notes.txt' tracks development, debugging, and performance testing

## Command-line Options

### Input Source ('-i')
- 'rdrand': Use hardware RNG (default); fails if unsupported
- 'mrand48_r': Use software RNG
- '/X': Use any file path (e.g., '/dev/urandom') as input source

### Output Method ('-o')
- 'stdio': Use standard buffered output (default)
- 'N': Use raw 'write' system call to write N bytes at a time

## Usage

'bash'
./randall SIZE [OPTIONS]
'bash'

Example:
'bash'
./randall 1048576 -i /dev/urandom -o 1024 > rand.data
'bash'

## Building

'bash'
tar -xzf randall-git.tgz
cd randall
git clone . randall-work
cd randall-work
make
'bash'

## Testing

Run built-in checks:
'bash'
make check
'bash'

## Performance Evaluation

Compare runtime for different input/output configurations:

'bash'
time ./randall 133562368 >/dev/null
time ./randall 133562368 -i /dev/urandom -o 4096 >rand.data
'bash'

## Notes

Development notes, debugging logs, and timing results are recorded in 'notes.txt'.

## License

This project uses the license specified in the 'COPYING' file.

---

This README summarizes the purpose, structure, and usage of the 'randall' random stream generator. It is part of a systems programming assignment focused on modularization, testing, and performance benchmarking.
