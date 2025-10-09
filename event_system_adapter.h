#pragma once
#include "esp_event.h"
#include "esp_err.h"
#include "esp_log.h"
//#include "system_context.h"   // for loop handles

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
    static inline esp_err_t prefix##_register_event(int32_t id) {               \
        return event_adapter_register_event(prefix##_ROUTINE_EVENT_BASE, id);   \
    }                                                                           \
                                                                                \
    static inline esp_err_t prefix##_register_exception(int32_t id) {           \
        return event_adapter_register_exception(prefix##_EXCEPTION_EVENT_BASE, id); \
    }





esp_err_t event_system_adapter_init(esp_event_loop_handle_t main_loop,esp_event_loop_handle_t exception_loop,esp_event_handler_t s_main_loop_handler,esp_event_handler_t s_exception_loop_handler);