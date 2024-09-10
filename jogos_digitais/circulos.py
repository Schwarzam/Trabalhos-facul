import pygame
import random
import math

# Inicializa o Pygame
pygame.init()

# Configurações da tela
width, height = 800, 600
window = pygame.display.set_mode((width, height))
pygame.display.set_caption("Oval que rebate com DVD")

# Definindo a cor inicial e velocidade
colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0), (255, 0, 255)]

# Configuração da fonte
font = pygame.font.SysFont(None, 50)  # Fonte e tamanho para o texto "DVD"

# Classe do Oval
class Oval:
    def __init__(self):
        self.width = 140  # Largura do oval
        self.height = 100  # Altura do oval
        self.color = random.choice(colors)
        self.x = random.randint(self.width // 2, width - self.width // 2)
        self.y = random.randint(self.height // 2, height - self.height // 2)
        self.angle = random.uniform(0, 2 * math.pi)  # Ângulo de movimento inicial
        self.speed = 2  # Velocidade de movimento
        self.hit_bordas = False  # Para detectar o ponto exato de colisão

    def move(self):
        # Movendo o oval baseado no ângulo de movimento
        self.x += self.speed * math.cos(self.angle)
        self.y += self.speed * math.sin(self.angle)

        # Colisão nas laterais (esquerda e direita)
        if self.x - self.width // 2 <= 0 or self.x + self.width // 2 >= width:
            if not self.hit_bordas:  # Muda de cor apenas se tiver batido
                self.angle = math.pi - self.angle  # Inverte o ângulo horizontalmente
                self.color = random.choice(colors)  # Muda a cor
            self.hit_bordas = True
        elif self.y - self.height // 2 <= 0 or self.y + self.height // 2 >= height:
            if not self.hit_bordas:  # Colisão no topo e base
                self.angle = -self.angle  # Inverte o ângulo verticalmente
                self.color = random.choice(colors)  # Muda a cor
            self.hit_bordas = True
        else:
            self.hit_bordas = False  # Redefine para permitir mudança de cor na próxima colisão

    def draw(self, surface):
        # Desenha o oval
        pygame.draw.ellipse(surface, self.color, (self.x - self.width // 2, self.y - self.height // 2, self.width, self.height))
        
        # Desenha o texto "DVD" no centro do oval
        text_surface = font.render('DVD', True, (0, 0, 0))  # Texto preto
        text_rect = text_surface.get_rect(center=(self.x, self.y))  # Centraliza o texto no oval
        surface.blit(text_surface, text_rect)

# Inicializando o oval
oval = Oval()

fps = 60
clock = pygame.time.Clock()

# Loop principal
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Movendo e redesenhando o oval
    oval.move()
    window.fill((255, 255, 255))  # Cor de fundo branca
    oval.draw(window)

    pygame.display.flip()
    clock.tick(fps)

# Finalizando o Pygame
pygame.quit()