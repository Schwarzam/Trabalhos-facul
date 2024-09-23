import pygame
import random
import math
import time

# Inicializa o Pygame
pygame.init()

# Configurações da tela
SCREEN_WIDTH, SCREEN_HEIGHT = 1200, 720
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Batalha Espacial")

# Carregar imagem da nave
nave_imagem = pygame.image.load("imagens/nave-espacial.png")
nave_imagem = pygame.transform.scale(nave_imagem, (50, 50))

# Carregar imagem do background
background_image = pygame.image.load("imagens/background.jpg")
background_image = pygame.transform.scale(background_image, (SCREEN_WIDTH, SCREEN_HEIGHT))

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
        self.ultimo_tiro = 0  # Controla o tempo de recarga

    def mover(self, direcao_x, direcao_y):
        if direcao_x != 0 or direcao_y != 0:  # Somente atualizar a direção se houver movimento
            self.direcao = math.degrees(math.atan2(-direcao_y, direcao_x))  # Calcula o ângulo em graus
        self.x += direcao_x * self.velocidade
        self.y += direcao_y * self.velocidade

    def desenhar(self, tela):
        # Rotaciona a nave com base na direção atual
        rotacionada = pygame.transform.rotate(self.image, self.direcao)
        nova_rect = rotacionada.get_rect(center=self.image.get_rect(topleft=(self.x, self.y)).center)
        tela.blit(rotacionada, nova_rect.topleft)

    def girar(self, direcao):
        if direcao == 'esquerda':
            self.direcao = (self.direcao + 90) % 360
        elif direcao == 'direita':
            self.direcao = (self.direcao - 90) % 360

    def atirar(self):
        agora = time.time()
        if self.energia >= 10 and agora - self.ultimo_tiro >= 1:  # Tempo de recarga de 1 segundo
            self.energia -= 10
            self.ultimo_tiro = agora
            rad = math.radians(self.direcao)

            # Calcular a posição central da nave (adiciona metade da largura e altura)
            tiro_x = self.x + self.image.get_width() // 2
            tiro_y = self.y + self.image.get_height() // 2

            return Tiro(tiro_x, tiro_y, self.direcao)
        return None
    
    def recarregar(self):
        agora = time.time()
        if agora - self.ultimo_tiro >= 1:
            self.ultimo_tiro = agora
            self.energia += 10

    def receber_dano(self, dano):
        self.escudo -= dano
        if self.escudo <= 0:
            self.viva = False

    def desenhar(self, tela):
        rotacionada = pygame.transform.rotate(self.image, self.direcao)
        nova_rect = rotacionada.get_rect(center=self.image.get_rect(topleft=(self.x, self.y)).center)
        tela.blit(rotacionada, nova_rect.topleft)

# Classe do Asteroide
class Asteroide:
    def __init__(self):
        self.raio = random.randint(10, 50)  # Tamanho aleatório
        self.x = random.randint(0, SCREEN_WIDTH)
        self.y = random.randint(0, SCREEN_HEIGHT)
        self.velocidade_x = random.uniform(-3, 3)  # Velocidade aleatória no eixo x
        self.velocidade_y = random.uniform(-3, 3)  # Velocidade aleatória no eixo y

    def mover(self):
        self.x += self.velocidade_x
        self.y += self.velocidade_y

        # Verifica se o asteroide saiu da tela e faz ele reaparecer do lado oposto
        if self.x < 0:
            self.x = SCREEN_WIDTH
        elif self.x > SCREEN_WIDTH:
            self.x = 0
        if self.y < 0:
            self.y = SCREEN_HEIGHT
        elif self.y > SCREEN_HEIGHT:
            self.y = 0

    def desenhar(self, tela):
        pygame.draw.circle(tela, (100, 100, 100), (int(self.x), int(self.y)), self.raio)

    def colidiu(self, nave):
        distancia = math.hypot(self.x - nave.x, self.y - nave.y)
        return distancia < self.raio + 25  # 25 é metade do tamanho da nave

