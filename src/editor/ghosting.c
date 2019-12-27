// spawn "ghosts" of the objects which are dirty...this appears when the game
// is paused and shows where all the objects will return to when the game
// is run again
void spawn_ghosted_objects(void)
{
int i,o;
	for(i=0;i<MAX_OBJECTS;i++)
	{
		if (saved_objects[i].exists && saved_objects[i].type != OBJ_PLAYER)
		{
			o = spawn_object(saved_objects[i].x, saved_objects[i].y, OBJ_GHOST);
			objects[o].sprite = saved_objects[i].sprite;
		}
	}
}

// sets whether or not to show object "ghosts" when paused
void editor_set_do_ghosting(int newval)
{
int i;
char *ptr;

	options[OPT_GHOSTING] = newval;
	if (objects_dirty)
	{
		if (options[OPT_GHOSTING])
		{
			spawn_ghosted_objects();
		}
		else
		{
			for(i=0;i<MAX_OBJECTS;i++)
			{
				if (objects[i].exists && objects[i].type==OBJ_GHOST)
				{
					delete_object(i);
				}
			}
		}
	}
	
	SaveOptions();
	
	ptr = options[OPT_GHOSTING] ? "GHOST":"     ";
	font_draw(ptr,LASTBUTTON_X-2,LASTBUTTON_Y+BUTTON_H+6+8,drawcharacter_clear_erasebg);
}
