import pygame

# Inicializando o Pygame
pygame.init()

# Configurações da tela
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Nave Espacial")

# Definindo cores
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

# Classe NaveEspacial que herda de pygame.sprite.Sprite
class NaveEspacial(pygame.sprite.Sprite):
    def __init__(self, name, position, speed=5, shield=100, energy=100):
        super().__init__()
        self.name = name
        self.alive = True
        self.position = pygame.Vector2(position)
        self.speed = speed
        self.shield = shield
        self.energy = energy

        # Definindo a imagem da nave como um retângulo
        self.image = pygame.Surface((40, 30))
        self.image.fill(WHITE)
        self.rect = self.image.get_rect(center=self.position)

    def update(self):
        keys = pygame.key.get_pressed()

        # Movimentação com setas direcionais
        if keys[pygame.K_LEFT]:
            self.position.x -= self.speed  # Move para a esquerda
        if keys[pygame.K_RIGHT]:
            self.position.x += self.speed  # Move para a direita
        if keys[pygame.K_UP]:
            self.position.y -= self.speed  # Move para cima
        if keys[pygame.K_DOWN]:
            self.position.y += self.speed  # Move para baixo

        # Atualiza a posição do retângulo com base na nova posição
        self.rect.center = self.position

# Função principal do jogo
def main():
    clock = pygame.time.Clock()
    all_sprites = pygame.sprite.Group()

    # Criando a nave espacial
    nave = NaveEspacial(name="Explorador", position=(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2))
    all_sprites.add(nave)

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Atualizando os sprites
        all_sprites.update()

        # Desenhando na tela
        screen.fill(BLACK)
        all_sprites.draw(screen)

        # Atualizando o display
        pygame.display.flip()

        # Controla a taxa de quadros
        clock.tick(60)

    pygame.quit()

# Executando o jogo
if __name__ == "__main__":
    main()