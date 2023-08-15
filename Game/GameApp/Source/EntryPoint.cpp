#include "Yumi.h"

int main()
{
    printf("Yumi Engine begin create...\n");
    Yumi::Engine::CreateInstance().Start();
    Yumi::Engine::GetInstance().DestroyInstance();
}