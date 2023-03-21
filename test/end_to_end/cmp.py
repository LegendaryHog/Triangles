#! /usr/bin/env python3

import sys, os

# path to build          - 1 arg
# name of file with test - after first arg

run_file  = sys.argv[1]
number_of_tests = len(sys.argv) - 2

def take_list_from_file(name_of_file):
    f = open(name_of_file, "r")
    answer = list(map(int, f.read().split()))
    return answer

def take_run_answer(ind):
    os.system("./" + run_file + " < " + sys.argv[ind + 2] + "_task > out")
    run_answ = take_list_from_file("out")
    os.system("rm out")
    return run_answ

def compare_answers(test_answ, run_answ, ind):
    test_answ.sort()
    run_answ.sort()
    if test_answ != run_answ:
        print(str(ind) + ": Error:")
        print("\ttest answer:" + str(test_answ))
        print("\trun answer: " + str(run_answ))
    else:
        print(str(ind) + ": Success")

def main():
    i = 0
    while i != number_of_tests:
        test_answ = take_list_from_file(sys.argv[i + 2] + "_answ")
        run_answ  = take_run_answer(i)
        compare_answers(test_answ, run_answ, i)
        i+=1

main()
        