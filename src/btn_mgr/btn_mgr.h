#ifndef BTN_MGR_H
#define BTN_MGR_H

void btn_mgr_thread(void *arg);

/* Configure the button pin as input and enable its GPIO clock. */
void btn_mgr_init(void);

/* Returns 1 if button is pressed, 0 otherwise. */
int btn_mgr_is_pressed(void);

#endif /* BTN_MGR_H */