#pragma once
#include "esp_event.h"
#include "esp_err.h"
#include "esp_log.h"
//#include "system_context.h"   // for loop handles


// 1️⃣  Declare these functions BEFORE the macro.
//     This ensures the compiler already knows them when
//     the macro body refers to them.
// -----------------------------------------------------------

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
    ESP_EVENT_DEFINE_BASE(prefix##_ROUTINE_EVENT_BASE);                         \
    ESP_EVENT_DEFINE_BASE(prefix##_EXCEPTION_EVENT_BASE);                       \
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