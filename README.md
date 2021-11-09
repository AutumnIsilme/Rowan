# Rowan

The Rowan programming language is inspired by JAI, Rust and C. It is designed as a systems programming language, providing a minimal interface with the OS in the @TODO standard library and exposing low-level operation to the programmer.

## Building
Currently incompatible with plain Microsoft Windows, but this will be fixed at some point. 
Requires a modern version of gnu Make utility.

### Compiler
To compile:

`cd /path/to/Compiler`

Release version:
`make release`

Debug version:
`make debug`

## Branches

The statemachinekeywords branch is where I have made the state machine process keywords instead of processing them in the same place as identifiers.
