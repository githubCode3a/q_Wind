#ifndef __SINGLETON_H__
static_assert(0, "Include win32.util/Singleton.h instead!");
#endif

#include <cassert>

template <typename T>
std::mutex Singleton<T>::mutex_;

template <typename T>
std::unique_ptr<typename Singleton<T>::singleton_type> Singleton<T>::instance_;

template <typename T>
template <typename... Args>
typename Singleton<T>::singleton_type* Singleton<T>::getInstance(Args&&... args) {
	if (!instance_) {
		lock_guard guard(mutex_);
		if (!instance_) {
			instance_.reset(new singleton_type(std::forward<Args>(args)...));
		}
	}
	assert(!!instance_);
	return instance_.get();
}

template <typename T>
void Singleton<T>::destroyInstance() {
	lock_guard guard(mutex_);
	instance_.reset();
}