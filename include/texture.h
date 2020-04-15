// texture.h

#ifndef _TEXTURE_H
#define _TEXTURE_H

void* texture_load_from_file(const char* path);

void texture_free(void* texture);

#endif