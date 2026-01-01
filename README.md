# cpp-logger

A C++ logging library without dependencies.

## Features
- Easy managing of the indentation level.
- Tag system that allows to disable logging for specific parts of the code.

## Dependencies
- None.

## Build

### Prerequisites
- CMake 3.10+
- C++20-compatible compiler (MSVC, GCC, Clang).

### Steps
1. Clone the repository (if not already done):
   ```sh
   git clone https://github.com/Foxclip/cpp-logger.git
   cd cpp-logger
   ```
2. Build the library and tests:
   ```sh
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

## Usage

### Include the Library
```cpp
#include <logger.h>
```

### Log Messages
```cpp
logger << "Hello, world!" << std::endl;
logger << 1 << " " << 2 << " " << 3 << std::endl;
logger << true << " " << false << std::endl;
```

### Manage indentation level
```cpp
logger << "Line 1" << std::endl;
{
    LoggerIndent indent(logger);
    logger << "Line 2" << std::endl; // line 2 will be indented
}
logger << "Line 3" << std::endl;
```

### Deactivate logger for some tags
```cpp
Logger logger(true);
LoggerDisableTag disable_tag2(logger, "tag2");
{
    LoggerTag tag1(logger, "tag1");
    logger << "tag1\n"; // will be logged
}
{
    LoggerTag tag2(logger, "tag2");
    logger << "tag2\n"; // will not be logged
}
```

### Deactivate logger except for some tags
```cpp
Logger logger(true);
LoggerDeactivate deact(logger);
LoggerEnableTag enable_tag1(logger, "tag1");
{
    LoggerTag tag1(logger, "tag1");
    logger << "tag1\n"; // will be logged
}
{
    LoggerTag tag2(logger, "tag2");
    logger << "tag2\n"; // will not be logged
}
```

### Special handling of large amounts of logging
```cpp
logger << "Line 1" << std::endl;
{
    LoggerLargeText logger_large_text(logger);
    logger << "Text Line 1" << std::endl;
    logger << "Text Line 2" << std::endl;
    ...
    logger << "Text Line 1000" << std::endl;
}
logger << "Line 2" << std::endl;
```

### 
