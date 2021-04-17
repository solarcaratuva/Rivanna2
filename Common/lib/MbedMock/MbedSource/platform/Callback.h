// Adapted from Mbed source

#ifndef MBED_CALLBACK_H
#define MBED_CALLBACK_H

// #include <cstring>
// #include <mstd_cstddef>
// #include <stdint.h>
// #include <mstd_new>
// #include "platform/mbed_assert.h"
// #include "platform/mbed_toolchain.h"
// #include <mstd_type_traits>
// #include <mstd_functional>
#include <utility>

// Controlling switches from config:
// MBED_CONF_PLATFORM_CALLBACK_NONTRIVIAL - support storing non-trivial function objects
// MBED_CONF_PLATFORM_CALLBACK_COMPARABLE - support memcmp comparing stored objects (requires zero padding)

namespace mbed {
/** \addtogroup platform-public-api */
/** @{*/
/**
 * \defgroup platform_Callback Callback class
 * @{
 */

/** Callback class based on template specialization
 *
 * @note Synchronization level: Not protected
 */
template <typename Signature>
class Callback;

/** Callback class based on template specialization
 *
 * @note Synchronization level: Not protected
 */
template <typename R, typename... ArgTs>
class Callback<R(ArgTs...)> {
public:
    using result_type = R;

    /** Create an empty Callback
     */
    Callback() noexcept { }

    /** Create an empty Callback
     */
    Callback(std::nullptr_t) noexcept : Callback() { }

    Callback(const Callback &other) = default;
    Callback(Callback &&other) = default;

    /** Create a Callback with a member function
     *  @param obj      Pointer to object to invoke member function on
     *  @param method   Member function to attach
     */
    template<typename Obj, typename Method>
    Callback(Obj obj, Method method) { }

    // *INDENT-OFF*
    /** Create a Callback with a function object
     *  @param f Function object to attach
     *  @note The function object is limited to a a few words of storage
     */
    template <typename F>
    Callback(F f) { }

    /** Destroy a callback
     */
    ~Callback() = default;

    Callback &operator=(const Callback &that) = default;
    Callback &operator=(Callback &&that) = default;

    /** Assign a callback
     */
    // C++ std::function lacks the is_same restriction here, which would mean non-const lvalue references hit this,
    // rather than the normal copy assignment (`F &&` is a better match for `Callback &` than `const Callback &`).
    // Wouldn't matter if both used the swap form, but having cut it down, for code size want to ensure we don't use this
    // instead of copy assignment. (If nontrivial disabled, definitely want to use the default copy assignment, and
    // if nontrivial enabled, we know this doesn't handle self-assignment).
    // *INDENT-OFF*
    template <typename F>
    Callback &operator=(F &&f)
    {
        // C++ standard says to use swap, but that's overkill with no exceptions
        // Callback(std::forward<F>(that)).swap(*this);
        this->~Callback();
        new (this) Callback(std::forward<F>(f));
        return *this;
    }
    // *INDENT-ON*

    template <typename F>
    Callback &operator=(std::reference_wrapper<F> f) noexcept
    {
        // C++ standard says to use swap, but that's overkill with no exceptions
        // Callback(f).swap(*this);
        this->~Callback();
        new (this) Callback(f);
        return *this;
    }

    /** Empty a callback
     */
    Callback &operator=(std::nullptr_t) noexcept
    {
        // destroy();
        // clear();

        return *this;
    }

    /** Test if function has been assigned
     */
    explicit operator bool() const noexcept
    {
        // return control();
        return false;
    }

    /** Test for emptiness
     */
    friend bool operator==(const Callback &f, std::nullptr_t) noexcept
    {
        return !f;
    }

    /** Test for emptiness
     */
    friend bool operator==(std::nullptr_t, const Callback &f) noexcept
    {
        return !f;
    }

    /** Test for non-emptiness
     */
    friend bool operator!=(const Callback &f, std::nullptr_t) noexcept
    {
        return bool(f);
    }

    /** Test for non-emptiness
     */
    friend bool operator!=(std::nullptr_t, const Callback &f) noexcept
    {
        return bool(f);
    }
};

/** Create a callback class with type inferred from the arguments
 *
 *  @param func     Static function to attach
 *  @return         Callback with inferred type
 */
template <typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(R(*func)(ArgTs...) = nullptr) noexcept
{
    return Callback<R(ArgTs...)>(func);
}

/** Create a callback class with type inferred from the arguments
 *
 *  @param func     Static function to attach
 *  @return         Callback with inferred type
 */
template <typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(const Callback<R(ArgTs...)> &func)
{
    return Callback<R(ArgTs...)>(func);
}

/** Create a callback class with type inferred from the arguments
 *
 *  @param func     Static function to attach
 *  @return         Callback with inferred type
 */
template <typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(Callback<R(ArgTs...)> &&func) noexcept
{
    return Callback<R(ArgTs...)>(std::move(func));
}

/** Create a callback class with type inferred from the arguments
 *
 *  @param obj      Optional pointer to object to bind to function
 *  @param method   Member function to attach
 *  @return         Callback with inferred type
 */
template<typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(U *obj, R(T::*method)(ArgTs...)) noexcept
{
    return Callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(U *obj, R(T::*method)(ArgTs...) &) noexcept
{
    return Callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(const U *obj, R(T::*method)(ArgTs...) const) noexcept
{
    return Callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(const U *obj, R(T::*method)(ArgTs...) const &) noexcept
{
    return Callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(volatile U *obj, R(T::*method)(ArgTs...) volatile) noexcept
{
    return Callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(volatile U *obj, R(T::*method)(ArgTs...) volatile &) noexcept
{
    return Callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(const volatile U *obj, R(T::*method)(ArgTs...) const volatile) noexcept
{
    return Callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(const volatile U *obj, R(T::*method)(ArgTs...) const volatile &) noexcept
{
    return Callback<R(ArgTs...)>(obj, method);
}

/** Create a callback class with type inferred from the arguments
 *
 *  @param func     Static function to attach
 *  @param arg      Pointer argument to function
 *  @return         Callback with inferred type
 */
template <typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(R(*func)(T *, ArgTs...), U *arg) noexcept
{
    return Callback<R(ArgTs...)>(func, arg);
}

template <typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(R(*func)(const T *, ArgTs...), const U *arg) noexcept
{
    return Callback<R(ArgTs...)>(func, arg);
}

template <typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(R(*func)(volatile T *, ArgTs...), volatile U *arg) noexcept
{
    return Callback<R(ArgTs...)>(func, arg);
}

template <typename T, typename U, typename R, typename... ArgTs>
Callback<R(ArgTs...)> callback(R(*func)(const volatile T *, ArgTs...), const volatile U *arg) noexcept
{
    return Callback<R(ArgTs...)>(func, arg);
}

/** Create a Create a callback class with type inferred from the arguments
 *  @param f Function object to attach
 *  @note The function object is limited to a single word of storage
 */
// template <typename F>
// Callback<detail::unqualify_fn_t<detail::member_type_t<decltype(&mstd::remove_cvref_t<F>::operator())>>>
// callback(F &&f)
// {
//     return Callback<detail::unqualify_fn_t<detail::member_type_t<decltype(&mstd::remove_cvref_t<F>::operator())>>>(std::forward<F>(f));
// }

/**@}*/

/**@}*/

} // namespace mbed

#endif
