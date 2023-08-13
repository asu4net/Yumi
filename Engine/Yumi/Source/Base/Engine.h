#pragma once

namespace Yumi
{
    class Engine : public Singleton<Engine>
    {
        YUMI_SINGLETON(Engine)

    protected:
        void OnCreateInstance() override;
    };
}