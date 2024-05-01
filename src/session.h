#ifndef _CTT_SESSION_
#define _CTT_SESSION_

#include "session_lock.h"
#include "time.h"

#include <stdio.h>

#define ERR_CREATING_SESSION -1
#define SESSION_RETRIEVED 0
#define SESSION_INITIALIZED 1

typedef int sessionresp_t;

struct session {
  struct lock lock;
};

sessionresp_t get_or_init_session(struct session *session);

void session_report(struct session *session);
int complete_session(struct session *session);

#endif
