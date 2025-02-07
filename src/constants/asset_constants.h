#pragma once

namespace Constants {
// Use `extern` to prevent internal linkage, meaning that source files will only
// have one instance of the variable that is shared across all source files that
// include the header file.
// Not using `extern` would result in copying the variable for each source file
// that includes the header file. This would result in multiple instances of the
// variable, which is not what we want.
// Note: `extern` needs to be used with a declaration in a header file, and the
// variable needs to be defined in a source file.

extern const char* BACKGROUND_FILE_PATH;

extern const char* CHARACTER_MAGE_DOWN_FOLDER_PATH;
extern const char* CHARACTER_MAGE_LEFT_FOLDER_PATH;
extern const char* CHARACTER_MAGE_RIGHT_FOLDER_PATH;
extern const char* CHARACTER_MAGE_UP_FOLDER_PATH;

extern const char* CHARACTER_ELF_DOWN_FOLDER_PATH;
extern const char* CHARACTER_ELF_LEFT_FOLDER_PATH;
extern const char* CHARACTER_ELF_RIGHT_FOLDER_PATH;
extern const char* CHARACTER_ELF_UP_FOLDER_PATH;

enum class Direction { UP, DOWN, LEFT, RIGHT };
}  // namespace Constants