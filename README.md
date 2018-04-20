# file-injector
Simple command-line utility to replace matched strings with file contents.

## Usage
This utility works in a similar fashion to the MySQL
[replace utility](https://dev.mysql.com/doc/refman/5.7/en/replace-utility.html),
except, rather than replacing search terms with specified strings, search terms are replaced with the contents of files
specified.

The syntax is as follows:

`file-injector 'term 1' file-to-replace-1.txt 'term 2' file-to-replace-2.txt < template-file.txt > output.txt`

The program is invoked with an even number of arguments: pairs of search-replace arguments, where the search part is
the string to find and the replace part is the name of the file whose contents are to replace the preceding term, if
found.

It reads from the standard input, and writes to the standard output.

At the moment, there are no options or special arguments.

## Building
Simply run `make`

## Testing
`make test`

This requires the `diff` utility to be installed on your system.

## Installing
After building, the binary file `file-injector` will be in the project directory. Move it to any directory in your
`PATH`, such as `~/bin`.
