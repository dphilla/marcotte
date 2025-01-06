# marcotte

Create Layers of host-agnostic system functionality for your WebAssembly (Wasm) application.

## Use

uses your standard c compiler, and marcotte-provided libc/interfaces to build an
underlying layer/series of layers of system functionality that your program specifies.

Can use the --mod flag to modularize different system layers ( i.e. net, fs, sigs, etc. -- future)
 - **This just provides the system function interfaces as WebAssembly exports for the
 target program to use **

Future:
non-c-standard lib langs - like golang, etc.

## Development

for now, things that need attention are marked with `TODO` -- grep around for these (sorry).
Better bug and issues reporting to come as project grows.

### CLI

`marcotte build <anyfile.c>`

### Lib

`marcotte::build(anyfile.c)`


### What's boxer's role?

Marcotte literally just lets programs run in (or against/on) Wasm without them needing to
modified, by building the various system layers -- but it says nothing about what
environment it will be run in, what the entrypoint is, how it should communicate
with the outside world, etc. Boxer does this, starting with container definition
compatibility, but then in the future with further configuration and box-building options
that take that compat and allow it to be extended for various new runtime environments,
peer-functionality (etc. ... more info to come on that later )


for use with [Boxer](https://github.com/dphilla/wasmboxer), please see `docs/`

## Installation

clone and `cargo build --release` and drop the generated binary in your /usr/bin directory.

Please see the repo's [issues](https://github.com/dphilla/marcotte-wasm/issues) for more information on these.

