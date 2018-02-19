#include "c/schemas/ModioEvent.h"

extern "C"
{
  void modioInitEvent(ModioEvent* event, json event_json)
  {
    event->id = 0;
    if(modio::hasKey(event_json, "id"))
      event->id = event_json["id"];

    event->mod_id = 0;
    if(modio::hasKey(event_json, "mod_id"))
      event->mod_id = event_json["mod_id"];

    event->user_id = 0;
    if(modio::hasKey(event_json, "user_id"))
      event->user_id = event_json["user_id"];

    event->event_type = 0;
    if(modio::hasKey(event_json, "event_type"))
    {
      if(event_json["event_type"] == "MODFILE_CHANGED")
        event->event_type = EVENT_MODFILE_CHANGED;
      else if(event_json["event_type"] == "MOD_AVAILABLE")
        event->event_type = EVENT_MOD_AVAILABLE;
      else if(event_json["event_type"] == "MOD_UNAVAILABLE")
        event->event_type = EVENT_MOD_UNAVAILABLE;
      else if(event_json["event_type"] == "MOD_EDITED")
        event->event_type = EVENT_MOD_EDITED;
      else
        event->event_type = EVENT_UNDEFINED;
    }

    event->date_added = 0;
    if(modio::hasKey(event_json, "date_added"))
      event->date_added = event_json["date_added"];
  }

  void modioFreeEvent(ModioEvent* tag)
  {
    //No pointers
  }
}
