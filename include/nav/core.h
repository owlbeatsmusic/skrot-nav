#ifndef NAV_CORE_H_
#define NAV_CORE_H_

extern int nav_spaceobjects_index;


extern int nav_core_get_sclk(void);

extern void nav_core_proc_main_tick(void);
extern void nav_core_shutdown(void);
extern int nav_core_create(void);

#endif
