import requests
import pygame
url = 'http://localhost:8000/'
payload = {'key1': 'value1', 'key2': 'value2'}

pygame.init()
pygame.display.set_mode((100, 100))

while True:
    
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN and event.key == pygame.K_d:
            is_moving = True
            print 'down'
        elif event.type == pygame.KEYUP and event.key == pygame.K_d:
            is_moving = False
            print 'up'