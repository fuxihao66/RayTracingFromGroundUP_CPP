// ConsoleApplication5.cpp : Defines the entry point for the console application.
//
#include "World.h"


int main()
{
	World w = World();
	w.prepare_scene();
	w.render_scene();
	w.save_to_file();
    return 0;
}

