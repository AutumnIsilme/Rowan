# Rowan language spec

## Lexical structure

### Keywords
Keywords cannot be used as identifiers.   
The following words are classed as keywords:   
#### Control flow:
```
if
for
while
return
break
switch
case
```
####  @TODO Something I should probably name:
```
include
using
cast
true
false
```
#### Data structures:
```
struct
enum
union
soa
```

### Identifiers

Identifiers must fit the following regex: `[a-zA-Z_][a-zA-Z0-9_]*`
That is to say, identifiers can start with a letter or underscore, and can continue with any number of letters, underscores and numbers.
This regex will include `_`, but this will be treated separately as meaning whatever is happening to the variable will go nowhere.

### Comments
Block comments can be nested. Comments can be started and ended the same way as in C:
```rust
// This is a line comment
/*
This is a block comment
/* This is a nested block comment */
// */ This is still in a comment! Even if it doesn't look like it. The line comment at the start of this line makes it so.

// /*
Also still in a comment here! */
```

### Operators and types


## Parser

### Language structures

## Type system

## Code generation