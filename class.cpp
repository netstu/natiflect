//
// Copyright (c) 2016 Richard Chien
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//
// Created by Richard Chien on 7/5/16.
//

#include "class.h"

namespace natiflect {

#pragma mark - Public

    Class::Class(JNIEnv *env, jclass clz) {
        env_ = env;
        clz_ = clz;
    }

    Class::Class(JNIEnv *env, const char *name) {
        env_ = env;
        clz_ = env_->FindClass(name);
        if (env_->ExceptionCheck()) {
            env_->ExceptionClear();
            throw NoSuchClassException(name);
        }
    }

    void Class::Call_V(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        env_->CallStaticVoidMethodV(clz_, method_id, args);
        CheckMethodCallException(name, sig, args);
        va_end(args);
    }

    jboolean Class::Call_Z(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jboolean result = env_->CallStaticBooleanMethodV(clz_, method_id, args);
        CheckMethodCallException(name, sig, args);
        va_end(args);
        return result;
    }

    jbyte Class::Call_B(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jbyte result = env_->CallStaticByteMethodV(clz_, method_id, args);
        CheckMethodCallException(name, sig, args);
        va_end(args);
        return result;
    }

    jchar Class::Call_C(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jchar result = env_->CallStaticCharMethodV(clz_, method_id, args);
        CheckMethodCallException(name, sig, args);
        va_end(args);
        return result;
    }

    jshort Class::Call_S(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jshort result = env_->CallStaticShortMethodV(clz_, method_id, args);
        CheckMethodCallException(name, sig, args);
        va_end(args);
        return result;
    }

    jint Class::Call_I(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jint result = env_->CallStaticIntMethodV(clz_, method_id, args);
        CheckMethodCallException(name, sig, args);
        va_end(args);
        return result;
    }

    jlong Class::Call_J(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jlong result = env_->CallStaticLongMethodV(clz_, method_id, args);
        CheckMethodCallException(name, sig, args);
        va_end(args);
        return result;
    }

    jfloat Class::Call_F(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jfloat result = env_->CallStaticFloatMethodV(clz_, method_id, args);
        CheckMethodCallException(name, sig, args);
        va_end(args);
        return result;
    }

    jdouble Class::Call_D(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jdouble result = env_->CallStaticDoubleMethodV(clz_, method_id, args);
        CheckMethodCallException(name, sig, args);
        va_end(args);
        return result;
    }

    jobject Class::Call_L(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jobject result = env_->CallStaticObjectMethodV(clz_, method_id, args);
        CheckMethodCallException(name, sig, args);
        va_end(args);
        return result;
    }

#pragma mark - Private

    jmethodID Class::GetStaticMethodID(const char *name, const char *sig) {
        jmethodID method_id = env_->GetStaticMethodID(clz_, name, sig);
        if (env_->ExceptionCheck()) {
            env_->ExceptionClear();
            throw NoSuchStaticMethodException(name, sig);
        }
        return method_id;
    }

    void Class::CheckMethodCallException(const char *name, const char *sig, va_list args) {
        if (env_->ExceptionCheck()) {
            env_->ExceptionClear();
            va_end(args);
            throw InvokeException(name, sig);
        }
    }
}
