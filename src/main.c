#include <stdbool.h>

#include "logger.h"
#include "scene_manager/sorting_scene.h"

int main(void)
{
    bool error         = false;
    struct sorting_scene scene;

    error = sscene_init(&scene);
    if (error)
    {
        LOGG_FAILURE("sscene_init");
        sscene_deinit(&scene);
        return 1;
    }

    sscene_exist(&scene);
    sscene_deinit(&scene);

    return 0;
}
