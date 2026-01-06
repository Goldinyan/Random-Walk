#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xFFFFFF
#define SCALE 10
#define AGENT_SIZE 2

typedef struct {
  int vx, vy;
} velocity_t;

typedef struct {
  int x, y;
  velocity_t v;
  Uint32 color;
} agent_t;

void get_rand_v(velocity_t *v) {
  for (;;) { // infinite loop
    int choice = rand() % 4;

    switch (choice) {
    case 0: // UP
      if (v->vy != 1) {
        v->vx = 0;
        v->vy = -1;
        return;
      }
      break;

    case 1: // DOWN
      if (v->vy != -1) {
        v->vx = 0;
        v->vy = 1;
        return;
      }
      break;

    case 2: // LEFT
      if (v->vx != 1) {
        v->vx = -1;
        v->vy = 0;
        return;
      }
      break;

    case 3: // RIGHT
      if (v->vx != -1) {
        v->vx = 1;
        v->vy = 0;
        return;
      }
      break;
    }
  }
}

void move_agent(SDL_Surface *p_surface, agent_t *p_agent) {
  get_rand_v(&p_agent->v);

  for (size_t i = 0; i < SCALE; i++) {
    p_agent->x += p_agent->v.vx;
    p_agent->y += p_agent->v.vy;

    SDL_Rect rect = (SDL_Rect){p_agent->x, p_agent->y, AGENT_SIZE, AGENT_SIZE};

    // Performance trade off, but idc anymore
    SDL_FillRect(p_surface, &rect, p_agent->color);
  }
}

int main(int argc, const char *argv[]) {

  int num_agents = 5;
  if (argc == 2)
    num_agents = atoi(argv[1]);
  else if (argc > 2) {
    printf("Usage: %s <num_of_agents>\n", argv[0]);
    return -1;
  }

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Window *p_window =
      SDL_CreateWindow("Random-Walk", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  if (!p_window) {
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Surface *p_surface = SDL_GetWindowSurface(p_window);

  agent_t *p_agents = calloc(num_agents, sizeof(agent_t));
  for (int i = 0; i < num_agents; i++) {
    p_agents[i].x = WIDTH / 2;
    p_agents[i].y = HEIGHT / 2;
    p_agents[i].v = (velocity_t){0, 0};
    p_agents[i].color = rand() & 0xFFFFFF;
  }

  int running = 1;

  srand(time(NULL)); // have to seed a random number, and time is pretty random

  while (running) {

    SDL_Event e;

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        running = 0;
    }
    for (int i = 0; i < num_agents; i++) {
      move_agent(p_surface, &p_agents[i]);
    }

    SDL_UpdateWindowSurface(p_window);

    SDL_Delay(20); // 50 fps
  }

  SDL_DestroyWindow(p_window);
  SDL_Quit();
  return 0;
}
