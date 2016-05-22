Boyer-Moore search
Author: Magnus Hagmar
ZID: z5088131

The provided code implements a modified version of the text searching
Boyer-Moore algorithm.

When searching files for multiple terms, a choice has to be made in the order
of which things will be performed. One way is to search all files for the first
term and then to exclude any files which don't contain the term from all
following searches. The problem with this approach is that each file will need
to be opened and read once for each search term. In a bad case where every, or
at least many, files contains every search term, this means every file is read
unnecessarily many times.

The alternate approach is to search the file for all terms at once. The worst
case with this method is one in which the file being searched does not contain
the first search term. In that case, the other searches are being performed
even though they don't need to be. However, the time lost would simply be the
time required for the search algorithm to run, which is significantly smaller
than the time to read the entire file multiple times. As such, this
implementation searches for all of the terms while only reading each file once.

To limit the number of IO operations, the file contents are read into a buffer,
which is then searched. A problem may arise when searching a buffer in this
way. If the search algorithm has shifted (as described in the BM algorithm) the
pattern so that it is trying to check for a match across the end of the buffer
when there is more text in the file, then it can't check for a match. If one
simply reads more data into the buffer, then matches across the boundaries of
buffers would be missed.

This has been solved by saving the offset of the pattern's current position
from the end of the buffer when the buffer's end has been reached. When more
text is read from the file, a small number of characters are moved from the end
of the current buffer into the front of the new one. The number of characters
to be retained is the maximum of all of the searches' offsets from the buffer's
end. When the searches continue with the new buffer contents, they don't start
at the beginning of the buffer, but rather a small offset so they skip any
retained characters which they have already checked.

To further speed up searching, this implementation includes a skip loop to
rapidly skip ahead in the text without making many unnecessary comparisons.
The skip loop is on line 48 in searchquery.cpp, and is an adapted version of
the fast skip loop described in section 4.1.4 of Andrew Hume's and Daniel
Sunday's paper "Fast String Searching" from 1991.



Description of the different files:

- searchquery.h & searchquery.cpp
    These files implement a class which contains a single search pattern. Its
    main feature is the search-function. This function takes as arguments a
    buffer containing the text to be searched through, an unsigned int
    specifying how many characters are in the buffer, and a table to be used
    for translating the text's characters to lower case.


- multisearch.h & multisearch.cpp
    These files implement a class which acts as a container for multiple search
    queries. When the performSearch function is called, it is provided with a
    path to a file to be searched. A buffer is used to retain the file contents
    while it is being searched. Every time the buffer is filled with text from
    the file, all of the contained searches are executed in order. Once all of
    the searches have finished, the MultiSearch checks which of the searches
    is positioned furthest from the end of the buffer in its current position.
    This way, the required characters can be kept in the buffer so the searches
    can continue searching across buffers. Each search has an offset which it
    uses to determine how far from the start of the buffer to continue
    searching.

- a3search.h & a3search.cpp
    These files implement the main function as well as functionality for
    reading the contents of the specified folder, passing the files to the
    MultiSearch object's performSearch function, and printing the output.
