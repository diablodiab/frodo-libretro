
/*
  libretro-Frodo - dlgSnapshot.c

*/

#include <assert.h>

#include "dialog.h"
#include "sdlgui.h"

#define SNATSHOTDLG_LOAD	2
#define SNATSHOTDLG_SAVE	3
#define SNATSHOTDLG_EXIT	4

/* The floppy disks dialog: */
static SGOBJ snapshotdlg[] =
{
	{ SGBOX, 0, 0, 0,0, 40,6, NULL },
	{ SGTEXT, 0, 0, 3,1, 30,1, "Snapshot Load & Save :" },
	{ SGBUTTON, SG_EXIT/*0*/, 0, 3,4, 10,1,  "Load" },
	{ SGBUTTON, SG_EXIT/*0*/, 0, 15,4, 10,1, "Save" },
	{ SGBUTTON, SG_EXIT/*SG_CANCEL*/, 0, 27,4, 10,1, "Return" },
	{ -1, 0, 0, 0,0, 0,0, NULL }
};

void Dialog_SnapshotDlg(void)
{
	int but, i;
	char *snapfile;

	SDLGui_CenterDlg(snapshotdlg);

	/* Draw and process the dialog */
	do
	{       
		but = SDLGui_DoDialog(snapshotdlg, NULL);

		switch (but)
		{
			case SNATSHOTDLG_LOAD:

				snapfile = SDLGui_FileSelect("dump.sna", NULL, false);

				if (snapfile)
				{	
					if(TheC64->LoadSnapshot(snapfile)){
							printf("loading snapfile (%s)\n",snapfile);
					}
					else 	printf("error loading snapfile (%s)\n",snapfile);

					free(snapfile);
				}

				break;

			case SNATSHOTDLG_SAVE:
			
				snapfile=malloc(512*sizeof(char));

				if(ThePrefs.DrivePath[0]!=NULL){

					sprintf(snapfile,"%s\0",ThePrefs.DrivePath[0]);
					char *pch=strrchr(snapfile, '.');

					if(strlen(pch)>3){
						*(pch+1)='s';
						*(pch+2)='n';
						*(pch+3)='a';
					}
					else sprintf(snapfile,"%s.sna\0","dump");
				}
				else sprintf(snapfile,"%s.sna\0","dump");

				TheC64->SaveSnapshot(snapfile);
				printf("saving snapfile (%s)\n",snapfile);

				free(snapfile);

				break;

		}

        gui_poll_events();

	}
	while (but != SNATSHOTDLG_EXIT && but != SDLGUI_QUIT
	        && but != SDLGUI_ERROR && !bQuitProgram);


}