def desenhar_barra(tela, x, y, valor, maximo, cor):
    largura_total = 200  # Largura total da barra
    altura = 20  # Altura da barra
    proporcao = valor / maximo  # Proporção do valor em relação ao máximo
    largura_valor = largura_total * proporcao  # Calcula o tamanho correspondente ao valor

    # Desenha a barra completa em vermelho (barra vazia)
    pygame.draw.rect(tela, (255, 0, 0), (x, y, largura_total, altura))
    
    # Desenha a parte correspondente ao valor atual
    pygame.draw.rect(tela, cor, (x, y, largura_valor, altura))
    
def main():
    clock = pygame.time.Clock()
    nave1 = Starship("Vingador Estelar", 100, 300)
    nave2 = Starship("Predador Cósmico", 600, 300)

    tiros_nave1 = []
    tiros_nave2 = []

    asteroides = [Asteroide() for _ in range(5)]  # Criar 5 asteroides

    rodando = True
    fundo_velocidade = 0.2
    fundo_y = 0
    while rodando:
        #screen.fill((255, 0, 0))  # Limpar tela com preto
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                rodando = False
        
        fundo_y += fundo_velocidade
        if fundo_y >= SCREEN_HEIGHT:
            fundo_y = 0
            
        screen.blit(background_image, (0, fundo_y - SCREEN_HEIGHT))
        screen.blit(background_image, (0, fundo_y))

        keys = pygame.key.get_pressed()

        # Controles da nave 1
        direcao_x_nave1, direcao_y_nave1 = 0, 0  # Inicializar direção da nave 1
        if keys[pygame.K_w]:  # Andar para cima
            direcao_y_nave1 = -1
        if keys[pygame.K_s]:  # Andar para baixo
            direcao_y_nave1 = 1
        if keys[pygame.K_a]:  # Andar para a esquerda
            direcao_x_nave1 = -1
        if keys[pygame.K_d]:  # Andar para a direita
            direcao_x_nave1 = 1

        nave1.mover(direcao_x_nave1, direcao_y_nave1)

        # Controles da nave 2
        direcao_x_nave2, direcao_y_nave2 = 0, 0  # Inicializar direção da nave 2
        if keys[pygame.K_UP]:  # Andar para cima
            direcao_y_nave2 = -1
        if keys[pygame.K_DOWN]:  # Andar para baixo
            direcao_y_nave2 = 1
        if keys[pygame.K_LEFT]:  # Andar para a esquerda
            direcao_x_nave2 = -1
        if keys[pygame.K_RIGHT]:  # Andar para a direita
            direcao_x_nave2 = 1

        nave2.mover(direcao_x_nave2, direcao_y_nave2)


        if keys[pygame.K_SPACE]:
            tiro = nave1.atirar()
            if tiro:
                tiros_nave1.append(tiro)
        
        if keys[pygame.K_r]:
            nave1.recarregar()


        if keys[pygame.K_RETURN]:
            tiro = nave2.atirar()
            if tiro:
                tiros_nave2.append(tiro)
                
        if keys[pygame.K_l]:
            nave2.recarregar()
            
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

        # Mover e desenhar os asteroides
        for asteroide in asteroides:
            asteroide.mover()
            asteroide.desenhar(screen)
            if asteroide.colidiu(nave1):
                nave1.receber_dano(10)
                asteroides.remove(asteroide)
            if asteroide.colidiu(nave2):
                nave2.receber_dano(10)
                asteroides.remove(asteroide)

        # Desenhar naves
        if nave1.viva:
            nave1.desenhar(screen)
        if nave2.viva:
            nave2.desenhar(screen)

        desenhar_barra(screen, 10, 10, nave1.escudo, 100, (0, 255, 0))  # Escudo (verde)
        desenhar_barra(screen, 10, 35, nave1.energia, 100, (0, 255, 255))  # Energia (ciano)

        # Desenhar a barra de escudo e energia da nave 2
        desenhar_barra(screen, SCREEN_WIDTH - 210, 10, nave2.escudo, 100, (0, 0, 255))  # Escudo (azul)
        desenhar_barra(screen, SCREEN_WIDTH - 210, 35, nave2.energia, 100, (255, 255, 0))  # Energia (amarelo)

        if len(asteroides) < 5:
            asteroides.append(Asteroide())
        
        pygame.display.flip()
        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()