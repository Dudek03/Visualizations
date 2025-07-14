import ctypes
import math
import os
from ctypes import POINTER, byref, c_double, c_int

import pygame


# ===== DLL Setup =====
class Mass(ctypes.Structure):
    _fields_ = [("x", ctypes.c_int), ("y", ctypes.c_int), ("mass", ctypes.c_double)]


base_dir = os.path.dirname(os.path.abspath(__file__))
dll_path = os.path.join(base_dir, "Gravity.dll")
Gravity = ctypes.CDLL(dll_path)

# Zarejestruj sygnatury funkcji
Gravity.addMass.argtypes = [c_int, c_int, c_double]
Gravity.addMass.restype = None

Gravity.clearMasses.argtypes = []
Gravity.clearMasses.restype = None

Gravity.vectorDir.argtypes = [c_int, c_int, POINTER(c_double), POINTER(c_double)]
Gravity.vectorDir.restype = None

Gravity.removeMass.argtypes = [c_int, c_int]
Gravity.removeMass.restype = None

Gravity.getMasses.argtypes = None
Gravity.getMasses.restype = ctypes.POINTER(Mass)

Gravity.getMassesCount.argtypes = None
Gravity.getMassesCount.restype = c_int

# ===== Pygame Setup =====
WIDTH, HEIGHT = 800, 600
GRID_SPACING = 40
ARROW_SCALE = 200  # zwiększ/zmniejsz długość strzałek
MAX_ARROW_LENGTH = 30

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Pole grawitacyjne")
clock = pygame.time.Clock()


def color_from_magnitude(vx, vy):
    magnitude = (vx**2 + vy**2) ** 0.5
    max_mag = 10.0
    t = min(magnitude / max_mag, 1.0)
    r = int(255 * t)
    g = int(255 * (1 - t))
    return (r, g, 0)


def get_masses_array():
    ptr = Gravity.getMasses()
    if not ptr:
        masses = []
    else:
        count = Gravity.getMassesCount()
        masses = [ptr[i] for i in range(count)]
    return masses


# ===== Główna pętla =====
running = True
Gravity.clearMasses()

while running:
    screen.fill((0, 0, 0))

    # Obsługa zdarzeń
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        # Dodawanie masy kliknięciem
        if event.type == pygame.MOUSEBUTTONDOWN:
            mx, my = pygame.mouse.get_pos()
            if event.button == 1:
                Gravity.addMass(mx, my, 100.0)
            elif event.button == 3:
                for mass in get_masses_array():
                    radius = mass.mass**0.5
                    if (
                        mx > mass.x - radius
                        and mx < mass.x + radius
                        and my > mass.y - radius
                        and my < mass.y + radius
                    ):
                        Gravity.removeMass(mass.x, mass.y)

    for mass in get_masses_array():
        x, y, value = mass.x, mass.y, mass.mass
        radius = int(value**0.5)
        pygame.draw.circle(screen, (255, 255, 0), (x, y), radius)

    # Rysowanie siatki wektorów
    for x in range(0, WIDTH, GRID_SPACING):
        for y in range(0, HEIGHT, GRID_SPACING):
            fx = c_double()
            fy = c_double()
            Gravity.vectorDir(x, y, byref(fx), byref(fy))

            # Skaluj wektor, aby nie był zbyt długi
            vx = fx.value * ARROW_SCALE
            vy = fy.value * ARROW_SCALE

            length = math.hypot(vx, vy)
            if length > MAX_ARROW_LENGTH:
                scale = MAX_ARROW_LENGTH / length
                vx *= scale
                vy *= scale
            end_x = int(x + vx)
            end_y = int(y + vy)

            pygame.draw.line(
                screen, color_from_magnitude(vx, vy), (x, y), (end_x, end_y), 1
            )
            pygame.draw.circle(screen, (0, 255, 0), (end_x, end_y), 2)

    pygame.display.flip()
    clock.tick(60)

pygame.quit()
