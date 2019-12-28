#include <windows.h>
#include "Globals.h"

#include "network/test.h"
#include "restapi/test.h"
#include "jsnparse/test.h"


/* Global instance handle */
HINSTANCE g_hInstance = NULL;

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

    BOOL result = FALSE;
    OutputDebugString("Test Started\n");

    result = test_network();

    if(result){
        OutputDebugString("Test Network passed\n");
    } else {
        OutputDebugString("Test Network failed\n");
    }

    result = test_restapi();

    if(result){
        OutputDebugString("Test RestAPI passed\n");
    } else {
        OutputDebugString("Test RestAPI failed\n");
    }

    result = test_jsnparse();

    if(result){
        OutputDebugString("Test JSNParse passed\n");
    } else {
        OutputDebugString("Test JSNParse failed\n");
    }


    OutputDebugString("Test Ended\n");
    return 0;
}
