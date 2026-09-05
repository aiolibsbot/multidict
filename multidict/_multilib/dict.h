#ifndef _MULTIDICT_C_H
#define _MULTIDICT_C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "htkeys.h"
#include "pythoncapi_compat.h"
#include "state.h"

#if PY_VERSION_HEX >= 0x030c00f0
#define MANAGED_WEAKREFS
#endif

typedef struct {
    PyObject_HEAD
#ifndef MANAGED_WEAKREFS
    PyObject* weaklist;
#endif
    mod_state* state;
    Py_ssize_t used;

    uint64_t version;
    bool is_ci;

    htkeys_t* keys;
} MultiDictObject;

typedef struct {
    PyObject_HEAD
#ifndef MANAGED_WEAKREFS
    PyObject* weaklist;
#endif
    MultiDictObject* md;
} MultiDictProxyObject;

static inline PyObject*
multidict_forbidden_new(PyTypeObject* type, PyObject* args, PyObject* kwargs)
{
    PyErr_Format(PyExc_TypeError,
                 "cannot create '%s' instances directly",
                 type->tp_name);
    return NULL;
}

#ifdef __cplusplus
}
#endif

#endif
