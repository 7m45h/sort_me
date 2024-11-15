#pragma once

#include "sorting_scene.h"

bool sscene_handle_events(struct sorting_scene* sscene);
void sscene_update_screen(struct sorting_scene* sscene);
void sscene_alighn_items(struct sorting_scene* sscene);
bool sscene_set_current_algo(struct sorting_scene* sscene, enum SORTING_ALGO algo);
