# -*- coding: utf-8 -*-
"""
Created on Wed Sep 11 16:36:03 2013

@author: Leo
"""

import pygame

SCREEN_WIDTH = 480
SCREEN_HEIGHT = 800

TYPE_SMALL = 1
TYPE_MIDDLE = 2
TYPE_BIG = 3
items = pygame.sprite.Group() # 여러 객체를 관리하는 컨테이너 클래스

# 총알
class Bullet(pygame.sprite.Sprite):
    def __init__(self, bullet_img, init_pos):
        pygame.sprite.Sprite.__init__(self)
        self.image = bullet_img
        self.rect = self.image.get_rect()
        self.rect.midbottom = init_pos
        self.speed = 10

    def move(self):
        self.rect.top -= self.speed

# 플레이어 클래스
class Player(pygame.sprite.Sprite):
    def __init__(self, plane_img, player_rect, init_pos):
        pygame.sprite.Sprite.__init__(self)
        self.image = []                                 # 플레이어 개체 스프라이트 이미지를 저장하는 데 사용되는 목록

        for i in range(len(player_rect)):
          self.image.append(plane_img.subsurface(player_rect[i]).convert_alpha())
        self.rect = player_rect[0]                      # 그림이 있는 직사각형 초기화
        self.rect.topleft = init_pos                    # 사각형의 왼쪽 위 모서리 좌표를 초기화합니다.
        self.speed = 8                                  # 플레이어 속도를 초기화합니다. 여기에 특정 값이 있습니다.
        self.bullets = pygame.sprite.Group()            # 플레이어의 항공기에서 발사된 총알 모음
        self.img_index = 0                              # 플레이어 스프라이트 이미지 인덱스
        self.is_hit = False                             # 플레이어가 맞았는지 여부

    def shoot(self, bullet_img):
        bullet = Bullet(bullet_img, self.rect.midtop)
        self.bullets.add(bullet)

    def moveUp(self):
        if self.rect.top <= 0:
            self.rect.top = 0
        else:
            self.rect.top -= self.speed

    def moveDown(self):
        if self.rect.top >= SCREEN_HEIGHT - self.rect.height:
            self.rect.top = SCREEN_HEIGHT - self.rect.height
        else:
            self.rect.top += self.speed

    def moveLeft(self):
        if self.rect.left <= 0:
            self.rect.left = 0
        else:
            self.rect.left -= self.speed

    def moveRight(self):
        if self.rect.left >= SCREEN_WIDTH - self.rect.width:
            self.rect.left = SCREEN_WIDTH - self.rect.width
        else:
            self.rect.left += self.speed

# 적 클래스
class Enemy(pygame.sprite.Sprite):
    def __init__(self, enemy_img, enemy_down_imgs, init_pos):
       pygame.sprite.Sprite.__init__(self)
       self.image = enemy_img
       self.rect = self.image.get_rect()
       self.rect.topleft = init_pos
       self.down_imgs = enemy_down_imgs
       self.speed = 2
       self.down_index = 0

    def move(self):
        self.rect.top += self.speed

    def die(self, heart_img):
        heart = Heart(heart_img,self.rect.topleft)
        items.add(heart)


# 아이템 하트
class Heart(pygame.sprite.Sprite):
    def __init__(self, heart_img, init_pos):
        pygame.sprite.Sprite.__init__(self)
        self.image = heart_img
        self.rect = self.image.get_rect()
        self.rect.topleft = init_pos
        self.speed = 1.1

    def move(self):
        self.rect.top += self.speed

# score 파일에서 최고 점수를 가져오는 함수
def loadHighScore():
    try:
        f = open("score.txt", 'r')
        s = int(f.readline())
        f.close()
    except:
        return 0
    return s

# score 파일에 최고 점수를 저장하는 함수
def saveHighScore(s):
    savedScore = loadHighScore()
    if savedScore < s:
        f = open("score.txt", 'w')
        f.write(str(s))
        f.close()
    return
