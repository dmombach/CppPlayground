#pragma once
#include <stdexcept>
#include <limits>
#define NOMINMAX // this mprevents Windows from defining 'min' and 'max' macros that break STL code.
#include <Windows.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>

class Exception
{
public:
    void MyFunc(int c)
    {
        if (c > std::numeric_limits<char>::max()) 
        {
            throw std::invalid_argument("MyFunc argument is too large!");
        }
    }
};

std::string FormatErrorMessage(DWORD error, const std::string& msg)
{
    static const int BUFFERLENGTH = 1024;
    std::vector<char> buf(BUFFERLENGTH);
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, error, 0, buf.data(), BUFFERLENGTH - 1, 0);
    
    return std::string(buf.data()) + "    (" + msg + ")";
}

class Win32Exception : public std::runtime_error
{
private:
    DWORD m_error;
public:
    Win32Exception(DWORD error, const std::string& msg)
        : runtime_error(FormatErrorMessage(error, msg)), m_error(error) { }

    DWORD GetErrorCode() const { return m_error; }

    

};

void ThrowLastErrorIf(bool expression, const std::string& msg)
{ 
    if (expression) 
    { 
        throw Win32Exception(GetLastError(), msg); 
    }
}

class File
{
private:
    HANDLE m_handle{INVALID_HANDLE_VALUE};

public:
    File() = default;
    
    // Disable copying explicitly
    File(const File&) = delete;
    File& operator=(const File&) = delete;

    // Allow moving (safe transfer of ownership)
    File(File&& other) noexcept : m_handle(other.m_handle)
    {
        other.m_handle = INVALID_HANDLE_VALUE;
    }
    File& operator=(File&& other) noexcept
    {
        if (this != &other)
        {
            if (m_handle != INVALID_HANDLE_VALUE) CloseHandle(m_handle);
            m_handle = other.m_handle;
            other.m_handle = INVALID_HANDLE_VALUE;
        }
        return *this;
    }

    explicit File(const std::string& filename)
    {
        m_handle = CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, 
            nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, nullptr);
        ThrowLastErrorIf(m_handle == INVALID_HANDLE_VALUE, 
            "CreateFile call failed on file named " + filename);
    }

    ~File() 
    {
        if (m_handle != INVALID_HANDLE_VALUE)
            CloseHandle(m_handle); 
    }

    HANDLE GetHandle() { return m_handle; } 
};

size_t GetFileSizeSafe(const std::string& filename)
{
    File fobj(filename);
    LARGE_INTEGER filesize;

    BOOL result = GetFileSizeEx(fobj.GetHandle(), &filesize);
    ThrowLastErrorIf(result == FALSE, "GetFileSizeEx call failed: " + filename);

    if (static_cast<unsigned long long>(filesize.QuadPart) < std::numeric_limits<size_t>::max())
    {
        return filesize.QuadPart;
    }
    else
    {
        throw;
    }
}

std::vector<char> ReadFileVoctor(const std::string& filename)
{
    File fobj(filename);
    size_t filesize = GetFileSizeSafe(filename);
    DWORD bytesRead = 0;

    std::vector<char> readbuffer(filesize);

    BOOL result = ReadFile(fobj.GetHandle(), readbuffer.data(), readbuffer.size(), &bytesRead, nullptr);
    ThrowLastErrorIf(result == FALSE, "ReadFile failed: " + filename);
        
    std::cout << filename << " file size: " << filesize << ", bytes read: " << bytesRead << std::endl;

    return readbuffer;
}

bool IsFileDiff(const std::string& filename1, const std::string& filename2)
{
    return ReadFileVoctor(filename1) != ReadFileVoctor(filename2);
}


