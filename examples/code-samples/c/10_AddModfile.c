#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool wait = true;

void onAddModfile(u32 response_code, u32 mod_id)
{
  printf("Add modfile response: %i\n", response_code);
  if (response_code == 201)
  {
    printf("Modfile added!\n");
  }
  wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, false, true, "e91c01b8882f4affeddd56c96111977b", NULL);

  if (!modioIsLoggedIn())
  {
    printf("You are not logged in, please login before creating a mod.\n");
    return 0;
  }

  // You need to know the mod_id beforehand so you can attach a modfile to it
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  // The Modfile Creator helps us setting up the modfile fields and the mod directory that will be zipped and uploaded
  ModioModfileCreator modfile_creator;
  modioInitModfileCreator(&modfile_creator);
  // The path for the modfile can be either a zip file or a folder that will zipped and uploaded on the background
  modioSetModfileCreatorPath(&modfile_creator, "../ModExample/modfile/");
  //modioSetModfileCreatorPath(&modfile_creator, "../ModExample/modfile.zip");
  modioSetModfileCreatorVersion(&modfile_creator, "v1.1.0");
  modioSetModfileCreatorChangelog(&modfile_creator, "This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog");
  modioSetModfileCreatorMetadataBlob(&modfile_creator, "This metadata field was added via the SDK examples.");
  modioSetModfileCreatorActive(&modfile_creator, true);

  // Just like the download listener, we can register a function to be called every time a mod us uploaded
  modioSetUploadListener(&onAddModfile);

  // To start the modfile upload, we provide the mod id and the modfile creator object
  modioAddModfile(mod_id, modfile_creator);
  modioFreeModfileCreator(&modfile_creator);

  while (wait)
  {
    // While a mod is being uploaded, we can track it's progress by using the mod upload queue related functions
    u32 queue_size = modioGetModfileUploadQueueCount();
    if (queue_size != 0)
    {
      // The upload queue contains all the information about the current uploads
			ModioQueuedModfileUpload *upload_queue = malloc(queue_size * sizeof *upload_queue);
      modioGetModfileUploadQueue(upload_queue);

      printf("\n");
      printf("Upload queue:\n");
      printf("===============\n");

      for (u32 i = 0; i < queue_size; i++)
      {
        ModioQueuedModfileUpload *queued_mod_upload = &(upload_queue[i]);
        printf("Id: %d\n", queued_mod_upload->mod_id);
        double current_progress = queued_mod_upload->current_progress;
        double total_size = queued_mod_upload->total_size;
        printf("Upload progress: %f%%\n", (current_progress / total_size) * 100.0);
        printf("\n");
      }
      free(upload_queue);
    }

    modioProcess();
    modioSleep(10);
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
