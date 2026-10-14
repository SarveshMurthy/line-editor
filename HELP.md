# Line Editor – User Guide

The Line Editor is a simple command-line text editor written in C. Use the numbered menu options to create, modify, view, save, and load a text document.

### 1. Insert a Line

Adds a new line of text at a specified line number. Existing lines at and below that position are shifted down.

**Example:**
Select `1` → Enter line number `1` → Enter text `Hello World`

### 2. Delete a Line

Removes the line at the specified line number. The lines below it are shifted up automatically.

**Example:**
Select `2` → Enter line number `2`

### 3. Display Document

Displays the complete document with numerical line prefixes.

**Example:**
Select `3`

Output:
`1: Hello World`
`2: Welcome to the Line Editor`

### 4. Save Document to File

Saves the current document to a text file on your computer.

**Example:**
Select `4` → Enter filename `note.txt`

### 5. Load Document from File

Loads the contents of an existing text file into the Line Editor.

**Example:**
Select `5` → Enter filename `note.txt`

### 6. Search Text

Searches the document for a word or phrase and displays the line number(s) where it is found.

**Example:**
Select `6` → Enter search text `Hello`

### 7. Find and Replace

Finds specified text on a selected line and replaces its first occurrence with new text.

**Example:**
Select `7` → Enter line number → Enter text to find → Enter replacement text

### 8. Line Count / Word Count

Displays simple statistics about the current document, including the total number of lines and words.

**Example:**
Select `8`

### 9. Exit

Closes the Line Editor program.

**Example:**
Select `9`
