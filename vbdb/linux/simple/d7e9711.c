#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

//static pthread_mutex_t i_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutexattr_t i_lock_attr;
pthread_mutex_t i_lock;

int inode_get_rsv_space(void)
{
  assert(pthread_mutex_lock(&i_lock)==0);// (4) ERROR
  // do something
  pthread_mutex_unlock(&i_lock);
  return 0;
}

void add_dquot_ref(void)
{
  pthread_mutexattr_init(&i_lock_attr);
  pthread_mutexattr_settype(&i_lock_attr,2);//PTHREAD_MUTEX_ERRORCHECK);
  pthread_mutex_init(&i_lock, &i_lock_attr);
  
#ifdef CONFIG_QUOTA_DEBUG
  int reserved = 0;
#endif

  int i, j;
  for (i=0; i<10; i++) {
    pthread_mutex_lock(&i_lock); // (2) lock is acquired
    //    if (rand() % 2) { // evaluates to false
    //pthread_mutex_unlock(&i_lock);
    //continue;
    //}

#ifdef CONFIG_QUOTA_DEBUG
    if (inode_get_rsv_space() > 0) // (3)
      reserved = 1;
#endif

    pthread_mutex_unlock(&i_lock);
  }
}

int main(int argc, char** arv) {
  add_dquot_ref(); // (1)
  return 0;
}
