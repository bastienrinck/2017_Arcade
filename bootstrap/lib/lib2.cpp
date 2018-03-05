/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by rectoria
*/

#include <stdio.h>

__attribute__((constructor))
static void construct() {
	printf("[lib2] Loading lib2 library...\n");
}

__attribute__((destructor))
static void destruct() {
	printf("[lib2] lib2 closing...\n");
}

extern "C" void entryPoint(void){
	printf("[lib2] Entry point for lib2 !\n");
}