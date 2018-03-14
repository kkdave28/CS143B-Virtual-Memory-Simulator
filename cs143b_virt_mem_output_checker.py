#!/usr/bin/python

from __future__ import print_function
import sys

reg_keywords = {"pf", "err"}
tlb_keywords = {"h", "m"}

def reg_word_valid(word):
    try:
        i = int(word)
        return True
    except ValueError:
        if word not in reg_keywords:
            print("ERROR: non-TLB output word '%s' does not match any of the valid outputs: %s" % (word, ', '.join(reg_keywords)))
            return False
        return True

def tlb_word_valid(word):
    if word not in tlb_keywords:
        print("ERROR: TLB output word '%s' does not match any of the valid outputs: %s" % (word, ', '.join(tlb_keywords)))
        return False
    return True

def main():
    if len(sys.argv) < 3:
        print("Usage: {} <your_non-TLB_output_file> <your_TLB_output_file>".format(sys.argv[0]))
        return -1

    try:
        fname1, txt1 = sys.argv[1].split('.')
        if fname1.lower().startswith('x'):
            fname1 = fname1[1:]
        i = int(fname1)
        if txt1 != 'txt':
            raise ValueError
    except ValueError:
        print("ERROR: non-TLB filename should be your student ID number and a .txt extension only!! Example: 123456.txt")
        return -1

    try:
        fname2, txt2 = sys.argv[2].split('.')
        if fname2.lower().startswith('x'):
            fname2 = fname2[1:]
        fname2, tlb = fname2.split('_')
        i = int(fname2)
        if tlb != 'tlb':
            raise ValueError
        if txt2 != 'txt':
            raise ValueError
    except ValueError:
        print("ERROR: TLB filename should be your student ID number and '_tlb.txt'!! Example: 123456_tlb.txt")
        return -1

    with open(sys.argv[1]) as reg_out:
        lines = reg_out.readlines()
        if len(lines) > 1:
            print("ERROR: more than one line present in non-TLB output file!")
            return -1

        results = lines[0]
        try:
            results = results.split()
        except BaseException as e:
            print("ERROR: failed to split up your outputs by spaces due to error: %s" % e)
            return -1

        if len(results) <= 2:
            print("ERROR: expected more than two output test cases!  Even the sample files have 4...")
            return -1

        for word in results:
            if not reg_word_valid(word):
                return -1

    print("non-TLB file looks good... checking TLB file")

    with open(sys.argv[2]) as tlb_out:
        lines = tlb_out.readlines()
        if len(lines) > 1:
            print("ERROR: more than one line present in TLB output file!")
            return -1

        results = lines[0]
        try:
            results = results.split()
        except BaseException as e:
            print("ERROR: failed to split up your outputs by spaces due to error: %s" % e)
            return -1

        if len(results) <= 4:
            print("ERROR: expected more than two output test cases!  Even the sample files have 4...")
            return -1

        if len(results) % 2 == 1:
            print("ERROR: expected an even number of output words in your TLB output file!")
            return -1

        i = 0
        for test_case in results:
            if i % 2 == 0:
                if not tlb_word_valid(test_case):
                    return -1
            else:
                if not reg_word_valid(test_case):
                    return -1
            i += 1

    print("All files parsed properly! This only means we can grade your file:\n"
          "\n*********    PLEASE NOTE     ***************\n"
          "This DOES NOT MEAN your grade will be 100%!!"
          "\n********************************************\n\n\n"
          "You still need to ensure your outputs are correct!"
          "Write lots of test cases and ask questions if you're unsure about something...")

    return 0

if __name__ == "__main__":
    ret = main()
    if ret:
        print("""
    ********************************************************************************
    Expectations:
    1. Each output file should contain a single line only!
    2a. For the non-TLB output file, each address translation should be a single
    "word" (i.e. separated by a single space).  Each such word should be either an
    integer representing the physical address, 'pf' for page fault, or 'err' for error.
    2b. For the TLB output file, each address translation should be TWO words, also
     separated by spaces. The first word should be either 'm' or 'h' for hit/miss
     respectively.  The second word should be identical to the expected output in 2a.

    When in doubt, please see the example output files and follow them exactly!
    ********************************************************************************
    """)
