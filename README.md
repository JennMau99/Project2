# Project2

*Last edited 4/24/18 at 2:46AM*

Current due date: Friday

**Number of testcases passing:** 7/17

# Things to do:
1. Rewrite part of hash_words so that it correctly processes strings that include special characters. I don't know if that means using something other than strtok or not, we'll have to talk about it.
2. Change hash_words so that it can take both lines and words of variable length. Currently, two of the testcases are failing because they test that very long lines/words can be read correctly. Same as above, I don't know if that'll involve changing strtok or not.
3. Add some error messages for input. That's why testcase 1 and 2 are failing.
4. Add support for stdin. I've tried working on it, but the word counts are way off.
5. Fix word count stuff? Some testcases look like they're just not being counted correctly. Maybe if we fix all the other problems, it'll go away, but I don't know. Pretty sure the problem is in hash_words though, as that's where the other problems are coming from.
6. Split this program up into multiple files. That should come last, so the only thing we have to worry about is copy/pasting and setting up the extern variables correctly.

**Biggest thing to work on:** hash_words has the most problems, so let's start there.

# What I just changed:
1. I removed the delete function. For some reason, it wasn't freeing the list of pointers correctly. It was only 3 lines of code anyway, and that exact same code (that doesn't work in delete) works in resize. No more memory leaks in the current code.
2. Modified compare so that it takes into account words with the same frequency and words with the same frequency that start with the same letter(s).
3. Lots of general error fixing to get some testcases to pass. Went from 3 testcases passing to 7 passing.
4. Deleted that extra print function that nothing was using.
5. Cleaned up the code. There were some commented out pieces here and there, which I removed.
6. Put comments at the top of each function.
7. Got rid of those 2 warnings about unused pointers that had been there for forever. :)

&nbsp;

Let me know whenver we can meet up!


