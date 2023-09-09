#include "Yumi.h"

int main()
{
    YLOG_TRACE("Yumi Engine begin create...\n");

    Yumi::CreateEngine();
    Yumi::GetEngine().StartMainLoop();
    Yumi::DestroyEngine();
}