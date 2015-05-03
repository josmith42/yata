## Currently Implemented Features ##

Here is a high level list of currently implemented features:
  * Opening large files quickly (called "partial layout" in the code, since only part of the file is read and "laid out")
  * Opening small files (called "full layout"); having a separate layout scheme for small files allows the scrollbars to behave well
  * Real time monitor of file changes: both passive and active monitoring is used
  * Simple search through plain text and regular expressions (currently, a separate dialog window appears when CTRL-F is pressed); selection of current search term supported; highlighting of all search terms not yet supported
  * Follow tail -- as file changes, view is continuously scrolled to end of file
  * monitoring multiple files with tabs showing each file
  * User sessions -- option to automatically restore user's last session on startup
  * User options -- ability to change font and colors and save the user's preferences

## Planned features ##

Here is a list of planned features, in no particular order.

### Targeted for 1.0 release ###
  * User sessions -- ability to choose a session file to restore
  * Better, "prettier" search interface, similar to the search interface of firefox (a long, narrow widget at the bottom of the screen)
  * Search: highlighting of all text that matches
  * Multiple searches at once: separate searches will be addable to a list, and text that matches any of the search terms will be highlighted.  Different colors for each search item will be supported.
  * Selecting and copying text
  * Display of line numbers, even on large files

### Targeted for after 1.0 release ###
  * Highlighting of recently changed text
  * Hex viewing mode for monitoring binary files
  * Option to view files in separate windows rather than in tabs
  * Possible support for Mac (in theory, this is already possible, but has not been tested)
  * Optional key bindings that match the key bindings of GNU-less ('/' for search, 'j' and 'k' for up and down, respectively, etc.)