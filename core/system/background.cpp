
#include "background.h"

#ifdef _WIN32

#include <windows.h>
#include <tlhelp32.h>
#include "encode/studio_encode.h"

#else  // Linux

#include <dirent.h>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>  // For kill()

#endif  // 头文件

#ifdef _WIN32

bool studio_background::getAllPrj()
{
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
        prj_info temp_info;

        // 使用QueryFullProcessImageName获取完整路径
        TCHAR szProcessPath[MAX_PATH];
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
        if (hProcess != NULL)
        {
            DWORD dwSize = MAX_PATH;
            if (QueryFullProcessImageName(hProcess, 0, szProcessPath, &dwSize))
            {
                std::wstring wPath(szProcessPath);
                std::string prgPath;
                studio_char_conv::WcharToChar(szProcessPath, prgPath);
                temp_info.path = prgPath;
            }
            CloseHandle(hProcess);
        }
        std::string prgName;
        studio_char_conv::WcharToChar(pe32.szExeFile, prgName);
        temp_info.name = prgName;
        temp_info.pid = pe32.th32ProcessID;
        prj_list[prgName].push_back(temp_info);

    } while (Process32Next(hSnapshot, &pe32));

    // 关闭句柄
    CloseHandle(hSnapshot);

    return true;
}

bool studio_background::stopPrj(const std::string& name)
{
    if (prj_list.find(name) == prj_list.end())
    {
        std::cout << "Process " << name << " not found!" << std::endl;
        return false;
    }
    for (const auto& info : prj_list[name])
    {
        // 打开进程，获取进程句柄
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, info.pid);

        if (hProcess == NULL)
        {
            std::cout << "Failed to open process with PID " << info.pid << "!" << std::endl;
            return false;
        }

        // 终止进程
        BOOL result = TerminateProcess(hProcess, 0);  // 0 是退出码，表示正常退出

        if (result)
        {
            std::cout << "Process with PID " << info.pid << " terminated successfully!" << std::endl;
        }
        else
        {
            std::cout << "Failed to terminate process with PID " << info.pid << "!" << std::endl;
        }

        // 关闭进程句柄
        CloseHandle(hProcess);
    }

    return true;
}

#else  // Linux

// 从 /proc/<pid>/cmdline 读取命令行参数
std::string getCmdline(unsigned int pid)
{
    std::ifstream cmdline_file("/proc/" + std::to_string(pid) + "/cmdline");
    if (cmdline_file.is_open())
    {
        std::string cmdline;
        getline(cmdline_file, cmdline, '\0');  // 以 null 字符分隔
        return cmdline;
    }
    return "";
}

// 从 /proc/<pid>/exe 读取可执行文件路径
std::string getExePath(unsigned int pid)
{
    char exe_path[PATH_MAX];
    // readlink函数是Linux系统中用于读取符号链接内容的系统调用
    ssize_t len = readlink(("/proc/" + std::to_string(pid) + "/exe").c_str(), exe_path, sizeof(exe_path) - 1);
    if (len != -1)
    {
        exe_path[len] = '\0';
        return std::string(exe_path);
    }
    return "";
}

bool studio_background::getAllPrj()
{
    DIR* dir = opendir("/proc");
    if (dir == nullptr)
    {
        std::cerr << "Failed to open /proc directory!" << std::endl;
        return false;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_DIR)
        {
            unsigned int pid;
            if (std::stringstream(entry->d_name) >> pid)
            {
                // 检查是否为数字
                prj_info temp_info;
                temp_info.pid = pid;
                temp_info.name = getCmdline(pid);
                temp_info.path = getExePath(pid);
                // temp_info.status = true;  // 根据需要设置状态

                // 将进程信息添加到列表中
                if (!temp_info.name.empty())
                {
                    prj_list[temp_info.name].push_back(temp_info);
                }
            }
        }
    }

    closedir(dir);
    return true;
}

bool studio_background::stopPrj(const std::string& name)
{
    if (prj_list.find(name) == prj_list.end())
    {
        std::cout << "Process " << name << " not found!" << std::endl;
        return false;
    }

    for (const auto& info : prj_list[name])
    {
        pid_t pid = info.pid;

        if (kill(pid, SIGTERM) == 0)
        {
            std::cout << "Sent SIGTERM to process with PID " << pid << "!" << std::endl;
        }
        else
        {
            if (errno == ESRCH)
            {
                std::cout << "Process with PID " << pid << " does not exist!" << std::endl;
            }
            else if (kill(pid, SIGKILL) == 0)
            {
                std::cout << "Sent SIGKILL to process with PID " << pid << "!" << std::endl;
            }
            else
            {
                std::cout << "Failed to terminate process with PID " << pid << "! Error: " << strerror(errno) << std::endl;
                return false;
            }
        }
    }

    return true;
}

#endif