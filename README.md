# Hugo's build tool

## Options file

The file have to following the [*HCF standard*](https://github.com/hugocotoflorez/vshcfp) and be named `build.hcf`.

### Default field

The **default** field stores *global variables* and the *default exec entry point*. All the variables in default can be referenced only by it's name.

### Exec

The entry field (default by default) have to had a exec entry. It can only have *keys* or *field names* joined by spaces. Each key  value would be executed, from left to right. If a field name is found, it executes their exec.

### Priority

Local variables have more priority than global ones.

### Extern keys

If it's needed to acced a key that is defined in another field which is not the default, it can be accesed using *field*.*key*.

### Accessing variables

For accessing a variable it is needed to use the '$' symbol before the local key name or the field.key entry.

## Example
```hcf
default:
    cc          gcc
    flags       -Wall -Wextra -fsanitize=address,null
    src         ./src/*
    inc         ./include
    filename    hbuild
    exec        compile install

compile:
    exec        1
    1           $cc $flags $src -L $inc -o $filename

install:
    exec        1
    1           mv ./$filename ~/.local/bin/$filename
```

## How to Install

You can compile it with the makefile. If it is yet compiled, it can recompile itself with the given build.hcf file.
