// hud.c

#include "render.h"
#include "hud.h"

void hud_render() {
  render_text(10, 10, 0.5f, "HP: 5/5");
}