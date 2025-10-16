#pragma once

#include "esp_err.h"
#include "esp_log.h"
//#include "system_context.h"   // for loop handles


// 1️⃣  Declare these functions BEFORE the macro.
//     This ensures the compiler already knows them when
//     the macro body refers to them.
// -----------------------------------------------------------

//Redefinition to avoid having esp_event in header

#define EVENT_ADAPTER_DECLARE_BASE(id) extern esp_event_base_t const id
#define EVENT_ADAPTER_DEFINE_BASE(id) esp_event_base_t const id = #id

// Event loop library types
typedef const char*  esp_event_base_t; /**< unique pointer to a subsystem that exposes events */
//typedef void*        esp_event_loop_handle_t; /**< a number that identifies an event with respect to a base */
typedef void (*esp_event_handler_t)(void* event_handler_arg,
                                    esp_event_base_t event_base,
                                    int32_t event_id,
                                    void* event_data); /**< function called when an event is posted to the queue */
//typedef void*        esp_event_handler_instance_t; /**< context identifying an instance of a registered event handler */


esp_err_t event_adapter_post_event(esp_event_base_t base, int32_t id,
                                   const void *data, size_t len);

esp_err_t event_adapter_post_exception(esp_event_base_t base, int32_t id,
                                       const void *data, size_t len);

esp_err_t event_adapter_register_event(esp_event_base_t base, int32_t id,
                                       void *handler_args);

esp_err_t event_adapter_register_exception(esp_event_base_t base, int32_t id,
                                           void *handler_args);



#define DEFINE_EVENT_ADAPTER(prefix)                                            \
    /* Define both event bases */                                               \
    EVENT_ADAPTER_DEFINE_BASE(prefix##_ROUTINE_EVENT_BASE);                         \
    EVENT_ADAPTER_DEFINE_BASE(prefix##_EXCEPTION_EVENT_BASE);                       \
                                                                                \
    static inline esp_err_t prefix##_post_event(int32_t id,                     \
                                                const void *data, size_t len) { \
        return event_adapter_post_event(prefix##_ROUTINE_EVENT_BASE, id, data, len); \
    }                                                                           \
                                                                                \
    static inline esp_err_t prefix##_post_exception(int32_t id,                 \
                                                    const void *data, size_t len) { \
        return event_adapter_post_exception(prefix##_EXCEPTION_EVENT_BASE, id, data, len); \
    }                                                                           \
                                                                                \
    static inline esp_err_t prefix##_register_event(int32_t id,void* handler_args) {               \
        return event_adapter_register_event(prefix##_ROUTINE_EVENT_BASE, id,handler_args);   \
    }                                                                           \
                                                                                \
    static inline esp_err_t prefix##_register_exception(int32_t id,void* handler_args) {           \
        return event_adapter_register_exception(prefix##_EXCEPTION_EVENT_BASE, id, handler_args); \
    }



esp_err_t event_system_adapter_init(esp_event_handler_t s_main_loop_handler,esp_event_handler_t s_exception_loop_handler);