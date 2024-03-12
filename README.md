# Micro moulinette 

![the test](https://imgur.com/vobv8Ux.png)

## What is this?
The original moulinette, is a test runner, that verifies the correctness of your app, while you study in 42 Madrid, this project is a local test runner, that gives feedback on your mistakes instantly. But it's mostly a C library/framework, for creating tests of stdout / return type apps / functions in c.


## Who is this for?
Nobody! You should never use this, it is unfinished and undocumented, It only has tests written for C00, out of 12 chapters.

## My inspiration / What should you use
* [Francinette](https://github.com/xicodomingues/francinette) - A very capable and very pretty test runner
* [mini-moulinette](https://github.com/khairulhaaziq/mini-moulinette) - A more complete runner, but has less rigorous tests then francinette, I would use both

## Capabilities
* Written in C
* buffered strings (my own implementation)
* Selective logging
* Variadic argument support with logging
* Has basic arguments support
* Can test functions and full apps
* Can be used for debugging with a debugger (undocumented)
* Can be easily extended
* Has pretty useful a single line diff mode
* You can select which tests to run

## Drawbacks
* Written in C
* Lacks a "manager" app, that automaticaly compiles and runs the tests
* Needs to be compiled manually
* Only covers the C00 out of C00-C11 range (the implementation, not the library)
