#ifndef STORAGE_H___
#define STORAGE_H___

void storage_init(void);
void storage_save(void *value, int size);
void storage_load(void *value, int size);
void storage_clear(void);

#endif // STORAGE_H___
