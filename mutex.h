

#include <pthread.h>
#include <string.h>

namespace compat {

class mutex {
 public:
  typedef pthread_mutex_t native_handle_type;
  mutex();
  ~mutex();

  void lock();
  bool try_lock();
  void unlock();
  
  native_handle_type native_handle() const;

 private:
  native_handle_type native_handle_;

};



mutex::mutex() {
    int err = pthread_mutex_init(&native_handle_, NULL);
    if (err != 0) {
        throw std::runtime_error(strerror(err));
    }
}

mutex::~mutex() {
    pthread_mutex_destroy(&native_handle_);
}

void mutex::lock() {
    int err = pthread_mutex_lock(&native_handle_);
    if (err != 0) {
        throw std::runtime_error(strerror(err));
    }
}

bool mutex::try_lock() {
    int err = pthread_mutex_trylock(&native_handle_);
    if (err == 0) {
        return true;
    } else if (err == EBUSY) {
        return false;
    } else {
        throw std::runtime_error(strerror(err));
    }
}

void mutex::unlock() {
    int err = pthread_mutex_unlock(&native_handle_);
    if (err != 0) {
        throw std::runtime_error(strerror(err));
    }
}

mutex::native_handle_type mutex::native_handle() const {
    return native_handle_;
}


    
}  // namespace compat
