# Gustavo Schwarz 10389588

import random

class Starship:
    def __init__(self, nome):
        self.nome = nome
        self.posicao = [0, 0]  # Posição inicial
        self.direcao = 0  # Direção inicial
        self.velocidade = 1  # Velocidade inicial
        self.escudo = 100  # Escudo inicial
        self.energia = 10  # Energia inicial
        self.viva = True

    def move(self):
        # Mover a nave com base na direção atual
        if self.direcao == 0:  # Para frente
            self.posicao[1] += self.velocidade
        elif self.direcao == 90:  # Para direita
            self.posicao[0] += self.velocidade
        elif self.direcao == 180:  # Para trás
            self.posicao[1] -= self.velocidade
        elif self.direcao == 270:  # Para esquerda
            self.posicao[0] -= self.velocidade
        print(f"{self.nome} moveu-se para a posição {self.posicao}.")

    def turn(self, direcao):
        if direcao.lower() == 'esquerda':
            self.direcao = (self.direcao - 90) % 360
        elif direcao.lower() == 'direita':
            self.direcao = (self.direcao + 90) % 360
        print(f"{self.nome} virou para {direcao}. Agora está apontando para {self.direcao} graus.")

    def shoot(self, alvo):
        if self.energia >= 10:
            self.energia -= 10
            dano = random.randint(1, 50)
            alvo.receber_dano(dano)
            print(f"{self.nome} disparou causando {dano} de dano. Energia restante: {self.energia}")
        else:
            print(f"{self.nome} não tem energia suficiente para atirar.")

    def get_hit(self, dano):
        self.escudo -= dano
        if self.escudo <= 0:
            self.viva = False
            print(f"{self.nome} foi destruída!")
        else:
            print(f"{self.nome} foi atingida! Escudo restante: {self.escudo}")

    def recharge(self):
        self.energia += 10
        print(f"{self.nome} recarregou sua energia.")

def realizar_acao_jogador(jogador, oponente):
    while True:
        acao = input(f"\n[{jogador.nome}] Escolha uma ação (mover, girar, atirar, recarregar): ").lower()
        
        if acao == 'mover':
            jogador.mover()
            break
        elif acao == 'girar':
            direcao = input("Escolha a direção (esquerda ou direita): ").lower()
            jogador.girar(direcao)
            break
        elif acao == 'atirar':
            jogador.atirar(oponente)
            break
        elif acao == 'recarregar':
            jogador.recarregar()
            break
        else:
            print("Ação inválida, tente novamente.")

def batalha(jogador1, jogador2):
    rodada = 1
    while jogador1.viva and jogador2.viva:
        print(f"\n--- Rodada {rodada} ---")
        
        if jogador1.viva:
            realizar_acao_jogador(jogador1, jogador2)
        
        if jogador2.viva:
            realizar_acao_jogador(jogador2, jogador1)
        
        rodada += 1
    
    vencedor = jogador1.nome if jogador1.viva else jogador2.nome
    print(f"\n{vencedor} venceu a batalha!")

# Exemplo de uso
nave1 = Starship("Vingador Estelar")
nave2 = Starship("Predador Cósmico")
batalha(nave1, nave2)