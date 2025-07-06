import ctypes
import os

import pygame

# ==== Setup ====
base_dir = os.path.dirname(os.path.abspath(__file__))
dll_path = os.path.join(base_dir, "GameOfLife.dll")

gol = ctypes.CDLL(dll_path)


gol.GameOfLife_create.argtypes = [ctypes.c_int, ctypes.c_int]
gol.GameOfLife_create.restype = ctypes.c_void_p

gol.GameOfLife_destroy.argtypes = [ctypes.c_void_p]

gol.GameOfLife_setCell.argtypes = [
    ctypes.c_void_p,
    ctypes.c_int,
    ctypes.c_int,
    ctypes.c_bool,
]
gol.GameOfLife_getCell.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
gol.GameOfLife_getCell.restype = ctypes.c_bool

gol.GameOfLife_step.argtypes = [ctypes.c_void_p]

gol.GameOfLife_getBoard.argtypes = [ctypes.c_void_p]
gol.GameOfLife_getBoard.restype = ctypes.POINTER(ctypes.c_uint8)

gol.GameOfLife_getBoardSize.argtypes = [ctypes.c_void_p]
gol.GameOfLife_getBoardSize.restype = ctypes.c_int

# ==== Config ====
width, height = 30, 30
cell_size = 20
window_width = width * cell_size
window_height = height * cell_size
handle = gol.GameOfLife_create(height, width)

pygame.init()
screen = pygame.display.set_mode((window_width, window_height))
clock = pygame.time.Clock()

running = True
paused = True

# ==== Main Loop ====
while running:
    screen.fill((0, 0, 0))  # Czarny background

    # Events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif event.type == pygame.MOUSEBUTTONDOWN:
            x, y = pygame.mouse.get_pos()
            grid_x = x // cell_size
            grid_y = y // cell_size

            old_state = gol.GameOfLife_getCell(handle, grid_x, grid_y)
            gol.GameOfLife_setCell(handle, grid_x, grid_y, not old_state)

        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                paused = not paused

    # Update
    if not paused:
        gol.GameOfLife_step(handle)

    # Draw
    stateAll = gol.GameOfLife_getBoard(handle)
    for y in range(height):
        for x in range(width):
            state = stateAll[y * width + x]
            color = (255, 255, 255) if state else (30, 30, 30)
            rect = pygame.Rect(
                x * cell_size, y * cell_size, cell_size - 1, cell_size - 1
            )
            pygame.draw.rect(screen, color, rect)

    pygame.display.flip()
    clock.tick(10)

# Cleanup
gol.GameOfLife_destroy(handle)
pygame.quit()
