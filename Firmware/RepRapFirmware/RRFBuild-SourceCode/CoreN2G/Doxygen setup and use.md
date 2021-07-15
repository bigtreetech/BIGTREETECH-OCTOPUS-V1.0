# Overview
The API documentatoin for this project is generated using Doxygen. Here is a guide for using Doxygen in this project.

# Documenting files
- Only header (.h) files should be documented.
- Any header file that includes global declarations other than class declarations must have a Doxygen "file" comment at the start, otherwuse it should be ignored.
- Use Javadoc style and C++ single line documentationcomments. Do ont use Qt-style documentation comments.
- All entities for which documentation is required must have documentation comments, because we suppress documentation for other entities.

# Running Doxygen
- Set the input file filter to *.h only
- Enable the following Doxygen features: JAVADOC_AUTOBRIEF, OPTIMIZE_OUTPUT_FOR_C, HIDE_UNDOC_MEMBERS.
- Leave other Doxygen options at their default values
- Exclude folders containing Microchip-provided or Microchip-generated files.

DC 2020-07-27
