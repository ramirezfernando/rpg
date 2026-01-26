# RPG

## Overview
A 2D RPG written in C++ from scratch (in development).

## Screenshot
<img width="761" height="789" alt="Screenshot 2026-01-21 at 12 32 27 AM" src="https://github.com/user-attachments/assets/ca6a50bc-435f-4f2d-b4b2-29bc6dd533a7" />

## TODO
- Explore C++20 modules
- Use List-initialization / Brace initialization over copy-initialization (for some complex types) to prevent narrowing conversions.
   - Bjarne Stroustrup (creator of C++) and Herb Sutter (C++ expert) also recommend using list-initialization to initialize your variables.
   - [ES.20: Always initialize an object](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#es20-always-initialize-an-object)
- Use `'\n'` rather than `std::endl` unless I need to explicitly flush the buffer.
   - Also ensure to use single quotes unless adding it into existing double quote text.
- Use std::string_view