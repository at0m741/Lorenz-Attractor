#include <SDL2/SDL.h>
#include <stdio.h>

double lorenz_sigma = 10.0;
double lorenz_rho = 28.0;
double lorenz_beta = 8.0 / 3.0;

double lorenz_dx(double x, double y, double z) {
    return lorenz_sigma * (y - x);
}

double lorenz_dy(double x, double y, double z) {
    return x * (lorenz_rho - z) - y;
}

double lorenz_dz(double x, double y, double z) {
    return x * y - lorenz_beta * z;
}

void runge_kutta4(double *x, double *y, double *z, double dt) {
    double kx1, kx2, kx3, kx4;
    double ky1, ky2, ky3, ky4;
    double kz1, kz2, kz3, kz4;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            kx1 = dt * lorenz_dx(*x, *y, *z);
            ky1 = dt * lorenz_dy(*x, *y, *z);
            kz1 = dt * lorenz_dz(*x, *y, *z);
        }
        #pragma omp section
        {
            kx2 = dt * lorenz_dx(*x + kx1 / 2, *y + ky1 / 2, *z + kz1 / 2);
            ky2 = dt * lorenz_dy(*x + kx1 / 2, *y + ky1 / 2, *z + kz1 / 2);
            kz2 = dt * lorenz_dz(*x + kx1 / 2, *y + ky1 / 2, *z + kz1 / 2);
        }
        #pragma omp section
        {
            kx3 = dt * lorenz_dx(*x + kx2 / 2, *y + ky2 / 2, *z + kz2 / 2);
            ky3 = dt * lorenz_dy(*x + kx2 / 2, *y + ky2 / 2, *z + kz2 / 2);
            kz3 = dt * lorenz_dz(*x + kx2 / 2, *y + ky2 / 2, *z + kz2 / 2);
        }
        #pragma omp section
        {
            kx4 = dt * lorenz_dx(*x + kx3, *y + ky3, *z + kz3);
            ky4 = dt * lorenz_dy(*x + kx3, *y + ky3, *z + kz3);
            kz4 = dt * lorenz_dz(*x + kx3, *y + ky3, *z + kz3);
        }
    }

    *x += (kx1 + 2 * kx2 + 2 * kx3 + kx4) / 6;
    *y += (ky1 + 2 * ky2 + 2 * ky3 + ky4) / 6;
    *z += (kz1 + 2 * kz2 + 2 * kz3 + kz4) / 6;
}

void rainbowColor(int step, Uint8* r, Uint8* g, Uint8* b) {
    *r = (Uint8)(sin(0.003 * step + 0) * 157 + 128);
    *g = (Uint8)(sin(0.003 * step + 2) * 127 + 128);
    *b = (Uint8)(sin(0.003 * step + 4) * 127 + 128);
}

void positionColor(double x, double y, double z, Uint8* r, Uint8* g, Uint8* b) {
    *r = (Uint8)( 255 * sqrt(x * x) / 50 ), *g = (Uint8)(  255 * sqrt(y * y) / 50 ), *b = (Uint8)( 255 * sqrt(z * z) / 50 );
}

void accelerationColor(double x, double y, double z, Uint8* r, Uint8* g, Uint8* b) {
    static double previous_x = 1.0, previous_y = 1.0, previous_z = 1.0;
    double dist = fmin(1.0, sqrt(((previous_x - x) * (previous_x - x)) + ((previous_y - y) * (previous_y - y)) + ((previous_z - z) * (previous_z - z))) * 50);
    *r = (Uint8)( 255 * (dist) ), *g = (Uint8)(  255 * (1 - dist) ), *b = (Uint8)( 255 * (1 - dist));

    previous_x = x, previous_y = y, previous_z = z;
}

void exit_sdl(SDL_Renderer* renderer, SDL_Window* window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    double x = 1.0, y = 1.0, z = 1.0; 
    double dt = 0.0001;
    int steps = 1000000;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Lorenz Attractor",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1920, 1080, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int i = 0; i < steps; i++) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
               exit_sdl(renderer, window);
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                exit_sdl(renderer, window);
        }
        runge_kutta4(&x, &y, &z, dt);
        Uint8 r, g, b;
        // rainbowColor(steps, &r, &g, &b);
        // positionColor(x, y, z,&r, &g, &b);
        accelerationColor(x, y, z,&r, &g, &b);
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderDrawPoint(renderer, 960 + (int)(x * 15), 740 - (int)(z * 15)); 
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(5000);
    exit_sdl(renderer, window);

    return 0;
}
