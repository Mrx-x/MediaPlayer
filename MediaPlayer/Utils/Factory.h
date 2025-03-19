#ifndef UTILS_FACTORY_H
#define UTILS_FACTORY_H

#include <type_traits>
#include <functional>

namespace Utils
{
    template <typename R, typename... Args>
    class Factory
    {
    private:
        template <typename T> using RequiresInvocable =
            std::enable_if_t<std::is_invocable_r_v<R, std::decay_t<T>, Args...>, std::integral_constant<int, 0>>;
        template <typename T> using RequiresCreateMethod =
            std::enable_if_t<std::is_convertible_v<decltype(std::declval<T>().Create(std::declval<Args>()...)), R>,
                            std::integral_constant<int, 1>>;
        template <typename T> using RequiresCreateMethodViaPointer =
            std::enable_if_t<std::is_convertible_v<decltype(std::declval<T>()->Create(std::declval<Args>()...)), R>,
                            std::integral_constant<int, 2>>;

    public:
        Factory() = default;
        Factory(const Factory&) = default;
        Factory(Factory&&) = default;
        Factory& operator=(const Factory&) = default;
        Factory& operator=(Factory&&) = default;
        template <typename T> Factory(T&& arg, RequiresInvocable<T> = {}) : _function(std::forward<T>(arg)) {}
        template <typename T> Factory(T&& arg, RequiresCreateMethod<T> = {});
        template <typename T> Factory(T&& arg, RequiresCreateMethodViaPointer<T> = {});
        Factory(const std::decay_t<R>& arg) : _function([arg](Args... args) { return arg; }) {}
        Factory(std::decay_t<R>&& arg) : _function([arg=std::move(arg)](Args... args) { return arg; }) {}
    public:
        R Create(Args... args) const { return _function(std::forward<Args>(args)...); }
    public:
        operator bool () const { return _function != nullptr; }
    private:
        std::function<R(Args...)> _function;
    };

    template <typename R, typename... Args>
    template <typename T>
    Factory<R, Args...>::Factory(T&& arg, RequiresCreateMethod<T>)
        : _function([arg=std::forward<T>(arg)](Args... args) { return arg.Create(std::forward<Args>(args)...); })
    {}

    template <typename R, typename... Args>
    template <typename T>
    Factory<R, Args...>::Factory(T&& arg, RequiresCreateMethodViaPointer<T>)
        : _function([arg=std::forward<T>(arg)](Args... args) { return arg->Create(std::forward<Args>(args)...); })
    {}
}

#endif // UTILS_FACTORY_H
