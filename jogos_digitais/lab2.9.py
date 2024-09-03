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
nave_imagem = pygame.image.load("nave-espacial.png")  # Certifique-se de ter uma imagem chamada "nave.png"
nave_imagem = pygame.transform.scale(nave_imagem, (50, 50))  # Redimensione a imagem se necessário

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
        print(f"{self.nome} moveu-se para a posição ({self.x}, {self.y}).")

    def girar(self, direcao):
        if direcao == 'esquerda':
            self.direcao = (self.direcao + 90) % 360
        elif direcao == 'direita':
            self.direcao = (self.direcao - 90) % 360
        print(f"{self.nome} virou para {direcao}. Agora está apontando para {self.direcao} graus.")

    def atirar(self, alvo):
        if self.energia >= 10:
            self.energia -= 10
            dano = random.randint(1, 10)
            alvo.receber_dano(dano)
            print(f"{self.nome} disparou causando {dano} de dano. Energia restante: {self.energia}")
        else:
            print(f"{self.nome} não tem energia suficiente para atirar.")

    def receber_dano(self, dano):
        self.escudo -= dano
        if self.escudo <= 0:
            self.viva = False
            print(f"{self.nome} foi destruída!")
        else:
            print(f"{self.nome} foi atingida! Escudo restante: {self.escudo}")

    def recarregar(self):
        self.energia = 100
        print(f"{self.nome} recarregou sua energia.")

    def desenhar(self, tela):
        rotacionada = pygame.transform.rotate(self.image, self.direcao)
        nova_rect = rotacionada.get_rect(center=self.image.get_rect(topleft=(self.x, self.y)).center)
        tela.blit(rotacionada, nova_rect.topleft)

def main():
    clock = pygame.time.Clock()
    nave1 = Starship("Vingador Estelar", 100, 300)
    nave2 = Starship("Predador Cósmico", 600, 300)

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
        if keys[pygame.K_a]:
            nave1.girar('esquerda')
        if keys[pygame.K_d]:
            nave1.girar('direita')
        if keys[pygame.K_SPACE]:
            nave1.atirar(nave2)

        # Controles da nave 2
        if keys[pygame.K_UP]:
            nave2.mover()
        if keys[pygame.K_LEFT]:
            nave2.girar('esquerda')
        if keys[pygame.K_RIGHT]:
            nave2.girar('direita')
        if keys[pygame.K_RETURN]:
            nave2.atirar(nave1)

        # Desenhar naves
        nave1.desenhar(screen)
        nave2.desenhar(screen)

        pygame.display.flip()
        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()