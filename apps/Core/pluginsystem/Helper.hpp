/*
 *
 *  Copyright (c) 2015-2017 Stanislav Zhukov
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#ifndef PLUGINHELPER_HPP
#define	PLUGINHELPER_HPP

template<typename T> struct sizeof_void {enum {value = sizeof (T)};};

template<> struct sizeof_void<void> { enum { value = 0};};

template<typename T, size_t t> struct TypeChar {static_assert(!t, "Unsupported type in variadic type list");};

template<typename T> struct TypeChar<T*, sizeof (void*)> {enum {value = 'p'};};
template<> struct TypeChar<double*, sizeof (double*)> {enum {value = 'd'};};
template<typename T> struct TypeChar<T, sizeof (uint8_t)> {enum {value = std::is_signed<T>::value ? 'q' : 'i'};};
template<typename T> struct TypeChar<T, sizeof (uint16_t)> {enum {value = std::is_signed<T>::value ? 'q' : 'i'};};
template<typename T> struct TypeChar<T, sizeof (uint32_t)> {enum {value = std::is_signed<T>::value ? 'q' : 'i'};};
template<typename T> struct TypeChar<T, sizeof (uint64_t)> {enum { value = std::is_signed<T>::value ? 'w' : 'l'};};
template<> struct TypeChar<double, sizeof (double)> {enum {value = 'f'};};
template<> struct TypeChar<char*, sizeof (char*)> {enum {value = 's'};};
template<> struct TypeChar<const char*, sizeof (const char*)> {enum {value = 's'};};
template<> struct TypeChar<void, sizeof_void<void>::value> {enum { value = 'v'};};

template<const char t> struct ReturnType { static_assert(!t, "Unsupported type in variadic type list"); };
template<> struct ReturnType<'p'> { typedef void* type; };
template<> struct ReturnType<'d'> { typedef double* type; };
template<> struct ReturnType<'q'> { typedef signed int type; };
template<> struct ReturnType<'i'> { typedef unsigned int type; };
template<> struct ReturnType<'w'> { typedef signed long long type; };
template<> struct ReturnType<'l'> { typedef unsigned long long type; };
template<> struct ReturnType<'f'> { typedef double type; };
template<> struct ReturnType<'s'> { typedef const char* type; };
template<> struct ReturnType<'v'> { typedef void type; };

template<typename... Types>
struct TypeString
{
    static constexpr char value[sizeof...(Types) + 1] = {
            TypeChar<Types, sizeof (Types)>::value...
    };
};


template<typename R = void*>
struct SystemInterface
{
#ifdef __WIN32__
    typedef HMODULE lib_t;
#else
    typedef void* lib_t;
#endif

    union
    {
        R result;
#ifdef __WIN32__
        decltype(GetProcAddress(lib_t(), nullptr)) data;
#else
        decltype(dlsym(lib_t(), nullptr)) data;
#endif
    };

    static_assert(sizeof (result) == sizeof (data), "R should have the same size");

    SystemInterface() : data(nullptr) {}

    explicit operator bool() {return data;}

#ifdef __WIN32__
    SystemInterface(lib_t handle, const char* name) : data(GetProcAddress(handle, name)) {}
#else
    SystemInterface(lib_t handle, const char* name) : data(dlsym(handle, name)) {}
#endif
};



template<typename R, typename... Types>
using Function = R(*)(Types...);

template<typename R>
using FunctionEllipsis = R(*)(...);

struct FunctionIdentity
{
    const char* types;
    const char ret;
    const unsigned int numargs;

    constexpr bool matches(const char* types, const unsigned int N = 0) const
    {
        return N < numargs ? this->types[N] == types[N] && matches(types, N + 1) : this->types[N] == types[N];
    }

    template<typename R, typename... Types>
    constexpr FunctionIdentity(Function<R, Types...>) : types(TypeString<Types...>::value), ret(TypeChar<R, sizeof_void<R>::value>::value), numargs(sizeof (TypeString<Types...>::value) - 1)
    {
    }
};

struct FunctionPointer : public FunctionIdentity
{
    Function<void> addr;

    template<typename R, typename... Types>
    constexpr FunctionPointer(Function<R, Types...> _addr) : FunctionIdentity(_addr), addr(reinterpret_cast<Function<void>>(_addr))
    {
    }
};

struct FunctionData
{
    const char* name;
    const FunctionPointer func;

    constexpr FunctionData(const char* _name, const FunctionPointer& _func) : name(_name), func(_func)
    {
    }
};

struct FunctionCallbackData
{
    const char* name;
    const unsigned int index;
    const FunctionIdentity callback;

    template<size_t N = 0>
    constexpr FunctionCallbackData(const char(&name)[N], const FunctionIdentity& _callback) : name(name), index(Utils::hash(name)), callback(_callback)
    {
    }
};


#endif	/* PLUGINHELPER_HPP */

