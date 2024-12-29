System Programming Homework
Furkan GÖNEN-B211202035
Yusuf Buğra KILIÇ-B231202355
Kayra Kaan KABAKÇIOĞLU-B231202350
İsmail BELİ-B211202071


-Overview

This project is a command-line file manager that enables users to perform basic file and directory operations efficiently. It leverages Linux/Unix system calls to interact directly with the file system, providing a practical learning experience in system-level programming.

-Supported Features
*Creating, deleting, copying, and moving files and directories
*Changing file and directory permissions
*Viewing file contents
*Logging operations for future reference

-Goals
The project was designed with the following objectives:
1-Learning Linux/Unix System Calls: To understand and utilize system calls such as opendir, readdir, stat, creat, unlink, rmdir, chmod, open, read, write, and rename.
2-Developing a User-Friendly CLI: To create an intuitive interface for performing file and directory operations.
3-Effective Resource Management: To efficiently handle system resources and minimize unnecessary disk I/O operations.

-Project Structure
The project is divided into modular components to ensure clarity and maintainability:
*Source Files
main.c: Handles program flow, processes user input, and invokes the appropriate functions.
file_operations.c: Implements file-related operations like reading, writing, copying, and moving files.
directory_ops.c: Contains functions for listing, creating, and deleting directories.
permissions.c: Manages file and directory permission changes.
logger.c: Logs all operations performed and records their results in a log file.

*Header Files
DIRECTORY_OPS_H: Prototypes for directory operations, including listing, creating, and removing directories.
FILE_OPERATIONS_H: Prototypes for file operations, such as deleting, copying, displaying contents, and creating files.
PERMISSIONS_H: Prototypes for managing file and directory permissions.
LOGGER_H: Prototypes for logging operations and their outcomes.

-Conclusion
This project provided a comprehensive understanding of system programming concepts and file system manipulation using Linux/Unix system calls. The modular design and logging capabilities make it easy to maintain and extend the project. Hosting the source code on GitHub serves as both a collaborative tool and a showcase of our skills in system programming and teamwork.

