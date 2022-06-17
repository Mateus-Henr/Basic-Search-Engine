cmake_minimum_required(VERSION 3.21)
project(TP1-AEDS2 C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(TP1-AEDS2 src/main.c src/file/file.c src/linkedlist/linkedlist.c src/pairlinkedlist/pairlinkedlist.c src/hashtable/hashtable.c src/linkedlist/node.c src/pairlinkedlist/pairnode.c src/tfidf/tfidf.c src/tfidf/tfidf.h)
