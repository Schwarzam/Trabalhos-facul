# Gustavo Schwarz 10389588

import pygame
import random
import math

# Inicializa o Pygame
pygame.init()

# Configurações da tela
SCREEN_WIDTH, SCREEN_HEIGHT = 800, 600
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Batalha Espacial")

# Carregar imagem da nave
nave_imagem = pygame.image.load("imagens/nave-espacial.png")
nave_imagem = pygame.transform.scale(nave_imagem, (50, 50))

# Classe do Tiro
class Tiro:
    def __init__(self, x, y, direcao):
        self.x = x
        self.y = y
        self.direcao = direcao
        self.velocidade = 10
        self.raio = 5

    def mover(self):
        rad = math.radians(self.direcao)
        self.x += self.velocidade * math.cos(rad)
        self.y -= self.velocidade * math.sin(rad)

    def desenhar(self, tela):
        pygame.draw.circle(tela, (255, 255, 255), (int(self.x), int(self.y)), self.raio)

    def colidiu(self, nave):
        distancia = math.hypot(self.x - nave.x, self.y - nave.y)
        return distancia < self.raio + 25  # 25 é metade do tamanho da nave (50/2)

# Classe da Nave Espacial
class Starship:
    def __init__(self, nome, x, y):
        self.nome = nome
        self.image = nave_imagem
        self.x = x
        self.y = y
        self.velocidade = 5
        self.direcao = 0  # Direção em graus
        self.escudo = 100
        self.energia = 100
        self.viva = True

    def mover(self):
        rad = math.radians(self.direcao)
        self.x += self.velocidade * math.cos(rad)
        self.y -= self.velocidade * math.sin(rad)

    def girar(self, direcao):
        if direcao == 'esquerda':
            self.direcao = (self.direcao + 90) % 360
        elif direcao == 'direita':
            self.direcao = (self.direcao - 90) % 360

    def atirar(self):
        if self.energia >= 10:
            self.energia -= 10
            rad = math.radians(self.direcao)
            tiro_x = self.x + 25 * math.cos(rad)
            tiro_y = self.y - 25 * math.sin(rad)
            return Tiro(tiro_x, tiro_y, self.direcao)
        return None

    def receber_dano(self, dano):
        self.escudo -= dano
        if self.escudo <= 0:
            self.viva = False

    def desenhar(self, tela):
        rotacionada = pygame.transform.rotate(self.image, self.direcao)
        nova_rect = rotacionada.get_rect(center=self.image.get_rect(topleft=(self.x, self.y)).center)
        tela.blit(rotacionada, nova_rect.topleft)

def main():
    clock = pygame.time.Clock()
    nave1 = Starship("Vingador Estelar", 100, 300)
    nave2 = Starship("Predador Cósmico", 600, 300)

    tiros_nave1 = []
    tiros_nave2 = []

    # Variáveis para controlar a rotação
    key_left_pressed = False
    key_right_pressed = False
    key_a_pressed = False
    key_d_pressed = False

    rodando = True
    while rodando:
        screen.fill((0, 0, 0))  # Limpar tela com preto
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                rodando = False

        keys = pygame.key.get_pressed()

        # Controles da nave 1
        if keys[pygame.K_w]:
            nave1.mover()

        if keys[pygame.K_a] and not key_a_pressed:
            nave1.girar('esquerda')
            key_a_pressed = True
        if not keys[pygame.K_a]:
            key_a_pressed = False

        if keys[pygame.K_d] and not key_d_pressed:
            nave1.girar('direita')
            key_d_pressed = True
        if not keys[pygame.K_d]:
            key_d_pressed = False

        if keys[pygame.K_SPACE]:
            tiro = nave1.atirar()
            if tiro:
                tiros_nave1.append(tiro)

        # Controles da nave 2
        if keys[pygame.K_UP]:
            nave2.mover()

        if keys[pygame.K_LEFT] and not key_left_pressed:
            nave2.girar('esquerda')
            key_left_pressed = True
        if not keys[pygame.K_LEFT]:
            key_left_pressed = False

        if keys[pygame.K_RIGHT] and not key_right_pressed:
            nave2.girar('direita')
            key_right_pressed = True
        if not keys[pygame.K_RIGHT]:
            key_right_pressed = False

        if keys[pygame.K_RETURN]:
            tiro = nave2.atirar()
            if tiro:
                tiros_nave2.append(tiro)

        # Mover e desenhar os tiros
        for tiro in tiros_nave1:
            tiro.mover()
            tiro.desenhar(screen)
            if tiro.colidiu(nave2):
                nave2.receber_dano(10)
                tiros_nave1.remove(tiro)

        for tiro in tiros_nave2:
            tiro.mover()
            tiro.desenhar(screen)
            if tiro.colidiu(nave1):
                nave1.receber_dano(10)
                tiros_nave2.remove(tiro)

        # Desenhar naves
        if nave1.viva:
            nave1.desenhar(screen)
        if nave2.viva:
            nave2.desenhar(screen)

        pygame.display.flip()
        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()