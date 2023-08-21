#include "Yumi.h"

int main()
{
    YLOG_TRACE("Yumi Engine begin create...\n");
    Yumi::Engine::CreateInstance().Start();
    Yumi::Engine::GetInstance().DestroyInstance();
}