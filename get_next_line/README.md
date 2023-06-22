
## Expected File
```
get_next_line.c get_next_line.h
```
## Allowed Functions
```
read, free, malloc
```

## Prototype
```
char *get_next_line(int fd)
```

## The Program

Your function must return a line that has been read from the file descriptor passe    d as parameter. What we call a "line that has been read" is a succession of 0 to n     characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).
