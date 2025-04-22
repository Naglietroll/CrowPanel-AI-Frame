#include "ui.h"
#include "display.h"
#include "sd_card.h"

static int current_mode = -1; // -1: Нет режима, 0: Оффлайн, 1: Онлайн

static void offline_btn_event_cb(lv_event_t *e) {
    current_mode = 0;
    lv_label_set_text(lv_obj_get_child(lv_scr_act(), 0), "Mode: Offline (SD)");
    Serial.println("[UI] Offline mode selected");
    sd_display_random_jpg(30000); // Запускаем демонстрацию с интервалом 30 секунд
}

static void online_btn_event_cb(lv_event_t *e) {
    current_mode = 1;
    lv_label_set_text(lv_obj_get_child(lv_scr_act(), 0), "Mode: Online (Grok)");
    Serial.println("[UI] Online mode selected");
}

void ui_init() {
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Select Mode");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
    Serial.println("[UI] Label created");

    lv_obj_t *btn_offline = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn_offline, 300, 100);
    lv_obj_align(btn_offline, LV_ALIGN_CENTER, 0, -50);
    lv_obj_add_event_cb(btn_offline, offline_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label_offline = lv_label_create(btn_offline);
    lv_label_set_text(label_offline, "Offline: SD");
    lv_obj_center(label_offline);
    Serial.println("[UI] Offline button created");

    lv_obj_t *btn_online = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn_online, 300, 100);
    lv_obj_align(btn_online, LV_ALIGN_CENTER, 0, 50);
    lv_obj_add_event_cb(btn_online, online_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label_online = lv_label_create(btn_online);
    lv_label_set_text(label_online, "Online: Grok");
    lv_obj_center(label_online);
    Serial.println("[UI] Online button created");

    lv_scr_load(lv_scr_act()); // Принудительное обновление экрана
}

int get_current_mode() {
    return current_mode;
}