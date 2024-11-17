# Hugo's very simple build tool

## Options file

The file have to following the HCF stanard.

### Variables field

``` hcf
globals:
    variable1 variable 1 value
    ...
    varibaleN variable N value
```

- Variables from global field can be accessed from elsewhere
as if their where locals.
- Local variables can be accessed using $*keyname* where keyname is a valid key name.
- External variables can be accesed using $*field*.*keyname* where field is the fieldname where the key is placed.

Where the first word is the key and the remainig text is the value. You can write comments using "//" and the comment text after it.

### Fields

A field is a space with local variables and local sequences.

### Sequences

A sequence is a entry whose value is a command sequence. It can be defined as a normal variable.

The exec sequence is the entry point for executing commands. The exec sequence have to call other sequences. As the exec sequence is an especial sequence it cant have explicit commands. It just can call other sequences. To call other sequences it have to had their names, by execution order from left to right, splitted by a space.

```hcf
default:
    filename a.out      // local variable
    exec    1 2 3       // main method

// The following entries are called if their
// key name is in the exec sequence

    1       $cc $flags $src -L $inc $filename
    2       ./$filename
    3       rm $filename
```

### Example file

```
globals:
    cc      gcc
    flags   -Wall -Wextra -fsanitize=address,null
    src     ./src/*
    inc     ./include

default:
    filename a.out      // local variable
    exec    1 2 3       // main method

// The following entries are called if their
// key name is in the exec sequence

    1       $cc $flags $src -L $inc $filename
    2       ./$filename
    3       rm $filename



// external variable example

some_other_field:
    local_variable 2

this_field:
    local_variable = $some_other_field.local_variable


// Restrictions
- field keys cant have '.' or spaces
```
