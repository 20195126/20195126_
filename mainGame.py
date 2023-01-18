# -*- 코딩: utf-8 -*-
"""
생성일 수요일 9월 11일 11:05:00 2013
@저자: 레오
"""

import time
import pygame
from sys import exit
from pygame.image import save
from gameRole import *
from pygame.locals import *
import random

# 게임 초기화
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT)) #화면 크기 지정
pygame.display.set_caption('Shooting Game')  # 화면 창에 제목 넣기

# 게임 음악 불러오기
bullet_sound = pygame.mixer.Sound('resources/sound/bullet.wav')
enemy1_down_sound = pygame.mixer.Sound('resources/sound/enemy1_down.wav')
game_over_sound = pygame.mixer.Sound('resources/sound/game_over.wav')
bullet_sound.set_volume(0.3)
enemy1_down_sound.set_volume(0.3)
game_over_sound.set_volume(0.3)
pygame.mixer.music.load('resources/sound/game_music.wav')
pygame.mixer.music.play(-1, 0.0)
pygame.mixer.music.set_volume(0.25)

# 배경 이미지 불러오기
background = pygame.image.load('resources/image/background.png').convert()
game_over = pygame.image.load('resources/image/gameover.png')

filename = 'resources/image/shoot.png'
plane_img = pygame.image.load(filename)

# 플레이어 관련 매개변수 설정
player_rect = []
player_rect.append(pygame.Rect(0, 99, 102, 126))        # 플레이어 스프라이트 이미지 영역
player_rect.append(pygame.Rect(165, 360, 102, 126))
player_rect.append(pygame.Rect(165, 234, 102, 126))     # 플레이어 폭발 스프라이트 이미지 영역
player_rect.append(pygame.Rect(330, 624, 102, 126))
player_rect.append(pygame.Rect(330, 498, 102, 126))
player_rect.append(pygame.Rect(432, 624, 102, 126))
player_pos = [200, 600]
#player = Player(plane_img, player_rect, player_pos)

# 글머리 기호 개체가 사용하는 표면 관련 매개변수를 정의합니다.
bullet_rect = pygame.Rect(1004, 987, 9, 21)
bullet_img = plane_img.subsurface(bullet_rect)

# 적 항공기 개체가 사용하는 표면 관련 매개변수를 정의합니다.
enemy1_rect = pygame.Rect(534, 612, 57, 43)
enemy1_img = plane_img.subsurface(enemy1_rect)
enemy1_down_imgs = []
enemy1_down_imgs.append(plane_img.subsurface(pygame.Rect(267, 347, 57, 43)))
enemy1_down_imgs.append(plane_img.subsurface(pygame.Rect(873, 697, 57, 43)))
enemy1_down_imgs.append(plane_img.subsurface(pygame.Rect(267, 296, 57, 43)))
enemy1_down_imgs.append(plane_img.subsurface(pygame.Rect(930, 697, 57, 43)))

#enemies1 = pygame.sprite.Group()

# 파괴 스프라이트 애니메이션을 렌더링하는 데 사용되는 파괴된 항공기를 저장합니다.
enemies_down = pygame.sprite.Group()

#하트 아이템 및 UI
heart_img = pygame.image.load('resources/image/heart.png')
heart_UI = pygame.image.load('resources/image/heart.png')

# 게임 RUN 함수 -> 게임 종료되면 main_menu() 함수로 되돌아감

