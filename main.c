/*
 * PSP Homebrew - HTTP File Downloader
 *
 * Connects to the network using a saved PSP Wi-Fi profile, then downloads
 * a file over HTTP using sceHttp, saving it to ms0:/ (memory stick).
 *
 * Build with PSPSDK (see Makefile / README for instructions).
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <psphttp.h>
#include <pspsdk.h>
#include <kubridge.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "downloader.h"

PSP_MODULE_INFO("sixsixone_ofw_dldr", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);
PSP_HEAP_SIZE_KB(1024);

#define printf pspDebugScreenPrintf

/* ---- config: edit these for your target file ---- */
#define DOWNLOAD_URL      "http://du01.psp.update.playstation.org/update/psp/image/us/2014_1212_6be8878f475ac5b1a499b95ab2f7d301/EBOOT.PBP"
#define DOWNLOAD_URL_GO   "http://du01.psp.update.playstation.org/update/psp/image2/us/2014_1212_fd0f7d0798b4f6e6d32ef95836740527/EBOOT.PBP"
#define OUTPUT_PATH       "ms0:/661.PBP"
#define OUTPUT_PATH_GO    "ms0:/661GO.PBP"
#define OUTPUT_PATH_GO    "ms0:/661GO.PBP"
/* -------------------------------------------------- */

static int psp_model = -1;

int exit_callback(int arg1, int arg2, void *common)
{
    sceKernelExitGame();
    return 0;
}

int callback_thread(SceSize args, void *argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int setup_callbacks(void)
{
    int thid = sceKernelCreateThread("update_thread", callback_thread,
                                      0x11, 0xFA0, 0, 0);
    if (thid >= 0)
        sceKernelStartThread(thid, 0, 0);
    return thid;
}

int main(int argc, char *argv[])
{
    pspDebugScreenInit();
    setup_callbacks();

    psp_model = kuKernelGetModel();

    #ifdef DEBUG
    printf("PSP HTTP Downloader\n");
    printf("===================\n\n");
    #endif

    #ifdef DEBUG
    printf("\nDownloading:\n  %s\n->%s\n\n",
           (psp_model == 4) ? DOWNLOAD_URL_GO : DOWNLOAD_URL,
           (psp_model == 4) ? OUTPUT_PATH_GO : OUTPUT_PATH);
    #endif

	int r = download_file((psp_model == 4) ? DOWNLOAD_URL_GO : DOWNLOAD_URL,
                           (psp_model == 4) ? OUTPUT_PATH_GO : OUTPUT_PATH);
    if (r < 0) {
        #ifdef DEBUG
        printf("\nDownload failed (0x%08X).\n", r);
        #endif
    } else {
        #ifdef DEBUG
        printf("\nSuccess!\n");
        #endif
    }

    printf("\nPress HOME to exit.\n");
    sceKernelSleepThread();
    return 0;
}

