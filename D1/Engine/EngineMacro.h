#pragma once

// Singleton
#define DECLARE_SINGLETON(ClassName)                 \
public:                                              \
    static ClassName& Get()                          \
    {                                                \
        static ClassName instance;                   \
        return instance;                             \
    }                                                \
private:                                             \
    ClassName() = default;                           \
    ~ClassName() = default;                          \
    ClassName(const ClassName&) = delete;            \
    ClassName& operator=(const ClassName&) = delete; \
    ClassName(ClassName&&) = delete;                 \
    ClassName& operator=(ClassName&&) = delete;

// Reference Macro
#define MAKE_SHARED_REF(ClassName)                  \
using ClassName##Ref = SharedPtr<class ClassName>

