/* SPDX-License-Identifier: MIT OR X11
 *
 * Copyright © 2024 Enrico Weigelt, metux IT consult <info@metux.net>
 */
#include <dix-config.h>

#include "dix/callback_priv.h"
#include "dix/dix_priv.h"
#include "dix/gc_priv.h"
#include "include/screenint.h"
#include "include/scrnintstr.h"

void dixFreeScreen(ScreenPtr pScreen)
{
    if (!pScreen)
        return;

    FreeGCperDepth(pScreen);
    dixDestroyPixmap(pScreen->defaultStipple, 0);
    dixFreeScreenSpecificPrivates(pScreen);
    dixScreenRaiseClose(pScreen);
    dixFreePrivates(pScreen->devPrivates, PRIVATE_SCREEN);
    DeleteCallbackList(&pScreen->hookWindowDestroy);
    DeleteCallbackList(&pScreen->hookWindowPosition);
    DeleteCallbackList(&pScreen->hookClose);
    DeleteCallbackList(&pScreen->hookPostClose);
    DeleteCallbackList(&pScreen->hookPixmapDestroy);
    free(pScreen);
}
