# my_ls

- **Binary name:** my_ls  
- **Language:** C  
- **Group Size:** 1  
- **Compilation:** via Makefile, including re, clean and fclean rules  

## Usage

./my_ls [-ldrt]

## Subject

You must recode the ls [-lRdrt] [FILE] command.  
Options can be given in either order.  

## Authorized functions  

The only system calls allowed are the following ones:  
- opendir  
- readdir  
- closedir  
- stat  
- lstat  
- write  
- getpwuid  
- getgrgid  
- time  
- ctime  
- readlink  
- malloc  
- free  
- perror  
- strerror  
- exit  
  
## Examples

![ScreenShot](https://raw.github.com/L0rentz/my_ls/master/examples/example.png)
