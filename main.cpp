#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cstdint>
#include <cstdio>

#define WHITE 0xFFFFFFFF
#define BLACK 0xFF000000

const int height = 800, width = 800;
const int canvas_Height = 60, canvas_Width = 60;

// Khai bao canvas la 1 vector 2 chieu, moi phan tu la 1 mau sac (uint32_t), khoi tao voi mau trang (0xFFFFFFFF)
std::vector<uint32_t> canvas(canvas_Width *canvas_Height, 0xFFFFFFFF);
int x_Point, y_Point;

// ham setPixel de set mau sac cho 1 pixel tren canvas
void setPixel(int x, int y, uint32_t color)
{
    if (x >= 0 && x < canvas_Width && y >= 0 && y < canvas_Height)
    {
        int index = y * canvas_Width + x; // Tinh toan index trong vector 1 chieu
        canvas[index] = color;
    }
}

int main(int argc, char *argv[])
{
    // Khoi tao SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow(
        "SDL Tutorial",          // Title of the window
        SDL_WINDOWPOS_UNDEFINED, // Toa do x
        SDL_WINDOWPOS_UNDEFINED, // Toa do y
        width,                   // Chieu rong cua so
        height,                  // Chieu cao cua so
        SDL_WINDOW_SHOWN         // Flags cua so
    );

    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // Tao renderer de ve len window
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,                  // Window de ve len
        -1,                      // Index cua renderer (su dung -1 de chon renderer mac dinh)
        SDL_RENDERER_ACCELERATED // Su dung acceleration (GPU) de ve nhanh hon
    );

    // Tao texture de ve canvas len window
    SDL_Texture *texture = SDL_CreateTexture(
        renderer,                    // Renderer de ve len
        SDL_PIXELFORMAT_ARGB8888,    // Dinh dang mau sac cua texture (ARGB8888: 8 bit cho moi kenh A, R, G, B)
        SDL_TEXTUREACCESS_STREAMING, // Texture co the duoc cap nhat lien tuc (streaming)
        canvas_Width,                // Chieu rong cua texture (bang chieu rong cua canvas)
        canvas_Height                // Chieu cao cua texture (bang chieu cao cua canvas)
    );

    bool isRunning = true;         // Bien kiem tra xem chuong trinh co dang chay hay khong
    bool isDrawing = false;        // Bien kiem tra xem nguoi dung co dang ve hay khong
    uint32_t currentColor = BLACK; // Mau sac hien tai de ve (mac dinh la den)
    SDL_Event event;               // Bien luu tru event

    // while isRunning = true => run loop
    while (isRunning)
    {
        // while event rong => xu ly event
        while (SDL_PollEvent(&event) != 0)
        {
            // Neu event la quit => thoat chuong trinh
            if (event.type == SDL_QUIT)
            {
                // Thoat chuong trinh
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    currentColor = BLACK; // Chuyen mau sang den khi nhan chuot trai
                }
                else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
                {
                    currentColor = WHITE; // Chuyen mau sang trang khi nhan chuot phai
                }
                isDrawing = true;
                int x_point = event.button.x * canvas_Width / width;   // Chuyen doi toa do x tu window sang canvas
                int y_point = event.button.y * canvas_Height / height; // Chuyen doi toa do y tu window sang canvas
                setPixel(x_point, y_point, currentColor);              // Set mau trang cho pixel tai toa do (x_point, y_point)
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                // Neu event la mouse button up => ket thuc ve
                isDrawing = false;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                // Neu event la mouse motion va isDrawing = true => ve len canvas
                if (isDrawing)
                {
                    x_Point = event.motion.x * canvas_Width / width;   // Chuyen doi toa do x tu window sang canvas
                    y_Point = event.motion.y * canvas_Height / height; // Chuyen doi toa do y tu window sang canvas
                    setPixel(x_Point, y_Point, currentColor);          // Set mau den cho pixel tai toa do (x_Point, y_Point) tren canvas
                }
            }
        }
        SDL_UpdateTexture(
            texture,                        // Texture can cap nhat
            NULL,                           // Rect can cap nhat (NULL de cap nhat toan bo texture)
            canvas.data(),                  // Du lieu can cap nhat (pointer toi du lieu cua canvas)
            canvas_Width * sizeof(uint32_t) // Pitch (so byte moi hang trong texture, bang chieu rong cua canvas nhan voi so byte moi pixel)
        );

        SDL_RenderClear(renderer);                     // Xoa noi dung hien tai tren renderer
        SDL_RenderCopy(renderer, texture, NULL, NULL); // Ve texture len renderer (NULL
        SDL_RenderPresent(renderer);                   // Hien thi noi dung da ve len window

        // Cap nhat texture voi du lieu tu canvas
        SDL_Delay(16); // Delay 16ms ~ 60fps
    }

    // Giai phong SDL
    SDL_DestroyWindow(window);     // Huy window
    SDL_DestroyRenderer(renderer); // Huy renderer
    SDL_DestroyTexture(texture);   // Huy texture
    SDL_Quit();                    // Thoat SDL
    printf("Chuong trinh da ket thuc!\n");

    return 0;
}