def game_run():
    # 게임 루프에 들어가기 전에 모든 파라미터 초기화, player와 enemies를 다시 만들어준다.
    plane_img = pygame.image.load(filename)
    player_rect = []
    player_rect.append(pygame.Rect(0, 99, 102, 126))        # 플레이어 스프라이트 이미지 영역
    player_rect.append(pygame.Rect(165, 360, 102, 126))
    player_rect.append(pygame.Rect(165, 234, 102, 126))     # 플레이어 폭발 스프라이트 이미지 영역
    player_rect.append(pygame.Rect(330, 624, 102, 126))
    player_rect.append(pygame.Rect(330, 498, 102, 126))
    player_rect.append(pygame.Rect(432, 624, 102, 126))
    player = Player(plane_img, player_rect, player_pos) # player 위치 초기화
    enemies1 = pygame.sprite.Group()
    life = 3
    running = True
    score = 0
    
    shoot_frequency = 0
    enemy_frequency = 0
    player_down_index = 16

    playtime = 0
    timeChecker = time.time()

    clock = pygame.time.Clock()
    isStop = False
    
    # 게임 메인 루프
    while running:
        # 게임의 최대 프레임 속도를 60으로 제어
        clock.tick(45)

          # 플레이 시간 추가
        playtime += time.time() - timeChecker
        timeChecker = time.time()

        # isStop이 true인 동안 wait상태
        while isStop:
            clock.tick(45) # FPS 설정
            score_font = pygame.font.Font(None, 36)   # pygame,텍스트 출력, 글꼴 지정
            score_text = score_font.render("Pause", True, (128, 128, 128)) # 텍스트,안티앨리어싱여부,색지정RGB
            text_rect = score_text.get_rect() 
            text_rect.centerx = round(SCREEN_WIDTH / 2)
            text_rect.centery = round(SCREEN_HEIGHT / 2)
            screen.blit(score_text, text_rect)
            pygame.display.update()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    exit()
                # 스페이스바를 누르면 게임 재개
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_SPACE:
                        isStop = False
            timeChecker = time.time()

        # 총알 발사 빈도 조절, 총알 발사
        if not player.is_hit:
            if shoot_frequency % 15 == 0:
                bullet_sound.play()
                player.shoot(bullet_img)
            shoot_frequency += 1
            if shoot_frequency >= 15:
                shoot_frequency = 0

        #     # 적 비행기 생성

        if enemy_frequency % 50 == 0:
            enemy1_pos = [random.randint(0, SCREEN_WIDTH - enemy1_rect.width), 0]
            enemy1 = Enemy(enemy1_img, enemy1_down_imgs, enemy1_pos)
            enemies1.add(enemy1)
        enemy_frequency += 1
        if enemy_frequency >= 100:
            enemy_frequency = 0

        # 글머리 기호 이동, 창 범위 초과 시 삭제
        for bullet in player.bullets:
            bullet.move()
            if bullet.rect.bottom < 0:
                player.bullets.remove(bullet)

        # 적기 이동, 창 범위를 초과하면 삭제
        for enemy in enemies1:
            enemy.move()
            # 플레이어가 맞았는지 확인
            if pygame.sprite.collide_circle(enemy, player):
                enemies_down.add(enemy)
                enemies1.remove(enemy)
                life -= 1
                if life <= 0:
                    player.is_hit = True
                    break
                game_over_sound.play()
                break
            if enemy.rect.top > SCREEN_HEIGHT:
                enemies1.remove(enemy)

        # 파괴 애니메이션을 렌더링하기 위해 파괴 적 비행기 그룹에 충돌 적 비행기 개체를 추가
        enemies1_down = pygame.sprite.groupcollide(enemies1, player.bullets, 1, 1)
        for enemy_down in enemies1_down:
            enemies_down.add(enemy_down)

        # 배경을 그립니다
        screen.fill(0)
        screen.blit(background, (0, 0))

        # 플레이어 평면 그리기
        if not player.is_hit:
            screen.blit(player.image[player.img_index], player.rect)
            # 비행기가 애니메이션 효과를 갖도록 이미지 인덱스를 변경하십시오.
            player.img_index = shoot_frequency // 8
            game_over_sound.play() # 
        else:
            player.img_index = player_down_index // 8
            screen.blit(player.image[player.img_index], player.rect)
            player_down_index += 1
            if player_down_index > 47:
                running = False

        for item in items:
            item.move()
            if life < 3:
               life += 1
               items.remove(item)
            if item.rect.top > SCREEN_HEIGHT:
                items.remove(item)



        # 충돌 애니메이션 그리기
        for enemy_down in enemies_down:
            if enemy_down.down_index == 0:
                enemy1_down_sound.play()
            if enemy_down.down_index > 7:

                percent = random.randint(1,100)
                if percent < 4:
                    enemy_down.die(heart_img)

                enemies_down.remove(enemy_down)
                score += 1000
                continue
            screen.blit(enemy_down.down_imgs[enemy_down.down_index // 2], enemy_down.rect)
            enemy_down.down_index += 1

        # 총알과 적 비행기 그리기
        player.bullets.draw(screen)
        enemies1.draw(screen)
        items.draw(screen)

        score_font = pygame.font.Font(None, 36)
        score_text = score_font.render(str(score), True, (128, 128, 128))
        text_rect = score_text.get_rect()
        text_rect.topleft = [10, 10]
        screen.blit(score_text, text_rect)


        screen.blit(heart_UI,(5,SCREEN_HEIGHT-70))

        life_font = pygame.font.Font(None, 50)
        life_text = life_font.render(str(life), True, (255, 0, 0))
        text_rect = life_text.get_rect()
        text_rect.topleft = [70, SCREEN_HEIGHT-60]
        screen.blit(life_text, text_rect)


        #     # 업데이트 화면
        pygame.display.update()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            # 스페이스 바를 누르면 게임 일시정지
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    isStop = True

        # 키보드 이벤트 수신
        key_pressed = pygame.key.get_pressed()
        # 플레이어가 맞으면 작동하지 않습니다.
        if not player.is_hit:
            if key_pressed[K_w] or key_pressed[K_UP]:
                player.moveUp()
            if key_pressed[K_s] or key_pressed[K_DOWN]:
                player.moveDown()
            if key_pressed[K_a] or key_pressed[K_LEFT]:
                player.moveLeft()
            if key_pressed[K_d] or key_pressed[K_RIGHT]:
                player.moveRight()

    return score # score를 반환해 준다.

# 게임 메뉴 (재시작 선택 가능) 함수 -> game_run()을 호출
def main_menu():
    score = game_run() # 처음 게임이 시작되었으면, 메뉴를 보이기전에 게임부터 RUN시킴
    saveHighScore(score)
    
    title_font = pygame.font.SysFont("comicsans", 40)
    score_font = pygame.font.Font(None, 48) # score font
    menu_run = True
    
    while menu_run:
        screen.blit(game_over, (0,0))
        title_label = title_font.render("Press 'r' to restart", 1, (255,255,255))
        screen.blit(title_label, (SCREEN_WIDTH/2 - title_label.get_width()/2, 400))
        
        text = score_font.render('Your Score: '+ str(score), True, (128, 128, 128))
        text_rect = text.get_rect()
        text_rect.centerx = screen.get_rect().centerx
        text_rect.centery = screen.get_rect().centery + 82
        screen.blit(text, text_rect)

        text = score_font.render('High Score: '+ str(loadHighScore()), True, (255, 255, 255))
        text_rect = text.get_rect()
        text_rect.centerx = screen.get_rect().centerx
        text_rect.centery = screen.get_rect().centery + 120
        screen.blit(text, text_rect)
        
        pygame.display.update()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                menu_run = False
                
            if event.type == pygame.KEYDOWN: # R을 누르면 처음부터 다시 게임 RUN
                if event.key == pygame.K_r:
                    score = game_run()
                    saveHighScore(score)
                
    pygame.quit()

# main_menu()를 호출하여 게임 시작
main_menu()
