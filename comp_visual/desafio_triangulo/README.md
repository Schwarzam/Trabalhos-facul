# Transformações

| Nome             | RA       |
|------------------|----------|
| Gustavo Schwarz  | 10389588 |
| Thales Lopes     | 10389343 |
| Vincenzo Alberice| 10389354 |

*O que deve ser alterado no código original para que o programa exiba um cubo de cores que fica girando em um ou mais eixos sem parar?*

Para fazer a rotação do cubo em torno de um eixo, é necessário realizar a multiplicação da matriz de projeção pela matriz de visualização e pela matriz de modelo, e então passar o resultado para o shader. A rotação do cubo pode ser feita em torno de qualquer eixo, mas para este exemplo, será feita em torno do eixo Y.

A mudança feita está no trecho abaixo: 

```c

    float angle = 0.0f;
    Uint32 currentTime = 0, lastTime = 0;
    float deltaTime = 0;

    while (isRunning)
    {
        lastTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; // Convertendo milissegundos em segundos

        angle += 1.0f * deltaTime;
        glm_mat4_identity(modelMatrix);
        glm_rotate(modelMatrix, angle, (vec3){0.0f, 1.0f, 0.0f}); // Rotação em torno do eixo Y
        glm_mat4_mul(projectionMatrix, viewMatrix, MVPMatrix); 
        glm_mat4_mul(MVPMatrix, modelMatrix, MVPMatrix); 
        glUniformMatrix4fv(u_MVPMatrix, 1, GL_FALSE, (const GLfloat *)MVPMatrix);
```

O código acima faz a rotação do cubo em torno do eixo Y. A variável `angle` é incrementada a cada frame, e a matriz de modelo é rotacionada em torno do eixo Y. A matriz de projeção é multiplicada pela matriz de visualização e pela matriz de modelo, e o resultado é passado para o shader. 


Referências: 

- [LearnOpenGL - Transformations](https://learnopengl.com/Getting-started/Transformations)

- [Stack Overflow](https://stackoverflow.com/questions/59570789/opengl-triangle-rotates-wrong)