
#ifndef STUDIO_SINGLETON_H
#define STUDIO_SINGLETON_H

#include <iostream>

template <typename T>
class studio_singleton
{
  public:
    static T& sample()
    {
        static T sample;
        return sample;
    }

    // 删除声明的实例不能被复制或移动构造，也不能被赋值，从而保证了单例模式的特性：全局唯一性
    studio_singleton(T&&) = delete; // 删除移动构造函数
    studio_singleton(const T&) = delete;  // 删除拷贝构造函数
    void operator=(const T&) = delete;    // 删除赋值操作符重载

  protected:
    studio_singleton() = default;
    virtual ~studio_singleton() = default;
};



#endif // STUDIO_SINGLETON_H
