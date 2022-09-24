![](./.github/banner.png)

Prints only printable characters of a file

## Features

 - [x] Prints printable chars from a random file or stream

## Usage

```
hexcat <file>
```

## Compilation

Source files are located in `src/` and binary files will go in `bin/`. To compile hexcat, just type :

```
make
```

## Fixes

 1. Binary file (standard input) matches

    ```
    ./hexcat tests/test.log | grep "li"
    Binary file (standard input) matches

    ```

## Contributing

Pull requests are welcome. Feel free to open an issue if you want to add other features.