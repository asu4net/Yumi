#include "Asset.h"

namespace Yumi
{
    Asset::Asset(const std::string& name, const std::string& path, const Id& id)
        : m_Name(name)
        , m_Path(path.empty() ? "None" : path)
        , m_AbsolutePath(path.empty() ? "None" : GetWorkingDirectory() + "\\" + path)
        , m_Id(id)
    {
    }
}