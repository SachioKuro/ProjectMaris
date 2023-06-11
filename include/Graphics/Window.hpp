#pragma once

#include <string>

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual void Create(uint16_t width, uint16_t height, const std::string& title) = 0;
    virtual void Destroy() = 0;

    virtual bool IsOpen() const = 0;
    virtual void Close() = 0;

    virtual void PollEvents() = 0;
    virtual void Display() = 0;

    virtual void Clear() = 0;
    virtual void SetTitle(const std::string& title) = 0;

    virtual void* GetWindowObj() = 0;

    uint16_t GetWidth() const {
        return m_width;
    }
    uint16_t GetHeight() const {
        return m_height;
    }

    bool Resized() {
        bool resized = m_resized;
        m_resized = false;
        return resized;
    }

    void SetResized() {
        m_resized = true;
    }
protected:
    uint16_t m_width;
    uint16_t m_height;
    std::string m_title;
    bool m_resized;
};