// texture.h

#ifndef _TEXTURE_H
#define _TEXTURE_H

void* texture_from_image(struct Image* image);

void texture_free(void* texture);

#endif