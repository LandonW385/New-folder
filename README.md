# Directory Scanner

A Node.js script that scans a directory and its subdirectories to list all files and directories along with their sizes. The output can be customized using various command-line options.

## Features

- Scans directories recursively.
- Displays file and directory sizes.
- Supports sorting by path, extension, or size.
- Customizable output in metric or raw byte sizes.
- Optionally filters results based on a size threshold.
- Shows block size for files with the `--blocksize` option.

## Installation

1. Clone the repository or download the script.
2. Ensure that you have Node.js installed. You can download it from [nodejs.org](https://nodejs.org/).
3. Install the required dependencies:

    ```
    npm install filesize
    ```

## Usage

You can run the script from the command line with various options.

### Command-line Options:

- `-p, --path <path>`: Specifies the directory to scan. Defaults to the current directory (`.`).
- `-s, --sort <sort_by>`: Sorts the results. Available options are:
    - `alpha`: Sort by file/directory name (alphabetical order).
    - `exten`: Sort by file extension.
    - `size`: Sort by size (largest to smallest).
- `-m, --metric`: Show file sizes in a human-readable format (e.g., KB, MB, GB).
- `-t, --threshold <size>`: Only show files or directories larger than the specified size in bytes.
- `-b, --blocksize`: Show file sizes in block units (default block size is 512 bytes).
- `-h, --help`: Show help information.

## Commands

### Example Commands:

- Scan the current directory and sort files by size:

    ```
    node PJ2.js -s size
    ```

- Scan a specific directory, display sizes in human-readable format, and only show files larger than 1MB:

    ```
    node PJ2.js -p /path/to/directory -m -t 1048576
    ```

- Scan a directory, include block sizes, and sort files alphabetically:

    ```
    node PJ2.js -p /path/to/directory -b -s alpha
    ```

## Output Format

The script will print the following information for each file or directory:

- **Size**: The size of the file/directory. If `--metric` is used, the size will be shown in a human-readable format (e.g., KB, MB).
- **Path**: The relative path to the file or directory from the provided root directory.

### Example output:

    ```
    2.1 MB example.txt
    1.2 GB subfolder/
    450 KB image.jpg
    ...
    ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
