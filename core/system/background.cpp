
#include "background.h"

#ifdef _WIN32

#include <windows.h>
#include <tlhelp32.h>
#include "encode/studio_encode.h"

#endif  // _WIN32

bool studio_background::getAllPrj()
{
#ifdef _WIN32

    // 进程快照句柄
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        std::cout << "Failed to create snapshot!" << std::endl;
        return false;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // 获取第一个进程
    if (!Process32First(hSnapshot, &pe32))
    {
        std::cout << "Failed to get first process!" << std::endl;
        CloseHandle(hSnapshot);
        return false;
    }

    // 循环列出所有进程
    do
    {
        std::string prg;
        studio_char_conv::WcharToChar(pe32.szExeFile, prg);

        name_pid[prg].push_back(pe32.th32ProcessID);
        // std::cout << "Process:" << prg << ", PID: " << pe32.th32ProcessID << std::endl;

    } while (Process32Next(hSnapshot, &pe32));

    // 关闭句柄
    CloseHandle(hSnapshot);

#endif  // _WIN32

    return true;
}

bool studio_background::stopPrj(const std::string& name)
{
#ifdef _WIN32

    if (name_pid.find(name) == name_pid.end())
    {
        std::cout << "Process " << name << " not found!" << std::endl;
        return false;
    }
    for (const auto& pid : name_pid[name])
    {
        // 打开进程，获取进程句柄
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);

        if (hProcess == NULL)
        {
            std::cout << "Failed to open process with PID " << pid << "!" << std::endl;
            return false;
        }

        // 终止进程
        BOOL result = TerminateProcess(hProcess, 0);  // 0 是退出码，表示正常退出

        if (result)
        {
            std::cout << "Process with PID " << pid << " terminated successfully!" << std::endl;
        }
        else
        {
            std::cout << "Failed to terminate process with PID " << pid << "!" << std::endl;
        }

        // 关闭进程句柄
        CloseHandle(hProcess);
    }
#endif  // _WIN32

    return true;
}
